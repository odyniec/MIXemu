#include <stdio.h>

#include "mix_dev.h"
#include "mix_dbg.h"
#include "mix.h"

typedef void (*_mix_instr_t) ();

_mix_instr_t Instr[64];


/* Basic functions */

mix_addr_t get_pc()
{
    return _pc;
}

/* Register setting functions */

void set_rA(mix_word_t w)
{
    rA = w;
    ev_ra_changed();
}

void set_rX(mix_word_t w)
{
    rX = w;
    ev_rx_changed();
}

void set_rI1(mix_short_t s)
{
    rI1 = s;
    ev_ri1_changed();
}

void set_rI2(mix_short_t s)
{
    rI2 = s;
    ev_ri2_changed();
}

void set_rI3(mix_short_t s)
{
    rI3 = s;
    ev_ri3_changed();
}

void set_rI4(mix_short_t s)
{
    rI4 = s;
    ev_ri4_changed();
}

void set_rI5(mix_short_t s)
{
    rI5 = s;
    ev_ri5_changed();
}

void set_rI6(mix_short_t s)
{
    rI6 = s;
    ev_ri6_changed();
}

void set_rI(int i, mix_short_t s)
{
    switch (i) {
        case 1: set_rI1(s); break;
        case 2: set_rI2(s); break;
        case 3: set_rI3(s); break;
        case 4: set_rI4(s); break;
        case 5: set_rI5(s); break;
        case 6: set_rI6(s); break;
    }
}

void set_rJ(mix_short_t s)
{
    rJ = s;
    ev_rj_changed();
}

/* Set memory cell content */
void set_Mem(mix_addr_t addr, mix_word_t w)
{
    Mem[addr] = w;
    ev_mem_changed(addr,1);
}

/* Set comparison indicator */
void set_Cmp(mix_cmp_t c)
{
    Cmp = c;
    ev_cmp_changed();
}

/* Set overflow bit */
void set_Ofl(mix_ofl_t o)
{
    Ofl = o;
    ev_ofl_changed();
}

/* Set program counter */
void set_pc(mix_addr_t addr)
{
    if (addr >= 0 && addr < MIX_MEMSIZE) {
        _pc = addr;
        ev_pc_changed(_pc);
    }
    else
        ev_invalid_addr(addr);
}

/* Set computer state */
void set_state(mix_state_t s)
{
    _state = s;
    ev_state_changed(_state);
}


/* Instructions */

/* Current instruction word */
#define IW Mem[_pc]

/* Program counter modified -- jump instructions set this to 1 */
int _pc_modified = 0;

void instr_00()
{
    /* NOP */
}

void instr_01()
{
    /* No FADD for now */

    /* ADD */
    mix_word_t w = MIX_WORD_ZERO, u;

    frag_loaded(V(IW), F(IW), &w);

    if (mix_word_add(rA, w, &u))
        set_Ofl(OF);

    set_rA(u);
}

void instr_02()
{
    /* No FSUB for now */

    /* SUB */
    mix_word_t w = MIX_WORD_ZERO, u;

    frag_loaded(V(IW), F(IW), &w);

    if (mix_word_sub(rA, w, &u))
        set_Ofl(OF);

    set_rA(u);
}

void instr_03()
{
    /* No FMUL for now */

    /* MUL */
    mix_word_t w = MIX_WORD_ZERO, u, z;

    frag_loaded(V(IW), F(IW), &w);

    mix_word_mul(rA, w, &u, &z);

    set_rA(u);
    set_rX(z);
}

void instr_04()
{
    /* No FDIV as for now */

    /* DIV */
    mix_word_t w = MIX_WORD_ZERO, u, z;

    frag_loaded(V(IW), F(IW), &w);

    if (mix_word_div(rA, rX, w, &u, &z))
        set_Ofl(OF);

    set_rA(u);
    set_rX(z);
}

