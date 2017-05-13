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
    //TODO added an ir_i in hardware cpp to make this happen. please verify correctness
    long opc = ir_i ( REG_SIZE - 1, REG_SIZE - 6 );
    char buff [ 32 ];

    switch ( opc ) {
        case OPC_NOOP: // noop
            sprintf ( buff, "IR=NOOP " );
            cout << buff;
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
            sprintf ( buff, "IR=BRANCH " );
            cout << buff;
            // grab the required bits
            destalu_i.OP1 ( ).pullFrom ( ir_ir );
            destalu_i.OP2 ( ).pullFrom ( dispmask_i );
            aux_i.latchFrom ( destalu_i.OUT ( ) );
            destalu_i.perform ( BusALU::op_and );
            break;
        case OPC_JMP:
        case OPC_JSR:
        case OPC_RET:
        case OPC_JSRC:
        case OPC_RPCC: // mf
            sprintf ( buff, "IR=MF" );
            cout << buff;
            destalu_i.OP1 ( ).pullFrom ( pc_ir );
            destalu_i.OP2 ( ).pullFrom ( dispmask_i );
            aux_i.latchFrom ( destalu_i.OUT ( ) );
            destalu_i.perform ( BusALU::op_rop1 );
            break;
        default: // other formats
            // we don't care
            break;
    } // switch
    read1 ( );
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

    // move pc
    pcbus_i.IN ( ).pullFrom ( pc_fi );
    pc_ir.latchFrom ( pcbus_i.OUT ( ) );

    //  move ir
    irbus_i.IN ( ).pullFrom ( ir_fi );
    ir_ir.latchFrom ( irbus_i.OUT ( ) );

    switch ( opc ) {
        case OPC_NOOP: // noop
            sprintf ( buff, "IR=NOOP " );
            cout << buff;
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
            leftShift_alu.OP2 ( ).pullFrom ( shift11 );
            npc_ir.latchFrom ( leftShift_alu.OUT ( ) );
            leftShift_alu.perform ( OP )
            break;
        case OPC_JMP:
        case OPC_JSR:
        case OPC_RET:
        case OPC_JSRC:
        case OPC_RPCC: // mf
            // do we need to do anything?

            break;
        default: // other formats
            // we don't care
            break;
    } // switch

    read2 ( );

} // issue2

// issue.cpp end
