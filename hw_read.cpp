/**
 * hw_read
 *
 * Author   Jonathan Lo < >
 */
#include "includes.h"

Clearable ir_r ( "IR_R", REG_SIZE );
Clearable pc_r ( "PC_R", REG_SIZE );
Clearable ra_r ( "RAR", REG_SIZE );
Clearable rb_r ( "RBR", REG_SIZE );
Clearable rc_r ( "RCR", REG_SIZE );
Clearable literal_r ( "LITERAL_R", REG_SIZE );
Clearable dest_r ( "DEST_R", REG_SIZE );

Clearable ir_re ( "IR_RE", REG_SIZE );
Clearable pc_re ( "PC_RE", REG_SIZE );
Clearable ra_re ( "RA_RE", REG_SIZE );
Clearable rb_re ( "RB_RE", REG_SIZE );
Clearable rc_re ( "RC_RE", REG_SIZE );
Clearable literal_re ( "LITERAL_RE", REG_SIZE );
Clearable disp_re ( "DISP_RE", REG_SIZE );

Bus irbus_r1 ( "IRBUS_R1", REG_SIZE );
Bus irbus_r2 ( "IRBUS_R2", REG_SIZE );
Bus pcbus_r1 ( "PCBUS_R1", REG_SIZE );
Bus pcbus_r2 ( "PCBUS_R2", REG_SIZE );
Bus destbus_r2 ( "DESTBUS_R2", REG_SIZE );
Bus rabus_r1 ( "RABUS_R1", REG_SIZE );
Bus rbbus_r1 ( "RBBUS_R1", REG_SIZE );
Bus rcbus_r1 ( "RCBUS_R1", REG_SIZE );
Bus rabus_r2 ( "RABUS_R2", REG_SIZE );
Bus rbbus_r2 ( "RBBUS_R2", REG_SIZE );
Bus rcbus_r2 ( "RCBUS_R2", REG_SIZE );
Bus changePC_bus ( "CHANGEPCBUS", REG_SIZE );

BusALU signExtalu_r ( "SIGNEXTALU_R", REG_SIZE );
BusALU litalu_r1 ( "LITALU_R1", REG_SIZE );
BusALU litalu_r2 ( "LITALU_R2", REG_SIZE );
BusALU destalu_r ( "DESTALU_R", REG_SIZE );
// $(filename)
