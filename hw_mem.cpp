#include "hw_mem.h"

Bus dbus_m("DBUSM", REG_SIZE);
Counter out_em("OUTEM", REG_SIZE);
Bus mm_controlbus("MMCONTROLBUS", REG_SIZE);
Counter mem_flag("MEMFLAG", REG_SIZE);
Counter mm_internal_arith("MMINTERNALARITH", REG_SIZE);
