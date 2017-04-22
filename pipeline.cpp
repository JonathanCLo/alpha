/**
 * pipeline.cpp
 *
 * Author   Jonathan Lo < >
 */
#include "includes.h"

void pipeline ( );

/**
 * pipeline
 *
 * NOTE
 * stages MUST NOT move data into the pipeline registers themselves. results
 * must be move to stage outfeeders instead.
 * stages MUST pull data from the pipeline themselves.
 * stages MUST be TWO ticks.
 * stages MUST be TICK TERMINATING
 *
 * push_pipes uses one TICK
 */
void pipeline ( )
{
    fetch ( );
    issue ( );
    read ( );
    execute ( );
    memory ( );
    push_pipes ( );
}

/**
 * push_pipes
 *
 *
 */
void push_pipes ( )
{
    // SET PIPES FOR FETCH/ISSUE
    fetch_bus.IN ( ).pullFrom ( pc_f );
    pc_fi.latchFrom ( fetch_bus.OUT ( ) );
    Clock::tick ( );
}

// $(filename) end
