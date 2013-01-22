#ifndef MIX_TYPES_H_
#define MIX_TYPES_H_ 1

typedef enum { POS = 0, NEG = 1 } mix_sign_t;

typedef unsigned char mix_byte_t;

/* MIX byte size */
#define MIX_BYTESIZE 64
#define BS MIX_BYTESIZE
#define BS2 (BS*BS)
#define BS3 (BS2*BS)
#define BS4 (BS3*BS)
#define BS5 (BS4*BS)

/* MIX word */
typedef struct {
  mix_sign_t s:1;
  mix_byte_t b[5];
} mix_word_t;

/* Short MIX word */
typedef struct {
  mix_sign_t s:1;
  mix_byte_t b[2];
} mix_short_t;

/* MIX memory address */
typedef int mix_addr_t;

#define SHORT_TO_ADDR(h) \
  ((mix_addr_t)((h.s == POS ? 1 : -1) * (h.b[0] * BS + h.b[1])))
#define ADDR_TO_SHORT(a) \
  (mix_short(((a) >= 0 ? POS : NEG), \
   ((a) >= 0 ? (a) / BS : (-(a)) / BS), \
   ((a) >= 0 ? (a) % BS : (-(a)) % BS)))

/* Functions that produce words from bytes */

mix_short_t mix_short(mix_sign_t s, mix_byte_t k, mix_byte_t l);

mix_word_t mix_word(mix_sign_t s, mix_byte_t k, mix_byte_t l, mix_byte_t m,
    mix_byte_t n, mix_byte_t o);

mix_short_t * new_mix_short(mix_sign_t s, mix_byte_t k, mix_byte_t l);

mix_word_t * new_mix_word(mix_sign_t s, mix_byte_t k, mix_byte_t l,
    mix_byte_t m, mix_byte_t n, mix_byte_t o);

#define MIX_SHORT_ZERO (mix_short(POS, 0, 0))
#define MIX_WORD_ZERO (mix_word(POS, 0, 0, 0, 0, 0))

/* Arithmetic operations on mix_short_t */

int mix_short_cmp(mix_short_t u, mix_short_t v);

int mix_short_add(mix_short_t u, mix_short_t v, mix_short_t *w);

int mix_short_sub(mix_short_t u, mix_short_t v, mix_short_t *w);

/* Arithmetic operations on mix_word_t */

int mix_word_cmp(mix_word_t u, mix_word_t v);

int mix_word_add(mix_word_t u, mix_word_t v, mix_word_t *w);

int mix_word_sub(mix_word_t u, mix_word_t v, mix_word_t *w);

void mix_word_mul(mix_word_t u, mix_word_t v, mix_word_t *w1, mix_word_t *w2);

int mix_word_div(mix_word_t u1, mix_word_t u2, mix_word_t v, mix_word_t *q, 
    mix_word_t *r);

/* Print word as "-01 02 03 04 05" */
char * sprintf_mix_word(mix_word_t w);
/* Print word as "-0066 03 04 05" */
char * sprintf_mix_word2(mix_word_t w);

int sscanf_mix_word(char *s, mix_word_t *w);

char * sprintf_mix_short(mix_short_t h);

int sscanf_mix_short(char *s, mix_short_t *h);

#define FL(b) (b / 8)
#define FR(b) (b % 8)

void frag_loaded(mix_word_t w, mix_byte_t f, mix_word_t *r);

void frag_stored(mix_word_t w, mix_byte_t f, mix_word_t *r);

/* Miscellaneous macros */

/* Convert mix_word_t to mix_short_t */
#define WORD_TO_SHORT(w) (mix_short(w.s, w.b[3], w.b[4]))
/* Convert mix_short_t to mix_word_t */
#define SHORT_TO_WORD(h) (mix_word(h.s, 0, 0, 0, h.b[0], h.b[1]))

#define MIX_WORD_NEG(w) \
  (mix_word(w.s == POS ? NEG : POS, \
   w.b[0], w.b[1], w.b[2], w.b[3], w.b[4]))
#define MIX_SHORT_NEG(h) \
  (mix_short(h.s == POS ? NEG : POS, h.b[0], h.b[1]))

/* Length of mix_short_t as a string */
#define MIX_SHORT_STRLEN 7
/* Length of mix_word_t as a string */
#define MIX_WORD_STRLEN 16

void mix_word_to_long(mix_word_t w, long *l);

long mix_word_as_long(mix_word_t w);

int long_to_mix_word(long l, mix_word_t *w);

#endif   /* mix_types.h */
