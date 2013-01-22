#include "mix.h"
#include "mp.h"

/* Eat leading and trailing whitespace in a string */
char* _trim(char *s)
{
    int n;

    for (n = 0; s[n] == ' ' || s[n] == '\t'; n++)
        ;
    s += n;

    for (n = strlen(s)-1; n >= 0 && isspace(s[n]); n--)
        ;
    s[n+1] = '\0';

    return s;
}

int _load(char *filename, mix_addr_t *startaddr, int lines[])
{
    FILE *fp;
    mix_addr_t addr = 0;
    char *line, *s;

    *startaddr = 0;

    if ((fp = fopen(filename, "r")) == NULL)
        return 1;

    line = (char *)malloc(MP_LINELEN * sizeof(char));

    while (fgets(line, MP_LINELEN-1, fp) != NULL) {
        line = _trim(line);
    
        if (isdigit(line[0])) {
            /* A digit indicates location or start address */
      
            sscanf(line, "%u", &addr);

            /* The last read address is assumed to be the start address */
            *startaddr = addr;
        }
        else if (line[0] == '+' || line[0] == '-') {
            /* A sign indicates a MIX word */
            mix_word_t w;
      
            sscanf_mix_word(line, &w);
      
            if (lines != NULL)
                if ((s = strchr(line, '#')) != NULL)
                    lines[addr] = atoi(s+1)-1;

            Mem[addr++] = w;
        }
    }

    fclose(fp);

    return 0;
}

int mp_load(char *filename, mix_addr_t *startaddr)
{
    return _load(filename, startaddr, NULL);
}

int mp_load_dbg(char *filename, mix_addr_t *startaddr, int lines[])
{
    return _load(filename, startaddr, lines); 
}

