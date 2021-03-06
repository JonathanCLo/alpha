/**
 * execute.cpp
 *
 * Author   Jonathan Lo < >
 * Contributor: Nathan Castle
 */
#include "includes.h"
#include "hazards.h"

char pc1value_ex [16];
char opc1value_ex [16];
char ra1value_ex [16];
char rb1value_ex [16];
char rc1value_ex [16];
char lit1value_ex [16];
char disp1value_ex [16];
char opc2value_ex [16];
char addr2value_ex [16];
char shift2value_ex [16];
char arith2value_ex [16];
char print1_ex [256];
char print2_ex [256];

void execute ( );

/**
 * ex_mem_s1
 *
 *
 */
void ex_mem_s1 ( int opcode )
{
    ex_internal_shift.latchFrom ( shift_alu.OUT ( ) );
    shift_alu.OP1 ( ).pullFrom ( disp_re );
    shift_alu.OP2 ( ).pullFrom ( const16_g );
    if ( opcode == OPC_LDAH ) { shift_alu.perform ( BusALU::op_lshift ); return; } else { shift_alu.perform ( BusALU::op_rop1 ); return; } //disp already in position
    ex_internal_addr.latchFrom ( addr_alu.OUT ( ) );
    addr_alu.OP1 ( ).pullFrom ( rb_re );
    addr_alu.perform ( BusALU::op_rop1 );
} // ex_mem_s1

/**
 * ex_mem_s2
 *
 *
 */
void ex_mem_s2 ( int opcode )
{
    addr_alu.OP1 ( ).pullFrom ( ex_internal_addr );
    addr_alu.OP2 ( ).pullFrom ( ex_internal_shift );
    addr_alu.perform ( BusALU::op_add );
    //ex_out_addr.latchFrom(addr_alu.OUT()); - cheating in mem
    data_cache.MAR ( ).latchFrom ( addr_alu.OUT ( ) );
    return;
}


/**
 * ex_arith_s1
 *
 *
 */
void ex_arith_s1 ( int	opcode,
                   int	func,
                   bool imm )
{
    //accounts for all arithmetic instructions
    exec_read_after_write(imm); //handle both hazard and no-hazard
    if (opcode==17)
        ex_internal_addr.latchFrom ( addr_alu.OUT ( ) );
    //handle manipulation of Rb/Li at this pointer
    if ( opcode == 17 && ( func==8 || func==72 || func==40 ) ) {
        addr_alu.perform ( BusALU::op_not );
    }//BIC, EQV/ORNOT
    else if ( opcode == 17 ) {
        addr_alu.perform ( BusALU::op_rop1 );
    }

    ex_internal_arith.latchFrom ( arith_alu.OUT ( ) );
    //first conditional
    if ( opcode == 17 ) { //conditional moves
        arith_alu.perform ( BusALU::op_rop1 );
    }
    //  then normal
    else if ( opcode != 16 || ( func !=18 && func != 2 && func != 11 && func != 27 ) ) { //everything else
        arith_alu.perform ( BusALU::op_rop1 );
    } else if ( opcode == 16 && ( func == 2 || func == 11 ) ) { //Scaled 4
        arith_alu.OP2 ( ).pullFrom ( const2_g );
        arith_alu.perform ( BusALU::op_lshift );
    } else if ( opcode == 16 && ( func == 18 || func == 27 ) ) { //scaled 8
        arith_alu.OP2 ( ).pullFrom ( const3_g );
        arith_alu.perform ( BusALU::op_lshift );
    }
} // ex_arith_s1

/**
 * ex_arith_s2
 *
 *
 */
void ex_arith_s2 ( int opcode,
                   int func )
{
    if ( opcode == 17 ) {
        if ( func == 36 && !ex_internal_arith.zero ( ) ) { return; }                                      //CMOVEQ //TODO tell memory to no-op
        if ( func == 70 && !ex_internal_arith.zero ( ) && ex_internal_arith ( 31 ) == 1 ) { return; }     //CMOVGE
        if ( func == 102 && ( ex_internal_arith.zero ( ) || ex_internal_arith ( 31 ) == 1 ) ) { return; } //CMOVGT
        if ( func == 22 && ex_internal_arith ( 0 ) == 1 ) { return; }                                     //CMOVLBC
        if ( func == 20 && ex_internal_arith ( 0 ) == 0 ) { return; }                                     //CMOVLBS
        if ( func == 100 && !ex_internal_arith.zero ( ) && ex_internal_arith ( 31 ) == 0 ) { return; }    //CMOVLE
        if ( func == 68 && ( ex_internal_arith.zero ( ) || ex_internal_arith ( 31 ) == 0 ) ) { return; }  //CMOVLT
        if ( func == 38 && ex_internal_arith.zero ( ) ) { return; }                                       //CMOVNE
    }
    arith_alu.OP1 ( ).pullFrom ( ex_internal_arith );
    arith_alu.OP2 ( ).pullFrom ( ex_internal_addr );
    out_em.latchFrom ( arith_alu.OUT ( ) );
    if ( opcode == 16 && ( func == 0 || func == 2 || func == 18 ) ) { arith_alu.perform ( BusALU::op_add ); } else if ( opcode == 16 && ( func == 9 || func == 11 || func == 27 ) ) {
        arith_alu.perform ( BusALU::op_sub );
    } else if ( opcode == 17 && ( func == 8 || func == 0 ) ) {
        arith_alu.perform ( BusALU::op_and );
    } else if ( opcode == 17 && ( func == 32 || func == 40 ) ) {
        arith_alu.perform ( BusALU::op_or );
    } else if ( opcode == 17 && ( func == 72 || func == 64 ) ) {
        arith_alu.perform ( BusALU::op_xor );
    }
    return;
} // ex_arith_s2
/**
 * execute
 *  executes the instruction
 */
