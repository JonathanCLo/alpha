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
    pcbus_f.IN ( ).pullFrom ( pc_f );
    instr_cache.MAR ( ).latchFrom ( pcbus_f.OUT ( ) );
    decode1 ( );
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
    decode2 ( );
} // fetch2

// $(filename) end
