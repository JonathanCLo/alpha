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
    pc_f.latchFrom ( instr_cache.READ ( ) );
    Clock::tick ( );

    char  buff [ 128 ]; // sprintf buffer

    sprintf ( buff, "|%-18s|%-18s|%-18s|%-18s|%-18s|\n",
              "FETCH",
              "ISSUE",
              "READ",
              "EXECUTE",
              "MEMORY" );
    cout << buff;
    sprintf ( buff, "|%-18s|%-18s|%-18s|%-18s|%-18s|\n",
              "------------------",
              "------------------",
              "------------------",
              "------------------",
              "------------------" );
    cout << buff;

    while ( ! done ) // until we stop the simulation
        fetch ( );   // fetch stage
} // run_simulation

// $(filename) end
