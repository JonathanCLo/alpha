/**
 * read.cpp
 *
 * Author   Jonathan Lo < >
 */

#include "includes.h"

long ra_value = 0;
char buff [32];

void read ( );
void noop ( );
void md ( );
void b ( );
void mf ( );
void pcc ( );
void o ( );
void o_imm ( );
void o_reg ( );

/**
 * read
 * read stage of pipeline. Moves required values into pipeline registers
 * unused pipeline registers are not cleared, and hold unknown values
 */
void read ( )
{
    // move ir
    irbus_r.IN ( ).pullFrom ( ir_ir );
    ir_re.latchFrom ( irbus_r.OUT ( ) );

    // move pc
    pcbus_r.IN ( ).pullFrom ( pc_ir );
    pc_re.latchFrom ( pcbus_r.OUT ( ) );

    // aux = 4 * (npc >> 11 (sign extend) );
    // aux = npc >> 7
    leftShift_alu.OP1 ( ).pullFrom ( npc_ir );
    leftShift_alu.OP2 ( ).pullFrom ( shift7 );
    aux_r.latchFrom ( leftShift_alu );

    Clock::tick ( );
    long opc = ir_re ( REG_SIZE - 1, REG_SIZE - 6 );

    sprintf ( buff, "|pc=%02lx opc=%03lx ", pc_ir.value ( ), opc );
    cout << buff;

    switch ( opc ) {
        case OPC_NOOP:
            sprintf ( buff, "ir=NOOP " );
            cout << buff;
            noop ( );
            break;
        case OPC_LDA:
        case OPC_LDAH:
        case OPC_LDU:
        case OPC_LDL:
        case OPC_STL:
            md ( );
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
            sprintf ( buff, "ir=BRANCH " );
            cout << buff;
            b ( );
            break;
        case OPC_JMP:
        case OPC_JSR:
        case OPC_RET:
        case OPC_JSRC:
            mf ( );
            break;
        case OPC_RPCC: // pcc
            pcc ( );
            break;
        case OPC_ADDL:
        case OPC_S4ADDL:
        case OPC_S8ADDL:
        case OPC_SUBL:
        case OPC_S4SUBL:
        case OPC_S8SUBL:
        case OPC_AND:
        case OPC_BIC:
        case OPC_BIS:
        case OPC_EQV:
        case OPC_ORNOT:
        case OPC_XOR:
        case OPC_CMOVEQ:
        case OPC_CMOVGE:
        case OPC_CMOVGT:
        case OPC_CMOVBLC:
        case OPC_CMOVBLS:
        case OPC_CMOVLE:
        case OPC_CMOVLT:
        case OPC_CMOVNE:
        case OPC_SLL:
        case OPC_SRL:
            o ( );
            break;
        default: // unknown
            done = true;

    } // switch

    Clock::tick ( );

    execute ( );
} // read

/**
 * noop
 *
 *
 */
void noop ( )
{
    // TODO
}
/**
 * md
 * handles memory displacement instruction format, moves ra and rb into
 * pipeline registers
 *
 */
void md ( )
{
    long disp = ir_re ( REG_SIZE - 17, 0 );

    use_pc ( );
    pass_ir ( );

    // move ra
    move_ra ( );

    // move rb
    move_rb ( );

} // md

/**
 * b
 * handles branch instruction format, moves ra and rb into pipeline registers
 *
 */
void b ( )
{
    long branch = ir_re ( REG_SIZE - 1, REG_SIZE - 6 );

    // move ra
    move_ra ( );


    // calculate if we are taking branch
    switch ( branch ) {
        case OPC_BEQ:
            if ( ra_value == 0 ) { // take the branch
                use_npc ( );
                purge_ir ( );
            } else { // not taken... continue onward
                use_pc ( );
                pass_ir ( );
            }
            break;
        case OPC_BGE:
            if ( ra_value >= 0 ) { // take the branch
                use_npc ( );
                purge_ir ( );
            } else { // not taken... continue onward
                use_pc ( );
                pass_ir ( );
            }
            break;
        case OPC_BGT:
            if ( ra_value > 0 ) { // take the branch
                use_npc ( );
                purge_ir ( );
            } else { // not taken... continue onward
                use_pc ( );
                pass_ir ( );
            }
            break;
        case OPC_BLBC:
            if ( (long) ( ra_value & 0x0 ) == 0 ) { // take the branch
                use_npc ( );
                purge_ir ( );
            } else { // not taken... continue onward
                use_pc ( );
                pass_ir ( );
            }
            break;
        case OPC_BLBS:
            if ( (long) ( ra_value & 0x0 ) == 1 ) { // take the branch
                use_npc ( );
                purge_ir ( );
            } else { // not taken... continue onward
                use_pc ( );
                pass_ir ( );
            }
            break;
        case OPC_BLE:
            if ( ra_value <= 0 ) { // take the branch
                use_npc ( );
                purge_ir ( );
            } else { // not taken... continue onward
                use_pc ( );
                pass_ir ( );
            }
            break;
        case OPC_BLT:
            if ( ra_value < 0 ) { // take the branch
                use_npc ( );
                purge_ir ( );
            } else { // not taken... continue onward
                use_pc ( );
                pass_ir ( );
            }
            break;
        case OPC_BNE:
            if ( ra_value != 0 ) { // take the branch
                use_npc ( );
                purge_ir ( );
            } else { // not taken... continue onward
                use_pc ( );
                pass_ir ( );
            }
            break;
        case OPC_BR:
        case OPC_BSR:
            use_npc ( );
            purge_ir ( );

            rabus_r.IN ( ).pullFrom ( pc_ir );
            ra_re.latchFrom ( rabus_r.OUT ( ) );
            break;
        default: // dont care
    } // switch


} // b

