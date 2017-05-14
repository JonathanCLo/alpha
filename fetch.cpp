/**
 * fetch.cpp
 *
 * Author   Jonathan Lo < >
 */
#include "includes.h"

void fetch1 ( );
void fetch2 ( );

char pc1value_fetch [16];
char pc2value_fetch [16];
char print_fetch [128];

/**
 * fetch1
 *
 *
 */
void fetch1 ( )
{
    // set up MAR
    sprintf ( pc1value_fetch, "pc=%04lx", pc_load.value ( ) );
    pcbus_load.IN ( ).pullFrom ( pc_load );
    instr_cache.MAR ( ).latchFrom ( pcbus_load.OUT ( ) );

    // pc_f <- pc__f
    pcbus_f1.IN ( ).pullFrom ( pc_load );
    pc_f.latchFrom ( pcbus_f1.OUT ( ) );

} // fetch1

/**
 * fetch2
 *
 *
 */
void fetch2 ( )
{ 
    sprintf ( pc2value_fetch, "pc=%04lx", pc_f.value ( ) ); 
    if ( ir_purge ) {
        irbus_f2.IN ( ).pullFrom ( noop_g );
        ir_fi.latchFrom ( irbus_f2.OUT ( ) );
    } else { // read from mem
        instr_cache.read ( );
        ir_fi.latchFrom ( instr_cache.READ ( ) );
    }
    // move pc to pipeline

    pcbus_f2.IN ( ).pullFrom ( pc_f );
    pc_fi.latchFrom ( pcbus_f2.OUT ( ) );
    pc_load.incr ( );
    sprintf ( print_fetch, "|| %-10s | %-10s ",
              pc1value_fetch,
              pc2value_fetch );
    cout << print_fetch;
              
} // fetch2

// $(filename) end
