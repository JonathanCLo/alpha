/**
 * hw_mem
 *
 * Author   Jonathan Lo < >
 */
#include "hw_mem.h"

Bus dbus_m ( "DBUSM", REG_SIZE );
Counter pc_em ( "PC_EM", ADDR_SIZE );
Counter ir_em ( "IREM", REG_SIZE );
Counter out_em ( "OUTEM", REG_SIZE );
Bus mm_controlbus ( "MMCONTROLBUS", REG_SIZE );
Bus addrbus_m ( "ADDRBUS_M", REG_SIZE );
Counter mem_flag ( "MEMFLAG", REG_SIZE );
Counter mm_internal_arith ( "MMINTERNALARITH", REG_SIZE );
Counter mm_internal_type ( "MMINTERNALTYPE", REG_SIZE );
Constant no_mem ( "NO_MEM", REG_SIZE, 0 );
Constant read_mem ( "READ_MEM", REG_SIZE, 1 );
Constant write_mem ( "WRITE_MEM", REG_SIZE, 2 );
Constant writeback ( "WRITEBACK", REG_SIZE, 3 );


// $(filename)
