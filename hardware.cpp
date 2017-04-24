/**
 * hardware.cpp
 *
 * Author   Nathan Castle < >
 *          Jonathan Lo <jcl5201>
 */

#include "includes.h"

/**
 * CONSTANTS
 */
const unsigned int  ADDR_SIZE ( 32 );   // ADDRESS SIZE
const unsigned int  OPC_SIZE ( 6 );     // OP SIZE
const unsigned int  REG_SIZE ( 32 );    // REGISTER SIZE
const unsigned int  DATA_SIZE ( 16 );   // DATA SIZE

/**
 * SPECIAL RESERVED REGISTERS
 */
Counter  pcc ( "PCC", REG_SIZE );


/**
 * FETCH
 */
// REGISTERS
Counter    pc_f ( "PC_FETCH", ADDR_SIZE );
Clearable  ir_f ( "IR_FETCH", REG_SIZE );
// BUSES
Bus  pcbus_f ( "PCBUS_FETCH", ADDR_SIZE );
// AUX COMPONENTS
// PIPELINE COMPONENTS
Counter   pc_fi ( "PC_FETCH_ISSUE", ADDR_SIZE );
Clearble  ir_f ( "IR_FETCH_ISSUE", REG_SIZE );

/**
 * ISSUE
 */
// REGISTERS
Counter    pc_i ( "PC_ISSUE", ADDR_SIZE );
Clearable  ir_i ( "IR_ISSUE", REG_SIZE );
// BUSES
Bus        pcbus_i ( "PCBUS_ISSUE", ADDR_SIZE );
Bus        irbus_i ( "IRBUS_ISSUE", REG_SIZE );
// AUX COMPONENTS
BusALU     pcalu_i ( "PCALU_ISSUE", REG_SIZE );
// PIPELINE COMPONENTS
Counter    pc_ir ( "PC_ISSUE_READ", ADDR_SIZE );
Clearble   ir_ir ( "IR_ISSUE_READ", REG_SIZE );
Clearable  lock_ir ( "LOCK_ISSUE_READ", REG_SIZE );

/**
 * READ
 */
// REGISTERS
Counter    pc_r ( "PC_READ", ADDR_SIZE );
Clearable  ir_r ( "IR_READ", REG_SIZE );
Clearable  disp_r ( "DISPLACE_READ", DATA_SIZE );
Clearable  li_r ( "LITERAL_READ", DATA_SIZE );
Clearable  func_r ( "FUNC_READ", DATA_SIZE );
// BUSES
Bus  pcbus_r ( "PCBUS_READ", ADDR_SIZE );
Bus  irbus_r ( "IRBUS_READ", REG_SIZE );
Bus  dispbus_r ( "DISPLACEBUS_READ", DATA_SIZE );
Bus  libus_r ( "LITERALBUS_READ", DATA_SIZE );
Bus  func_r ( "FUNCBUS_READ", DATA_SIZE );
Bus  rabus_r ( "RABUS_READ", REG_SIZE );
Bus  rbbus_r ( "RBBUS_READ", REG_SIZE );
Bus  rcbus_r ( "RCBUS_READ", REG_SIZE );
Bus  auxbus_r ( "AUXBUS_READ", REG_SIZE );
// AUX COMPONENTS
// PIPELINE COMPONENTS
Counter    pc_re ( "PC_READ_EXECUTE", ADDR_SIZE );
Clearable  ir_re ( "IR_READ_EXECUTE", REG_SIZE );
Counter    ra_re ( "RA_READ_EXECUTE", REG_SIZE );
Counter    rb_re ( "RB_READ_EXECUTE", REG_SIZE );
Counter    rc_re ( "RC_READ_EXECUTE", REG_SIZE );
Counter    aux_re ( "AUX_READ_EXECUTE", AUX_SIZE );
Clearable  disp_re ( "DISPLACE_READ_EXECUTE", DATA_SIZE );
Clearable  li_re ( "LITERAL_READ_EXECUTE", DATA_SIZE );
Clearable  func_re ( "FUNC_READ_EXECUTE", DATA_SIZE );

/**
 * EXECUTE_BUS
 */
