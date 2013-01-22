#include <stdio.h>
#include <string.h>

#include "mix_types.h"

/* 
 * Basic arithmetic operations on mix_byte_t arrays representing non-negative
 * numbers.
 * 
 * The same array can be used as both operand and result, e.g.:
 *   _addnn(u, v, 5, u);    (u = u + v)
 */

/* Comparison */
int _cmpnn(mix_byte_t u[], mix_byte_t v[], int n)
{
    int c, j = n-1;

    for (; j > 0; j--)
        if ((c = u[j] - v[j]) != 0)
            return c;

    return u[0] - v[0];
}

/* Addition */
void _addnn(mix_byte_t u[], mix_byte_t v[], int n, mix_byte_t w[])
{
    int j = 0, k = 0;
    mix_byte_t a;

    for (; j < n; j++) {
        a = ((u[j] + v[j] + k) & (BS-1)) % BS;
        k = (u[j] + v[j] + k >= BS ? 1 : 0);
        w[j] = a;
    }

    w[n] = k;
}

/* Subtraction */
void _subnn(mix_byte_t u[], mix_byte_t v[], int n, mix_byte_t w[])
{
    int j = 0, k = 0;
    mix_byte_t a;

    for (; j < n; j++) {
        a = ((u[j] - v[j] + k) & (BS-1)) % BS;
        k = (u[j] - v[j] + k < 0 ? -1 : 0);
        w[j] = a;
    }
}

/* Multiplication */
void _mulnn(mix_byte_t u[], mix_byte_t v[], int m, int n, mix_byte_t w[])
{
    mix_byte_t *tw;
    int i, j = 0, t, k;

    tw = (mix_byte_t *)malloc((m+n) * sizeof(mix_byte_t));

    for (i = 0; i < m; i++)
        tw[i] = 0;

    for (j = 0; j < n; j++) {
        k = 0;

        for (i = 0; i < m; i++) {
            t = u[i] * v[j] + tw[i+j] + k;
            tw[i+j] = t % BS;
            k = t / BS;
        }

        tw[j+m] = k;
    }

    for (i = 0; i < m+n; i++)
        w[i] = tw[i];
}

/* Short division (the divisor is a single byte) */
void _divnns(mix_byte_t u[], mix_byte_t v, int n, mix_byte_t w[],
    mix_byte_t *r)
{
    int j = n-1;
    *r = 0;
  
    for (; j >= 0; j--) {
        w[j] = (*r * BS + u[j]) / v;
        *r = (*r * BS + u[j]) % v;
    }
}

/* Division */
void _divnn(mix_byte_t u[], mix_byte_t v[], int m, int n, mix_byte_t q[],
    mix_byte_t r[])
{
    int j, i;
    mix_byte_t *vb, *qvb;
    mix_byte_t b;

    for (j = 0; j < m-n+1; j++)
        q[j] = 0;

    vb = (mix_byte_t *)malloc(m * sizeof(mix_byte_t));
    qvb = (mix_byte_t *)malloc(m * sizeof(mix_byte_t));

    for (j = 0; j < m-n; j++)
        vb[j] = 0;
    for (j = m-n; j < m; j++)
        vb[j] = v[j-(m-n)];

    while (_cmpnn(u, vb, m) >= 0) {
        q[m-n] += 1;
        _subnn(u, vb, m, u);
    }

    for (i = m-1; i > n-1; i--) {
        q[i-n] = (mix_byte_t)(u[i] == v[n-1] ?
            BS-1 : (u[i]*BS + u[i-1]) / v[n-1]);
 
        while (q[i-n] * (v[n-1]*BS + v[n-2]) > u[i]*BS*BS + u[i-1]*BS + u[i-2])
            q[i-n] -= 1;

        for (j = 0; j < i-n; j++)
            vb[j] = 0;
        for (; j < i+1; j++)
            vb[j] = v[j-i+n];
        for (; j < m+1; j++)
            vb[j] = 0;
        _mulnn(vb, (mix_byte_t *)&q[i-n], m, 1, qvb);

        if (_cmpnn(u, qvb, m) < 0) {
            _addnn(u, vb, m, u);
            _subnn(u, qvb, m, u);
            q[i-n] -= 1;
        }
        else
          _subnn(u, qvb, m, u);
    }

    for (j = 0; j < n; j++)
        r[j] = u[j];
}

