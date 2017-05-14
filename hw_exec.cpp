/**
 * hw_exec
 *
 * Author   Jonathan Lo < >
 */
#include "hw_exec.h"

Counter disp_re ( "DISP_READ_EXECUTE", REG_SIZE );
Counter ir_re ( "IR_READ_EXECUTE", REG_SIZE );
Counter ra_re ( "RA_READ_EXECUTE", REG_SIZE );
Counter rb_re ( "RB_READ_EXECUTE", REG_SIZE );
Counter rc_re ( "RC_READ_EXECUTE", REG_SIZE );
Counter literal_re ( "LITERAL_READ_EXECUTE", REG_SIZE );
Counter ex_internal_arith ( "EXTINTARITH", REG_SIZE );
Counter ex_internal_shift ( "EXINTSHIFT", REG_SIZE );
Counter ex_internal_addr ( "EXINTADDR", REG_SIZE );
Counter ex_internal_ir ( "EXINTIR", REG_SIZE );
BusALU shift_alu ( "SHIFTALU", REG_SIZE );
BusALU addr_alu ( "ADDRALU", REG_SIZE );
BusALU arith_alu ( "ARITHALU", REG_SIZE );
// $(filename)
