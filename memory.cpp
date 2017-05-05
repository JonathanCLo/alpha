/**
 * memory.cpp
 *
 * Author   Jonathan Lo < >
 */
#include "includes.h"

void memory ( );

/**
 * memory
 * memory stage of pipeline. writes/read to/from memory. Writes to registers
 *
 */
void memory ( )
{
    // TODO
    Clock::tick ( );

    Clock::tick ( );

    // PIPELINE IS DONE
    char buff [32];
    sprintf ( buff, "|pc=%02lx o=%02lx a=%04lx |\n",
              pc_em.value ( ),
              out_em.value ( ),
              addr_em.value ( ) );
    cout << buff;
}

// $(filename) end