void instr_05()
{
    switch (F(IW)) {
    case 0:
        /* NUM */
        {
            long a;

            a = rX.b[4] % 10 +
                (rX.b[3] % 10) * 10 +
                (rX.b[2] % 10) * 100 +
                (rX.b[1] % 10) * 1000 +
                (rX.b[0] % 10) * 10000 +
                (rA.b[4] % 10) * 100000 +
                (rA.b[3] % 10) * 1000000 +
                (rA.b[2] % 10) * 10000000 +
                (rA.b[1] % 10) * 100000000 +
                (rA.b[0] % 10) * 1000000000;

            long_to_mix_word(a, &rA);

            ev_ra_changed();
        }
        break;
    case 1:
        /* CHAR */
        {
            long a;
            int i;

            mix_word_to_long(rA, &a);

            for (i = 4; i >= 0; i--) {
                rX.b[i] = 30 + a % 10;
                a /= 10;
            }
            for (i = 4; i >= 0; i--) {
                rA.b[i] = 30 + a % 10;
                a /= 10;
            }
            ev_rx_changed();
            ev_ra_changed();
        }
        break;
    case 2:
        /* HLT */
        set_state(HALTED);
        ev_prog_finish();
        break;
    default:
        ev_invalid_instr(0);
    }
}

void instr_06()
{
    int i = 0, m;
    mix_word_t w, u;

    switch (F(IW)) {
    case 0:
        /* SLA */
        m = M_ADDR(IW) % 5;

        for (; i <= 4; i++)
            rA.b[i] = (i+m <= 4 ? rA.b[i+m] : 0);
        set_rA(rA);
        break;
    case 1:
        /* SRA */
        m = M_ADDR(IW) % 5;

        for (i = 4; i >= 0; i--)
            rA.b[i] = (i-m >= 0 ? rA.b[i-m] : 0);
        set_rA(rA);
        break;
    case 2:
        /* SLAX */
        m = M_ADDR(IW) % 10;

        for (; i <= 4; i++)
            rA.b[i] = (i+m <= 4 ? rA.b[i+m] : (i+m <= 9 ? rX.b[i+m-5] : 0));
        for (; i <= 9; i++)
            rX.b[i-5] = (i+m <= 9 ? rX.b[i+m-5] : 0);
        set_rA(rA);
        set_rX(rX);
        break;
    case 3:
        /* SRAX */
        m = M_ADDR(IW) % 10;

        for (i = 9; i >= 5; i--)
            rX.b[i-5] = (i-m-5 >= 0 ? rX.b[i-m-5] : (i-m >= 0 ? rA.b[i-m] : 0));
        for (; i >= 0; i--)
            rA.b[i] = (i-m >= 0 ? rA.b[i-m] : 0);
        set_rA(rA);
        set_rX(rX);
        break;
    case 4:
        /* SLC */
        m = M_ADDR(IW) % 10;

        for (i = 0; i <= 4; i++)
            w.b[i] = (i+m <= 4 ? rA.b[i+m] :
                (i+m <= 9 ? rX.b[i+m-5] : rA.b[i+m-10]));
        for (i = 0; i <= 4; i++)
            u.b[i] = (i+m <= 4 ? rX.b[i+m] :
                (i+m <= 9 ? rA.b[i+m-5] : rX.b[i+m-10]));

        w.s = rA.s;
        u.s = rX.s;

        set_rA(w);
        set_rX(u);
        break;
    case 5:
        /* SRC */
        m = M_ADDR(IW) % 10;

        for (i = 0; i <= 4; i++)
            w.b[i] = (i-m >= 0 ? rA.b[i-m] :
                (i-m >= -5 ? rX.b[i-m+5] : rA.b[i-m+10]));
        for (i = 0; i <= 4; i++)
            u.b[i] = (i-m >= 0 ? rX.b[i-m] :
                (i-m >= -5 ? rA.b[i-m+5] : rX.b[i-m+10]));

        w.s = rA.s;
        u.s = rX.s;

        set_rA(w);
        set_rX(u);

        break;
    default:
        ev_invalid_instr(0);
    }
}

