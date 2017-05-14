#include "hw_exec.h"

Counter ex_internal_shift("EXINTSHIFT", REG_SIZE);
Counter ex_internal_addr("EXINTADDR", REG_SIZE);
BusALU shift_alu("SHIFTALU", REG_SIZE);
BusALU addr_alu("ADDRALU", REG_SIZE);
BusALU arith_alu("ARITHALU", REG_SIZE);
