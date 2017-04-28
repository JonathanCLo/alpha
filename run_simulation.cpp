/**
 * run_simulation.cpp
 *
 * Author   Nathan Castle   < >
 *          Jonathan Lo     < >
 */

#include "includes.h"

/**
 * run_simulation
 *
 */
void run_simulation ( char* objfile )
{
    // step 1:  load the object file
    instr_cache.load ( objfile );
    data_cache.load ( objfile );

    // step 2:  set the entry point
    pc_f.latchFrom ( instr_cache.READ ( ) );
    Clock::tick ( );

    char [] buff = new char [ 32 ]; // sprintf buffer

    while ( ! done ) // until we stop the simulation
        fetch ( ); // fetch stage
} // run_simulation

// $(filename) end
