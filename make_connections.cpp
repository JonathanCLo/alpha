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

/**
 * make_connections
 *  establishes all the wiring and connections of the hardware
 *
 */
void make_connections ( )
{
    make_connections_fetch ( );
    make_connections_issue ( );
    make_connections_read ( );
    make_connections_execute ( );
    //TODO make_connections_memory ( );
}

/**
 * make_connections
 *
 *
 */
void make_connections_fetch ( )
{
    pc_f.connectsTo ( pcbus_f.IN ( ) );
    pc_f.connectsTo ( instr_cache.READ ( ) );
    pc_fi.connectsTo ( pcbus_f.OUT ( ) );

    instr_cache.MAR ( ).connectsTo ( pcbus_f.OUT ( ) );

    ir_fi.connectsTo ( instr_cache.READ ( ) );
}

/**
 * make_connections_issue
 *
 *
 */
void make_connections_issue ( )
{
    pc_fi.connectsTo ( pcbus_i.IN ( ) );
    pc_i.connectsTo ( pcbus_i.OUT ( ) );
    pc_i.connectsTo ( pcbus_i.IN ( ) );
    pc_i.connectsTo ( pc_alu.OP1 ( ) );
    pc_i.connectsTo ( pc_alu.OUT ( ) );
    pc_ir.connectsTo ( pcbus_i.OUT ( ) );

    aux_i.connectsTo ( pc_alu.OP2 ( ) );

    ir_fi.connectsTo ( irbus_i.IN ( ) );
    ir_i.connectsTo ( irbus_i.OUT ( ) );
    ir_i.connectsTo ( irbus_i.IN ( ) );
    ir_ir.connectsTo ( irbus_i.OUT ( ) );

} // make_connections_issue

/**
 * make_connections_read
 *
 *
 */
