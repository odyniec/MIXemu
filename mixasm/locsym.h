#ifndef _LOCSYM_H
#define _LOCSYM_H 1

#include "mix_types.h"

typedef struct _ls {
    mix_addr_t loc;
    mix_word_t val;
    struct _ls *next;
} locsym_t;

#endif   /* locsym.h */
