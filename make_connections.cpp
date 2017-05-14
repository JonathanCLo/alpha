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
    pc_load.connectsTo ( pcbus_load.IN ( ) );
    pc_load.connectsTo ( pcbus_f1.IN ( ) );
    pc_f.connectsTo ( pcbus_f1.OUT ( ) );
    instr_cache.MAR ( ).connectsTo ( pcbus_load.OUT ( ) );

    pc_f.connectsTo ( pcbus_f2.IN ( ) );
    pc_fi.connectsTo ( pcbus_f2.OUT ( ) );

    noop_g.connectsTo ( irfi_noop_bus.IN ( ) );
    ir_fi.connectsTo ( irfi_noop_bus.OUT ( ) );

    ir_fi.connectsTo ( instr_cache.READ ( ) );
} // make_connections_fetch

/**
 * make_connections_issue
 * creates the connections for issue stage
 *
 */
void make_connections_issue ( )
{
    pc_fi.connectsTo ( pcbus_i1.IN ( ) );
    pc_i.connectsTo ( pcbus_i1.OUT ( ) );
    pc_i.connectsTo ( pcbus_i2.IN ( ) );
    pc_ir.connectsTo ( pcbus_i2.OUT ( ) );

    ir_fi.connectsTo ( irbus_i1.IN ( ) );
    ir_i.connectsTo ( irbus_i1.OUT ( ) );
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
    pc_ir.connectsTo ( pcbus_r1.IN ( ) );
    pc_r.connectsTo ( pcbus_r1.OUT ( ) );

    ir_ir.connectsTo ( irbus_r1.IN ( ) );
    ir_r.connectsTo ( irbus_r1.OUT ( ) );

    ir_ir.connectsTo ( litalu_r1.OP1 ( ) );
    literalmask_g.connectsTo ( litalu_r1.OP2 ( ) );
    literal_r.connectsTo ( litalu_r1.OUT ( ) );

    npc_ir.connecsTo ( signExtalu_r.OP1 ( ) );
    dispmask_g.connectsTo ( signExtalu_r.OP2 ( ) );
    shift7_g.connectsTo ( signExtalu_r.OP2 ( ) );
    dest_r.connectsTo ( signExtalu_r.OUT ( ) );

    dest_r.connectsTo ( changePC_bus.IN ( ) );
    pc_load.connecsTo ( changePC_bus.OUT ( ) );

    // connect rx to rabus_r1
    for ( int i = 0; i < 32; i++ ) {
        regfile[i].connectsTo ( rabus_r1.IN ( ) );
    }

    // connect rx to rbbus_r1
    for ( int i = 0; i < 32; i++ ) {
        regfile[i].connectsTo ( rbbus_r1.IN ( ) );
    }

    // connect rx to rcbus_r1
    for ( int i = 0; i < 32; i++ ) {
        regfile[i].connectsTo ( rcbus_r1.IN ( ) );
    }

    ra_r.connectsTo ( rabus_r1.OUT ( ) );
    rb_r.connectsTo ( rbbus_r1.OUT ( ) );
    rc_r.connectsTo ( rcbus_r1.OUT ( ) );

    ra_r.connectsTo ( rabus_r2.IN ( ) );
    rb_r.connectsTo ( rbbus_r2.IN ( ) );
    rc_r.connectsTo ( rcbus_r2.IN ( ) );
    ra_re.connectsTO ( rabus_r2.OUT ( ) );
    rb_re.connectsTO ( rbbus_r2.OUT ( ) );
    rc_re.connectsTO ( rcbus_r2.OUT ( ) );

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
    ex_internal_arith.connectsTo ( arith_alu.OUT ( ) );
    ex_internal_shift.connectsTo ( shift_alu.OUT ( ) );
    ex_internal_addr.connectsTo ( addr_alu.OUT ( ) );

    ex_out_addr.connectsTo ( addr_alu.OUT ( ) );
    ex_out_arith.connectsTo ( addr_alu.OUT ( ) );

    ex_internal_ir.connectsTo ( irbus_e.OUT ( ) );
    ir_re.connectsTo ( irbus_e.IN ( ) ); //protects from change to ir after phase 1
    pc_re.connectsTo ( arith_alu.OP1 ( ) );
    ra_re.connectsTo ( arith_alu.OP1 ( ) );
    ex_internal_arith.connectsTo ( arith_alu.OP1 ( ) );
    exec_const_2.connectsTo ( arith_alu.OP2 ( ) );
    exec_const_3.connectsTo ( arith_alu.OP2 ( ) );
    ex_internal_addr.connectsTo ( arith_alu.OP2 ( ) );

    pc_re.connectsTo ( shift_alu.OP1 ( ) );
    disp_re.connectsTo ( shift_alu.OP1 ( ) );
    exec_const_16.connectsTo ( shift_alu.OP2 ( ) );

    rb_re.connectsTo ( addr_alu.OP1 ( ) );
    disp_re.connectsTo ( addr_alu.OP1 ( ) );
    li_re.connectsTo ( addr_alu.OP1 ( ) );
    ex_internal_addr.connectsTo ( addr_alu.OP1 ( ) );
    ex_internal_arith.connectsTo ( addr_alu.OP1 ( ) );
    ex_internal_shift.connectsTo ( addr_alu.OP2 ( ) );
    ex_internal_addr.connectsTo ( addr_alu.OP2 ( ) );
    /*
     *  fout_e.connectsTo ( outbus_em.OUT ( ) );
     *  fout_e.connectsTo ( outbus_em.IN ( ) );
     *  fout_e.connectsTo ( arithop1_ebus.IN ( ) );
     *  fout_e.connectsTo ( shiftop1_ebus.IN ( ) );
     *  fout_e.connectsTo ( addrop1_ebus.IN ( ) );
     *
     *  arith_op1.connectsTo ( arithop1_ebus.OUT ( ) );
     *  arith_op2.connectsTo ( arithop2_ebus.OUT ( ) );
     *  arith_op1.connectsTo ( arith_alu.OP1 ( ) );
     *  arith_op2.connectsTo ( arith_alu.OP2 ( ) );
     *  shift_op1.connectsTo ( shiftop1_ebus.OUT ( ) );
     *  shift_op2.connectsTo ( shiftop2_ebus.OUT ( ) );
     *  shift_op1.connectsTo ( shift_alu.OP1 ( ) );
     *  shift_op2.connectsTo ( shift_alu.OP2 ( ) );
     *  addr_op1.connectsTo ( addrop1_ebus.OUT ( ) );
     *  addr_op2.connectsTo ( addrop2_ebus.OUT ( ) );
     *  addr_op1.connectsTo ( addr_alu.OP1 ( ) );
     *  addr_op2.connectsTo ( addr_alu.OP2 ( ) );
     *
     *  pc_re.connectsTo ( pcbus_e.IN ( ) );
     *  pc_re.connectsTo ( arithop1_ebus.IN ( ) );
     *  pc_re.connectsTo ( arithop2_ebus.IN ( ) );
     *
     *  ir_re.connectsTo ( irbus_e.IN ( ) );
     *  ir_em.connectsTo ( irbus_e.OUT ( ) );
     *
     *  ra_re.connectsTo ( arithop1_ebus.IN ( ) );
     *  ra_re.connectsTo ( arithop2_ebus.IN ( ) );
     *  rb_re.connectsTo ( arithop1_ebus.IN ( ) );
     *  rb_re.connectsTo ( arithop2_ebus.IN ( ) );
     *  aux_re.connectsTo ( arithop1_ebus.IN ( ) );
     *  aux_re.connectsTo ( arithop2_ebus.IN ( ) );
     *
     *  ra_re.connectsTo ( shiftop1_ebus.IN ( ) );
     *  ra_re.connectsTo ( shiftop2_ebus.IN ( ) );
     *  rb_re.connectsTo ( shiftop1_ebus.IN ( ) );
     *  rb_re.connectsTo ( shiftop2_ebus.IN ( ) );
     *  rc_re.connectsTo ( shiftop1_ebus.IN ( ) );
     *  rc_re.connectsTo ( shiftop2_ebus.IN ( ) );
     *  aux_re.connectsTo ( shiftop1_ebus.IN ( ) );
     *  aux_re.connectsTo ( shiftop2_ebus.IN ( ) );
     *
     *  pc_re.connectsTo ( addrop1_ebus.IN ( ) );
     *
     *  pc_em.connectsTo ( pcbus_e.OUT ( ) );
     *  out_em.connectsTo ( arith_alu.OUT ( ) );
     *  out_em.connectsTo ( shift_alu.OUT ( ) );
     *  out_em.connectsTo ( outbus_em.IN ( ) );
     *
     *  addr_em.connectsTo ( addr_alu.OUT ( ) );
     */
} // make_connections_execute

