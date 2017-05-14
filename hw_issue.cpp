/**
 * hw_issue
 *
 * Author   Jonathan Lo < >
 */
#include "hw_issue.h"
Bus pcbus_i1 ( "PCBUS_I1", REG_SIZE );
Bus irbus_i1 ( "IRBUS_I1", REG_SIZE );
Bus irbus_i2 ( "IRBUS_I2", REG_SIZE );
Bus pcbus_i2 ( "PCBUS_I2", REG_SIZE );
Clearable pc_i ( "PC_I", REG_SIZE );
Clearable ir_i ( "IR_I", REG_SIZE );
Clearable aux_i ( "AUX_I", REG_SIZE );
BusALU leftShift_alu ( "LEFTSHIFT_ALU", REG_SIZE );
// $(filename)
