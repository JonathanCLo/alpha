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
    pc_load.latchFrom ( instr_cache.READ ( ) );
    Clock::tick ( );

    char buff [ 128 ];  // sprintf buffer

    sprintf ( buff, "|| %-10s | %-10s || %-10s | %-10s || %-10s | %-10s || %-10s | %-10s || %-10s | %-10s ||",
              "FETCH1",
              "FETCH2",
              "ISSUE1",
              "ISSUE2",
              "READ1",
              "READ2",
              "EXECUTE1",
              "EXECUTE2",
              "MEMORY1",
              "MEMORY2" );
    cout << buff << endl;
   
    while ( !done ) { // until we stop the simulation
        pipeline ( );   // fetch stage
    }

} // run_simulation

// $(filename) end