void make_connections_read ( )
{
    pc_ir.connectsTo ( pcbus_r.IN ( ) );
    pc_r.connectsTo ( pcbus_r.OUT ( ) );
    pc_r.connectsTo ( pcbus_r.IN ( ) );
    pc_re.connectsTo ( pcbus_r.OUT ( ) );

    ir_ir.connectsTo ( irbus_r.IN ( ) );
    ir_r.connectsTo ( irbus_r.OUT ( ) );
    ir_r.connectsTo ( irbus_r.IN ( ) );
    ir_re.connectsTo ( irbus_r.OUT ( ) );

    r0.connectsTo ( rabus_r.IN ( ) );
    r1.connectsTo ( rabus_r.IN ( ) );
    r2.connectsTo ( rabus_r.IN ( ) );
    r3.connectsTo ( rabus_r.IN ( ) );
    r4.connectsTo ( rabus_r.IN ( ) );
    r5.connectsTo ( rabus_r.IN ( ) );
    r6.connectsTo ( rabus_r.IN ( ) );
    r7.connectsTo ( rabus_r.IN ( ) );
    r8.connectsTo ( rabus_r.IN ( ) );
    r9.connectsTo ( rabus_r.IN ( ) );
    r10.connectsTo ( rabus_r.IN ( ) );
    r11.connectsTo ( rabus_r.IN ( ) );
    r12.connectsTo ( rabus_r.IN ( ) );
    r13.connectsTo ( rabus_r.IN ( ) );
    r14.connectsTo ( rabus_r.IN ( ) );
    r15.connectsTo ( rabus_r.IN ( ) );
    r16.connectsTo ( rabus_r.IN ( ) );
    r17.connectsTo ( rabus_r.IN ( ) );
    r18.connectsTo ( rabus_r.IN ( ) );
    r19.connectsTo ( rabus_r.IN ( ) );
    r20.connectsTo ( rabus_r.IN ( ) );
    r21.connectsTo ( rabus_r.IN ( ) );
    r22.connectsTo ( rabus_r.IN ( ) );
    r23.connectsTo ( rabus_r.IN ( ) );
    r24.connectsTo ( rabus_r.IN ( ) );
    r25.connectsTo ( rabus_r.IN ( ) );
    r26.connectsTo ( rabus_r.IN ( ) );
    r27.connectsTo ( rabus_r.IN ( ) );
    r28.connectsTo ( rabus_r.IN ( ) );
    r29.connectsTo ( rabus_r.IN ( ) );
    r30.connectsTo ( rabus_r.IN ( ) );
    r31.connectsTo ( rabus_r.IN ( ) );

    r0.connectsTo ( rbbus_r.IN ( ) );
    r1.connectsTo ( rbbus_r.IN ( ) );
    r2.connectsTo ( rbbus_r.IN ( ) );
    r3.connectsTo ( rbbus_r.IN ( ) );
    r4.connectsTo ( rbbus_r.IN ( ) );
    r5.connectsTo ( rbbus_r.IN ( ) );
    r6.connectsTo ( rbbus_r.IN ( ) );
    r7.connectsTo ( rbbus_r.IN ( ) );
    r8.connectsTo ( rbbus_r.IN ( ) );
    r9.connectsTo ( rbbus_r.IN ( ) );
    r10.connectsTo ( rbbus_r.IN ( ) );
    r11.connectsTo ( rbbus_r.IN ( ) );
    r12.connectsTo ( rbbus_r.IN ( ) );
    r13.connectsTo ( rbbus_r.IN ( ) );
    r14.connectsTo ( rbbus_r.IN ( ) );
    r15.connectsTo ( rbbus_r.IN ( ) );
    r16.connectsTo ( rbbus_r.IN ( ) );
    r17.connectsTo ( rbbus_r.IN ( ) );
    r18.connectsTo ( rbbus_r.IN ( ) );
    r19.connectsTo ( rbbus_r.IN ( ) );
    r20.connectsTo ( rbbus_r.IN ( ) );
    r21.connectsTo ( rbbus_r.IN ( ) );
    r22.connectsTo ( rbbus_r.IN ( ) );
    r23.connectsTo ( rbbus_r.IN ( ) );
    r24.connectsTo ( rbbus_r.IN ( ) );
    r25.connectsTo ( rbbus_r.IN ( ) );
    r26.connectsTo ( rbbus_r.IN ( ) );
    r27.connectsTo ( rbbus_r.IN ( ) );
    r28.connectsTo ( rbbus_r.IN ( ) );
    r29.connectsTo ( rbbus_r.IN ( ) );
    r30.connectsTo ( rbbus_r.IN ( ) );
    r31.connectsTo ( rbbus_r.IN ( ) );

    r0.connectsTo ( rcbus_r.IN ( ) );
    r1.connectsTo ( rcbus_r.IN ( ) );
    r2.connectsTo ( rcbus_r.IN ( ) );
    r3.connectsTo ( rcbus_r.IN ( ) );
    r4.connectsTo ( rcbus_r.IN ( ) );
    r5.connectsTo ( rcbus_r.IN ( ) );
    r6.connectsTo ( rcbus_r.IN ( ) );
    r7.connectsTo ( rcbus_r.IN ( ) );
    r8.connectsTo ( rcbus_r.IN ( ) );
    r9.connectsTo ( rcbus_r.IN ( ) );
    r10.connectsTo ( rcbus_r.IN ( ) );
    r11.connectsTo ( rcbus_r.IN ( ) );
    r12.connectsTo ( rcbus_r.IN ( ) );
    r13.connectsTo ( rcbus_r.IN ( ) );
    r14.connectsTo ( rcbus_r.IN ( ) );
    r15.connectsTo ( rcbus_r.IN ( ) );
    r16.connectsTo ( rcbus_r.IN ( ) );
    r17.connectsTo ( rcbus_r.IN ( ) );
    r18.connectsTo ( rcbus_r.IN ( ) );
    r19.connectsTo ( rcbus_r.IN ( ) );
    r20.connectsTo ( rcbus_r.IN ( ) );
    r21.connectsTo ( rcbus_r.IN ( ) );
    r22.connectsTo ( rcbus_r.IN ( ) );
    r23.connectsTo ( rcbus_r.IN ( ) );
    r24.connectsTo ( rcbus_r.IN ( ) );
    r25.connectsTo ( rcbus_r.IN ( ) );
    r26.connectsTo ( rcbus_r.IN ( ) );
    r27.connectsTo ( rcbus_r.IN ( ) );
    r28.connectsTo ( rcbus_r.IN ( ) );
    r29.connectsTo ( rcbus_r.IN ( ) );
    r30.connectsTo ( rcbus_r.IN ( ) );
    r31.connectsTo ( rcbus_r.IN ( ) );

    r0.connectsTo ( auxbus_r.IN ( ) );
    r1.connectsTo ( auxbus_r.IN ( ) );
    r2.connectsTo ( auxbus_r.IN ( ) );
    r3.connectsTo ( auxbus_r.IN ( ) );
    r4.connectsTo ( auxbus_r.IN ( ) );
    r5.connectsTo ( auxbus_r.IN ( ) );
    r6.connectsTo ( auxbus_r.IN ( ) );
    r7.connectsTo ( auxbus_r.IN ( ) );
    r8.connectsTo ( auxbus_r.IN ( ) );
    r9.connectsTo ( auxbus_r.IN ( ) );
    r10.connectsTo ( auxbus_r.IN ( ) );
    r11.connectsTo ( auxbus_r.IN ( ) );
    r12.connectsTo ( auxbus_r.IN ( ) );
    r13.connectsTo ( auxbus_r.IN ( ) );
    r14.connectsTo ( auxbus_r.IN ( ) );
    r15.connectsTo ( auxbus_r.IN ( ) );
    r16.connectsTo ( auxbus_r.IN ( ) );
    r17.connectsTo ( auxbus_r.IN ( ) );
    r18.connectsTo ( auxbus_r.IN ( ) );
    r19.connectsTo ( auxbus_r.IN ( ) );
    r20.connectsTo ( auxbus_r.IN ( ) );
    r21.connectsTo ( auxbus_r.IN ( ) );
    r22.connectsTo ( auxbus_r.IN ( ) );
    r23.connectsTo ( auxbus_r.IN ( ) );
    r24.connectsTo ( auxbus_r.IN ( ) );
    r25.connectsTo ( auxbus_r.IN ( ) );
    r26.connectsTo ( auxbus_r.IN ( ) );
    r27.connectsTo ( auxbus_r.IN ( ) );
    r28.connectsTo ( auxbus_r.IN ( ) );
    r29.connectsTo ( auxbus_r.IN ( ) );
    r30.connectsTo ( auxbus_r.IN ( ) );
    r31.connectsTo ( auxbus_r.IN ( ) );

    ra_re.connectsTo ( rabus_r.OUT ( ) );
    rb_re.connectsTo ( rbbus_r.OUT ( ) );
    rc_re.connectsTo ( rcbus_r.OUT ( ) );
    aux_re.connectsTo ( auxbus_r.OUT ( ) );

    lock_ir.connectsTo ( lockbus_r.IN ( ) );
    lock_re.connectsTo ( lockbus_r.OUT ( ) );
} // make_connections_read

