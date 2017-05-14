/**
 * hw_read
 *
 * Author   Jonathan Lo < >
 */
#include "includes.h"

extern Clearable ir_r;
extern Clearable pc_r;
extern Clearable ra_r;
extern Clearable rb_r;
extern Clearable rc_r;
extern Clearable literal_r;
extern Clearable dest_r;

extern Clearable ir_re;
extern Clearable pc_re;
extern Clearable ra_re;
extern Clearable rb_re;
extern Clearable rc_re;
extern Clearable literal_re;
extern Clearable disp_re;

extern Bus irbus_r1;
extern Bus irbus_r2;
extern Bus pcbus_r1;
extern Bus pcbus_r2;
extern Bus destbus_r2;
extern Bus rabus_r1;
extern Bus rbbus_r1;
extern Bus rcbus_r1;
extern Bus rabus_r2;
extern Bus rbbus_r2;
extern Bus rcbus_r2;
extern Bus changePC_bus;

extern BusALU signExtalu_r;
extern BusALU litalu_r1;
extern BusALU litalu_r2;
extern BusALU destalu_r;
// hw_read
