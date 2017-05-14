/**
 * hw_read
 *
 * Author   Jonathan Lo < >
 */
#include "includes.h"

Bus irbus_r1 ( "IRBUSR1", REG_SIZE );
Bus irbus_r2 ( "IRBUSR2", REG_SIZE );
Bus pcbus_r1 ( "PCBUSR1", REG_SIZE );
Bus pcbus_r2 ( "PCBUSR2", REG_SIZE );

Bus destbus_r2 ( "DESTBUSR2", REG_SIZE );
Clearable ir_r ( "IRR", REG_SIZE );
Clearable ir_ir ( "IRIR", REG_SIZE );
Clearable pc_r ( "PC_R", REG_SIZE );
Clearable pc_ir ( "PC_IR", REG_SIZE );

BusALU signExtalu_r ( "SIGNEXTALUR", REG_SIZE );
Clearable npc_ir ( "NPCIR", REG_SIZE );
Clearable dest_r ( "DEST", REG_SIZE );

BusALU litalu_r1 ( "LITALUR1", REG_SIZE );
BusALU litalu_r2 ( "LITALUR2", REG_SIZE );
Clearable literal_r ( "LITERALR", REG_SIZE );

Bus rabus_r1 ( "RABUSR1", REG_SIZE );
Bus rbbus_r1 ( "RBBUSR1", REG_SIZE );
Bus rcbus_r1 ( "RCBUSR1", REG_SIZE );
Bus rabus_r2 ( "RABUSR2", REG_SIZE );
Bus rbbus_r2 ( "RBBUSR2", REG_SIZE );
Bus rcbus_r2 ( "RCBUSR2", REG_SIZE );

Clearable ra_r ( "RAR", REG_SIZE );
Clearable rb_r ( "RBR", REG_SIZE );
Clearable rc_r ( "RCR", REG_SIZE );

Bus changePC_bus ( "CHANGEPCBUS", REG_SIZE );

BusALU destalu_r ( "DESTALUR", REG_SIZE );
// $(filename)
