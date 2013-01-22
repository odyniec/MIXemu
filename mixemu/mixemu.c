/*
 * mixemu - MIX emulator command line interface
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "mix_dev.h"
#include "mix_dbg.h"
#include "mp.h"


#define PROMPT "> "

/* Command line length */
#define CMDLINE_LEN 80
/* Command name length */
#define CMD_LEN 12

/* Command line */
char cmdline[CMDLINE_LEN];

/* Current command line position */
static int pos = 0;

/* Is the program running? */
int _running = 0;

/* Has a breakpoint been triggered? */
int _break = 0;


/* Breakpoints list */
struct _bp {
    mix_addr_t addr;
    int num;
    struct _bp *next;
} *breakpoints = NULL;


/* Source code line numbers */
int src_lines[MIX_MEMSIZE];

/* Program source code */
char **source;

/* Device file pointers */
FILE *dev_fp[21];

/* "General purpose" string */
static char s[CMDLINE_LEN];

void getstr(char *s)
{
    char *p = s;

    while (cmdline[pos] == ' ' || cmdline[pos] == '\t')
        pos++;
    while (cmdline[pos] != ' ' && cmdline[pos] != '\t' && cmdline[pos] != '\n')
        *p++ = cmdline[pos++];

    *p = '\0';
}

void getstrn(char *s)
{
    char *p = s;
  
    while (cmdline[pos] == ' ' || cmdline[pos] == '\t')
        pos++;
    while (cmdline[pos] != '\n')
        *p++ = cmdline[pos++];

    *p = '\0';
}

/* Event handlers */

int event_invalid_addr(mix_addr_t addr)
{
    _running = 0;

    printf("Invalid address (%d)\n", addr);
}

int event_mem_changed(mix_addr_t addr, int n)
{
    /* No source code for modified memory */
    while (n-- > 0)
        src_lines[addr+n] = 0;
}

int event_pc_changed(mix_addr_t addr)
{
    if (_break)
        _break = 0;
    else
        if (_running) {
            struct _bp *p = breakpoints;

            while (p != NULL)
                if (p->addr == addr) {
                    printf("Breakpoint #%d at %04d.\n", p->num, addr);
                    _break = 1;
                    return;
                }
                else
                    p = p->next;
        }
}

int event_prog_finish()
{
    _running = 0;

    printf("Program finished normally at %04d.\n", get_pc());
}

/* Commands */

void cmd_break()
{
    mix_addr_t addr;
    struct _bp *p = breakpoints, *n;
    int b = 1;

    getstr(s);
    if (*s == '#') {
        /* Print breakpoint info */
        if (sscanf(s+1, "%d", &b) != 1) {
            printf("Syntax error\n");
            return;
        }

        while (p != NULL) {
            if (p->num == b) {
                printf("Breakpoint #%d set at %04d.\n", b, p->addr);
                return;
            }
            p = p->next;
        }

        printf("Breakpoint #%d not set.\n", b);
        return;
    }

    if (sscanf(s, "%d", &addr) != 1) {
        mix_addr_t a;

        addr = ((a = get_pc()) < MIX_MEMSIZE-1 ? a+1 : a);
    }
    else
        if (!VALID_ADDR(addr)) {
            printf("Invalid address\n");
            return;
        }

    /* Add new breakpoint to the list */

    if (p != NULL) {
        for (;;) {
            if (p->addr == addr) {
                printf("Breakpoint #%d already set at %04d!\n", p->num, addr);
                return;
            }
            if (p->num == b)
                b++;
            if (p->next != NULL)
                p = p->next;
            else
                break;
        }
    } 

    n = (struct _bp *)malloc(sizeof(struct _bp));

    n->addr = addr;
    n->next = NULL;
    n->num = b;

    if (p != NULL)
        p->next = n;
    else
        breakpoints = n;

    printf("Breakpoint #%d at %04d.\n", b, addr);
}


void cmd_clear()
{
    struct _bp *p = breakpoints, *q = NULL;
    int b;

    getstr(s);
    if (sscanf((*s == '#' ? s+1 : s), "%d", &b) != 1) {
        while (p != NULL) {
            q = p;
            p = p->next;
            free(q);
        }

        breakpoints = NULL;

        printf("Cleared all breakpoints.\n");
    }
    else {
        while (p != NULL) {
            if (p->num == b) {
                if (q != NULL)
                    q->next = p->next;
                else
                    breakpoints = p->next;
                free(p);
                printf("Cleared breakpoint #%d.\n", b);
                return;
            }

            q = p;
            p = p->next;
        }
    
        printf("Breakpoint #%d not set.\n", b);
    }
}


