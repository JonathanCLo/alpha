/**
 * registerRead.cpp
 *
 * Author   Jonathan Lo < >
 */

#include "includes.h"

void read ( );
void md ( );

/**
 * md
 *
 *
 */
void md ( )
{
    long  ra   = ir ( REG_SiZE - 7, REG_SIZE - 11 );
    long  rb   = ir ( REG_SIZE - 12, REG_SIZE - 16 );
    long  disp = ir ( REG_SIZE - 17, 0 );


    // move ir
    irbus_r.IN ( ).pullFrom ( ir_re );
    ir_r.latchFrom ( irbus_r.OUT ( ) );

    // move pc
    pcbus_r.IN ( ).pullFrom ( pc_ir );
    pc_r.latchFrom ( pcbus_r.OUT ( ) );

    Clock::tick ( );
    // move ra
    ra_re.latchFrom ( rabus_r.OUT ( ) );

    switch ( ra ) {
        case 0:
            rabus_r.IN ( ).pullFrom ( r0 );
            break;
        case 1:
            rabus_r.IN ( ).pullFrom ( r1 );
            break;
        case 2:
            rabus_r.IN ( ).pullFrom ( r2 );
            break;
        case 3:
            rabus_r.IN ( ).pullFrom ( r3 );
            break;
        case 4:
            rabus_r.IN ( ).pullFrom ( r4 );
            break;
        case 5:
            rabus_r.IN ( ).pullFrom ( r5 );
            break;
        case 6:
            rabus_r.IN ( ).pullFrom ( r6 );
            break;
        case 7:
            rabus_r.IN ( ).pullFrom ( r7 );
            break;
        case 8:
            rabus_r.IN ( ).pullFrom ( r8 );
            break;
        case 9:
            rabus_r.IN ( ).pullFrom ( r9 );
            break;
        case 10:
            rabus_r.IN ( ).pullFrom ( r10 );
            break;
        case 11:
            rabus_r.IN ( ).pullFrom ( r11 );
            break;
        case 12:
            rabus_r.IN ( ).pullFrom ( r12 );
            break;
        case 13:
            rabus_r.IN ( ).pullFrom ( r13 );
            break;
        case 14:
            rabus_r.IN ( ).pullFrom ( r14 );
            break;
        case 15:
            rabus_r.IN ( ).pullFrom ( r15 );
            break;
        case 16:
            rabus_r.IN ( ).pullFrom ( r16 );
            break;
        case 17:
            rabus_r.IN ( ).pullFrom ( r17 );
            break;
        case 18:
            rabus_r.IN ( ).pullFrom ( r18 );
            break;
        case 19:
            rabus_r.IN ( ).pullFrom ( r19 );
            break;
        case 20:
            rabus_r.IN ( ).pullFrom ( r20 );
            break;
        case 21:
            rabus_r.IN ( ).pullFrom ( r21 );
            break;
        case 22:
            rabus_r.IN ( ).pullFrom ( r22 );
            break;
        case 23:
            rabus_r.IN ( ).pullFrom ( r23 );
            break;
        case 24:
            rabus_r.IN ( ).pullFrom ( r24 );
            break;
        case 25:
            rabus_r.IN ( ).pullFrom ( r25 );
            break;
        case 26:
            rabus_r.IN ( ).pullFrom ( r26 );
            break;
        case 27:
            rabus_r.IN ( ).pullFrom ( r27 );
            break;
        case 28:
            rabus_r.IN ( ).pullFrom ( r28 );
            break;
        case 29:
            rabus_r.IN ( ).pullFrom ( r29 );
            break;
        case 30:
            rabus_r.IN ( ).pullFrom ( r30 );
            break;
        case 31:
            rabus_r.IN ( ).pullFrom ( r31 );
            break;
        default: // unknown
    } // switch

    // move rb
    rb_re.latchFrom ( rbbus_r.OUT ( ) );

    switch ( rb ) {
        case 0:
            rbbus_r.IN ( ).pullFrom ( r0 );
            break;
        case 1:
            rbbus_r.IN ( ).pullFrom ( r1 );
            break;
        case 2:
            rbbus_r.IN ( ).pullFrom ( r2 );
            break;
        case 3:
            rbbus_r.IN ( ).pullFrom ( r3 );
            break;
        case 4:
            rbbus_r.IN ( ).pullFrom ( r4 );
            break;
        case 5:
            rbbus_r.IN ( ).pullFrom ( r5 );
            break;
        case 6:
            rbbus_r.IN ( ).pullFrom ( r6 );
            break;
        case 7:
            rbbus_r.IN ( ).pullFrom ( r7 );
            break;
        case 8:
            rbbus_r.IN ( ).pullFrom ( r8 );
            break;
        case 9:
            rbbus_r.IN ( ).pullFrom ( r9 );
            break;
        case 10:
            rbbus_r.IN ( ).pullFrom ( r10 );
            break;
        case 11:
            rbbus_r.IN ( ).pullFrom ( r11 );
            break;
        case 12:
            rbbus_r.IN ( ).pullFrom ( r12 );
            break;
        case 13:
            rbbus_r.IN ( ).pullFrom ( r13 );
            break;
        case 14:
            rbbus_r.IN ( ).pullFrom ( r14 );
            break;
        case 15:
            rbbus_r.IN ( ).pullFrom ( r15 );
            break;
        case 16:
            rbbus_r.IN ( ).pullFrom ( r16 );
            break;
        case 17:
            rbbus_r.IN ( ).pullFrom ( r17 );
            break;
        case 18:
            rbbus_r.IN ( ).pullFrom ( r18 );
            break;
        case 19:
            rbbus_r.IN ( ).pullFrom ( r19 );
            break;
        case 20:
            rbbus_r.IN ( ).pullFrom ( r20 );
            break;
        case 21:
            rbbus_r.IN ( ).pullFrom ( r21 );
            break;
        case 22:
            rbbus_r.IN ( ).pullFrom ( r22 );
            break;
        case 23:
            rbbus_r.IN ( ).pullFrom ( r23 );
            break;
        case 24:
            rbbus_r.IN ( ).pullFrom ( r24 );
            break;
        case 25:
            rbbus_r.IN ( ).pullFrom ( r25 );
            break;
        case 26:
            rbbus_r.IN ( ).pullFrom ( r26 );
            break;
        case 27:
            rbbus_r.IN ( ).pullFrom ( r27 );
            break;
        case 28:
            rbbus_r.IN ( ).pullFrom ( r28 );
            break;
        case 29:
            rbbus_r.IN ( ).pullFrom ( r29 );
            break;
        case 30:
            rbbus_r.IN ( ).pullFrom ( r30 );
            break;
        case 31:
            rbbus_r.IN ( ).pullFrom ( r31 );
            break;
        default: // unknown
    } // switch

    Clock::tick ( );
} // md

/**
 * read
 *
 *
 */
void read ( )
{
    long  opc = ir ( REG_SIZE - 1, REG_SIZE - 6 );

    char  buff [ 8 ];


    sprintf ( buff, "opc=%03lx", opc );
    cout << buff;

    switch ( opc ) {

        case 8:
        case 9:
        case 10:
        case 40:
        case 12:
        case 44:
        case 13: // MD
            md ( );
            break;
        case 57:
        case 61:
        case 63:
        case 56:
        case 60:
        case 59:
        case 58:
        case 61:
        case 48:
        case 52: // B
            break;
        default:
    } // switch


    execute ( );
} // read

// $(filename) end