/* Basic arithmetic operations on non-negative mix_short_t numbers */

/* Comparison */
int _mix_short_cmpnn(mix_short_t u, mix_short_t v)
{
    int c, j;

    if ((c = u.b[0] - v.b[0]) != 0)
        return c;
    else
        return u.b[1] - v.b[1];
}

/* Addition */
int _mix_short_addnn(mix_short_t u, mix_short_t v, mix_short_t *w)
{
    int j, k = 0;

    for (j = 1; j >= 0; j--) {
        w->b[j] = ((u.b[j] + v.b[j] + k) & (BS - 1)) % BS;
        k = (u.b[j] + v.b[j] + k >= BS ? 1 : 0);
    }

    return k;
}

/* Subtraction */
int _mix_short_subnn(mix_short_t u, mix_short_t v, mix_short_t *w)
{
    int j, k = 0;

    for (j = 1; j >= 0; j--) {
        w->b[j] = ((u.b[j] - v.b[j] + k) & (BS - 1)) % BS;
        k = (u.b[j] - v.b[j] + k < 0 ? -1 : 0);
    }

    return -k;
}

/* Basic arithmetic operations on non-negative mix_word_t numbers */

/* Comparison */
int _mix_word_cmpnn(mix_word_t w1, mix_word_t w2)
{
    int c, j;

    for (j = 0; j < 4; j++)
        if ((c = w1.b[j] - w2.b[j]) != 0)
            return c;

    return w1.b[4] - w2.b[4];
}

/* Addition */
int _mix_word_addnn(mix_word_t w1, mix_word_t w2, mix_word_t *wr)
{
    int j, k = 0;

    for (j = 4; j >= 0; j--) {
        wr->b[j] = ((w1.b[j] + w2.b[j] + k) & (BS - 1)) % BS;
        k = (w1.b[j] + w2.b[j] + k >= BS ? 1 : 0);
    }

    return k;
}

/* Subtraction */
int _mix_word_subnn(mix_word_t w1, mix_word_t w2, mix_word_t *wr)
{
    int j, k = 0;

    for (j = 4; j >= 0; j--) {
        wr->b[j] = ((w1.b[j] - w2.b[j] + k) & (BS - 1)) % BS;
        k = (w1.b[j] - w2.b[j] + k < 0 ? -1 : 0);
    }

    return -k;
}

/* Multiplication */
void _mix_word_mulnn(mix_word_t w1, mix_word_t w2, mix_word_t *wr1,
    mix_word_t *wr2)
{
    mix_byte_t uu[5];
    mix_byte_t vv[5];
    mix_byte_t ww[10];

    uu[0] = w1.b[4];
    uu[1] = w1.b[3];
    uu[2] = w1.b[2];
    uu[3] = w1.b[1];
    uu[4] = w1.b[0];

    vv[0] = w2.b[4];
    vv[1] = w2.b[3];
    vv[2] = w2.b[2];
    vv[3] = w2.b[1];
    vv[4] = w2.b[0];

    _mulnn(uu, vv, 5, 5, ww);

    wr1->b[0] = ww[9];
    wr1->b[1] = ww[8];
    wr1->b[2] = ww[7];
    wr1->b[3] = ww[6];
    wr1->b[4] = ww[5];
    wr2->b[0] = ww[4];
    wr2->b[1] = ww[3];
    wr2->b[2] = ww[2];
    wr2->b[3] = ww[1];
    wr2->b[4] = ww[0];
}

