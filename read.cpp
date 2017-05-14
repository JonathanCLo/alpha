/**
 * read.cpp
 *
 * Author   Jonathan Lo < >
 */

#include "includes.h"

long ra_value;

char pc1value_read [16];
char pc2value_read [16];
char opc1value_read[16];
char opc2value_read[16];
char dest2value_read[16];
char lit2value_read[16];
char print_read [128];

void read1 ( );
void read2 ( );
void noop1 ( );
void noop2 ( );
void memdisp1 ( );
void memdisp2 ( );
void branch1 ( );
void branch2 ( );
void jump1 ( );
void jump2 ( );
void operate1 ( );
void operate2 ( );
void use_npc ( );
void use_pc ( );
void move_ra ( );
void write_ra ( );
void move_rb ( );
void move_rc ( );

/**
 * read1
 */
void read1 ( )
{
    // reset indicator. this does not get used until tick2
    ir_purge = false;
    // move ir
    irbus_r1.IN ( ).pullFrom ( ir_ir );
    ir_r.latchFrom ( irbus_r1.OUT ( ) );
    // move pc
    pcbus_r1.IN ( ).pullFrom ( pc_ir );
    pc_r.latchFrom ( pcbus_r1.OUT ( ) );
    long opc = ir_re ( REG_SIZE - 1, REG_SIZE - 6 );
    switch ( opc ) {
        case OPC_NOOP:
            noop1 ( );
            break;
        case OPC_LDA:  case OPC_LDAH:
        case OPC_LDWU: case OPC_LDL:
        case OPC_STL:
            memdisp1 ( );
            break;
        case OPC_BEQ: case OPC_BGE:
        case OPC_BGT: case OPC_BLBC:
        case OPC_BLBS: case OPC_BLE:
        case OPC_BLT: case OPC_BNE:
        case OPC_BR:  case OPC_BSR: // B
            branch1 ( );
            break;
        case OPC_JMP:
            jump1 ( );
            break;
        case OPC_RPCC: // pcc
            // pcc ( );
            break;
        case OPC_ADDL:
            operate1 ( );
            break;
        default: // unknown
            done = true;

    } // switch

    sprintf ( pc1value_read, "pc=%04lx",
             pc_ir.value ( ) );
    sprintf ( opc1value_read, "opc=%03lx",
            opc );

} // read1

/**
 * read2
 */
void read2 ( )
{
    long opc = ir_r ( REG_SIZE - 1, REG_SIZE - 6 );

    switch ( opc ) {
        case OPC_NOOP:
            noop2 ( );
            break;
        case OPC_LDA:  case OPC_LDAH:
        case OPC_LDWU: case OPC_LDL:
        case OPC_STL:
            memdisp2 ( );
            break;
        case OPC_BEQ:  case OPC_BGE:
        case OPC_BGT:  case OPC_BLBC:
        case OPC_BLBS: case OPC_BLE:
        case OPC_BLT:  case OPC_BNE:
        case OPC_BR:   case OPC_BSR: // B
            branch2 ( );
            break;
        case OPC_JMP:
            jump2 ( );
            break;
        case OPC_RPCC: // pcc
            // pcc ( );
            break;
        case OPC_ADDL:
            operate2 ( );
            break;
        default: // unknown
            done = true;
    } // switch

    sprintf ( pc2value_read, "pc=%04lx",
              pc_r.value ( ) );
    sprintf ( opc2value_read, "opc=%03lx",
              opc );
    sprintf ( lit2value_read, "lit=%08lx",
              literal_r.value ( ) );
    sprintf ( dest2value_read, "dest=%08lx",
              dest_r.value ( ) );

    sprintf ( print_read, "|| %-10s %-10s | %-10s %-10s %-10s %-10s ",
              pc1value_read,
              opc1value_read,
              pc2value_read,
              opc2value_read,
              lit2value_read,
              dest2value_read );
    cout << print_read;

} // read2

/**
 * noop1
 */
void noop1 ( )
{ }

/**
 * noop2 ( )
 */
void noop2 ( )
{ }

/**
 * memdisp1
 */
