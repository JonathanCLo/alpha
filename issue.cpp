/**
 * issue.cpp
 *
 * Author   Jonathan Lo < >
 */

#include "includes.h"

void issue1 ( );
void issue2 ( );
void detect ( );
void set_npc_branch ( );

/**
 * detect
 *
 *
 */
void issue1 ( )
{
    // move ir
    irbus_i1.IN ( ).pullFrom ( ir_fi );
    ir_i.latchFrom ( irbus_i1.OUT ( ) );

    // move pc
    pcbus_i1.IN ( ).pullFrom ( pc_fi );
    pc_i.latchFrom ( pcbus_i1.OUT ( ) );

    long opc = ir_i ( REG_SIZE - 1, REG_SIZE - 6 );
    char buff [ 32 ];

    switch ( opc ) {
        case OPC_NOOP: // noop
            break;
        case OPC_HALT: // halt
            done = true;
            return;
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
        case OPC_BSR: // branches
            // grab the required bits
            destalu_i.OP1 ( ).pullFrom ( ir_fi );
            destalu_i.OP2 ( ).pullFrom ( dispmask_g );
            aux_i.latchFrom ( destalu_i.OUT ( ) );
            destalu_i.perform ( BusALU::op_and );
            break;
        case OPC_JMP:
        case OPC_JSR:
        case OPC_RET:
        case OPC_JSRC:
        case OPC_RPCC: // mf
            destalu_i.OP1 ( ).pullFrom ( pc_fi );
            destalu_i.OP2 ( ).pullFrom ( dispmask_g );
            aux_i.latchFrom ( destalu_i.OUT ( ) );
            destalu_i.perform ( BusALU::op_rop1 );
            break;
        default: // other formats
            // we don't care
            break;
    } // switch
}     // detect

/**
 * set_npc
 * calculate possible new pc
 *
 */
void issue2 ( )
{
    long opc = ir_i ( REG_SIZE - 1, REG_SIZE - 6 );
    char buff [ 32 ];

    if ( ir_purge ) {
        irbus_i2.IN ( ).pullFrom ( noop_g );
        ir_ir.latchFrom ( irbus_i2.OUT ( ) );
    } else { // read from mem
        // move ir
        irbus_i2.IN ( ).pullFrom ( ir_i );
        ir_ir.latchFrom ( irbus_i2.OUT ( ) );
    }

    // move pc
    pcbus_i2.IN ( ).pullFrom ( pc_i );
    pc_ir.latchFrom ( pcbus_i2.OUT ( ) );

    switch ( opc ) {
        case OPC_NOOP: // noop
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
        case OPC_BSR: // branches
            // prep npc for calculation in read
            leftShift_alu.OP1 ( ).pullFrom ( aux_i );
            leftShift_alu.OP2 ( ).pullFrom ( shift11_g );
            npc_ir.latchFrom ( leftShift_alu.OUT ( ) );
            leftShift_alu.perform ( BusALU::op_lshift );
            break;
        case OPC_JMP: // mf
            // TODO do we need to do anything?
            // prep npc for calculation in read
            leftShift_alu.OP1 ( ).pullFrom ( aux_i );
            leftShift_alu.OP2 ( ).pullFrom ( shift11_g );
            npc_ir.latchFrom ( leftShift_alu.OUT ( ) );
            leftShift_alu.perform ( BusALU::op_rop1 );
            break;
        default: // other formats
            // we don't care
            break;
    } // switch

} // issue2

// issue.cpp end