/* Division */
int _mix_word_divnn(mix_word_t u1, mix_word_t u2, mix_word_t v, mix_word_t *q,
    mix_word_t *r)
{
    mix_byte_t uu[11];
    mix_byte_t vv[5];
    mix_byte_t qq[6];
    mix_byte_t rr[5];
    int i, n, m;

    /* Check for overflow or division by zero */
    if (_mix_word_cmpnn(u1, v) >= 0 || _mix_word_cmpnn(v, MIX_WORD_ZERO) == 0)
        return 1;

    for (i = 0; i < 10; i++) {
        uu[i] = (i < 5 ? u2.b[4-i] : u1.b[9-i]);
        if (uu[i] > 0)
            m = i+1;
    }
    uu[10] = 0;

    for (i = 0; i < 5; i++) {
        vv[i] = v.b[4-i];
        if (vv[i] > 0)
            n = i+1;
    }

    if (n > 1)
        //_divnn(uu, vv, m-1, n-1, qq, rr);
        _divnn(uu, vv, m, n, qq, rr);
    else
        _divnns(uu, vv[0], m, qq, &rr[0]);

    for (i = 0; i < 5; i++)
        q->b[4-i] = (i < m-n+1 ? qq[i] : 0);

    for (i = 0; i < n; i++)
        r->b[4-i] = rr[i];
    for (; i < 5; i++)
        r->b[4-i] = 0;

    return 0;
}

/* Make a short word out of two bytes and sign */
mix_short_t mix_short(mix_sign_t s, mix_byte_t k, mix_byte_t l)
{
    mix_short_t h;

    h.s = s;
    h.b[0] = k;
    h.b[1] = l;

    return h;
}

/* Make a word out of five bytes and sign */
mix_word_t mix_word(mix_sign_t s, mix_byte_t k, mix_byte_t l, mix_byte_t m,
    mix_byte_t n, mix_byte_t o)
{
    mix_word_t w;

    w.s = s;
    w.b[0] = k;
    w.b[1] = l;
    w.b[2] = m;
    w.b[3] = n;
    w.b[4] = o;

    return w;
}

mix_short_t * new_mix_short(mix_sign_t s, mix_byte_t k, mix_byte_t l)
{
    mix_short_t *h = (mix_short_t *)malloc(sizeof(mix_short_t));

    h->s = s;
    h->b[0] = k;
    h->b[1] = l;

    return h;
}

mix_word_t * new_mix_word(mix_sign_t s, mix_byte_t k, mix_byte_t l,
    mix_byte_t m, mix_byte_t n, mix_byte_t o)
{
    mix_word_t *w = (mix_word_t *)malloc(sizeof(mix_word_t));
  
    w->s = s;
    w->b[0] = k;
    w->b[1] = l;
    w->b[2] = m;
    w->b[3] = n;
    w->b[4] = o;

    return w;
}

/* Arithmetic operations on mix_short_t */

int mix_short_cmp(mix_short_t u, mix_short_t v)
{
    if (_mix_short_cmpnn(u, MIX_SHORT_ZERO) == 0)
        if (_mix_short_cmpnn(v, MIX_SHORT_ZERO) == 0)
            return 0;

    if (u.s == POS) {
        if (v.s == POS)
            return _mix_short_cmpnn(u, v);
        else
            return 1;
    }
    else {
        if (v.s == POS)
            return -1;
        else
            return -_mix_short_cmpnn(u, v);
    }
}

int mix_short_add(mix_short_t u, mix_short_t v, mix_short_t *w)
{
    if (u.s == POS && v.s == POS) {
        w->s = POS;
        return _mix_short_addnn(u, v, w);
    }

    if (u.s == POS && v.s == NEG) {
        if (_mix_short_cmpnn(u, v) >= 0) {
            w->s = POS;
            return _mix_short_subnn(u, v, w);
        }
        else {
            w->s = NEG;
            return _mix_short_subnn(v, u, w);
        }
    }

    if (u.s == NEG && v.s == POS) {
        if (_mix_short_cmpnn(u, v) >= 0) {
            w->s = NEG;
            return _mix_short_subnn(u, v, w);
        }
        else {
            w->s = POS;
            return _mix_short_subnn(v, u, w);
        }
    }
    
    /* Assume (u.s == NEG && v.s == NEG) */
    w->s = NEG;
    return _mix_short_addnn(u, v, w);
}