void instr_07()
{
    /* MOVE */
    mix_short_t h;
    mix_byte_t f = F(IW);
    mix_addr_t addr = M_ADDR(IW);
    mix_addr_t ri = SHORT_TO_ADDR(rI1);
    int i;
  
    /* 
     * set_Mem is not used here, ev_mem_changed is called only once, after the
     * whole operation has finished.
     */
    for (i = 0; i < f; i++)
        Mem[ri+i] = Mem[addr+i];

    ev_mem_changed(addr, f);
  
    mix_short_add(rI1, mix_short(POS, 0, f), &h);
    set_rI1(h);
}

void instr_08()
{
    /* LDA */
    mix_word_t w = MIX_WORD_ZERO;

    frag_loaded(V(IW), F(IW), &w);
  
    set_rA(w);
}

void instr_09()
{
    /* LD1 */
    mix_word_t w = MIX_WORD_ZERO;

    frag_loaded(V(IW), F(IW), &w);

    set_rI1(WORD_TO_SHORT(w));
}

void instr_10()
{
    /* LD2 */
    mix_word_t w = MIX_WORD_ZERO;

    frag_loaded(V(IW), F(IW), &w);

    set_rI2(WORD_TO_SHORT(w));
}

void instr_11()
{
    /* LD3 */
    mix_word_t w = MIX_WORD_ZERO;

    frag_loaded(V(IW), F(IW), &w);

    set_rI3(WORD_TO_SHORT(w));
}

void instr_12()
{
    /* LD4 */
    mix_word_t w = MIX_WORD_ZERO;

    frag_loaded(V(IW), F(IW), &w);

    set_rI4(WORD_TO_SHORT(w));
}

void instr_13()
{
    /* LD5 */
    mix_word_t w = MIX_WORD_ZERO;

    frag_loaded(V(IW), F(IW), &w);

    set_rI5(WORD_TO_SHORT(w));
}

void instr_14()
{
    /* LD6 */
    mix_word_t w = MIX_WORD_ZERO;

    frag_loaded(V(IW), F(IW), &w);

    set_rI6(WORD_TO_SHORT(w));
}

void instr_15()
{
    /* LDX */
    mix_word_t w = MIX_WORD_ZERO;

    frag_loaded(V(IW), F(IW), &w);

    set_rX(w);
}

void instr_16()
{
    /* LDAN */
    mix_word_t w = MIX_WORD_ZERO;

    frag_loaded(V(IW), F(IW), &w);
  
    set_rA(MIX_WORD_NEG(w));
}

void instr_17()
{
    /* LD1N */
    mix_word_t w = MIX_WORD_ZERO;

    frag_loaded(V(IW), F(IW), &w);

    set_rI1(MIX_SHORT_NEG(WORD_TO_SHORT(w)));
}

void instr_18()
{
    /* LD2N */
    mix_word_t w = MIX_WORD_ZERO;

    frag_loaded(V(IW), F(IW), &w);

    set_rI2(MIX_SHORT_NEG(WORD_TO_SHORT(w)));
}

void instr_19()
{
    /* LD3N */
    mix_word_t w = MIX_WORD_ZERO;

    frag_loaded(V(IW), F(IW), &w);

    set_rI3(MIX_SHORT_NEG(WORD_TO_SHORT(w)));
}

void instr_20()
{
    /* LD4N */
    mix_word_t w = MIX_WORD_ZERO;

    frag_loaded(V(IW), F(IW), &w);

    set_rI4(MIX_SHORT_NEG(WORD_TO_SHORT(w)));
}

void instr_21()
{
    /* LD5N */
    mix_word_t w = MIX_WORD_ZERO;

    frag_loaded(V(IW), F(IW), &w);

    set_rI5(MIX_SHORT_NEG(WORD_TO_SHORT(w)));
}

void instr_22()
{
    /* LD6N */
    mix_word_t w = MIX_WORD_ZERO;

    frag_loaded(V(IW), F(IW), &w);

    set_rI6(MIX_SHORT_NEG(WORD_TO_SHORT(w)));
}

void instr_23()
{
    /* LDXN */
    mix_word_t w = MIX_WORD_ZERO;

    frag_loaded(V(IW), F(IW), &w);

    set_rX(MIX_WORD_NEG(w));
}

void instr_24()
{
    /* STA */
    mix_word_t w = V(IW);

    frag_stored(rA, F(IW), &w);

    set_Mem(M_ADDR(IW), w);
}

