
#include "hw_issue.h"
Bus pcbus_i1("PCBUS_I1", REG_SIZE);
Bus irbus_i1("IRBUS_I1", REG_SIZE);
Bus irbus_i2("IRBUS_I2", REG_SIZE);
Bus pcbus_i2("PCBUS_I2", REG_SIZE);
Clearable pc_i("PC_I", REG_SIZE);
Clearable ir_i("IR_I", REG_SIZE);
Clearable aux_i("AUX_I", REG_SIZE);
Clearable shift11_g("SHIFT11G", REG_SIZE, 11);
Clearable dispmask_g("DISPMASKG", REG_SIZE, 2097151);
BusALU leftShift_alu();