void memdisp1 ( )
{
    // sign extend
    signExtalu_r.OP1 ( ).pullFrom ( npc_ir );
    signExtalu_r.OP2 ( ).pullFrom ( dispmask_g );
    dest_r.latchFrom ( signExtalu_r.OUT ( ) );
    signExtalu_r.perform ( BusALU::op_extendSign );
}

/**
 * memdisp2
 */
void memdisp2 ( )
{
    // move ir
    irbus_r2.IN ( ).pullFrom ( ir_r );
    ir_re.latchFrom ( irbus_r2.OUT ( ) );
    // move pc
    pcbus_r2.IN ( ).pullFrom ( pc_r );
    pc_re.latchFrom ( pcbus_r2.OUT ( ) );
    // move disp
    destbus_r2.IN ( ).pullFrom ( dest_r );
    disp_re.latchFrom ( destbus_r2.OUT ( ) );
} // memdisp2

/**
 * branch1
 * calculates the possible npc
 */
void branch1 ( )
{
    // sign extend
    signExtalu_r.OP1 ( ).pullFrom ( npc_ir );
    signExtalu_r.OP2 ( ).pullFrom ( shift7_g );
    dest_r.latchFrom ( signExtalu_r.OUT ( ) );
    signExtalu_r.perform ( BusALU::op_rashift );

    // get ra for comparison

    long ra = ir_ir ( REG_SIZE - 7, REG_SIZE - 11 );
    ra_value = (*regfile[ra] ).value ( );
    // grab the ra_value
    //TODO ???
} // branch1

/**
 * branch2
 * calculates if we take the branch
 *
 */
void branch2 ( )
{
    long branch = ir_re ( REG_SIZE - 1, REG_SIZE - 6 );

    // calculate if we are taking branch
    switch ( branch ) {
        case OPC_BEQ:
            if ( ra_value == 0 ) { // take the branch
                use_npc ( );
            } else { // not taken... continue onward
                use_pc ( );
            }
            break;
        case OPC_BGE:
            if ( ra_value >= 0 ) { // take the branch
                use_npc ( );
            } else { // not taken... continue onward
                use_pc ( );
            }
            break;
        case OPC_BGT:
            if ( ra_value > 0 ) { // take the branch
                use_npc ( );
            } else { // not taken... continue onward
                use_pc ( );
            }
            break;
        case OPC_BLBC:
            if ( ( ra_value & 1 ) == 0 ) { // take the branch
                use_npc ( );
            } else { // not taken... continue onward
                use_pc ( );
            }
            break;
        case OPC_BLBS:
            if ( ( ra_value & 1 ) == 1 ) { // take the branch
                use_npc ( );
            } else { // not taken... continue onward
                use_pc ( );
            }
            break;
        case OPC_BLE:
            if ( ra_value <= 0 ) { // take the branch
                use_npc ( );
            } else { // not taken... continue onward
                use_pc ( );
            }
            break;
        case OPC_BLT:
            if ( ra_value < 0 ) { // take the branch
                use_npc ( );
            } else { // not taken... continue onward
                use_pc ( );
            }
            break;
        case OPC_BNE:
            if ( ra_value != 0 ) { // take the branch
                use_npc ( );
            } else { // not taken... continue onward
                use_pc ( );
            }
            break;
        case OPC_BR:
        case OPC_BSR:
            use_npc ( );
            break;
        default: // dont care
            break;
    } // switch

} // branch2

/**
 * use_npc
 * change the pc in fetch to fetch the good instr and purge useless ones.
 */
void use_npc ( )
{
    // change pc_load
    changePC_bus.IN ( ).pullFrom ( dest_r );//npc_r
    pc_load.latchFrom ( changePC_bus.OUT ( ) );
    // discard pc_re // TODO do we?

    // indicate stage that it should purge instruction
    ir_purge = true;
    // toss curr inst
    irbus_r2.IN ( ).pullFrom ( noop_g );
    ir_re.latchFrom ( irbus_r2.OUT ( ) );

} // use_npc

/**
 * use_pc
 * use the old pc and move forward
 */
