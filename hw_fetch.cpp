/**
 * hw_issue
 *
 * Author   Jonathan Lo < >
 */
#include "hw_fetch.h"

Counter pc_load ( "PCLOAD", REG_SIZE );
Counter pc_f ( "PCF", REG_SIZE );
Counter pc_fi ( "PCFI", REG_SIZE );
Counter ir_fi ( "IRFI", REG_SIZE );

Bus pcbus_load ( "PCBUSLOAD", REG_SIZE );
Bus pcbus_f1 ( "PCBUSF1", REG_SIZE );
Bus pcbus_f2 ( "PCBUSF2", REG_SIZE );
Bus irbus_f2 ( "IRBUS_F2", REG_SIZE );

// $(filename)