void execute1 ( )
{
    int opcode = ir_re ( 31, 26 );
    bool imm   = ir_re ( 12 ) != 0;
    int func   = ir_re ( 11, 5 );
    sprintf ( pc1value_ex, "pc=%04lx",
              pc_re.value ( ) );
    sprintf ( opc1value_ex, "opc=%03d",
              opcode );
    sprintf ( ra1value_ex, "ra=%08lx",
              ra_re.value ( ) );
    sprintf ( rb1value_ex, "rb=%08lx",
              rb_re.value ( ) );
    sprintf ( rc1value_ex, "rc=%08lx",
              rc_re.value ( ) );
    sprintf ( lit1value_ex, "lit=%08lx",
              literal_re.value ( ) );
    sprintf ( disp1value_ex, "disp=%08lx",
              disp_re.value ( ) );
    if (detect_read_after_load_dist()) {
        memory_stall();
    }
    //preserve re for cycle 2
    switch ( opcode ) {
        case OPC_LDA: case OPC_LDAH: case OPC_LDBU:
        case OPC_LDL: case OPC_LDWU:
        case OPC_STL: case OPC_STW:
            ex_mem_s1 ( opcode );
            break;
        case OPC_ADDL: case OPC_AND:
            ex_arith_s1 ( opcode, func, imm );
            break;
        case OPC_BGE: case OPC_BGT: case OPC_BEQ: case OPC_BLBS:
        case OPC_BLE: case OPC_BLT: case OPC_BNE: case OPC_BR:
        case OPC_BSR:
            //ex_br_s1(opcode, func);
            break;
        default:
            break;
    } // switch
    irbus_e1.IN ( ).pullFrom ( ir_re );
    ex_internal_ir.latchFrom ( irbus_e1.OUT ( ) );

} // execute1

/**
 * execute2
 *
 *
 */
void execute2 ( )
{
    int opcode = ex_internal_ir ( 31, 26 );
    bool imm   = ex_internal_ir ( 12 ) != 0;
    int func   = ex_internal_ir ( 11, 5 );

    switch ( opcode ) {
        case OPC_LDA: case OPC_LDAH:
        case OPC_LDL: case OPC_LDWU:
        case OPC_STW: case OPC_LDBU:
            mem_flag.latchFrom ( read_mem.OUT ( ) );
            ex_mem_s2 ( opcode );
            break;
        case OPC_STL:
            mem_flag.latchFrom ( write_mem.OUT ( ) );
            ex_mem_s2 ( opcode );
            break;
        case OPC_ADDL: case OPC_AND:
            mem_flag.latchFrom ( writeback.OUT ( ) );
            ex_arith_s2 ( opcode, func );
            break;
        case OPC_BGE: case OPC_BGT: case OPC_BEQ: case OPC_BLBS:
        case OPC_BLE: case OPC_BLT: case OPC_BNE: case OPC_BR:
        case OPC_BSR:
            mem_flag.latchFrom ( no_mem.OUT ( ) );
            //ex_br_s2(opcode);
            break;
        default:
            break;
    } // switch
    
    sprintf ( opc2value_ex, "opc=%03d",
              opcode );
    sprintf ( addr2value_ex, "addr=%08lx",
              ex_internal_addr.value ( ) );
    sprintf ( shift2value_ex, "shift=%08lx",
              ex_internal_shift.value ( ) );
    sprintf ( arith2value_ex, "arith=%08lx",
              ex_internal_arith.value ( ) );
    
    // first stage
    sprintf ( print1_ex, "|X| %-7s %-7s %-12s %-12s %-12s %-12s %-12s ",
              pc1value_ex,
              opc1value_ex,
              ra1value_ex,
              rb1value_ex,
              rc1value_ex,
              lit1value_ex,
              disp1value_ex );
    sprintf ( print2_ex, "| %-7s %-14s %-14s %-14s ",
              opc2value_ex,
              addr2value_ex,
              shift2value_ex,
              arith2value_ex );
    cout << print1_ex << print2_ex;
} // execute2
// $(filename) end
