/**
 * issue.cpp
 *
 * Author   Jonathan Lo < >
 */

#include "includes.h"

void issue ( );

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

    char  buff [ 32 ];
    sprintf ( buff, "|pc=%02lx             ", pc_i.value ( ) );
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
    // move pc to pipe
    pcbus_i.IN ( ).pullFrom ( pc_i );
    pc_ir.latchFrom ( pcbus_i.OUT ( ) );

    irbus_i.IN ( ).pullFrom ( ir_i );
    ir_ir.latchFrom ( irbus_i.OUT ( ) );

    Clock::tick ( );
} // issue2

// $(filename) end
