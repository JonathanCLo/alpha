
#include "hw_fetch.h"

Counter pc_load ("PCLOAD", REG_SIZE);
Counter pc_f("PCF", REG_SIZE);
Counter pc_fi("PCFI", REG_SIZE);
Counter ir_fi("IRFI", REG_SIZE);
Counter noop_g("NOOPG", REG_SIZE);

Bus pcbus_load("PCBUSLOAD", REG_SIZE);
Bus pcbus_f1("PCBUSF1", REG_SIZE);
Bus pcbus_f2("PCBUSF2", REG_SIZE);
Bus irfi_noop_bus("IRFINOOPBUS", REG_SIZE);

bool ir_purge = false;
