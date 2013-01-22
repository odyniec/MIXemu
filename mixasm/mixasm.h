#ifndef _MIXASM_H
#define _MIXASM_H 1

#include "hashtbl.h"
#include "locsym.h"

FILE *ifp, *ofp;

/* Input and output file names */
char *ifname, *ofname;

/* Instruction opcodes hash table */
hashtbl_t *opcodes;

/* Symbols hash table */
hashtbl_t *symbols;

/* Local symbols */
locsym_t *locsyms[10];

int output;

/* Source code line number */
int linenum;

/* Current memory location */
mix_addr_t loc;

/* Last location */
mix_addr_t last_loc;

#endif   /* mixasm.h */

