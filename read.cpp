/**
 * read.cpp
 *
 * Author   Jonathan Lo < >
 */

#include "includes.h"

/**
 * read1
 *
 *
 */
void read1 ( )
{
    // reset indicator. this does not get used until tick2
    ir_purge = false;
    // move ir
    irbus_r1.IN ( ).pullFrom ( ir_ir );
    ir_r.latchFrom ( irbus_r1.OUT ( ) );

    // move pc
    pcbus_r1.IN ( ).pullFrom ( pc_ir );
    pc_r.latchFrom ( pcbus_r1.OUT ( ) );

    long opc = ir_re ( REG_SIZE - 1, REG_SIZE - 6 );

    switch ( opc ) {
        case OPC_NOOP:
            noop1 ( );
            break;
        case OPC_LDA:
        case OPC_LDAH:
        case OPC_LDWU:
        case OPC_LDL:
        case OPC_STL:
            memdisp1 ( );
            break;
        case OPC_BEQ:
        case OPC_BGE:
        case OPC_BGT:
        case OPC_BLBC:
        case OPC_BLBS:
        case OPC_BLE:
        case OPC_BLT:
        case OPC_BNE:
        case OPC_BR:
        case OPC_BSR: // B
            branch1 ( );
            break;
        case OPC_JMP:
            jump1 ( );
            break;
        case OPC_RPCC: // pcc
            // pcc ( );
            break;
        case OPC_ADDL:
            operate1 ( );
            break;
        default: // unknown
            done = true;

    } // switch

    execute1 ( );
} // read1

/**
 * read2
 *
 *
 */
void read2 ( )
{

    long opc = ir_r ( REG_SIZE - 1, REG_SIZE - 6 );

    switch ( opc ) {
        case OPC_NOOP:
            noop2 ( );
            break;
        case OPC_LDA:
        case OPC_LDAH:
        case OPC_LDWU:
        case OPC_LDL:
        case OPC_STL:
            memdisp2 ( );
            break;
        case OPC_BEQ:
        case OPC_BGE:
        case OPC_BGT:
        case OPC_BLBC:
        case OPC_BLBS:
        case OPC_BLE:
        case OPC_BLT:
        case OPC_BNE:
        case OPC_BR:
        case OPC_BSR: // B
            branch2 ( );
            break;
        case OPC_JMP:
            jump2 ( );
            break;
        case OPC_RPCC: // pcc
            // pcc ( );
            break;
        case OPC_ADDL:
            operate2 ( );
            break;
        default: // unknown
            done = true;

    } // switch
    execute2 ( );
} // read


/**
 * noop1
 *
 *
 */
void noop1 ( )
{
    // nothing
}

/**
 * noop2
 *
 *
 */
void noop2 ( )
{
    // nothing
}

/**
 * memdisp1
 *
 *
 */
void memdisp1 ( )
{
    // sign extend
    signExtalu_r.OP1 ( ).pullFrom ( npc_ir );
    signExtalu_r.OP2 ( ).pullFrom ( dispmask_g );
    dest_r.latchFrom ( signExtalu_r.OUT ( ) );
    signExtalu_r.perform ( BusALU::op_extendSign );
}

/**
 * memdisp2
 *
 *
 */
void memdisp2 ( )
{
    // move ir
    irbus_r2.IN ( ).pullFrom ( ir_ir );
    ir_r.latchFrom ( irbus_r2.OUT ( ) );

    // move pc
    pcbus_r2.IN ( ).pullFrom ( pc_ir );
    pc_r.latchFrom ( pcbus_r2.OUT ( ) );

    // move disp
    destbus_r.IN ( ).pullFrom ( dest_r );
    disp_re.latchFrom ( destbus_r.OUT ( ) );
} // memdisp2

/**
 * branch1
 * calculates the possible npc
 *
 */