void use_pc ( )
{
    // move pc
    pcbus_r2.IN ( ).pullFrom ( pc_r );
    pc_re.latchFrom ( pcbus_r2.OUT ( ) );
    // move ir
    irbus_r2.IN ( ).pullFrom ( ir_r );
    ir_re.latchFrom ( irbus_r2.OUT ( ) );
}

/**
 * jumps
 */
void jump1 ( )
{
    // write to ra the pc
    write_ra ( );
    // TODO Data hazard?
    move_rb ( ); //get rb
} // jump1

/**
 * jump2
 *
 *
 */
void jump2 ( )
{
    destalu_r.OP1 ( ).pullFrom ( rb_r );
    destalu_r.OP2 ( ).pullFrom ( not3_g );
    pc_load.latchFrom ( destalu_r.OUT ( ) );
    destalu_r.perform ( BusALU::op_and );

    // purge curr instr
    // indicate stage that it should purge instruction
    ir_purge = true;
    // toss curr inst
    irbus_r2.IN ( ).pullFrom ( noop_g );
    ir_re.latchFrom ( irbus_r2.OUT ( ) );
} // jump2

/**
 * operate1
 */
void operate1 ( )
{
    long ind = ir_r ( REG_SIZE - 20 );

    move_ra ( );
    move_rc ( );
    switch ( ind ) {
        case 0: // register
            move_rb ( );
            break;
        case 1: // literal
            // get value
            litalu_r1.OP1 ( ).pullFrom ( ir_ir );
            litalu_r1.OP2 ( ).pullFrom ( literalmask_g );
            literal_r.latchFrom ( litalu_r1.OUT ( ) );
            litalu_r1.perform ( BusALU::op_and );
            break;
    } // switch

} // operate1

/**
 * operate2
 */
void operate2 ( )
{
    long ind = ir_r ( REG_SIZE - 20 );

    rabus_r2.IN ( ).pullFrom ( ra_r );
    ra_re.latchFrom ( rabus_r2.OUT ( ) );

    rcbus_r2.IN ( ).pullFrom ( rc_r );
    rc_re.latchFrom ( rcbus_r2.OUT ( ) );

    switch ( ind ) {
        case 0: // register
            rbbus_r2.IN ( ).pullFrom ( rb_r );
            rb_re.latchFrom ( rbbus_r2.OUT ( ) );
            break;
        case 1: // literal
            litalu_r2.OP1 ( ).pullFrom ( literal_r );
            litalu_r2.OP2 ( ).pullFrom ( literalShift_g );
            literal_re.latchFrom ( litalu_r1.OUT ( ) );
            litalu_r2.perform ( BusALU::op_rshift );
            break;
    } // switch

} // operate2

/**
 * move_ra
 * used in tick1
 *
 */
void move_ra ( )
{
    long ra = ir_ir ( REG_SIZE - 7, REG_SIZE - 11 ); // move ra

    rabus_r1.IN ( ).pullFrom ( pc_ir );
    ra_r.latchFrom ( rabus_r1.OUT ( ) );

} // move_ra

/**
 * write_ra
 * used in tick1
 *
 */
void write_ra ( )
{
    long ra = ir_ir ( REG_SIZE - 7, REG_SIZE - 11 );

    // move ra
    rabus_r1.IN ( ).pullFrom ( pc_ir );
    (*regfile[ra]).latchFrom ( rabus_r1.OUT ( ) );
}

/**
 * move_rb
 * used in tick1
 *
 */
void move_rb ( )
{
    long rb = ir_ir ( REG_SIZE - 12, REG_SIZE - 16 );

    // move ra
    rbbus_r1.IN ( ).pullFrom ( *regfile[rb] );
    rb_r.latchFrom ( rbbus_r1.OUT ( ) );
} // move_rb

/**
 * move_rc
 * used in tick1
 *
 */
void move_rc ( )
{
    long rc = ir_ir ( REG_SIZE - 28, 0 );

    // move ra
    rcbus_r1.IN ( ).pullFrom ( *regfile[rc] );
    rc_r.latchFrom ( rcbus_r1.OUT ( ) );

} // move_rc

// read.cpp end