int mix_short_sub(mix_short_t u, mix_short_t v, mix_short_t *w)
{
    if (u.s == POS && v.s == POS) {
        if (_mix_short_cmpnn(u, v) >= 0) {
            w->s = POS;
            return _mix_short_subnn(u, v, w);
        }
        else {
            w->s = NEG;
            return _mix_short_subnn(v, u, w);
        }
    }

    if (u.s == POS && v.s == NEG) {
        w->s = POS;
        return _mix_short_addnn(u, v, w);
    }

    if (u.s == NEG && v.s == POS) {
        w->s = NEG;
        return _mix_short_addnn(u, v, w);
    }

    /* Assume (u.s == NEG && v.s == NEG) */
    if (_mix_short_cmpnn(u, v) >= 0) {
        w->s = NEG;
        return _mix_short_subnn(u, v, w);
    }
    else {
        w->s = POS;
        return _mix_short_subnn(v, u, w);
    }
}

/* Arithmetic operations on mix_word_t */

int mix_word_cmp(mix_word_t w1, mix_word_t w2)
{
    if (_mix_word_cmpnn(w1, MIX_WORD_ZERO) == 0)
        if (_mix_word_cmpnn(w2, MIX_WORD_ZERO) == 0)
            return 0;

    if (w1.s == POS) {
        if (w2.s == POS)
            return _mix_word_cmpnn(w1, w2);
        else
            return 1;
    }
    else {
        if (w2.s == POS)
            return -1;
        else
            return -_mix_word_cmpnn(w1, w2);
    }
}


int mix_word_add(mix_word_t w1, mix_word_t w2, mix_word_t *wr)
{
    if (w1.s == POS && w2.s == POS) {
        wr->s = POS;
        return _mix_word_addnn(w1, w2, wr);
    }

    if (w1.s == POS && w2.s == NEG) {
        if (_mix_word_cmpnn(w1, w2) >= 0) {
            wr->s = POS;
            return _mix_word_subnn(w1, w2, wr);
        }
        else {
            wr->s = NEG;
            return _mix_word_subnn(w2, w1, wr);
        }
    }

    if (w1.s == NEG && w2.s == POS) {
        if (_mix_word_cmpnn(w1, w2) >= 0) {
            wr->s = NEG;
            return _mix_word_subnn(w1, w2, wr);
        }
        else {
            wr->s = POS;
            return _mix_word_subnn(w2, w1, wr);
        }
    }
  
    /* Assume (w1.s == NEG && w2.s == NEG) */
    wr->s = NEG;
    return _mix_word_addnn(w1, w2, wr);
}

int mix_word_sub(mix_word_t w1, mix_word_t w2, mix_word_t *wr)
{
    if (w1.s == POS && w2.s == POS) {
        if (_mix_word_cmpnn(w1, w2) >= 0) {
            wr->s = POS;
            return _mix_word_subnn(w1, w2, wr);
        }
        else {
            wr->s = NEG;
            return _mix_word_subnn(w2, w1, wr);
        }
    }

    if (w1.s == POS && w2.s == NEG) {
        wr->s = POS;
        return _mix_word_addnn(w1, w2, wr);
    }

    if (w1.s == NEG && w2.s == POS) {
        wr->s = NEG;
        return _mix_word_addnn(w1, w2, wr);
    }

    /* Assume (w1.s == NEG && w2.s == NEG) */
    if (_mix_word_cmpnn(w1, w2) >= 0) {
        wr->s = NEG;
        return _mix_word_subnn(w1, w2, wr);
    }
    else {
        wr->s = POS;
        return _mix_word_subnn(w2, w1, wr);
    }
}

