/**
 * fetch.cpp
 *
 * Author   Jonathan Lo < >
 */
#include "includes.h"

void fetch ( );

/**
 * fetch
 *  fetches an instruction from the instruction buffer
 *  TICK TERMINATING
 */
void fetch ( )
{
    // set up MAR
    pcbus_f.IN ( ).pullFrom ( pc_f );
    instr_cache.MAR ( ).latchFrom ( pcbus_f.OUT ( ) );
    Clock::tick ( );

    // read from mem
    instr_cache.read ( );
    ir_fi.latchFrom ( instr_cache.READ ( ) );
    // move pc to pipeline
    pcbus_f.IN ( ).pullFrom ( pc_f );
    pc_fi.latchFrom ( pcbus_f.OUT ( ) );
    Clock::tick ( );

    issue ( );
} // fetch

// $(filename) end