void branch1 ( )
{
    // sign extend
    signExtalu_r.OP1 ( ).pullFrom ( npc_ir );
    signExtalu_r.OP2 ( ).pullFrom ( shift7_g );
    dest_r.latchFrom ( signExtalu_r.OUT ( ) );
    signExtalu_r.perform ( BusALU::op_rashift );

    // get ra for comparison
    long ra = ir_re ( REG_SIZE - 7, REG_SIZE - 11 );
    long ra_value = 0;

    // grab the ra_value
    switch ( ra ) {
        case 0;
            ra_value = r0.value ( );
            break;
        case 1;
            ra_value = r1.value ( );
            break;
        case 2;
            ra_value = r2.value ( );
            break;
        case 3;
            ra_value = r3.value ( );
            break;
        case 4;
            ra_value = r4.value ( );
            break;
        case 5;
            ra_value = r5.value ( );
            break;
        case 6;
            ra_value = r6.value ( );
            break;
        case 7;
            ra_value = r7.value ( );
            break;
        case 8;
            ra_value = r8.value ( );
            break;
        case 9;
            ra_value = r9.value ( );
            break;
        case 10;
            ra_value = r10.value ( );
            break;
        case 11;
            ra_value = r11.value ( );
            break;
        case 12;
            ra_value = r12.value ( );
            break;
        case 13;
            ra_value = r13.value ( );
            break;
        case 14;
            ra_value = r14.value ( );
            break;
        case 15;
            ra_value = r15.value ( );
            break;
        case 16;
            ra_value = r16.value ( );
            break;
        case 17;
            ra_value = r17.value ( );
            break;
        case 18;
            ra_value = r18.value ( );
            break;
        case 19;
            ra_value = r19.value ( );
            break;
        case 20;
            ra_value = r20.value ( );
            break;
        case 21;
            ra_value = r21.value ( );
            break;
        case 22;
            ra_value = r22.value ( );
            break;
        case 23;
            ra_value = r23.value ( );
            break;
        case 24;
            ra_value = r24.value ( );
            break;
        case 25;
            ra_value = r25.value ( );
            break;
        case 26;
            ra_value = r26.value ( );
            break;
        case 27;
            ra_value = r27.value ( );
            break;
        case 28;
            ra_value = r28.value ( );
            break;
        case 29;
            ra_value = r29.value ( );
            break;
        case 30;
            ra_value = r30.value ( );
            break;
        case 31;
            ra_value = r31.value ( );
            break;
    } // switch // we can use ra_value

} // branch1

/**
 * branch2
 * calculates if we take the branch
 *
 */
void branch2 ( )
{
    long branch = ir_re ( REG_SIZE - 1, REG_SIZE - 6 );

    // calculate if we are taking branch
    switch ( branch ) {
        case OPC_BEQ:
            if ( ra_value == 0 ) { // take the branch
                use_npc ( );
            } else { // not taken... continue onward
                use_pc ( );
            }
            break;
        case OPC_BGE:
            if ( ra_value >= 0 ) { // take the branch
                use_npc ( );
            } else { // not taken... continue onward
                use_pc ( );
            }
            break;
        case OPC_BGT:
            if ( ra_value > 0 ) { // take the branch
                use_npc ( );
            } else { // not taken... continue onward
                use_pc ( );
            }
            break;
        case OPC_BLBC:
            if ( ( ra_value & 1 ) == 0 ) { // take the branch
                use_npc ( );
            } else { // not taken... continue onward
                use_pc ( );
            }
            break;
        case OPC_BLBS:
            if ( ( ra_value & 1 ) == 1 ) { // take the branch
                use_npc ( );
            } else { // not taken... continue onward
                use_pc ( );
            }
            break;
        case OPC_BLE:
            if ( ra_value <= 0 ) { // take the branch
                use_npc ( );
            } else { // not taken... continue onward
                use_pc ( );
            }
            break;
        case OPC_BLT:
            if ( ra_value < 0 ) { // take the branch
                use_npc ( );
            } else { // not taken... continue onward
                use_pc ( );
            }
            break;
        case OPC_BNE:
            if ( ra_value != 0 ) { // take the branch
                use_npc ( );
            } else { // not taken... continue onward
                use_pc ( );
            }
            break;
        case OPC_BR:
        case OPC_BSR:
            use_npc ( );
            break;
        default: // dont care
            break;
    } // switch

} // branch2

/**
 * use_npc
 * change the pc in fetch to fetch the good instr and purge useless ones.
 *
 */
void use_npc ( )
{
    // change pc_load
    changePC_bus.IN ( ).pullFrom ( npc_r );
    pc_load.latchFrom ( changePC_bus.OUT ( ) );
    // discard pc_re // TODO do we?

    // indicate stage that it should purge instruction
    ir_purge = true;
    // toss curr inst
    ir_noop_bus_r.IN ( ).pullFrom ( noop );
    ir_re.latchFrom ( ir_noop_bus_r.OUT ( ) );

} // use_npc

/**
 * use_pc
 * use the old pc and move forward
 *
 */
void use_pc ( )
{
    // move pc
    pcbus_r.IN ( ).pullFrom ( pc_r );
    pc_re.latchFrom ( pcbus_r.OUT ( ) );
    // move ir
    irbus_r.IN ( ).pullFrom ( ir_r );
    ir_re.latchFrom ( irbus_r.OUT ( ) );
}

