#include "mix_dbg.h"

/* Dummy event handlers */
int __ev_start() { return 0; }
int __ev_ra_changed() { return 0; }
int __ev_rx_changed() { return 0; }
int __ev_ri1_changed() { return 0; }
int __ev_ri2_changed() { return 0; }
int __ev_ri3_changed() { return 0; }
int __ev_ri4_changed() { return 0; }
int __ev_ri5_changed() { return 0; }
int __ev_ri6_changed() { return 0; }
int __ev_rj_changed() { return 0; }
int __ev_mem_changed(mix_addr_t addr, int n) { return 0; }
int __ev_cmp_changed() { return 0; }
int __ev_ofl_changed() { return 0; }
int __ev_pc_changed(mix_addr_t addr) { return 0; }
int __ev_state_changed(mix_state_t s) { return 0; }
int __ev_prog_finish() { return 0; }
int __ev_invalid_instr(int c) { return 0; }
int __ev_invalid_addr(mix_addr_t addr) { return 0; }

/* Debugger initialization */
void mix_dbg_init()
{
    ev_start = &__ev_start;
    ev_ra_changed = &__ev_ra_changed;
    ev_rx_changed = &__ev_rx_changed;
    ev_ri1_changed = &__ev_ri1_changed;
    ev_ri2_changed = &__ev_ri2_changed;
    ev_ri3_changed = &__ev_ri3_changed;
    ev_ri4_changed = &__ev_ri4_changed;
    ev_ri5_changed = &__ev_ri5_changed;
    ev_ri6_changed = &__ev_ri6_changed;
    ev_rj_changed = &__ev_rj_changed;
    ev_mem_changed = &__ev_mem_changed;
    ev_cmp_changed = &__ev_cmp_changed;
    ev_ofl_changed = &__ev_ofl_changed;
    ev_pc_changed = &__ev_pc_changed;
    ev_state_changed = &__ev_state_changed;
    ev_prog_finish = &__ev_prog_finish;
    ev_invalid_instr = &__ev_invalid_instr;
    ev_invalid_addr = &__ev_invalid_addr;
}