void mix_word_mul(mix_word_t u, mix_word_t v, mix_word_t *w1, mix_word_t *w2)
{
    if (u.s == v.s) {
        w1->s = POS;
        w2->s = POS;
    }
    else {
        w1->s = NEG;
        w2->s = NEG;
    }

    _mix_word_mulnn(u, v, w1, w2);
}

int mix_word_div(mix_word_t u1, mix_word_t u2, mix_word_t v, mix_word_t *q, 
    mix_word_t *r)
{
    if (u1.s == v.s)
        q->s = POS;
    else
        q->s = NEG;

    r->s = u1.s;

    return _mix_word_divnn(u1, u2, v, q, r);
}

char* sprintf_mix_word(mix_word_t w)
{
    char *s = (char *)malloc(MIX_WORD_STRLEN * sizeof(char));

    snprintf(s, MIX_WORD_STRLEN, "%c%02d %02d %02d %02d %02d",
        (w.s == POS ? '+' : '-'), w.b[0], w.b[1], w.b[2], w.b[3], w.b[4]);

    return s;
}

char* sprintf_mix_word2(mix_word_t w)
{
    char *s = (char *)malloc(MIX_WORD_STRLEN * sizeof(char));

    snprintf(s, MIX_WORD_STRLEN, "%c%04d %02d %02d %02d",
        (w.s == POS ? '+' : '-'), w.b[0]*BS + w.b[1], w.b[2], w.b[3], w.b[4]);

    return s;
}

int sscanf_mix_word(char *s, mix_word_t *w)
{
    w->s = (*s == '-' ? NEG : POS);

    return (sscanf(s+1, "%u %u %u %u %u", &w->b[0], &w->b[1], &w->b[2],
        &w->b[3], &w->b[4]) == 5);
}

char* sprintf_mix_short(mix_short_t h)
{
    char *s = (char *)malloc(MIX_SHORT_STRLEN * sizeof(char));

    snprintf(s, MIX_SHORT_STRLEN, "%c%02d %02d",
        (h.s == POS ? '+' : '-'), h.b[0], h.b[1]);

    return s;
}

int sscanf_mix_short(char *s, mix_short_t *h)
{
    h->s = (*s == '-' ? NEG : POS);

    return (sscanf(s+1, "%u %u", &h->b[0], &h->b[1]) == 2);
}

/* Fragment when loaded */
void frag_loaded(mix_word_t w, mix_byte_t f, mix_word_t *r)
{
    int i, j=4, l;

    if (FL(f) == 0) {
        r->s = w.s;
        l = 0;
    }
    else 
        l = FL(f)-1;

    for (i = FR(f)-1; i >= l; i--)
        r->b[j--] = w.b[i];
}

/* Fragment when stored */
void frag_stored(mix_word_t w, mix_byte_t f, mix_word_t *r)
{
    int i, j=4, l;

    if (FL(f) == 0) {
        r->s = w.s;
        l = 0;
    }
    else
        l = FL(f)-1;

    for (i = FR(f)-1; i >= l; i--)
        r->b[i] = w.b[j--];
}

#define _WORD_AS_LONG(w) \
    (w.b[4] + w.b[3]*BS + w.b[2]*BS2 + w.b[1]*BS3 + w.b[0]*BS4)

void mix_word_to_long(mix_word_t w, long *l)
{
    *l = _WORD_AS_LONG(w);
}

long mix_word_as_long(mix_word_t w)
{
    return _WORD_AS_LONG(w);
}

#undef _WORD_AS_LONG

int long_to_mix_word(long l, mix_word_t *w)
{
    w->b[4] = l % BS;
    l /= BS;
    w->b[3] = l % BS;
    l /= BS;
    w->b[2] = l % BS;
    l /= BS;
    w->b[1] = l % BS;
    l /= BS;
    w->b[0] = l;

    if (l >= BS) {
        w->b[0] = l % BS;
        return 1;
    }
    else
        return 0;
}