/**
 * jumps
 *
 *
 */
void jump1 ( )
{

    // write to ra the pc
    write_ra ( );
    // TODO Data hazard?

    // get rb
    move_rb ( );

} // jump1

/**
 * jump2
 *
 *
 */
void jump2 ( )
{
    destalu_r.OP1 ( ).pullFrom ( rb_r );
    destalu_r.OP2 ( ).pullFrom ( not3_g );
    pc_load.latchFrom ( destalu_r.OUT ( ) );
    destalu_r.perform ( BusALU::op_and );

    // purge curr instr
    // indicate stage that it should purge instruction
    ir_purge = true;
    // toss curr inst
    ir_noop_bus_r.IN ( ).pullFrom ( noop );
    ir_re.latchFrom ( ir_noop_bus_r.OUT ( ) );
} // jump2

/**
 * operate1
 *
 *
 */
void operate1 ( )
{
    long ind = ir_r ( REG_SIZE - 20 );

    switch ( ind ) {
        case 0; // register
            move_ra ( );
            move_rb ( );
            move_rc ( );
            break;
        case 1; // literal
            move_ra ( );
            move_rc ( );
            // get value
            litalu_r.OP1 ( ).pullFrom ( ir_r );
            litalu_r.OP2 ( ).pullFrom ( literalmask_g );
            literal_r.latchFrom ( litalu_r.OUT ( ) );
            litalu_r.peform ( BusALU::op_and );
            break;
    } // switch

} // operate1

/**
 * operate2
 *
 *
 */
void operate2 ( )
{
    long ind = ir_r ( REG_SIZE - 20 );

    switch ( ind ) {
        case 0; // register
            rabus_r.IN ( ).pullFrom ( ra_r );
            ra_re.latchFrom ( rabus_r.OUT ( ) );
            rbbus_r.IN ( ).pullFrom ( rb_r );
            rb_re.latchFrom ( rbbus_r.OUT ( ) );
            rcbus_r.IN ( ).pullFrom ( rc_r );
            rc_re.latchFrom ( rcbus_r.OUT ( ) );
            break;
        case 1; // literal
            rabus_r.IN ( ).pullFrom ( ra_r );
            ra_re.latchFrom ( rabus_r.OUT ( ) );
            rcbus_r.IN ( ).pullFrom ( rc_r );
            rc_re.latchFrom ( rcbus_r.OUT ( ) );

            litalu_r.OP1 ( ).pullFrom ( literal_r );
            litalu_r.OP2 ( ).pullFrom ( literalShift_g );
            literal_re.latchFrom ( litalu_r.OUT ( ) );
            litalu_r.perform ( BusALU::op_rshift );

            break;
    } // switch

} // operate2

/**
 * move_ra
 * support function to move a PVR's ddata to ra_r
 *
 */
void move_ra ( )
{
    long ra = ir_re ( REG_SIZE - 7, REG_SIZE - 11 );

    // move ra
    ra_r.latchFrom ( rabus_r.OUT ( ) );

    switch ( ra ) {
        case 0:
            rabus_r.IN ( ).pullFrom ( r0 );
            break;
        case 1:
            rabus_r.IN ( ).pullFrom ( r1 );
            break;
        case 2:
            rabus_r.IN ( ).pullFrom ( r2 );
            break;
        case 3:
            rabus_r.IN ( ).pullFrom ( r3 );
            break;
        case 4:
            rabus_r.IN ( ).pullFrom ( r4 );
            break;
        case 5:
            rabus_r.IN ( ).pullFrom ( r5 );
            break;
        case 6:
            rabus_r.IN ( ).pullFrom ( r6 );
            break;
        case 7:
            rabus_r.IN ( ).pullFrom ( r7 );
            break;
        case 8:
            rabus_r.IN ( ).pullFrom ( r8 );
            break;
        case 9:
            rabus_r.IN ( ).pullFrom ( r9 );
            break;
        case 10:
            rabus_r.IN ( ).pullFrom ( r10 );
            break;
        case 11:
            rabus_r.IN ( ).pullFrom ( r11 );
            break;
        case 12:
            rabus_r.IN ( ).pullFrom ( r12 );
            break;
        case 13:
            rabus_r.IN ( ).pullFrom ( r13 );
            break;
        case 14:
            rabus_r.IN ( ).pullFrom ( r14 );
            break;
        case 15:
            rabus_r.IN ( ).pullFrom ( r15 );
            break;
        case 16:
            rabus_r.IN ( ).pullFrom ( r16 );
            break;
        case 17:
            rabus_r.IN ( ).pullFrom ( r17 );
            break;
        case 18:
            rabus_r.IN ( ).pullFrom ( r18 );
            break;
        case 19:
            rabus_r.IN ( ).pullFrom ( r19 );
            break;
        case 20:
            rabus_r.IN ( ).pullFrom ( r20 );
            break;
        case 21:
            rabus_r.IN ( ).pullFrom ( r21 );
            break;
        case 22:
            rabus_r.IN ( ).pullFrom ( r22 );
            break;
        case 23:
            rabus_r.IN ( ).pullFrom ( r23 );
            break;
        case 24:
            rabus_r.IN ( ).pullFrom ( r24 );
            break;
        case 25:
            rabus_r.IN ( ).pullFrom ( r25 );
            break;
        case 26:
            rabus_r.IN ( ).pullFrom ( r26 );
            break;
        case 27:
            rabus_r.IN ( ).pullFrom ( r27 );
            break;
        case 28:
            rabus_r.IN ( ).pullFrom ( r28 );
            break;
        case 29:
            rabus_r.IN ( ).pullFrom ( r29 );
            break;
        case 30:
            rabus_r.IN ( ).pullFrom ( r30 );
            break;
        case 31:
            rabus_r.IN ( ).pullFrom ( r31 );
            break;
        default: // unknown
            done = true;
    } // switch

} // move_ra

