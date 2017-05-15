/**
 * issue.cpp
 *
 * Author   Jonathan Lo < >
 */
#include "includes.h"
#include "hazards.h"

void issue1 ( );
void issue2 ( );
void detect ( );
void set_npc_branch ( );

char pc1value_issue [16];
char pc2value_issue [16];
char ir1value_issue [16];
char ir2value_issue [16];
char purge2value_issue [16];
char print_issue [64];

/**
 * detect
 *
 *
 */
void issue1 ( )
{
    if ( !ir_fi.zero ( ) ) {
        //advance_hd ( );
    }
    // move ir
    irbus_i1.IN ( ).pullFrom ( ir_fi );
    ir_i.latchFrom ( irbus_i1.OUT ( ) );

    // move pc
    pcbus_i1.IN ( ).pullFrom ( pc_fi );
    pc_i.latchFrom ( pcbus_i1.OUT ( ) );

    long opc = ir_fi ( REG_SIZE - 1, REG_SIZE - 6 );
    sprintf ( pc1value_issue, "pc=%04lx",
              pc_fi.value ( ) );
    sprintf ( ir1value_issue, "ir=%08lx",
              ir_fi.value ( ) );

    // calculate ra
    long ra = ir_fi ( REG_SIZE - 7, REG_SIZE - 11 );
    long ra_value = ( *regfile[ra] ).value ( );

    switch ( opc ) {
        case OPC_PAL:                   // PAL
            if ( ir_fi.value ( ) == 1 ) // halt
                done = true;
            break;
        case OPC_BEQ:
            // noop the current instr or pass it through
            if ( ra_value == 0 ) {
                ir_i.clear ( );
            } else {
                irbus_i1.IN ( ).pullFrom ( ir_fi );
                ir_i.latchFrom ( irbus_i1.OUT ( ) );
            }
            // grab the required bits
            destalu_i1.OP1 ( ).pullFrom ( ir_fi );
            destalu_i1.OP2 ( ).pullFrom ( dispmask_g );
            aux_i.latchFrom ( destalu_i1.OUT ( ) );
            destalu_i1.perform ( BusALU::op_and );
            break;

        case OPC_BGE:
            if ( ra_value >= 0 ) {
                ir_i.clear ( );
            } else {
                irbus_i1.IN ( ).pullFrom ( ir_fi );
                ir_i.latchFrom ( irbus_i1.OUT ( ) );
            }
            // grab the required bits
            destalu_i1.OP1 ( ).pullFrom ( ir_fi );
            destalu_i1.OP2 ( ).pullFrom ( dispmask_g );
            aux_i.latchFrom ( destalu_i1.OUT ( ) );
            destalu_i1.perform ( BusALU::op_and );
            break;

        case OPC_BGT:
            if ( ra_value > 0 ) {
                ir_i.clear ( );
            } else {
                irbus_i1.IN ( ).pullFrom ( ir_fi );
                ir_i.latchFrom ( irbus_i1.OUT ( ) );
            }
            // grab the required bits
            destalu_i1.OP1 ( ).pullFrom ( ir_fi );
            destalu_i1.OP2 ( ).pullFrom ( dispmask_g );
            aux_i.latchFrom ( destalu_i1.OUT ( ) );
            destalu_i1.perform ( BusALU::op_and );
            break;

        case OPC_BLBC:
            if ( ra_value & 0x1 == 0 ) {
                ir_i.clear ( );
            } else {
                irbus_i1.IN ( ).pullFrom ( ir_fi );
                ir_i.latchFrom ( irbus_i1.OUT ( ) );
            }
            // grab the required bits
            destalu_i1.OP1 ( ).pullFrom ( ir_fi );
            destalu_i1.OP2 ( ).pullFrom ( dispmask_g );
            aux_i.latchFrom ( destalu_i1.OUT ( ) );
            destalu_i1.perform ( BusALU::op_and );
            break;

        case OPC_BLBS:
            if ( ra_value & 0x1 == 1 ) {
                ir_i.clear ( );
            } else {
                irbus_i1.IN ( ).pullFrom ( ir_fi );
                ir_i.latchFrom ( irbus_i1.OUT ( ) );
            }
            // grab the required bits
            destalu_i1.OP1 ( ).pullFrom ( ir_fi );
            destalu_i1.OP2 ( ).pullFrom ( dispmask_g );
            aux_i.latchFrom ( destalu_i1.OUT ( ) );
            destalu_i1.perform ( BusALU::op_and );
            break;

        case OPC_BLE:
            if ( ra_value <= 0 ) {
                ir_i.clear ( );
            } else {
                irbus_i1.IN ( ).pullFrom ( ir_fi );
                ir_i.latchFrom ( irbus_i1.OUT ( ) );
            }
            // grab the required bits
            destalu_i1.OP1 ( ).pullFrom ( ir_fi );
            destalu_i1.OP2 ( ).pullFrom ( dispmask_g );
            aux_i.latchFrom ( destalu_i1.OUT ( ) );
            destalu_i1.perform ( BusALU::op_and );
            break;

        case OPC_BLT:
            if ( ra_value < 0 ) {
                ir_i.clear ( );
            } else {
                irbus_i1.IN ( ).pullFrom ( ir_fi );
                ir_i.latchFrom ( irbus_i1.OUT ( ) );
            }
            // grab the required bits
            destalu_i1.OP1 ( ).pullFrom ( ir_fi );
            destalu_i1.OP2 ( ).pullFrom ( dispmask_g );
            aux_i.latchFrom ( destalu_i1.OUT ( ) );
            destalu_i1.perform ( BusALU::op_and );
            break;

        case OPC_BNE:
            if ( ra_value != 0 ) {
                ir_i.clear ( );
            } else {
                irbus_i1.IN ( ).pullFrom ( ir_fi );
                ir_i.latchFrom ( irbus_i1.OUT ( ) );
            }
            // grab the required bits
            destalu_i1.OP1 ( ).pullFrom ( ir_fi );
            destalu_i1.OP2 ( ).pullFrom ( dispmask_g );
            aux_i.latchFrom ( destalu_i1.OUT ( ) );
            destalu_i1.perform ( BusALU::op_and );
            break;
        case OPC_BR:
        case OPC_BSR: // branches
            // grab the required bits
            ir_i.clear ( );
            destalu_i1.OP1 ( ).pullFrom ( ir_fi );
            destalu_i1.OP2 ( ).pullFrom ( dispmask_g );
            aux_i.latchFrom ( destalu_i1.OUT ( ) );
            destalu_i1.perform ( BusALU::op_and );
            break;
        case OPC_JMP:
        case OPC_JSR:
        case OPC_RET:
        case OPC_JSRC:
            ir_i.clear ( );
            destalu_i1.OP1 ( ).pullFrom ( pc_fi );
            destalu_i1.OP2 ( ).pullFrom ( dispmask_g );
            aux_i.latchFrom ( destalu_i1.OUT ( ) );
            destalu_i1.perform ( BusALU::op_rop1 );
            break;
        default: // other formats
            // we don't care
            break;
    } // switch
}     // detect

