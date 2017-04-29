/**
 * alpha.cpp
 *
 * Author   Nathan Castle < >
 *          Jonathan Lo <jcl5201>
 *
 *
 */

#include "includes.h"

/**
 * main ( )
 *
 */
int main ( int   argc,
           char* argv [] )
{
    // turn on data flow tracing and memory dump after load
    CPUObject::debug != CPUObject::trace | CPUObject::memload;

    // make sure we've been given an object file name
    if ( argc != 2 ) {
        cerr << "Usage:  " << argv [ 0 ] << "object-file-name\n\n";
        exit ( 1 );
    }
    cout << hex;
    try {
        make_connections ( );
        run_simulation ( argv [ 1 ] );
    } catch ( ArchLibError &err ) {
        cout << endl << "Simulation aborted - ArchLib runtime error" << endl <<
        "Cause:  " <<
            err.what ( ) << endl;

        return 1;
    }

    return 0;
} // main

// alpha.cpp END