/**
 * mf
 * handles memory instruction format, moves ra and rb into pipeline registers
 *
 */
void mf ( )
{
    use_pc ( );
    pass_ir ( );

    // move ra
    move_ra ( );

    // move rb
    move_rb ( );
} // mf

/**
 * pcc
 * special mf instruction format for pcc
 *
 */
void pcc ( )
{
    long rb	  = ir_re ( REG_SIZE - 12, REG_SIZE - 16 );
    long disp = ir_re ( REG_SIZE - 17, 0 );

    // move pc
    pcbus_r.IN ( ).pullFrom ( pc_ir );
    pc_re.latchFrom ( pcbus_r.OUT ( ) );

    // move ra
    move_ra ( );

    // check rb field
    switch ( rb ) {
        case 31:
            break;
        default:
            done = true;
    }

    // check disp field
    switch ( disp ) {
        case 49152:
            break;
        default:
            done = true;
    }
} // pcc

/**
 * o
 * handles operate instruction format
 *
 */
void o ( )
{
    long type = ir_re ( REG_SIZE - 20 );

    use_pc ( );
    pass_ir ( );

    // move ra
    move_ra ( );

    // move rc
    move_rc ( );

    switch ( type ) {
        case 0: // reg
            o_reg ( );
            break;
        case 1: // literal
            o_imm ( );
            break;
    }
} // o

/**
 * o_imm
 *
 *
 */
void o_imm ( )
{
    // DO NOTHING
}

/**
 * o_reg
 * pass register to rb;
 *
 */
void o_reg ( )
{
    // move_rb
    move_rb ( );
}

/**
 * move_ra
 * support function to move a PVR to RA
 *
 */
