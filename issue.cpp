/**
 * issue.cpp
 *
 * Author   Jonathan Lo < >
 */

#include "includes.h"

void issue ( );
void issue1 ( );
void issue2 ( );
void detect_branch ( );

/**
 * detect_branch
 *
 *
 */
void detect_branch ( )
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
    }
}

/**
 * issue
 *
 *
 * $(javaparem)
 * @throws
 */
void issue ( )
{
    issue1 ( );
    issue2 ( );

    char buff [ 32 ];
    sprintf ( buff, "|pc=%02lx ", pc_i.value ( ) );
    cout << buff;
    read ( );
} // fetch

/**
 * issue1
 *
 *
 */
void issue1 ( )
{
    // move pc and ir
    pcbus_i.IN ( ).pullFrom ( pc_fi );
    pc_i.latchFrom ( pcbus_i.OUT ( ) );

    irbus_i.IN ( ).pullFrom ( ir_fi );
    ir_i.latchFrom ( irbus_i.OUT ( ) );

    Clock::tick ( );
} // issue1

/**
 * issue2
 *
 *
 */
void issue2 ( )
{
    detect_branch ( );

    // move pc to pipe
    pcbus_i.IN ( ).pullFrom ( pc_i );
    pc_ir.latchFrom ( pcbus_i.OUT ( ) );

    irbus_i.IN ( ).pullFrom ( ir_i );
    ir_ir.latchFrom ( irbus_i.OUT ( ) );

    Clock::tick ( );
} // issue2

// $(filename) end
