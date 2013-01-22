#ifndef MIX_DBG_H_
#define MIX_DBG_H_ 1

#include "mix.h"

/* MIX emulator start event */
int (*ev_start)();

/* rA register change event */
int (*ev_ra_changed)();

/* rX register change event */
int (*ev_rx_changed)();

/* Index registers change events */
int (*ev_ri1_changed)();
int (*ev_ri2_changed)();
int (*ev_ri3_changed)();
int (*ev_ri4_changed)();
int (*ev_ri5_changed)();
int (*ev_ri6_changed)();

/* Jump register change event */
int (*ev_rj_changed)();

/* Memory change event (addr is the address of the first modified cell, n is the 
 * range of modified cells following addr) */
int (*ev_mem_changed)(mix_addr_t addr, int n);

/* Comparison flag change event */
int (*ev_cmp_changed)();

/* Overflow flag change event */
int (*ev_ofl_changed)();

/* Program counter change event */
int (*ev_pc_changed)(mix_addr_t addr);

/* Computer state change event */
int (*ev_state_changed)(mix_state_t s);

/* Program finish event */
int (*ev_prog_finish)();

/* Invalid instruction event - happens when an instruction appears to be
 * invalid, e.g. when the C part is 5 and F is greater than 2 (c can be used as
 * error code to be returned) */
int (*ev_invalid_instr)(int c);

/* Invalid memory address event */
int (*ev_invalid_addr)(mix_addr_t addr);

void mix_dbg_init();

#endif   /* mix_dbg.h */
