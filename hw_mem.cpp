/**
 * hw_mem
 *
 * Author   Jonathan Lo < >
 */
#include "hw_mem.h"

Bus dbus_m ( "DBUSM", REG_SIZE );
Bus mm_controlbus ( "MMCONTROLBUS", REG_SIZE );
Bus addrbus_m ( "ADDRBUS_M", REG_SIZE );
Counter mem_flag ( "MEMFLAG", REG_SIZE );
Counter mm_internal_arith ( "MMINTERNALARITH", REG_SIZE );
Counter mm_internal_type ( "MMINTERNALTYPE", REG_SIZE );


// $(filename)
