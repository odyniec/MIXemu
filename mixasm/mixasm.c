#include <stdio.h>
#include <unistd.h>   /* for getopt() */
#include <string.h>

#include "mix.h"
#include "parser.h"
#include "errstr.h"
#include "mixasm.h"

extern int yyparse();

void init_opcodes()
{
    hashtbl_put(opcodes, "NOP",  new_mix_word(POS,  0,  0,  0,  0,  0));
    hashtbl_put(opcodes, "ADD",  new_mix_word(POS,  0,  0,  0,  5,  1));
    hashtbl_put(opcodes, "SUB",  new_mix_word(POS,  0,  0,  0,  5,  2));
    hashtbl_put(opcodes, "MUL",  new_mix_word(POS,  0,  0,  0,  5,  3));
    hashtbl_put(opcodes, "DIV",  new_mix_word(POS,  0,  0,  0,  5,  4));
    hashtbl_put(opcodes, "NUM",  new_mix_word(POS,  0,  0,  0,  0,  5));
    hashtbl_put(opcodes, "CHAR", new_mix_word(POS,  0,  0,  0,  1,  5));
    hashtbl_put(opcodes, "HLT",  new_mix_word(POS,  0,  0,  0,  2,  5));
    hashtbl_put(opcodes, "SLA",  new_mix_word(POS,  0,  0,  0,  0,  6));
    hashtbl_put(opcodes, "SRA",  new_mix_word(POS,  0,  0,  0,  1,  6));
    hashtbl_put(opcodes, "SLAX", new_mix_word(POS,  0,  0,  0,  2,  6));
    hashtbl_put(opcodes, "SRAX", new_mix_word(POS,  0,  0,  0,  3,  6));
    hashtbl_put(opcodes, "SLC",  new_mix_word(POS,  0,  0,  0,  4,  6));
    hashtbl_put(opcodes, "SRC",  new_mix_word(POS,  0,  0,  0,  5,  6));
    hashtbl_put(opcodes, "MOVE", new_mix_word(POS,  0,  0,  0,  1,  7));
    hashtbl_put(opcodes, "LDA",  new_mix_word(POS,  0,  0,  0,  5,  8));
    hashtbl_put(opcodes, "LD1",  new_mix_word(POS,  0,  0,  0,  5,  9));
    hashtbl_put(opcodes, "LD2",  new_mix_word(POS,  0,  0,  0,  5, 10));
    hashtbl_put(opcodes, "LD3",  new_mix_word(POS,  0,  0,  0,  5, 11));
    hashtbl_put(opcodes, "LD4",  new_mix_word(POS,  0,  0,  0,  5, 12));
    hashtbl_put(opcodes, "LD5",  new_mix_word(POS,  0,  0,  0,  5, 13));
    hashtbl_put(opcodes, "LD6",  new_mix_word(POS,  0,  0,  0,  5, 14));
    hashtbl_put(opcodes, "LDX",  new_mix_word(POS,  0,  0,  0,  5, 15));
    hashtbl_put(opcodes, "LDAN", new_mix_word(POS,  0,  0,  0,  5, 16));
    hashtbl_put(opcodes, "LD1N", new_mix_word(POS,  0,  0,  0,  5, 17));
    hashtbl_put(opcodes, "LD2N", new_mix_word(POS,  0,  0,  0,  5, 18));
    hashtbl_put(opcodes, "LD3N", new_mix_word(POS,  0,  0,  0,  5, 19));
    hashtbl_put(opcodes, "LD4N", new_mix_word(POS,  0,  0,  0,  5, 20));
    hashtbl_put(opcodes, "LD5N", new_mix_word(POS,  0,  0,  0,  5, 21));
    hashtbl_put(opcodes, "LD6N", new_mix_word(POS,  0,  0,  0,  5, 22));
    hashtbl_put(opcodes, "LDXN", new_mix_word(POS,  0,  0,  0,  5, 23));
    hashtbl_put(opcodes, "STA",  new_mix_word(POS,  0,  0,  0,  5, 24));
    hashtbl_put(opcodes, "ST1",  new_mix_word(POS,  0,  0,  0,  5, 25));
    hashtbl_put(opcodes, "ST2",  new_mix_word(POS,  0,  0,  0,  5, 26));
    hashtbl_put(opcodes, "ST3",  new_mix_word(POS,  0,  0,  0,  5, 27));
    hashtbl_put(opcodes, "ST4",  new_mix_word(POS,  0,  0,  0,  5, 28));
    hashtbl_put(opcodes, "ST5",  new_mix_word(POS,  0,  0,  0,  5, 29));
    hashtbl_put(opcodes, "ST6",  new_mix_word(POS,  0,  0,  0,  5, 30));
    hashtbl_put(opcodes, "STX",  new_mix_word(POS,  0,  0,  0,  5, 31));
    hashtbl_put(opcodes, "STJ",  new_mix_word(POS,  0,  0,  0,  2, 32));
    hashtbl_put(opcodes, "STZ",  new_mix_word(POS,  0,  0,  0,  5, 33));
    hashtbl_put(opcodes, "JBUS", new_mix_word(POS,  0,  0,  0,  0, 34));
    hashtbl_put(opcodes, "IOC",  new_mix_word(POS,  0,  0,  0,  0, 35));
    hashtbl_put(opcodes, "IN",   new_mix_word(POS,  0,  0,  0,  0, 36));
    hashtbl_put(opcodes, "OUT",  new_mix_word(POS,  0,  0,  0,  0, 37));
    hashtbl_put(opcodes, "JRED", new_mix_word(POS,  0,  0,  0,  0, 38));
    hashtbl_put(opcodes, "JMP",  new_mix_word(POS,  0,  0,  0,  0, 39));
    hashtbl_put(opcodes, "JSJ",  new_mix_word(POS,  0,  0,  0,  1, 39));
    hashtbl_put(opcodes, "JOV",  new_mix_word(POS,  0,  0,  0,  2, 39));
    hashtbl_put(opcodes, "JNOV", new_mix_word(POS,  0,  0,  0,  3, 39));
    hashtbl_put(opcodes, "JL",   new_mix_word(POS,  0,  0,  0,  4, 39));
    hashtbl_put(opcodes, "JE",   new_mix_word(POS,  0,  0,  0,  5, 39));
    hashtbl_put(opcodes, "JG",   new_mix_word(POS,  0,  0,  0,  6, 39));
    hashtbl_put(opcodes, "JGE",  new_mix_word(POS,  0,  0,  0,  7, 39));
    hashtbl_put(opcodes, "JNE",  new_mix_word(POS,  0,  0,  0,  8, 39));
    hashtbl_put(opcodes, "JLE",  new_mix_word(POS,  0,  0,  0,  9, 39));
    hashtbl_put(opcodes, "JAN",  new_mix_word(POS,  0,  0,  0,  0, 40));
    hashtbl_put(opcodes, "JAZ",  new_mix_word(POS,  0,  0,  0,  1, 40));
    hashtbl_put(opcodes, "JAP",  new_mix_word(POS,  0,  0,  0,  2, 40));
    hashtbl_put(opcodes, "JANN", new_mix_word(POS,  0,  0,  0,  3, 40));
    hashtbl_put(opcodes, "JANZ", new_mix_word(POS,  0,  0,  0,  4, 40));
    hashtbl_put(opcodes, "JANP", new_mix_word(POS,  0,  0,  0,  5, 40));
    hashtbl_put(opcodes, "J1N",  new_mix_word(POS,  0,  0,  0,  0, 41));
    hashtbl_put(opcodes, "J1Z",  new_mix_word(POS,  0,  0,  0,  1, 41));
    hashtbl_put(opcodes, "J1P",  new_mix_word(POS,  0,  0,  0,  2, 41));
    hashtbl_put(opcodes, "J1NN", new_mix_word(POS,  0,  0,  0,  3, 41));
    hashtbl_put(opcodes, "J1NZ", new_mix_word(POS,  0,  0,  0,  4, 41));
    hashtbl_put(opcodes, "J1NP", new_mix_word(POS,  0,  0,  0,  5, 41));
    hashtbl_put(opcodes, "J2N",  new_mix_word(POS,  0,  0,  0,  0, 42));
    hashtbl_put(opcodes, "J2Z",  new_mix_word(POS,  0,  0,  0,  1, 42));
    hashtbl_put(opcodes, "J2P",  new_mix_word(POS,  0,  0,  0,  2, 42));
    hashtbl_put(opcodes, "J2NN", new_mix_word(POS,  0,  0,  0,  3, 42));
    hashtbl_put(opcodes, "J2NZ", new_mix_word(POS,  0,  0,  0,  4, 42));
    hashtbl_put(opcodes, "J2NP", new_mix_word(POS,  0,  0,  0,  5, 42));
    hashtbl_put(opcodes, "J3N",  new_mix_word(POS,  0,  0,  0,  0, 43));
    hashtbl_put(opcodes, "J3Z",  new_mix_word(POS,  0,  0,  0,  1, 43));
    hashtbl_put(opcodes, "J3P",  new_mix_word(POS,  0,  0,  0,  2, 43));
    hashtbl_put(opcodes, "J3NN", new_mix_word(POS,  0,  0,  0,  3, 43));
    hashtbl_put(opcodes, "J3NZ", new_mix_word(POS,  0,  0,  0,  4, 43));
    hashtbl_put(opcodes, "J3NP", new_mix_word(POS,  0,  0,  0,  5, 43));
    hashtbl_put(opcodes, "J4N",  new_mix_word(POS,  0,  0,  0,  0, 44));
    hashtbl_put(opcodes, "J4Z",  new_mix_word(POS,  0,  0,  0,  1, 44));
    hashtbl_put(opcodes, "J4P",  new_mix_word(POS,  0,  0,  0,  2, 44));
    hashtbl_put(opcodes, "J4NN", new_mix_word(POS,  0,  0,  0,  3, 44));
    hashtbl_put(opcodes, "J4NZ", new_mix_word(POS,  0,  0,  0,  4, 44));
    hashtbl_put(opcodes, "J4NP", new_mix_word(POS,  0,  0,  0,  5, 44));
    hashtbl_put(opcodes, "J5N",  new_mix_word(POS,  0,  0,  0,  0, 45));
    hashtbl_put(opcodes, "J5Z",  new_mix_word(POS,  0,  0,  0,  1, 45));
    hashtbl_put(opcodes, "J5P",  new_mix_word(POS,  0,  0,  0,  2, 45));
    hashtbl_put(opcodes, "J5NN", new_mix_word(POS,  0,  0,  0,  3, 45));
    hashtbl_put(opcodes, "J5NZ", new_mix_word(POS,  0,  0,  0,  4, 45));
    hashtbl_put(opcodes, "J5NP", new_mix_word(POS,  0,  0,  0,  5, 45));
    hashtbl_put(opcodes, "J6N",  new_mix_word(POS,  0,  0,  0,  0, 46));
    hashtbl_put(opcodes, "J6Z",  new_mix_word(POS,  0,  0,  0,  1, 46));
    hashtbl_put(opcodes, "J6P",  new_mix_word(POS,  0,  0,  0,  2, 46));
    hashtbl_put(opcodes, "J6NN", new_mix_word(POS,  0,  0,  0,  3, 46));
    hashtbl_put(opcodes, "J6NZ", new_mix_word(POS,  0,  0,  0,  4, 46));
    hashtbl_put(opcodes, "J6NP", new_mix_word(POS,  0,  0,  0,  5, 46));
    hashtbl_put(opcodes, "JXN",  new_mix_word(POS,  0,  0,  0,  0, 47));
    hashtbl_put(opcodes, "JXZ",  new_mix_word(POS,  0,  0,  0,  1, 47));
    hashtbl_put(opcodes, "JXP",  new_mix_word(POS,  0,  0,  0,  2, 47));
    hashtbl_put(opcodes, "JXNN", new_mix_word(POS,  0,  0,  0,  3, 47));
    hashtbl_put(opcodes, "JXNZ", new_mix_word(POS,  0,  0,  0,  4, 47));
    hashtbl_put(opcodes, "JXNP", new_mix_word(POS,  0,  0,  0,  5, 47));
    hashtbl_put(opcodes, "INCA", new_mix_word(POS,  0,  0,  0,  0, 48));
    hashtbl_put(opcodes, "DECA", new_mix_word(POS,  0,  0,  0,  1, 48));
    hashtbl_put(opcodes, "ENTA", new_mix_word(POS,  0,  0,  0,  2, 48));
    hashtbl_put(opcodes, "ENNA", new_mix_word(POS,  0,  0,  0,  3, 48));
    hashtbl_put(opcodes, "INC1", new_mix_word(POS,  0,  0,  0,  0, 49));
    hashtbl_put(opcodes, "DEC1", new_mix_word(POS,  0,  0,  0,  1, 49));
    hashtbl_put(opcodes, "ENT1", new_mix_word(POS,  0,  0,  0,  2, 49));
    hashtbl_put(opcodes, "ENN1", new_mix_word(POS,  0,  0,  0,  3, 49));
    hashtbl_put(opcodes, "INC2", new_mix_word(POS,  0,  0,  0,  0, 50));
    hashtbl_put(opcodes, "DEC2", new_mix_word(POS,  0,  0,  0,  1, 50));
    hashtbl_put(opcodes, "ENT2", new_mix_word(POS,  0,  0,  0,  2, 50));
    hashtbl_put(opcodes, "ENN2", new_mix_word(POS,  0,  0,  0,  3, 50));
    hashtbl_put(opcodes, "INC3", new_mix_word(POS,  0,  0,  0,  0, 51));
    hashtbl_put(opcodes, "DEC3", new_mix_word(POS,  0,  0,  0,  1, 51));
    hashtbl_put(opcodes, "ENT3", new_mix_word(POS,  0,  0,  0,  2, 51));
    hashtbl_put(opcodes, "ENN3", new_mix_word(POS,  0,  0,  0,  3, 51));
    hashtbl_put(opcodes, "INC4", new_mix_word(POS,  0,  0,  0,  0, 52));
    hashtbl_put(opcodes, "DEC4", new_mix_word(POS,  0,  0,  0,  1, 52));
    hashtbl_put(opcodes, "ENT4", new_mix_word(POS,  0,  0,  0,  2, 52));
    hashtbl_put(opcodes, "ENN4", new_mix_word(POS,  0,  0,  0,  3, 52));
    hashtbl_put(opcodes, "INC5", new_mix_word(POS,  0,  0,  0,  0, 53));
    hashtbl_put(opcodes, "DEC5", new_mix_word(POS,  0,  0,  0,  1, 53));
    hashtbl_put(opcodes, "ENT5", new_mix_word(POS,  0,  0,  0,  2, 53));
    hashtbl_put(opcodes, "ENN5", new_mix_word(POS,  0,  0,  0,  3, 53));
    hashtbl_put(opcodes, "INC6", new_mix_word(POS,  0,  0,  0,  0, 54));
    hashtbl_put(opcodes, "DEC6", new_mix_word(POS,  0,  0,  0,  1, 54));
    hashtbl_put(opcodes, "ENT6", new_mix_word(POS,  0,  0,  0,  2, 54));
    hashtbl_put(opcodes, "ENN6", new_mix_word(POS,  0,  0,  0,  3, 54));
    hashtbl_put(opcodes, "INCX", new_mix_word(POS,  0,  0,  0,  0, 55));
    hashtbl_put(opcodes, "DECX", new_mix_word(POS,  0,  0,  0,  1, 55));
    hashtbl_put(opcodes, "ENTX", new_mix_word(POS,  0,  0,  0,  2, 55));
    hashtbl_put(opcodes, "ENNX", new_mix_word(POS,  0,  0,  0,  3, 55));
    hashtbl_put(opcodes, "CMPA", new_mix_word(POS,  0,  0,  0,  5, 56));
    hashtbl_put(opcodes, "CMP1", new_mix_word(POS,  0,  0,  0,  5, 57));
    hashtbl_put(opcodes, "CMP2", new_mix_word(POS,  0,  0,  0,  5, 58));
    hashtbl_put(opcodes, "CMP3", new_mix_word(POS,  0,  0,  0,  5, 59));
    hashtbl_put(opcodes, "CMP4", new_mix_word(POS,  0,  0,  0,  5, 60));
    hashtbl_put(opcodes, "CMP5", new_mix_word(POS,  0,  0,  0,  5, 61));
    hashtbl_put(opcodes, "CMP6", new_mix_word(POS,  0,  0,  0,  5, 62));
    hashtbl_put(opcodes, "CMPX", new_mix_word(POS,  0,  0,  0,  5, 63));
}


