/**
 * hw_mem
 *
 * Author   Jonathan Lo < >
 */
#include "includes.h"
extern Bus dbus_m;
extern Bus mm_controlbus;
extern Bus addrbus_m;
extern Counter mm_internal_arith;
extern Counter mm_internal_type;

extern Counter mm_external_arith; //used for 3-tick read-after-write hazard
extern Bus mm_hazard_bus; 
// $(filename)
