/**
 * hw_exec
 *
 * Author   Jonathan Lo < >
 */
#include "hw_exec.h"

Counter pc_e ( "PC_E", ADDR_SIZE );
Counter ex_internal_arith ( "EXTINTARITH", REG_SIZE );
Counter ex_internal_shift ( "EXINTSHIFT", REG_SIZE );
Counter ex_internal_addr ( "EXINTADDR", REG_SIZE );
Counter ex_internal_ir ( "EXINTIR", REG_SIZE );

Clearable ir_em ( "IR_EM", REG_SIZE );
Counter pc_em ( "PC_EM", ADDR_SIZE );
Counter out_em ( "OUT_EM", REG_SIZE );
Clearable mem_flag ( "MEM_FLAG", REG_SIZE );

Bus irbus_e1 ( "IRBUS_E1", REG_SIZE );
Bus irbus_e2 ( "IRBUS_E2", REG_SIZE );
BusALU shift_alu ( "SHIFTALU", REG_SIZE );
BusALU addr_alu ( "ADDRALU", REG_SIZE );
BusALU arith_alu ( "ARITHALU", REG_SIZE );
// $(filename)
