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

    char  buff [ 128 ]; // sprintf buffer

    sprintf ( buff, "|%-20s|%-20s|%-20s|%-20s|%-20s|\n",
              char* f = "FETCH",
              char* i = "ISSUE",
              char* r = "READ",
              char* e = "EXECUTE",
              char* m = "MEMORY" );
    cout << buff;
    sprintf ( buff, "|%-20s|%-20s|%-20s|%-20s|%-20s|\n",
              char* f = "--------",
              char* i = "--------",
              char* r = "--------",
              char* e = "--------",
              char* m = "--------" );
    cout << buff;

    while ( ! done ) // until we stop the simulation
        fetch ( );   // fetch stage
} // run_simulation

// $(filename) end
