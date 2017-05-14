/**
 * hw_exec
 *
 * Author   Jonathan Lo < >
 */
#include "includes.h"

extern Counter pc_e;
extern Counter ex_internal_arith;
extern Counter ex_internal_shift;
extern Counter ex_internal_addr;
extern Counter ex_internal_ir;

extern Counter pc_em;
extern Clearable ir_em;
extern Counter out_em;
extern Clearable mem_flag;


extern Bus irbus_e1;
extern Bus irbus_e2;
extern BusALU shift_alu;
extern BusALU addr_alu;
extern BusALU arith_alu;
// $(filename)