/**
 * write_ra
 *
 *
 */
void write_ra ( )
{
    long ra = ir_re ( REG_SIZE - 7, REG_SIZE - 11 );

    // move ra
    rabus_r.IN ( ).pullFrom ( pc_r );

    switch ( ra ) {
        case 0:
            r0.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 1:
            r1.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 2:
            r2.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 3:
            r3.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 4:
            r4.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 5:
            r5.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 6:
            r6.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 7:
            r7.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 8:
            r8.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 9:
            r9.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 10:
            r10.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 11:
            r11.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 12:
            r12.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 13:
            r13.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 14:
            r14.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 15:
            r15.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 16:
            r16.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 17:
            r17.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 18:
            r18.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 19:
            r19.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 20:
            r20.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 21:
            r21.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 22:
            r22.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 23:
            r23.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 24:
            r24.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 25:
            r25.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 26:
            r26.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 27:
            r27.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 28:
            r28.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 29:
            r29.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 30:
            r30.latchFrom ( rabus_r.OUT ( ) );
            break;
        case 31:
            r31.latchFrom ( rabus_r.OUT ( ) );
            break;
        default: // unknown
            done = true;
    } // switch
}     // write_ra
/**
 * move_rb
 * support function to move a PVR's ddata to ra_r
 *
 */
void move_rb ( )
{
    long rb = ir_re ( REG_SIZE - 12, REG_SIZE - 16 );

    // move ra
    rb_r.latchFrom ( rbbus_r.OUT ( ) );

    switch ( rb ) {
        case 0:
            rbbus_r.IN ( ).pullFrom ( r0 );
            break;
        case 1:
            rbbus_r.IN ( ).pullFrom ( r1 );
            break;
        case 2:
            rbbus_r.IN ( ).pullFrom ( r2 );
            break;
        case 3:
            rbbus_r.IN ( ).pullFrom ( r3 );
            break;
        case 4:
            rbbus_r.IN ( ).pullFrom ( r4 );
            break;
        case 5:
            rbbus_r.IN ( ).pullFrom ( r5 );
            break;
        case 6:
            rbbus_r.IN ( ).pullFrom ( r6 );
            break;
        case 7:
            rbbus_r.IN ( ).pullFrom ( r7 );
            break;
        case 8:
            rbbus_r.IN ( ).pullFrom ( r8 );
            break;
        case 9:
            rbbus_r.IN ( ).pullFrom ( r9 );
            break;
        case 10:
            rbbus_r.IN ( ).pullFrom ( r10 );
            break;
        case 11:
            rbbus_r.IN ( ).pullFrom ( r11 );
            break;
        case 12:
            rbbus_r.IN ( ).pullFrom ( r12 );
            break;
        case 13:
            rbbus_r.IN ( ).pullFrom ( r13 );
            break;
        case 14:
            rbbus_r.IN ( ).pullFrom ( r14 );
            break;
        case 15:
            rbbus_r.IN ( ).pullFrom ( r15 );
            break;
        case 16:
            rbbus_r.IN ( ).pullFrom ( r16 );
            break;
        case 17:
            rbbus_r.IN ( ).pullFrom ( r17 );
            break;
        case 18:
            rbbus_r.IN ( ).pullFrom ( r18 );
            break;
        case 19:
            rbbus_r.IN ( ).pullFrom ( r19 );
            break;
        case 20:
            rbbus_r.IN ( ).pullFrom ( r20 );
            break;
        case 21:
            rbbus_r.IN ( ).pullFrom ( r21 );
            break;
        case 22:
            rbbus_r.IN ( ).pullFrom ( r22 );
            break;
        case 23:
            rbbus_r.IN ( ).pullFrom ( r23 );
            break;
        case 24:
            rbbus_r.IN ( ).pullFrom ( r24 );
            break;
        case 25:
            rbbus_r.IN ( ).pullFrom ( r25 );
            break;
        case 26:
            rbbus_r.IN ( ).pullFrom ( r26 );
            break;
        case 27:
            rbbus_r.IN ( ).pullFrom ( r27 );
            break;
        case 28:
            rbbus_r.IN ( ).pullFrom ( r28 );
            break;
        case 29:
            rbbus_r.IN ( ).pullFrom ( r29 );
            break;
        case 30:
            rbbus_r.IN ( ).pullFrom ( r30 );
            break;
        case 31:
            rbbus_r.IN ( ).pullFrom ( r31 );
            break;
        default: // unknown
            done = true;
    } // switch

} // move_rb