void cmd_go()
{
    int a;

    getstr(s);
    if (sscanf(s, "%d", &a) != 1) {
        printf("Syntax error\n");
        return;
    }

    if (!VALID_ADDR(a)) {
        printf("Invalid address\n");
        return;
    }

    set_pc(a);
}


void cmd_load()
{
    mix_addr_t startaddr;
    FILE *fp;
    char *p;
    char line[80];
    char num = 0;
    int size = 50, i;

    /* Clear line numbers */
    for (i = 0; i < MIX_MEMSIZE; i++)
        src_lines[i] = 0;

    getstr(s);

    if (mp_load_dbg(s, &startaddr, src_lines) != 0) {
        printf("Load error\n");
        return;
    }

    /* This is really ugly */
    p = strrchr(s, '.');
    *(p+2) = 'a';
    *(p+3) = 's';
    *(p+4) = '\0';

    if ((fp = fopen(s, "r")) != NULL) {
        source = (char **)malloc(50 * sizeof(char *));

        while (fgets(line, 80, fp) != NULL) {
            source[num++] = strdup(line);

            if (num >= size) {
                size += 50;
                source = (char **)realloc(source, size * sizeof(char *));
            }
        }

        fclose(fp);
    }

    set_pc(startaddr);

    printf("Start address: %04d\n", startaddr);
}


void cmd_mem()
{
    int beg, end;

    getstr(s);
    if (sscanf(s, "%d", &beg) != 1) {
        printf("Syntax error\n");
        return;
    }

    getstr(s);
    if (sscanf(s, "%d", &end) != 1)
        end = beg;

    if ((beg < 0) || (end >= MIX_MEMSIZE) || (beg > end)) {
        printf("Invalid range\n");
        return;
    }

    for (; beg <= end; beg++)
        printf("%04d  %s\n", beg, sprintf_mix_word(Mem[beg]));
}


void cmd_quit()
{
    printf("Goodbye!\n");
}


void cmd_regs()
{
    printf("A = (%s)   X = (%s)\n", sprintf_mix_word(rA),
        sprintf_mix_word(rX));
    printf("I1 = (%s)   I2 = (%s)   I3 = (%s)\n", sprintf_mix_short(rI1), 
        sprintf_mix_short(rI2), sprintf_mix_short(rI3));
    printf("I4 = (%s)   I5 = (%s)   I6 = (%s)\n", sprintf_mix_short(rI4), 
        sprintf_mix_short(rI5), sprintf_mix_short(rI6));
    printf("J = (%s)\n", sprintf_mix_short(rJ));
    printf("Cmp = %s   Overflow = %s\n",
        (Cmp == LESS ? "LESS" : (Cmp == EQUAL ? "EQUAL" : "GREATER")),
        (Ofl == OF ? "YES" : "NO"));
}


void cmd_run()
{
    _running = 1;

    set_pc(get_pc());

    while (_running && !_break)
        mix_exec();
}


