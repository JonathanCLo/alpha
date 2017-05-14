/**
 * make_connections
 *
 * Author   Nathan Castle   < >
 *          Jonathan Lo     < >
 */

#include "includes.h"

void make_connections ( );
void make_connections_fetch ( );
void make_connections_issue ( );
void make_connections_read ( );
void make_connections_execute ( );
void make_connections_memory ( );
void make_connections_auxillary ( );

/**
 * make_connections
 * establishes all the wiring and connections of the hardware
 *
 */
void make_connections ( )
{
    make_connections_fetch ( );
    make_connections_issue ( );
    make_connections_read ( );
    make_connections_execute ( );
    make_connections_memory ( );
    make_connections_auxillary ( );
}

/**
 * make_connections_fetch
 * creates the connections for fetch stage
 *
 */
void make_connections_fetch ( )
{
    // stage 1
    pc_load.connectsTo ( pcbus_load.IN ( ) );
    instr_cache.MAR ( ).connectsTo ( pcbus_load.OUT ( ) );
    
    pc_load.connectsTo ( instr_cache.READ ( ) );
    pc_load.connectsTo ( pcbus_f1.IN ( ) );
    pc_f.connectsTo ( pcbus_f1.OUT ( ) );

    // stage 2
    pc_f.connectsTo ( pcbus_f2.IN ( ) );
    pc_fi.connectsTo ( pcbus_f2.OUT ( ) );

    noop_g.connectsTo ( irbus_f2.IN ( ) );
    ir_fi.connectsTo ( irbus_f2.OUT ( ) );

    ir_fi.connectsTo ( instr_cache.READ ( ) );
} // make_connections_fetch

/**
 * make_connections_issue
 * creates the connections for issue stage
 *
 */
void make_connections_issue ( )
{
    // stage 1s
    pc_fi.connectsTo ( pcbus_i1.IN ( ) );
    pc_i.connectsTo ( pcbus_i1.OUT ( ) );

    pc_i.connectsTo ( pcbus_i2.IN ( ) );
    pc_ir.connectsTo ( pcbus_i2.OUT ( ) );

    ir_fi.connectsTo ( irbus_i1.IN ( ) );
    ir_i.connectsTo ( irbus_i1.OUT ( ) );

    // stage 2
    pc_i.connectsTo ( pcbus_i2.IN ( ) );
    pc_ir.connectsTo ( pcbus_i2.OUT ( ) );

    ir_fi.connectsTo ( destalu_i.OP1 ( ) );
    pc_fi.connectsTo ( destalu_i.OP1 ( ) );
    dispmask_g.connectsTo ( destalu_i.OP2 ( ) );
    aux_i.connectsTo ( destalu_i.OUT ( ) );

    aux_i.connectsTo ( leftShift_alu.OP1 ( ) );
    shift11_g.connectsTo ( leftShift_alu.OP2 ( ) );
    npc_ir.connectsTo ( leftShift_alu.OUT ( ) );

} // make_connections_issue

/**
 * make_connections_read
 * creates the connections for read stage
 *
 */
