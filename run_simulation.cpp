/**
 * run_simulation.cpp
 *
 * Original program:	Jim Heliotis, March 2000
 * Updates:
 *  2000/11/29:	wrc, restructured code
 *  2001/12/10:	wrc, modified simulation control
 *
 * runs the simulation.
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
    pc.latchFrom ( instr_cache.READ ( ) );
    Clock::tick ( );


    // ticks MUST BE HANDLED BY THE STAGES
    while ( ! done ) { // until we stop the simulation

        // FETCH
        fetch ( );

        // ISSUE
        issue ( );

        // REGISTER READ
        read ( );

        // EXECUTE
        execute ( );

        // MEMORY
        memory ( );
    }
} // run_simulation

// $(filename) end