/**
 * make_connections_execute
 *
 *
 */
void make_connections_execute ( )
{
    fout_e.connectsTo ( outbus_em.OUT ( ) );
    fout_e.connectsTo ( outbus_em.IN ( ) );
    fout_e.connectsTo ( arithop1_ebus.IN ( ) );
    fout_e.connectsTo ( shiftop1_ebus.IN ( ) );
    fout_e.connectsTo ( addrop1_ebus.IN ( ) );

    arith_op1.connectsTo ( arithop1_ebus.OUT ( ) );
    arith_op2.connectsTo ( arithop2_ebus.OUT ( ) );
    arith_op1.connectsTo ( arith_alu.OP1 ( ) );
    arith_op2.connectsTo ( arith_alu.OP2 ( ) );
    shift_op1.connectsTo ( shiftop1_ebus.OUT ( ) );
    shift_op2.connectsTo ( shiftop2_ebus.OUT ( ) );
    shift_op1.connectsTo ( shift_alu.OP1 ( ) );
    shift_op2.connectsTo ( shift_alu.OP2 ( ) );
    addr_op1.connectsTo ( addrop1_ebus.OUT ( ) );
    addr_op2.connectsTo ( addrop2_ebus.OUT ( ) );
    addr_op1.connectsTo ( addr_alu.OP1 ( ) );
    addr_op2.connectsTo ( addr_alu.OP2 ( ) );
    
    pc_re.connectsTo ( pcbus_e.IN ( ) );
    pc_re.connectsTo ( arithop1_ebus.IN ( ) );
    pc_re.connectsTo ( arithop2_ebus.IN ( ) );
    ra_re.connectsTo ( arithop1_ebus.IN ( ) );
    ra_re.connectsTo ( arithop2_ebus.IN ( ) );
    rb_re.connectsTo ( arithop1_ebus.IN ( ) );
    rb_re.connectsTo ( arithop2_ebus.IN ( ) );
    aux_re.connectsTo ( arithop1_ebus.IN ( ) );
    aux_re.connectsTo ( arithop2_ebus.IN ( ) );

    ra_re.connectsTo ( shiftop1_ebus.IN ( ) );
    ra_re.connectsTo ( shiftop2_ebus.IN ( ) );
    rb_re.connectsTo ( shiftop1_ebus.IN ( ) );
    rb_re.connectsTo ( shiftop2_ebus.IN ( ) );
    rc_re.connectsTo ( shiftop1_ebus.IN ( ) );
    rc_re.connectsTo ( shiftop2_ebus.IN ( ) );
    aux_re.connectsTo ( shiftop1_ebus.IN ( ) );
    aux_re.connectsTo ( shiftop2_ebus.IN ( ) );

    pc_re.connectsTo ( addrop1_ebus.IN ( ) );
    
    pc_em.connectsTo ( pcbus_e.IN ( ) );
    out_em.connectsTo ( arith_alu.OUT ( ) );
    out_em.connectsTo ( shift_alu.OUT ( ) );
    out_em.connectsTo ( outbus_em.IN ( ) );

    addr_em.connectsTo ( addr_alu.OUT ( ) );

} // make_connections_execute

/**
 * make_connections_memory
 *
 *
 */
void make_connections_memory ( )
{
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

// $(filename) end
