/**
 * hw_mem
 *
 * Author   Jonathan Lo < >
 */
#include "hw_mem.h"

Bus dbus_m ( "DBUSM", REG_SIZE );
Bus mm_controlbus ( "MMCONTROLBUS", REG_SIZE );
Bus addrbus_m ( "ADDRBUS_M", REG_SIZE );
Counter mm_internal_arith ( "MMINTERNALARITH", REG_SIZE );
Counter mm_internal_type ( "MMINTERNALTYPE", REG_SIZE );

Counter mm_external_arith("MMEXTERNALARITH", REG_SIZE);
Bus mm_hazard_bus("MMHAZARDBUS", REG_SIZE);

// $(filename)