// REGISTERS
Counter  out_e ( "OUT_EXECUTE", REG_SIZE );
Counter  arith_op1 ( "ARITH_OP1", REG_SIZE );
Counter  arith_op2 ( "ARITH_OP2", REG_SIZE );
Counter  shift_op1 ( "SHIFT_OP1", REG_SIZE );
Counter  shift_op2 ( "SHIFT_OP2", REG_SIZE );
Counter  addr_op1 ( "ADDR_OP1", ADDR_SIZE );
Counter  addr_op2 ( "ADDR_OP2", ADDR_SIZE );
// BUSES
Bus      arith_ebus ( "ARITH_EBUS", REG_SIZE );
Bus      shift_ebus ( "SHIFT_EBUS", REG_SIZE );
Bus      addr_ebus ( "ADDR_EBUS", ADDR_SIZE );
// AUX COMPONENTS
BusALU   arith_alu ( "ARITH_ALU", REG_SIZE );
BusALU   shift_alu ( "SHIFT_ALU", REG_SIZE );
BusALU   addr_alu ( "ADDR_ALU", ADDR_SIZE );
// PIPELINE COMPONENTS
Counter  out_em ( "OUT_EXECUTE_MEMORY", REG_SIZE );
Counter  addr_em ( "ADDR_EXECUTE_MEMORY", ADDR_SIZE );
Bus      outbus_em ( "OUTBUS_EXECUTE_MEMORY", REG_SIZE );
Bus      addrbus_em ( "ADDRBUS_EXECUTE_MEMORY", ADDR_SIZE );

/**
 * MEMORY
 */
// REGISTERS
Clearable  data_m ( "DATA_MEMORY", DATA_SIZE );
Clearable  out_m ( "OUT_MEMORY", REG_SIZE );
// BUSES
Bus  dbus_m ( "DATABUS_MEMORY", REG_SIZE ); // TODO CONFLICTING SIZE!
// AUX COMPONENTS
// PIPELINE COMPONENTS

/**
 * Programmer-viewable registers
 */
Counter    r0 ( "R0", REG_SIZE );
Counter    r1 ( "R1", REG_SIZE );
Counter    r2 ( "R2", REG_SIZE );
Counter    r3 ( "R3", REG_SIZE );
Counter    r4 ( "R4", REG_SIZE );
Counter    r5 ( "R5", REG_SIZE );
Counter    r6 ( "R6", REG_SIZE );
Counter    r7 ( "R7", REG_SIZE );
Counter    r8 ( "R8", REG_SIZE );
Counter    r9 ( "R9", REG_SIZE );
Counter    r10 ( "R10", REG_SIZE );
Counter    r11 ( "R11", REG_SIZE );
Counter    r12 ( "R12", REG_SIZE );
Counter    r13 ( "R13", REG_SIZE );
Counter    r14 ( "R14", REG_SIZE );
Counter    r15 ( "R15", REG_SIZE );
Counter    r16 ( "R16", REG_SIZE );
Counter    r17 ( "R17", REG_SIZE );
Counter    r18 ( "R18", REG_SIZE );
Counter    r19 ( "R19", REG_SIZE );
Counter    r20 ( "R20", REG_SIZE );
Counter    r21 ( "R21", REG_SIZE );
Counter    r22 ( "R22", REG_SIZE );
Counter    r23 ( "R23", REG_SIZE );
Counter    r24 ( "R24", REG_SIZE );
Counter    r25 ( "R25", REG_SIZE );
Counter    r26 ( "R26", REG_SIZE );
Counter    r27 ( "R27", REG_SIZE );
Counter    r28 ( "R28", REG_SIZE );
Counter    r29 ( "R29", REG_SIZE );
Counter    r30 ( "R30", REG_SIZE );
Clearable  r31 ( "R31", REG_SIZE );

// CROSS STAGE BUSES
Bus  sbus1 ( "STAGE_BUS1", REG_SIZE );
Bus  sbus2 ( "STAGE_BUS2", REG_SIZE );
Bus  sbus3 ( "STAGE_BUS3", REG_SIZE );
Bus  sbus4 ( "STAGE_BUS4", REG_SIZE );
Bus  sbus5 ( "STAGE_BUS5", REG_SIZE );

/**
 * Cache
 */
// insstruction cache
Memory  instr_cache ( "INSTRUCTION_CACHE", ADDR_SIZE, DATA_SIZE );
// data cache
Memory  data_cache ( "DATA_CACHE", ADDR_SIZE, DATA_SIZE );

/* Runtime control variables */
bool  done ( false ); // is the simulation over?

// $(filename) END
