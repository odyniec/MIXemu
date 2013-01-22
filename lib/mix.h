#ifndef _MIX_H
#define _MIX_H 1

#include "mix_types.h"

/* Comparison indicator values */
typedef enum { LESS, EQUAL, GREATER } mix_cmp_t;
/* Overflow */
typedef enum { OF, NOF } mix_ofl_t;

/* Computer states */
typedef enum { HALTED, RUNNING } mix_state_t;

/* Memory size */
#define MIX_MEMSIZE 4000

/* Check if memory address is valid */
#define VALID_ADDR(a) ((a) >= 0 && (a) < MIX_MEMSIZE)

/* Memory cells */
mix_word_t Mem[MIX_MEMSIZE];

/* Registers */
mix_word_t rA;
mix_word_t rX;
mix_short_t rI[6];
/* Abbreviations for index registers */
#define rI1 rI[0]
#define rI2 rI[1]
#define rI3 rI[2]
#define rI4 rI[3]
#define rI5 rI[4]
#define rI6 rI[5]

/* Jump register */
mix_short_t rJ;

/* Compare flag */
mix_cmp_t Cmp;
/* Overflow flag */
mix_ofl_t Ofl;

/* Program counter (not an actual register) */
static mix_addr_t _pc;

/* Current computer state */
static mix_state_t _state;

/* Macros that extract specific parts of an opcode */
#define AA(w) (mix_short(w.s, w.b[0], w.b[1]))
#define I(w) (w.b[2])
#define F(w) (w.b[3])
#define C(w) (w.b[4])

/* Memory address after indexing, as mix_addr_t */
#define M_ADDR(w) (SHORT_TO_ADDR(AA(w)) + (I(w) > 0 ? SHORT_TO_ADDR(rI[I(w)-1]) : 0))
/* As mix_short_t */
#define M(w) (ADDR_TO_SHORT(M_ADDR(w)))

#define CONTENTS(a) (Mem[(a)])
#define V(w) (Mem[M_ADDR(w)])

mix_addr_t get_pc();

void set_rA(mix_word_t w);
void set_rX(mix_word_t w);
void set_rI1(mix_short_t s);
void set_rI2(mix_short_t s);
void set_rI3(mix_short_t s);
void set_rI4(mix_short_t s);
void set_rI5(mix_short_t s);
void set_rI6(mix_short_t s);
void set_rJ(mix_short_t s);
void set_Mem(mix_addr_t addr, mix_word_t w);
void set_Cmp(mix_cmp_t c);
void set_Ofl(mix_ofl_t o);
void set_pc(mix_addr_t addr);

#endif   /* mix.h */
