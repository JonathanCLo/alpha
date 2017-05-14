#include "includes.h"

extern int instr_index;
extern void hazard_init(void);
extern void load_dep_table();
extern void advance_hd();
extern void exec_read_after_write(bool imm);
