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
    fetch1 ( );

    fetch2 ( );

    char  buff [ 32 ];
    sprintf ( buff, "|pc=%02lx                   ", pc_f.value ( ) );
    cout << buff;
    issue ( );
} // fetch

/**
 * fetch1
 *
 *
 */
void fetch1 ( )
{
    // set up MAR
    pcbus_f.IN ( ).pullFrom ( pc_f );
    instr_cache.MAR ( ).latchFrom ( pcbus_f.OUT ( ) );
    Clock::tick ( );
}

/**
 * fetch2
 *
 *
 */
void fetch2 ( )
{
    // read from mem
    instr_cache.read ( );
    ir_fi.latchFrom ( instr_cache.READ ( ) );
    // move pc to pipeline
    pcbus_f.IN ( ).pullFrom ( pc_f );
    pc_fi.latchFrom ( pcbus_f.OUT ( ) );
    Clock::tick ( );
} // fetch2

// $(filename) end