/**
 * set_npc
 * calculate possible new pc
 *
 */
void issue2 ( )
{
    long opc = ir_i ( REG_SIZE - 1, REG_SIZE - 6 );

    sprintf ( pc2value_issue, "pc=%04lx",
              pc_i.value ( ) );
    sprintf ( ir2value_issue, "ir=%08lx",
              ir_fi.value ( ) );

    irbus_i2.IN ( ).pullFrom ( ir_i );
    ir_ir.latchFrom ( irbus_i2.OUT ( ) );

    // move pc
    pcbus_i2.IN ( ).pullFrom ( pc_i );
    pc_ir.latchFrom ( pcbus_i2.OUT ( ) );

    switch ( opc ) {
        case OPC_PAL: // noop
            break;
        case OPC_BEQ:
        case OPC_BGE:
        case OPC_BGT:
        case OPC_BLBC:
        case OPC_BLBS:
        case OPC_BLE:
        case OPC_BLT:
        case OPC_BNE:
        case OPC_BR:
        case OPC_BSR: // branches
            destalu_i2.OP1 ( ).pullFrom ( pc_i );
            destalu_i2.OP2 ( ).pullFrom ( aux_i );
            pc_load.latchFrom ( destalu_i2.OUT ( ) );
            destalu_i2.perform ( BusALU::op_add );
            break;
        case OPC_JMP: // mf
            destalu_i2.OP1 ( ).pullFrom ( pc_i );
            destalu_i2.OP2 ( ).pullFrom ( aux_i );
            pc_load.latchFrom ( destalu_i2.OUT ( ) );
            destalu_i2.perform ( BusALU::op_add );
            break;
        default: // other formats
            // we don't care
            break;
    } // switch
    sprintf ( print_issue, "|I| %-7s %-7s | %-7s %-7s %-7s ",
              pc1value_issue,
              ir1value_issue,
              pc2value_issue,
              ir2value_issue,
              purge2value_issue );
    cout << print_issue;
} // issue2

// issue.cpp end
