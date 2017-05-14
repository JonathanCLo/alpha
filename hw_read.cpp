/**
 * hw_read
 *
 * Author   Jonathan Lo < >
 */
#include "hw_read.h"

extern Bus irbus_r1 ( "IRBUSR1", REG_SIZE );
extern Bus irbus_r2 ( "IRBUSR2", REG_SIZE );
extern Bus pcbus_r1 ( "PCBUSR1", REG_SIZE );
extern Bus pcbus_r2 ( "PCBUSR2", REG_SIZE );

extern Bus destbus_r2 ( "DESTBUSR2", REG_SIZE );
extern Clearable ir_r ( "IRR", REG_SIZE );
extern Clearable ir_ir ( "IRIR", REG_SIZE );

extern BusALU signExtalu_r ( "SIGNEXTALUR", REG_SIZE );
extern Clearable npc_ir ( "NPCIR", REG_SIZE );
extern Clearable dest_r ( "DEST", REG_SIZE );

extern BusALU litalu_r1 ( "LITALUR1", REG_SIZE );
extern BusALU litalu_r2 ( "LITALUR2", REG_SIZE );
extern Clearable literal_r ( "LITERALR", REG_SIZE );

extern Bus rabus_r1 ( "RABUSR1", REG_SIZE );
extern Bus rbbus_r1 ( "RBBUSR1", REG_SIZE );
extern Bus rcbus_r1 ( "RCBUSR1", REG_SIZE );
extern Bus rabus_r2 ( "RABUSR2", REG_SIZE );
extern Bus rbbus_r2 ( "RBBUSR2", REG_SIZE );
extern Bus rcbus_r2 ( "RCBUSR2", REG_SIZE );

extern Clearbale ra_r ( "RAR", REG_SIZE );
extern Clearable rb_r ( "RBR", REG_SIZE );
extern Clearable rc_r ( "RCR", REG_SIZE );

extern Bus changePC_bus ( "CHANGEPCBUS", REG_SIZE );

extern BusALU destalu_r ( "DESTALUR", REG_SIZE );
// $(filename)
