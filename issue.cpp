/**
 * issue.cpp
 *
 * Author   Jonathan Lo < >
 */

#include "includes.h"

void issue ( );
void detect ( );
void set_npc_branch ( );

/**
 * issue
 *
 *
 */
void issue ( )
{
    detect ( );

    char buff [ 32 ];
    sprintf ( buff, "|pc=%02lx ", pc_i.value ( ) );
    cout << buff;
    read ( );
} // fetch

/**
 * detect
 *
 *
 */
void detect ( )
{
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
            set_npc_branch ( );
            break;
        case OPC_JMP:
        case OPC_JSR:
        case OPC_RET:
        case OPC_JSRC:
        case OPC_RPCC: // mf
            sprintf ( buff, "IR=MF" );
            cout << buff;
            break;
        default: // other formats
            // we don't care
    } // switch
}     // detect

/**
 * set_npc
 * calculate possible new pc
 *
 */
void set_npc_branch ( )
{
    /**
     *  C equivalent
     *  long disp = ir_fi ( ADDR_SIZE - 12, 0 ); // get disp field
     *  npx_ir = ( disp << 11 );
     *
     */

    mask_alu.OP1 ( ).pullFrom ( ir_ir );
    mask_alu.OP2 ( ).pullFrom ( dispmask_i );
    aux_i.latchFrom ( mask_alu.OUT ( ) );
    mask_alu.perform ( BusALU::op_and );
    Clock::tick ( ); // found the required bits

    // move pc
    pcbus_i.IN ( ).pullFrom ( pc_fi );
    pc_ir.latchFrom ( pcbus_i.OUT ( ) );

    //  move ir
    irbus_i.IN ( ).pullFrom ( ir_fi );
    ir_ir.latchFrom ( irbus_i.OUT ( ) );

    // prep npc for calculation in read
    rightShift_alu.OP1 ( ).pullFrom ( aux_i );
    rightShift_alu.OP2 ( ).pullFrom ( shift11 );
    npc_ir.latchFrom ( rightShift_alu.OUT ( ) );

    Clock::tick ( );

} // set_npc_branch

// $(filename) end
