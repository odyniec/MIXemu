#ifndef _MIX_CHARS_H
#define _MIX_CHARS_H 1

#include "mix_types.h"

extern mix_byte_t _mix_chars[256];
extern char _ascii_chars[56];

#define ASCII_TO_MIX(c) (_mix_chars[c])
#define MIX_TO_ASCII(c) (_ascii_chars[c])

#endif   /* mix_chars.h */