void instr_25()
{
    /* ST1 */
    mix_word_t w = V(IW);
  
    frag_stored(SHORT_TO_WORD(rI1), F(IW), &w);

    set_Mem(M_ADDR(IW), w);
}

void instr_26()
{
    /* ST2 */
    mix_word_t w = V(IW);
  
    frag_stored(SHORT_TO_WORD(rI2), F(IW), &w);

    set_Mem(M_ADDR(IW), w);
}

void instr_27()
{
    /* ST3 */
    mix_word_t w = V(IW);
  
    frag_stored(SHORT_TO_WORD(rI3), F(IW), &w);

    set_Mem(M_ADDR(IW), w);
}

void instr_28()
{
    /* ST4 */
    mix_word_t w = V(IW);
  
    frag_stored(SHORT_TO_WORD(rI4), F(IW), &w);

    set_Mem(M_ADDR(IW), w);
}

void instr_29()
{
    /* ST5 */
    mix_word_t w = V(IW);
  
    frag_stored(SHORT_TO_WORD(rI5), F(IW), &w);

    set_Mem(M_ADDR(IW), w);
}

void instr_30()
{
    /* ST6 */
    mix_word_t w = V(IW);
  
    frag_stored(SHORT_TO_WORD(rI6), F(IW), &w);

    set_Mem(M_ADDR(IW), w);
}

void instr_31()
{
    /* STX */
    mix_word_t w = V(IW);

    frag_stored(rX, F(IW), &w);

    set_Mem(M_ADDR(IW), w);
}

void instr_32()
{
    /* STJ */
    mix_word_t w = V(IW);
  
    frag_stored(SHORT_TO_WORD(rJ), F(IW), &w);

    set_Mem(M_ADDR(IW), w);
}

void instr_33()
{
    /* STZ */
    mix_word_t w = V(IW);

    frag_stored(MIX_WORD_ZERO, F(IW), &w);

    set_Mem(M_ADDR(IW), w);
}

# define DO_JUMP \
   { \
       set_rJ(ADDR_TO_SHORT(_pc+1)); \
       set_pc(M_ADDR(IW)); \
       _pc_modified = 1; \
   }

void instr_34()
{
    /* JBUS */

    /* Nothing to do here -- we assume the devices are always ready. */
}

void instr_35()
{
    /* IOC */

    if (F(IW) < 8) {
        /* Tape */
        if (M_ADDR(IW) == 0)
            mix_dev_set_pos(F(IW), 0);
        else
            mix_dev_rel_pos(F(IW), M_ADDR(IW));
    }
    else if (F(IW) < 16) {
        /* Disk -- no operation required */
    }
    else if (F(IW) == 18) {
        /* Line printer */
        if (M_ADDR(IW) == 0) {
            /* New page */
        }
    }
    else if (F(IW) == 20) {
        /* Paper tape */
        if (M_ADDR(IW) == 0) {
            /* Rewind tape */
            mix_dev_set_pos(20, 0);
        }
    }
}

void instr_36()
{
    /* IN */

    /* 
     * Erroneous situation - when
     * (M_ADDR(IW) + _dev_blocksize[F(IW)] > MIX_MEMSIZE)
     */

    if (F(IW) >= 8 && F(IW) < 16)
        mix_dev_set_pos(F(IW), mix_word_as_long(rX));

    mix_dev_read(F(IW), M_ADDR(IW));
}

void instr_37()
{
    /* OUT */

    /* 
     * Erroneous situation - when
     * (M_ADDR(IW) + _dev_blocksize[F(IW)] > MIX_MEMSIZE)
     */

    if (F(IW) >= 8 && F(IW) < 16)
        mix_dev_set_pos(F(IW), mix_word_as_long(rX));

    mix_dev_write(F(IW), M_ADDR(IW));
}

void instr_38()
{
    /* JRED */

    /* We assume the devices are always ready, therefore an immediate jump. */
    DO_JUMP;
}

