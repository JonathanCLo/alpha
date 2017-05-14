/**
 * $(filename)
 *
 * Author   Jonathan Lo < >
 */
#include "includes.h"

unsigned int ADDR_SIZE ( 32 );
unsigned int DATA_SIZE ( 16 );
unsigned int REG_SIZE ( 32 );

Clearable noop_g ( "NOOP_G", REG_SIZE, 0 );
Clearable not3_g ( "NOT3_G", REG_SIZE, ~3 );
Clearable mult4_g ( "MULT4_G", REG_SIZE, 2 );
Clearable shift11_g ( "SHIFT11_G", REG_SIZE, 11 );
Clearable dispmask_g ( "DISPMASK_G", REG_SIZE, 2097151 );
Clearable const2_g ( "CONST2_G", REG_SIZE, 2 );
Clearable const3_g ( "CONST3_G", REG_SIZE, 3 );
Clearable const16_g ( "CONST16_G", REG_SIZE, 16 );

Constant no_mem ( "NO_MEM", REG_SIZE, 0 );
Constant read_mem ( "READ_MEM", REG_SIZE, 1 );
Constant write_mem ( "WRITE_MEM", REG_SIZE, 2 );
Constant writeback ( "WRITEBACK", REG_SIZE, 3 );

Memory instr_cache ( "INSTR_CACHE", ADDR_SIZE, REG_SIZE, 0xFFFF );
Memory data_cache ( "DATA_CACHE", ADDR_SIZE, DATA_CACHE, 0xFFFF );

bool done ( false );
// $(filename)
