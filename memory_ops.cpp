/**
 * memory_ops.cpp
 *
 * Author   Nathan Caster   < >
 *          Jonathan Lo     <jcl5201>
 */

#include "includes.h"

void instr_read ( );
void  data_read ( StorageObject );
void  data_write ( StorageObject );

/**
 * instr_read
 *  reads from the instruction cache using PC
 *  instruction is sent to ir_f
 */
void instr_read ( )
{
    addr_ibus.IN ( ).pullFrom ( pc );
    instr_cache.MAR ( ).latchFrom ( addr_ibus.OUT ( ) );
    Clock::tick ( );
    instr_cache.read ( );
    ir_f.latchFrom ( instr_cache.READ ( ) );
    Clock::tick ( );
}

/**
 * data_read
 *
 *
 */
void data_read ( )
{

}

// $(filename) END