void move_ra ( )
{
    long ra = ir_re ( REG_SIZE - 7, REG_SIZE - 11 );

    // move ra
    ra_re.latchFrom ( rabus_r.OUT ( ) );

    switch ( ra ) {
        case 0:
            rabus_r.IN ( ).pullFrom ( r0 );
            ra_value = r0.value ( );
            break;
        case 1:
            rabus_r.IN ( ).pullFrom ( r1 );
            ra_value = r1.value ( );
            break;
        case 2:
            rabus_r.IN ( ).pullFrom ( r2 );
            ra_value = r2.value ( );
            break;
        case 3:
            rabus_r.IN ( ).pullFrom ( r3 );
            ra_value = r3.value ( );
            break;
        case 4:
            rabus_r.IN ( ).pullFrom ( r4 );
            ra_value = r4.value ( );
            break;
        case 5:
            rabus_r.IN ( ).pullFrom ( r5 );
            ra_value = r5.value ( );
            break;
        case 6:
            rabus_r.IN ( ).pullFrom ( r6 );
            ra_value = r6.value ( );
            break;
        case 7:
            rabus_r.IN ( ).pullFrom ( r7 );
            ra_value = r7.value ( );
            break;
        case 8:
            rabus_r.IN ( ).pullFrom ( r8 );
            ra_value = r8.value ( );
            break;
        case 9:
            rabus_r.IN ( ).pullFrom ( r9 );
            ra_value = r9.value ( );
            break;
        case 10:
            rabus_r.IN ( ).pullFrom ( r10 );
            ra_value = r10.value ( );
            break;
        case 11:
            rabus_r.IN ( ).pullFrom ( r11 );
            ra_value = r11.value ( );
            break;
        case 12:
            rabus_r.IN ( ).pullFrom ( r12 );
            ra_value = r12.value ( );
            break;
        case 13:
            rabus_r.IN ( ).pullFrom ( r13 );
            ra_value = r13.value ( );
            break;
        case 14:
            rabus_r.IN ( ).pullFrom ( r14 );
            ra_value = r14.value ( );
            break;
        case 15:
            rabus_r.IN ( ).pullFrom ( r15 );
            ra_value = r15.value ( );
            break;
        case 16:
            rabus_r.IN ( ).pullFrom ( r16 );
            ra_value = r16.value ( );
            break;
        case 17:
            rabus_r.IN ( ).pullFrom ( r17 );
            ra_value = r17.value ( );
            break;
        case 18:
            rabus_r.IN ( ).pullFrom ( r18 );
            ra_value = r18.value ( );
            break;
        case 19:
            rabus_r.IN ( ).pullFrom ( r19 );
            ra_value = r19.value ( );
            break;
        case 20:
            rabus_r.IN ( ).pullFrom ( r20 );
            ra_value = r20.value ( );
            break;
        case 21:
            rabus_r.IN ( ).pullFrom ( r21 );
            ra_value = r21.value ( );
            break;
        case 22:
            rabus_r.IN ( ).pullFrom ( r22 );
            ra_value = r22.value ( );
            break;
        case 23:
            rabus_r.IN ( ).pullFrom ( r23 );
            ra_value = r23.value ( );
            break;
        case 24:
            rabus_r.IN ( ).pullFrom ( r24 );
            ra_value = r24.value ( );
            break;
        case 25:
            rabus_r.IN ( ).pullFrom ( r25 );
            ra_value = r25.value ( );
            break;
        case 26:
            rabus_r.IN ( ).pullFrom ( r26 );
            ra_value = r26.value ( );
            break;
        case 27:
            rabus_r.IN ( ).pullFrom ( r27 );
            ra_value = r27.value ( );
            break;
        case 28:
            rabus_r.IN ( ).pullFrom ( r28 );
            ra_value = r28.value ( );
            break;
        case 29:
            rabus_r.IN ( ).pullFrom ( r29 );
            ra_value = r20.value ( );
            break;
        case 30:
            rabus_r.IN ( ).pullFrom ( r30 );
            ra_value = r30.value ( );
            break;
        case 31:
            rabus_r.IN ( ).pullFrom ( r31 );
            ra_value = r31.value ( );
            break;
        default: // unknown
            done = true;
    } // switch
}     // move_ra

/**
 * move_rb
 * support function to move PVR to RB
 *
 */
void move_rb ( )
{
    long rb = ir_re ( REG_SIZE - 12, REG_SIZE - 16 );

    // move rb
    rb_re.latchFrom ( rbbus_r.OUT ( ) );

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
 * support function to move PVR to RC
 *
 */
void move_rc ( )
{
    long rc = ir_re ( REG_SIZE - 28, 0 );

    // move rc
    rc_re.latchFrom ( rcbus_r.OUT ( ) );

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
            rabus_r.IN ( ).pullFrom ( r19 );
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
}     // move_rc

/**
 * use_pc
 * transfer pc from pipeling forward
 *
 */
void use_pc ( )
{

    // move pc
    pcbus_r.IN ( ).pullFrom ( npc_r );
    pc_re.latchFrom ( pcbus_r.OUT ( ) );
}

/**
 * pass_ir
 *
 * pass the old ir to next stage
 */
void pass_ir ( )
{
    // move ir
    irbus_r.IN ( ).pullFrom ( ir_ir );
    ir_re.latchFrom ( irbus_r.OUT ( ) );
}

/**
 * use_npc
 * calculates the new pc, ir_f <- npc
 */
void use_npc ( )
{
    long npc = pc.value ( ) + aux_r.value ( );

    sprintf ( buff, "npc=%02lx ", npc );
    cout << buff;

    dest_alu.OP1 ( ).pullFrom ( pc_ir );
    dest_alu.OP2 ( ).pullFrom ( aux_r );
    pc_f.connectsTo ( dest_alu.OUT ( ) );
} // use_npc

/**
 * purge_ir
 * noops recently added instructions and current
 *
 */
void purge_ir ( )
{
    // NO OP THE INSTRUCTION and PURGE THE REST
    irfi_noop_bus.IN ( ).pullFrom ( noop );
    irir_noop_bus.IN ( ).pullFrom ( noop );
    irre_noop_bus.IN ( ).pullFrom ( noop );
    // TODO ELIMINATE ENTRIES FROM REGISTER DEPENDENCY TABLE
}

// read.cpp end
