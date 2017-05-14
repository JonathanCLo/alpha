#include "includes.h"

extern int instr_index;
extern void hazard_init(void);
extern void load_dep_table(void);
extern void advance_hd(void);
extern void exec_read_after_write(bool imm);
extern bool detect_read_after_load_dist(void);
extern void memory_stall(void);