void usage(char *name)
{
    fprintf(stderr, "Usage: %s [-o output_file] input_file\n", name);
}


main(int argc, char *argv[])
{
    int c, i, ret;

    /* Prevent getopt from displaying its error messages */
    opterr = 0;

    while ((c = getopt(argc, argv, "o:h")) != EOF) {
        switch (c) {
        case 'o':
            ofname = strdup(optarg);
            break;
        case 'h':
            usage(argv[0]);
            exit(0);
        default:
            /* Unrecognized option */
            fprintf(stderr, "%s: %s -- %c\n", argv[0],
                errstr(ERR_OPTION_UNKNOWN), optopt);
            usage(argv[0]);
            exit(1);
        }
    }

    if (optind < argc)
        ifname = argv[optind];
    else {
        fprintf(stderr, "%s: missing input file name\n", argv[0]);
        usage(argv[0]);
        exit(1);
    }

    if (ofname == NULL) {
        /* Output file name not specified */
        char *s;

        ofname = (char *)malloc((strlen(ifname) + 4) * sizeof(char));
        strcpy(ofname, ifname);
        s = strrchr(ofname, '.');
        strcpy(s != NULL ? s : ofname, ".mp");
    }

    if ((ifp = fopen(ifname, "r")) == NULL) {
        fprintf(stderr, "%s\n", errstr(ERR_CANT_OPEN_INPUT));
        usage(argv[0]);
        exit(1);
    }

    if ((ofp = fopen(ofname, "w")) == NULL) {
        fprintf(stderr, "%s\n", errstr(ERR_CANT_OPEN_OUTPUT));
        usage(argv[0]);
        exit(1);
    }
  
    lex_first_pass();

    hashtbl_init(&symbols, 211);

    hashtbl_init(&opcodes, 67);
    init_opcodes();

    for (i = 0; i < 10; i++)
        locsyms[i] = NULL;

    output = 0;
  
    linenum = 1;

    loc = last_loc = 0;

    if (yyparse() != 0) {
        fclose(ifp);
        hashtbl_free(symbols);

        return 1;
    }

    /* Second pass */
  
    rewind(ifp);

    /* Enable output */
    output = 1;

    last_loc = loc-1;
    loc = 0;

    linenum = 1;

    lex_second_pass();

    ret = yyparse();

    fclose(ifp);
    fclose(ofp);

    hashtbl_free(opcodes);
    hashtbl_free(symbols);

    /* Discard output if error */
    if (ret != 0) {
        ofp = fopen(ofname, "w");
        fclose(ofp);
    }

    return ret;
}

