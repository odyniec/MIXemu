/*
 * MP (MIX Program) file format routines
 */

#ifndef MP_H_
#define MP_H_ 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "mix.h"

/* Maximum line length */
#define MP_LINELEN 128

/* Load MP file into memory */
int mp_load(char *filename, mix_addr_t *startaddr);

/* Load MP file into memory along with debugging information (line numbers) */
int mp_load_dbg(char *filename, mix_addr_t *startaddr, int lines[]);

#endif   /* mp.h */