void instr_39()
{
    switch (F(IW)) {
    case 0:
        /* JMP */
        DO_JUMP;
        break;
    case 1:
        /* JSJ */
        set_pc(M_ADDR(IW));
        _pc_modified = 1;
        break;
    case 2:
        /* JOV */
        if (Ofl == OF) {
            set_Ofl(NOF);
            DO_JUMP;
        }
        break;
    case 3:
        /* JNOV */
        if (Ofl == NOF) {
            DO_JUMP;
        }
        else
            set_Ofl(NOF);
        break;
    case 4:
        /* JL */
        if (Cmp == LESS)
            DO_JUMP;
        break;
    case 5:
        /* JE */
        if (Cmp == EQUAL)
            DO_JUMP;
        break;
    case 6:
        /* JG */
        if (Cmp == GREATER)
            DO_JUMP;
        break;
    case 7:
        /* JGE */
        if (Cmp == GREATER || Cmp == EQUAL)
            DO_JUMP;
        break;
    case 8:
        /* JNE */
        if (Cmp != EQUAL)
            DO_JUMP;
        break;
    case 9:
        /* JLE */
        if (Cmp == LESS || Cmp == EQUAL)
            DO_JUMP;
        break;
    default:
        ev_invalid_instr(0);
    }
}

void instr_40()
{
    switch (F(IW)) {
    case 0:
        /* JAN */
        if (mix_word_cmp(rA, MIX_WORD_ZERO) < 0)
            DO_JUMP;
        break;
    case 1:
        /* JAZ */
        if (mix_word_cmp(rA, MIX_WORD_ZERO) == 0)
            DO_JUMP;
        break;
    case 2:
        /* JAP */
        if (mix_word_cmp(rA, MIX_WORD_ZERO) > 0)
            DO_JUMP;
        break;
    case 3:
        /* JANN */
        if (mix_word_cmp(rA, MIX_WORD_ZERO) >= 0)
            DO_JUMP;
        break;
    case 4:
        /* JANZ */
        if (mix_word_cmp(rA, MIX_WORD_ZERO) != 0)
            DO_JUMP;
        break;
    case 5:
        /* JANP */
        if (mix_word_cmp(rA, MIX_WORD_ZERO) <= 0)
            DO_JUMP;
        break;
    default:
        ev_invalid_instr(0);
    }
}

void instr_41__46()
{
    int i = C(IW)-41;

    switch (F(IW)) {
    case 0:
        /* JiN */
        if (mix_short_cmp(rI[i], MIX_SHORT_ZERO) < 0)
            DO_JUMP;
        break;
    case 1:
        /* JiZ */
        if (mix_short_cmp(rI[i], MIX_SHORT_ZERO) == 0)
            DO_JUMP;
        break;
    case 2:
        /* JiP */
        if (mix_short_cmp(rI[i], MIX_SHORT_ZERO) > 0)
            DO_JUMP;
        break;
    case 3:
        /* JiNN */
        if (mix_short_cmp(rI[i], MIX_SHORT_ZERO) >= 0)
            DO_JUMP;
        break;
    case 4:
        /* JiNZ */
        if (mix_short_cmp(rI[i], MIX_SHORT_ZERO) != 0)
            DO_JUMP;
        break;
    case 5:
        /* JiNP */
        if (mix_short_cmp(rI[i], MIX_SHORT_ZERO) <= 0)
            DO_JUMP;
        break;
    default:
        ev_invalid_instr(0);
    }
}

void instr_47()
{
    switch (F(IW)) {
    case 0:
        /* JXN */
        if (mix_word_cmp(rX, MIX_WORD_ZERO) < 0)
            DO_JUMP;
        break;
    case 1:
        /* JXZ */
        if (mix_word_cmp(rX, MIX_WORD_ZERO) == 0)
            DO_JUMP;
        break;
    case 2:
        /* JXP */
        if (mix_word_cmp(rX, MIX_WORD_ZERO) > 0)
            DO_JUMP;
        break;
    case 3:
        /* JXNN */
        if (mix_word_cmp(rX, MIX_WORD_ZERO) >= 0)
            DO_JUMP;
        break;
    case 4:
        /* JXNZ */
        if (mix_word_cmp(rX, MIX_WORD_ZERO) != 0)
            DO_JUMP;
        break;
    case 5:
        /* JXNP */
        if (mix_word_cmp(rX, MIX_WORD_ZERO) <= 0)
            DO_JUMP;
        break;
    default:
        ev_invalid_instr(0);
    }
}