void cmd_set()
{
    getstr(s);
    if (!strcmp(s, "mem")) {
        int a, c;
        mix_word_t w;
    
        getstr(s);
        if (sscanf(s, "%d", &a) != 1) {
            printf("Syntax error\n");
            return;
        }
    
        if (!VALID_ADDR(a)) {
            printf("Invalid address\n");
            return;
        }

        getstrn(s);
        if (!sscanf_mix_word(s, &w)) {
            printf("Syntax error\n");
            return;
        }

        w.s = (*s == '-' ? NEG : POS);
    
        set_Mem(a, w);
    }
    else if (!strcmp(s, "dev")) {
        int n;
        FILE *fp;
    
        getstr(s);
        if (sscanf(s, "%d", &n) != 1) {
            printf("Syntax error\n");
            return;
        }

        getstr(s);
        if (strlen(s) == 0) {
            printf("Syntax error\n");
            return;
        }

        if (n <= 16) {
            /* Tape or disk device */
            if ((fp = fopen(s, "r+")) == NULL)
                if ((fp = fopen(s, "w+")) == NULL) {
                    printf("Cannot open ``%s''.\n", s);
                    return;
                }
        }
        else if (n == 16) {
            /* Card reader */
            if ((fp = fopen(s, "r")) == NULL) {
                printf("Cannot open ``%s''.\n", s);
                return;
            }
        }
        else if (n == 17) {
            /* Card writer */
            if ((fp = fopen(s, "w")) == NULL) {
                printf("Cannot open ``%s''.\n", s);
                return;
            }
        }
        else if (n == 18) {
            /* Line printer */
            if ((fp = fopen(s, "w")) == NULL) {
                printf("Cannot open ``%s''.\n", s);
                return;
            }
        }
        else if (n == 19) {
            /* Terminal */
            if ((fp = fopen(s, "r")) == NULL) {
                printf("Cannot open ``%s''.\n", s);
                return;
            }
        }
        else if (n == 20) {
            /* Paper tape */
            if ((fp = fopen(s, "w")) == NULL) {
                printf("Cannot open ``%s''.\n", s);
                return;
            }
        }

        mix_dev_set_fp(n, fp);

        if (dev_fp[n] != NULL)
            fclose(dev_fp[n]);
        dev_fp[n] = fp;
    }
    else if (*s == 'r') {
        switch (*(s+1)) {
        case 'A': case 'X': {
            mix_word_t w;

            getstrn(s+2);

            if (sscanf_mix_word(s+2, &w) != 1) {
                printf("Syntax error\n");
                return;
            }
    
            switch (*(s+1)) {
            case 'A':
                set_rA(w);
                break;
            case 'X':
                set_rX(w);
                break;
            }
            break;
        }
        case 'I': case 'J': {
            mix_short_t h;

            getstrn(s+3);   /* A little trick */

            if (sscanf_mix_short(s+3, &h) != 1) {
                printf("Syntax error\n");
                return;
            }

            switch (*(s+1)) {
            case 'I':
                switch (*(s+2)) {
                case '1':
                    set_rI1(h);
                    break;
                case '2':
                    set_rI2(h);
                    break;
                case '3':
                    set_rI3(h);
                    break;
                case '4':
                    set_rI4(h);
                    break;
                case '5':
                    set_rI5(h);
                    break;
                case '6':
                    set_rI6(h);
                    break;
                default:
                    printf("Syntax error\n");
                    return;
                }
                break;
            case 'J':
                set_rJ(h);
                break;
            default:
                printf("Syntax error\n");
                return;
            }
            break;
        }
        default:
            printf("Syntax error\n");
            return;
        }
    }
    else {
        printf("Syntax error\n");
        return;
    }
}


void cmd_step()
{
    static int steps;

    getstr(s);

    if (sscanf(s, "%d", &steps) != 1)
        steps = 1;

    if (steps > 0) {
        _running = 1;

        set_pc(get_pc());

        while (steps-- > 0 && _running && !_break)
            mix_exec();

        if (_running)
            /* Show next instruction to be executed */
            printf("%04d   %s     %s", get_pc(),
                sprintf_mix_word2(Mem[get_pc()]),
                (src_lines[get_pc()] != 0 ? source[src_lines[get_pc()]] :
                    "\n"));
    }
}


void init()
{
    mix_init();

    /* Set up event handlers */
    ev_invalid_addr = &event_invalid_addr;
    ev_mem_changed = &event_mem_changed;
    ev_pc_changed = &event_pc_changed;
    ev_prog_finish = &event_prog_finish;

    mix_start();
}


main(int argc, char *argv[])
{
    char cmd[CMD_LEN];
    int i;

    init();

    while (1) {
        printf(PROMPT);

        fgets(cmdline, CMDLINE_LEN, stdin);
        pos = 0;
        getstr(cmd);
    
        if (!strcmp(cmd, "break"))
            cmd_break();
        else if (!strcmp(cmd, "clear"))
            cmd_clear();
        else if (!strcmp(cmd, "go"))
            cmd_go();
        else if (!strcmp(cmd, "load"))
            cmd_load();
        else if (!strcmp(cmd, "mem") || !strcmp(cmd, "memory"))
            cmd_mem();
        else if (!strcmp(cmd, "quit") || !strcmp(cmd, "q")) {
            cmd_quit();
            break;
        }
        else if (!strcmp(cmd, "regs"))
            cmd_regs();
        else if (!strcmp(cmd, "run") || !strcmp(cmd, "r"))
            cmd_run();
        else if (!strcmp(cmd, "set"))
            cmd_set();
        else if (!strcmp(cmd, "step") || !strcmp(cmd, "s"))
            cmd_step();
        else
            printf("Unknown command ``%s''.\n", cmd);
    }

    /* Close device files */
    for (i = 0; i < 21; i++)
        if (dev_fp[i] != NULL)
            fclose(dev_fp[i]);

    return 0;
}

