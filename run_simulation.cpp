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
    cout << "running";
    // step 1:  load the object file
    instr_cache.load ( objfile );
    data_cache.load ( objfile );

    // step 2:  set the entry point
    pc_load.latchFrom ( instr_cache.READ ( ) );
    Clock::tick ( );

    char buff [ 128 ];  // sprintf buffer

    sprintf ( buff, "|%-24s|%-24s|%-24s|%-24s|%-24s|\n",
              "FETCH",
              "ISSUE",
              "READ",
              "EXECUTE",
              "MEMORY" );
    cout << buff;
    sprintf ( buff, "|%-24s|%-24s|%-24s|%-24s|%-24s|\n",
              "------------------------",
              "------------------------",
              "------------------------",
              "------------------------",
              "------------------------" );
    cout << buff;

    while ( !done ) { // until we stop the simulation
        fetch1 ( );   // fetch stage
    }

} // run_simulation

// $(filename) end