# undef DO_JUMP

void instr_48()
{
    mix_word_t w;

    switch (F(IW)) {
    case 0:   
        /* INCA */
        if (mix_word_add(rA, SHORT_TO_WORD(M(IW)), &w))
            set_Ofl(OF);
        set_rA(w);
        break;
    case 1:
        /* DECA */
        if (mix_word_sub(rA, SHORT_TO_WORD(M(IW)), &w))
            set_Ofl(OF);
        set_rA(w);
        break;
    case 2:
        /* ENTA */
        set_rA(SHORT_TO_WORD(M(IW)));
        break;
    case 3:
        /* ENNA */
        set_rA(SHORT_TO_WORD(MIX_SHORT_NEG(M(IW))));
        break;
    default:
        ev_invalid_instr(0);
    }
}

void instr_49__54()
{
    mix_short_t h;
    int i = C(IW)-48;

    switch (F(IW)) {
    case 0:   
        /* INCi */
        if (mix_short_add(rI[i-1], M(IW), &h)) {
            /* 
             * "Overflow must not occur; if the magnitude of the result is more
             * than two bytes, the result of this instruction is undefined."
             */
        }
        set_rI(i, h);
        break;
    case 1:
        /* DECi */
        if (mix_short_sub(rI[i-1], M(IW), &h)) {
            /* See above */
        }
        set_rI(i, h);
        break;
    case 2:
        /* ENTi */
        set_rI(i, M(IW));
        break;
    case 3:
        /* ENNi */
        set_rI(i, MIX_SHORT_NEG(M(IW)));
        break;
    default:
        ev_invalid_instr(0);
    }
}

void instr_55()
{
    mix_word_t w;

    switch (F(IW)) {
    case 0:   
        /* INCX */
        if (mix_word_add(rX, SHORT_TO_WORD(M(IW)), &w))
            set_Ofl(OF);
        set_rX(w);
        break;
    case 1:
        /* DECX */
        if (mix_word_sub(rX, SHORT_TO_WORD(M(IW)), &w))
            set_Ofl(OF);
        set_rX(w);
        break;
    case 2:
        /* ENTX */
        set_rX(SHORT_TO_WORD(M(IW)));
        break;
    case 3:
        /* ENNX */
        set_rX(SHORT_TO_WORD(MIX_SHORT_NEG(M(IW))));
        break;
    default:
        ev_invalid_instr(0);
    }
}

void instr_56()
{
    /* No FCMP as for now */

    /* CMPA */
    mix_word_t w = MIX_WORD_ZERO, u = MIX_WORD_ZERO;
    int c;

    frag_loaded(rA, F(IW), &w);
    frag_loaded(V(IW), F(IW), &u);

    if ((c = mix_word_cmp(w, u)) < 0)
        set_Cmp(LESS);
    else if (c == 0)
        set_Cmp(EQUAL);
    else
        set_Cmp(GREATER);
}

void instr_57__62()
{
    /* CMPi */
    int i = C(IW)-57;
    mix_word_t w = MIX_WORD_ZERO, u = MIX_WORD_ZERO;
    int c;

    frag_loaded(SHORT_TO_WORD(rI[i]), F(IW), &w);
    frag_loaded(V(IW), F(IW), &u);

    if ((c = mix_word_cmp(w, u)) < 0)
        set_Cmp(LESS);
    else if (c == 0)
        set_Cmp(EQUAL);
    else
        set_Cmp(GREATER);
}

void instr_63()
{
    /* CMPX */
    mix_word_t w = MIX_WORD_ZERO, u = MIX_WORD_ZERO;
    int c;

    frag_loaded(rX, F(IW), &w);
    frag_loaded(V(IW), F(IW), &u);

    if ((c = mix_word_cmp(w, u)) < 0)
        set_Cmp(LESS);
    else if (c == 0)
        set_Cmp(EQUAL);
    else
        set_Cmp(GREATER);
}

