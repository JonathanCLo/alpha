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
    char print_pipes [200];
    char pipes [12];
    sprintf ( pipes, "----------" );
    sprintf ( print_pipes, 
              "|F| %-10s | %-10s |I| %-10s | %-10s |R| %-10s | %-10s |X| %-10s | %-10s |M| %-10s | %-10s |!|",
              pipes,
              pipes,
              pipes,
              pipes,
              pipes,
              pipes,
              pipes,
              pipes,
              pipes,
              pipes );
    cout << print_pipes << endl;
    tick1 ( );
    tick2 ( );
    cout << "|!|"  << endl;
}

void tick1 ( ) 
{
    fetch1 ( );
    issue1 ( );
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

