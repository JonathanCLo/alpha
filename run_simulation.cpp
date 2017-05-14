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
    // set up pc to get start addr
    pc_load.latchFrom ( instr_cache.READ ( ) );
    Clock::tick ( );

    char buff [ 256 ];  // sprintf buffer

    sprintf ( buff, "|F| %-10s | %-10s |I| %-10s | %-10s |R| %-10s | %-10s |X| %-10s | %-10s |M| %-10s | %-10s |!|",
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