void make_connections_read ( )
{
    // stage 1
    pc_ir.connectsTo ( pcbus_r1.IN ( ) );
    pc_r.connectsTo ( pcbus_r1.OUT ( ) );

    ir_ir.connectsTo ( irbus_r1.IN ( ) );
    ir_r.connectsTo ( irbus_r1.OUT ( ) );

    ir_ir.connectsTo ( litalu_r1.OP1 ( ) );
    literalmask_g.connectsTo ( litalu_r1.OP2 ( ) );
    literal_r.connectsTo ( litalu_r1.OUT ( ) );

    npc_ir.connectsTo ( signExtalu_r.OP1 ( ) );
    dispmask_g.connectsTo ( signExtalu_r.OP2 ( ) );
    shift7_g.connectsTo ( signExtalu_r.OP2 ( ) );
    dest_r.connectsTo ( signExtalu_r.OUT ( ) );

    dest_r.connectsTo ( changePC_bus.IN ( ) );
    pc_load.connectsTo ( changePC_bus.OUT ( ) );

    // connect rx to rabus_r1
    for ( int i = 0; i < 32; i++ ) {
        ( *regfile[i] ).connectsTo ( rabus_r1.IN ( ) );
    }

    // connect rx to rbbus_r1
    for ( int i = 0; i < 32; i++ ) {
        ( *regfile[i] ).connectsTo ( rbbus_r1.IN ( ) );
    }

    // connect rx to rcbus_r1
    for ( int i = 0; i < 32; i++ ) {
        ( *regfile[i] ).connectsTo ( rcbus_r1.IN ( ) );
    }

    ra_r.connectsTo ( rabus_r1.OUT ( ) );
    rb_r.connectsTo ( rbbus_r1.OUT ( ) );
    rc_r.connectsTo ( rcbus_r1.OUT ( ) );

    // stage 2

    ra_r.connectsTo ( rabus_r2.IN ( ) );
    rb_r.connectsTo ( rbbus_r2.IN ( ) );
    rc_r.connectsTo ( rcbus_r2.IN ( ) );
    ra_re.connectsTo ( rabus_r2.OUT ( ) );
    rb_re.connectsTo ( rbbus_r2.OUT ( ) );
    rc_re.connectsTo ( rcbus_r2.OUT ( ) );

    rb_r.connectsTo ( destalu_r.OP1 ( ) );
    not3_g.connectsTo ( destalu_r.OP2 ( ) );
    pc_load.connectsTo ( destalu_r.OUT ( ) );

    pc_r.connectsTo ( pcbus_r2.IN ( ) );
    pc_re.connectsTo ( pcbus_r2.OUT ( ) );

    literal_r.connectsTo ( litalu_r2.OP1 ( ) );
    literalShift_g.connectsTo ( litalu_r2.OP2 ( ) );
    literal_re.connectsTo ( litalu_r2.OUT ( ) );

    ir_r.connectsTo ( irbus_r2.IN ( ) );
    noop_g.connectsTo ( irbus_r2.IN ( ) );
    ir_re.connectsTo ( irbus_r2.OUT ( ) );

    dest_r.connectsTo ( destbus_r2.IN ( ) );
    disp_re.connectsTo ( destbus_r2.OUT ( ) );
} // make_connections_read

/**
 * make_connections_execute
 *
 *
 */
void make_connections_execute ( )
{
    ra_re.connectsTo ( arith_alu.OP1 ( ) );
    const2_g.connectsTo ( arith_alu.OP2 ( ) );
    const3_g.connectsTo ( arith_alu.OP2 ( ) );
    rb_re.connectsTo ( addr_alu.OP1 ( ) );
    literal_re.connectsTo ( addr_alu.OP1 ( ) );
    ex_internal_arith.connectsTo ( arith_alu.OUT ( ) );
    ex_internal_addr.connectsTo ( addr_alu.OUT ( ) );

    ir_re.connectsTo ( irbus_e1.IN ( ) );
    ex_internal_ir.connectsTo ( irbus_e1.OUT ( ) );
    ex_internal_ir.connectsTo ( irbus_e2.IN ( ) );
    ir_em.connectsTo ( irbus_e2.OUT ( ) );

    disp_re.connectsTo ( shift_alu.OP1 ( ) );
    const16_g.connectsTo ( shift_alu.OP2 ( ) );
    ex_internal_shift.connectsTo ( shift_alu.OUT ( ) );

    ex_internal_arith.connectsTo ( arith_alu.OP1 ( ) );
    ex_internal_addr.connectsTo ( arith_alu.OP2 ( ) );
    out_em.connectsTo ( arith_alu.OUT ( ) );

    ex_internal_addr.connectsTo ( addr_alu.OP1 ( ) );
    ex_internal_shift.connectsTo ( addr_alu.OP2 ( ) );
    data_cache.MAR ( ).connectsTo ( addr_alu.OUT ( ) );

    mem_flag.connectsTo ( read_mem.OUT ( ) );
    mem_flag.connectsTo ( write_mem.OUT ( ) );
    mem_flag.connectsTo ( no_mem.OUT ( ) );
    mem_flag.connectsTo ( writeback.OUT ( ) );

} // make_connections_execute

/**
 * make_connections_memory
 *
 *
 */
void make_connections_memory ( )
{
    mm_internal_type.connectsTo ( mm_controlbus.OUT ( ) );

    out_em.connectsTo ( dbus_m.IN ( ) );
    mm_internal_arith.connectsTo ( dbus_m.OUT ( ) );
    mm_internal_arith.connectsTo ( data_cache.WRITE ( ) );

    data_cache.MAR ( ).connectsTo ( addrbus_m.OUT ( ) );

    for ( int i = 0; i < 32; i++ ) {
        ( *regfile[i] ).connectsTo ( dbus_m.OUT ( ) );
    }

    for ( int i = 0; i < 32; i++ ) {
        ( *regfile[i] ).connectsTo ( data_cache.READ ( ) );
    }

} // make_connections_memory

/**
 * make_connections_auxillary
 *
 *
 */
void make_connections_auxillary ( )
{ }

// make_onnections end
