/**
 * fetch.cpp
 *
 * Author   Jonathan Lo < >
 */
#include "includes.h"

void fetch1 ( );
void fetch2 ( );

/**
 * fetch1
 *
 *
 */
void fetch1 ( )
{
    // set up MAR
    pcbus_load.IN ( ).pullFrom ( pc_load );
    instr_cache.MAR ( ).latchFrom ( pcbus_load.OUT ( ) );

    // pc_f <- pc__f
    pcbus_f1.IN ( ).pullFrom ( pc_load );
    pc_f.latchFrom ( pcbus_f1.OUT ( ) );

    issue1 ( );

} // fetch1

/**
 * fetch2
 *
 *
 */
void fetch2 ( )
{
    if ( ir_purge ) {
        irfi_noop_bus.IN ( ).pullFrom ( noop_g );
        ir_fi.latchFrom ( irfi_noop_bus.OUT ( ) );
    } else { // read from mem
        instr_cache.read ( );
        ir_fi.latchFrom ( instr_cache.READ ( ) );
    }
    // move pc to pipeline

    pcbus_f.IN ( ).pullFrom ( pc_f );
    pc_fi.latchFrom ( pcbus_f.OUT ( ) );
    issue2 ( );
} // fetch2

// $(filename) end
