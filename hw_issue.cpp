
#include "hw_issue.h"
extern Bus pcbus_i1("PCBUS_I1", REG_SIZE);
extern Bus irbus_i1("IRBUS_I1", REG_SIZE);
extern Bus irbus_i2("IRBUS_I2", REG_SIZE);
extern Bus pcbus_i2("PCBUS_I2", REG_SIZE);
extern Clearable pc_i("PC_I", REG_SIZE);
extern Clearable ir_i("IR_I", REG_SIZE);
extern Clearable aux_i("AUX_I", REG_SIZE);
extern Clearable shift11_g("SHIFT11G", REG_SIZE, 11);
extern Clearable dispmask_g("DISPMASKG", REG_SIZE, 2097151);
extern BusALU leftShift_alu();