/**
 * move_rc
 *
 *
 */
void move_rc ( )
{
    long rc = ir_re ( REG_SIZE - 28, 0 );

    // move ra
    rc_r.latchFrom ( rcbus_r.OUT ( ) );

    switch ( rc ) {
        case 0:
            rcbus_r.IN ( ).pullFrom ( r0 );
            break;
        case 1:
            rcbus_r.IN ( ).pullFrom ( r1 );
            break;
        case 2:
            rcbus_r.IN ( ).pullFrom ( r2 );
            break;
        case 3:
            rcbus_r.IN ( ).pullFrom ( r3 );
            break;
        case 4:
            rcbus_r.IN ( ).pullFrom ( r4 );
            break;
        case 5:
            rcbus_r.IN ( ).pullFrom ( r5 );
            break;
        case 6:
            rcbus_r.IN ( ).pullFrom ( r6 );
            break;
        case 7:
            rcbus_r.IN ( ).pullFrom ( r7 );
            break;
        case 8:
            rcbus_r.IN ( ).pullFrom ( r8 );
            break;
        case 9:
            rcbus_r.IN ( ).pullFrom ( r9 );
            break;
        case 10:
            rcbus_r.IN ( ).pullFrom ( r10 );
            break;
        case 11:
            rcbus_r.IN ( ).pullFrom ( r11 );
            break;
        case 12:
            rcbus_r.IN ( ).pullFrom ( r12 );
            break;
        case 13:
            rcbus_r.IN ( ).pullFrom ( r13 );
            break;
        case 14:
            rcbus_r.IN ( ).pullFrom ( r14 );
            break;
        case 15:
            rcbus_r.IN ( ).pullFrom ( r15 );
            break;
        case 16:
            rcbus_r.IN ( ).pullFrom ( r16 );
            break;
        case 17:
            rcbus_r.IN ( ).pullFrom ( r17 );
            break;
        case 18:
            rcbus_r.IN ( ).pullFrom ( r18 );
            break;
        case 19:
            rcbus_r.IN ( ).pullFrom ( r19 );
            break;
        case 20:
            rcbus_r.IN ( ).pullFrom ( r20 );
            break;
        case 21:
            rcbus_r.IN ( ).pullFrom ( r21 );
            break;
        case 22:
            rcbus_r.IN ( ).pullFrom ( r22 );
            break;
        case 23:
            rcbus_r.IN ( ).pullFrom ( r23 );
            break;
        case 24:
            rcbus_r.IN ( ).pullFrom ( r24 );
            break;
        case 25:
            rcbus_r.IN ( ).pullFrom ( r25 );
            break;
        case 26:
            rcbus_r.IN ( ).pullFrom ( r26 );
            break;
        case 27:
            rcbus_r.IN ( ).pullFrom ( r27 );
            break;
        case 28:
            rcbus_r.IN ( ).pullFrom ( r28 );
            break;
        case 29:
            rcbus_r.IN ( ).pullFrom ( r29 );
            break;
        case 30:
            rcbus_r.IN ( ).pullFrom ( r30 );
            break;
        case 31:
            rcbus_r.IN ( ).pullFrom ( r31 );
            break;
        default: // unknown
            done = true;
    } // switch

} // move_rc

// read.cpp end
