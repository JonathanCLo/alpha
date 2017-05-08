/**
 * memory.cpp
 *
 * Author   Jonathan Lo < >
 */
#include "includes.h"

void memory ( );
void memory1 ( );
void memory2 ( );
void memory_writeback ( );
/**
 * memory
 * memory stage of pipeline. writes/read to/from memory. Writes to registers
 *
 */
void memory ( )
{
    memory1 ( );
    memory2 ( );

    // PIPELINE IS DONE
    char  buff [ 32 ];


    sprintf ( buff, "|pc=%02lx mf=%02lx out=%02lx addr=%04lx        |\n",
              pc_em.value ( ),
              out_em.value ( ),
              addr_em.value ( ) );
    cout << buff;
} // memory

/**
 * memory1
 *
 *
 */
void memory1 ( )
{
    // read mem_flag
    long mem_type = mem_flag.value ( );
    
    switch ( mem_type ) {
        case 0: // doesn't use memory
            // write back 
        case 1: // read to memory
        case 2: // write to memory
    }
    // read ir for RC dest register
    
    Clock::tick ( );
}

void memory_writeback ( )

/**
 * memory2
 *
 *
 */
void memory2 ( )
{
    // TODO
    Clock::tick ( );
}

// $(filename) end
