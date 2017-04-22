/**
 * make_connections
 *
 * Author   Nathan Castle   < >
 *          Jonathan Lo     < >
 */

#include "includes.h"
void make_connections ( );
void make_connections_fetch ( );
void make_connections_issue ( );
void make_connections_read ( );
void make_connections_execute ( );
void make_connections_memory ( );

/**
 * make_connections
 *  establishes all the wiring and connections of the hardware
 *
 */
void make_connections ( )
{
    make_connections_fetch ( );
    // FETCH-ISSUE pipeline connections
    pc_f.connectsTo ( fetch_bus.IN ( ) );
    pc_fi.connectsTo ( fetch_bus.OUT ( ) );
    ir_f.connectsTo ( fetch_bus.IN ( ) );
    ir_fi.connectsTo ( fetch_bus.OUT ( ) );
    //
    make_connections_issue ( );
    // ISSUE-READ pipeline connections
    //
    make_connections_read ( );
    // READ-EXECUTE pipeline connections
    //
    make_connections_execute ( );
    // EXECUTE-MEMORY pipeline connections
    //
    make_connections_memory ( );

} // make_connections

/**
 * make_connections_fetch
 *  makes hardware connections within the fetch stage. EXCLUDES PIPELINE
 *
 */
void make_connections_fetch ( )
{
    instr_cache.MAR ( ).connectsTo ( addr_ibus.OUT ( ) );
    pc_f.connectsTo ( addr_ibus.IN ( ) );
    pc_f.connectsTo ( fetch_bus.IN ( ) );
    ir_f.connectsTo ( data_ibus.OUT ( ) );
    data_ibus.OUT ( ).connectsTo ( instr_cache.READ ( ) );
}

/**
 * make_connections_issue
 *  makes hardware connections within the issue stage. EXCLUDES PIPELINE
 *
 */
void make_connections_issue ( )
{

}

/**
 * make_connections_read
 *  makes hardware connections within the read stage. EXCLUDES PIPELINE
 *
 */
void make_connections_read ( )
{

}

/**
 * make_connections_execute
 *  makes hardware connections within the execute stage. EXCLUDES PIPELINE
 *
 */
void make_connections_execute ( )
{

}

/**
 * make_connections_memory
 *  makes hardware connections within the memory stage. EXCLUDES PIPELINE
 *
 */
void make_connections_memory ( )
{

}

// $(filename) end