/**
 * make_connections_memory
 *
 *
 */
void make_connections_memory ( )
{

    mem_flag.connectsTo ( no_mem.OUT ( ) );
    mem_flag.connectsTo ( read_mem.OUT ( ) );
    mem_flag.connectsTo ( write_mem.OUT ( ) );
    mem_flag.connectsTo ( writeback.OUT ( ) );
    mem_flag.connectsTo ( mm_controlbus.IN ( ) );
    mm_internal_type.connectsTo ( mm_controlbus.OUT ( ) );
    mm_internal_arith.connectsTo ( dbus_m.OUT ( ) );

    addr_em.connectsTo ( addrbus_m.IN ( ) );
    data_cache.MAR ( ).connectsTo ( addrbus_m.OUT ( ) );

    out_em.connectsTo ( data_cache.WRITE ( ) );
    out_em.connectsTo ( dbus_m.IN ( ) );

    r0.connectsTo ( dbus_m.OUT ( ) );
    r1.connectsTo ( dbus_m.OUT ( ) );
    r2.connectsTo ( dbus_m.OUT ( ) );
    r3.connectsTo ( dbus_m.OUT ( ) );
    r4.connectsTo ( dbus_m.OUT ( ) );
    r5.connectsTo ( dbus_m.OUT ( ) );
    r6.connectsTo ( dbus_m.OUT ( ) );
    r7.connectsTo ( dbus_m.OUT ( ) );
    r8.connectsTo ( dbus_m.OUT ( ) );
    r9.connectsTo ( dbus_m.OUT ( ) );
    r10.connectsTo ( dbus_m.OUT ( ) );
    r11.connectsTo ( dbus_m.OUT ( ) );
    r12.connectsTo ( dbus_m.OUT ( ) );
    r13.connectsTo ( dbus_m.OUT ( ) );
    r14.connectsTo ( dbus_m.OUT ( ) );
    r15.connectsTo ( dbus_m.OUT ( ) );
    r16.connectsTo ( dbus_m.OUT ( ) );
    r17.connectsTo ( dbus_m.OUT ( ) );
    r18.connectsTo ( dbus_m.OUT ( ) );
    r19.connectsTo ( dbus_m.OUT ( ) );
    r20.connectsTo ( dbus_m.OUT ( ) );
    r21.connectsTo ( dbus_m.OUT ( ) );
    r22.connectsTo ( dbus_m.OUT ( ) );
    r23.connectsTo ( dbus_m.OUT ( ) );
    r24.connectsTo ( dbus_m.OUT ( ) );
    r25.connectsTo ( dbus_m.OUT ( ) );
    r26.connectsTo ( dbus_m.OUT ( ) );
    r27.connectsTo ( dbus_m.OUT ( ) );
    r28.connectsTo ( dbus_m.OUT ( ) );
    r29.connectsTo ( dbus_m.OUT ( ) );
    r30.connectsTo ( dbus_m.OUT ( ) );
    r31.connectsTo ( dbus_m.OUT ( ) );

    r0.connectsTo ( data_cache.READ ( ) );
    r1.connectsTo ( data_cache.READ ( ) );
    r2.connectsTo ( data_cache.READ ( ) );
    r3.connectsTo ( data_cache.READ ( ) );
    r4.connectsTo ( data_cache.READ ( ) );
    r5.connectsTo ( data_cache.READ ( ) );
    r6.connectsTo ( data_cache.READ ( ) );
    r7.connectsTo ( data_cache.READ ( ) );
    r8.connectsTo ( data_cache.READ ( ) );
    r9.connectsTo ( data_cache.READ ( ) );
    r10.connectsTo ( data_cache.READ ( ) );
    r11.connectsTo ( data_cache.READ ( ) );
    r12.connectsTo ( data_cache.READ ( ) );
    r13.connectsTo ( data_cache.READ ( ) );
    r14.connectsTo ( data_cache.READ ( ) );
    r15.connectsTo ( data_cache.READ ( ) );
    r16.connectsTo ( data_cache.READ ( ) );
    r17.connectsTo ( data_cache.READ ( ) );
    r18.connectsTo ( data_cache.READ ( ) );
    r19.connectsTo ( data_cache.READ ( ) );
    r20.connectsTo ( data_cache.READ ( ) );
    r21.connectsTo ( data_cache.READ ( ) );
    r22.connectsTo ( data_cache.READ ( ) );
    r23.connectsTo ( data_cache.READ ( ) );
    r24.connectsTo ( data_cache.READ ( ) );
    r25.connectsTo ( data_cache.READ ( ) );
    r26.connectsTo ( data_cache.READ ( ) );
    r27.connectsTo ( data_cache.READ ( ) );
    r28.connectsTo ( data_cache.READ ( ) );
    r29.connectsTo ( data_cache.READ ( ) );
    r30.connectsTo ( data_cache.READ ( ) );
    r31.connectsTo ( data_cache.READ ( ) );

} // make_connections_memory

/**
 * make_connections_auxillary
 *
 *
 */
void make_connections_auxillary ( )
{ }

// make_onnections end
