/**
 * pipeline.cpp
 *
 * Author    Jonathan Lo < >
 */

#include "includes.h"

void pipeline ( );
void tick1 ( );
void tick2 ( );

void pipeline ( ) 
{
    tick1 ( );
    tick2 ( );
}

void tick1 ( ) 
{
    fetch1 ( );
    issue1 ( );
    if ( done ) return;
    read1 ( );
    execute1 ( );
    memory1 ( );
    Clock::tick  ( );
}

void tick2  ( ) 
{
    fetch2 ( );
    issue2 ( );
    read2 ( );
    execute2 ( );
    memory2 ( );
    Clock::tick ( );
}