/* End of instructions */

int mix_init()
{
    Instr[ 0] = &instr_00;
    Instr[ 1] = &instr_01;
    Instr[ 2] = &instr_02;
    Instr[ 3] = &instr_03;
    Instr[ 4] = &instr_04;
    Instr[ 5] = &instr_05;
    Instr[ 6] = &instr_06;
    Instr[ 7] = &instr_07;
    Instr[ 8] = &instr_08;
    Instr[ 9] = &instr_09;
    Instr[10] = &instr_10;
    Instr[11] = &instr_11;
    Instr[12] = &instr_12;
    Instr[13] = &instr_13;
    Instr[14] = &instr_14;
    Instr[15] = &instr_15;
    Instr[16] = &instr_16;
    Instr[17] = &instr_17;
    Instr[18] = &instr_18;
    Instr[19] = &instr_19;
    Instr[20] = &instr_20;
    Instr[21] = &instr_21;
    Instr[22] = &instr_22;
    Instr[23] = &instr_23;
    Instr[24] = &instr_24;
    Instr[25] = &instr_25;
    Instr[26] = &instr_26;
    Instr[27] = &instr_27;
    Instr[28] = &instr_28;
    Instr[29] = &instr_29;
    Instr[30] = &instr_30;
    Instr[31] = &instr_31;
    Instr[32] = &instr_32;
    Instr[33] = &instr_33;
    Instr[34] = &instr_34;
    Instr[35] = &instr_35;
    Instr[36] = &instr_36;
    Instr[37] = &instr_37;
    Instr[38] = &instr_38;
    Instr[39] = &instr_39;
    Instr[40] = &instr_40;
    Instr[41] = &instr_41__46;
    Instr[42] = &instr_41__46;
    Instr[43] = &instr_41__46;
    Instr[44] = &instr_41__46;
    Instr[45] = &instr_41__46;
    Instr[46] = &instr_41__46;
    Instr[47] = &instr_47;
    Instr[48] = &instr_48;
    Instr[49] = &instr_49__54;
    Instr[50] = &instr_49__54;
    Instr[51] = &instr_49__54;
    Instr[52] = &instr_49__54;
    Instr[53] = &instr_49__54;
    Instr[54] = &instr_49__54;
    Instr[55] = &instr_55;
    Instr[56] = &instr_56;
    Instr[57] = &instr_57__62;
    Instr[58] = &instr_57__62;
    Instr[59] = &instr_57__62;
    Instr[60] = &instr_57__62;
    Instr[61] = &instr_57__62;
    Instr[62] = &instr_57__62;
    Instr[63] = &instr_63;
  
    mix_dbg_init();
}

int mix_start()
{
    int i;

    /* Set registers to zero */
    set_rA(MIX_WORD_ZERO);
    set_rX(MIX_WORD_ZERO);
    set_rI1(MIX_SHORT_ZERO);
    set_rI2(MIX_SHORT_ZERO);
    set_rI3(MIX_SHORT_ZERO);
    set_rI4(MIX_SHORT_ZERO);
    set_rI5(MIX_SHORT_ZERO);
    set_rI6(MIX_SHORT_ZERO);
    set_rJ(MIX_SHORT_ZERO);

    /* Initial flag values */
    set_Cmp(EQUAL);
    set_Ofl(NOF);

    /* Set all memory cells to zero */
    for (i = 0; i < MIX_MEMSIZE; i++)
        Mem[i] = MIX_WORD_ZERO;

    /* No program running (yet) */
    set_state(HALTED);

    set_pc(0);

    /* Tell the debugger that MIX startup is done */
    ev_start();
}

void mix_exec()
{
    /* Execute instruction */
    Instr[C(IW)]();

    if (_pc_modified)
        /* Program counter was modified by this instruction -- reset flag */
        _pc_modified = 0;
    else
        /* Increment program counter */
        set_pc(_pc+1);
}

void mix_run()
{
    set_state(RUNNING);

    while (_state == RUNNING)
        mix_exec();
}

void mix_halt()
{
    set_state(HALTED);
}

