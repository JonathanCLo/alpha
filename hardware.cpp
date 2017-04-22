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


// FETCH stage
Counter    pc_f ( "PC", ADDR_SIZE );
Clearable  ir_f ( "IR_FETCH", REG_SIZE );
Bus  fetch_bus ( "FETCH_BUS", ADDR_SIZE ); // BUS to pipeline

// FETCH-ISSUE pipeline
Clearable  pc_fi ( "PC_FETCH_ISSUE", ADDR_SIZE );
Clearable  ir_fi ( "IR_FETCH_ISSUE", REG_SIZE );

// ISSUE stage
Counter    pc_i ( "PC_ISSUE", ADDR_SIZE );
Clearable  ir_i ( "IR_ISSUE", REG_SIZE );
BusALU     alu_i ( "ALU_ISSUE", REG_SIZE );
Clearable  reg_lock1_i ( "REG_LOCK1_ISSUE", REG_SIZE );
Clearable  reg_lock2_i ( "REG_LOCK2_ISSUE", REG_SIZE );
Clearable  mem_lock_i ( "MEM_LOCK_ISSUE", REG_SIZE );
Bus  issue_bus ( "ISSUE_BUS", ADDR_SIZE );

// ISSUE-READ Pipeline
Counter    pc_ir ( "PC_ISSUE_READ", ADDR_SIZE );
Clearable  ir_ir ( "IR_ISSUE_READ", REG_SIZE );
Clearable  reg_lock1_ir ( "REG_LOCK1_ISSUE_READ", REG_SIZE );
Clearable  reg_lock2_ir ( "REG_LOCK2_ISSUE_READ", REG_SIZE );
Clearable  mem_lock_ir ( "MEM_LOCK_ISSUE_READ", REG_SIZE );

// READ stage
Counter    pc_r ( "PC_READ", ADDR_SIZE )
Clearable  ir_r ( "IR_READ", REG_SIZE );
Clearable  reg_lock1_r ( "REG_LOCK1_READ", REG_SIZE );
Clearable  reg_lock2_r ( "REG_LOCK2_READ", REG_SIZE );
Clearable  mem_lock_r ( "MEM_LOCK_READ", REG_SIZE );
Bus  read_bus ( "READ_BUS", ADDR_SIZE );

// READ-EXECUTE Pipeline
Counter    pc_re ( "PC_READ_EXECUTE", ADDR_SIZE );
Counter    ra_re ( "RA_READ_EXECUTE", REG_SIZE );
Counter    rb_re ( "RB_READ_EXECUTE", REG_SIZE );
Clearable  reg_lock1_re ( "REG_LOCK1_READ_EXECUTE", REG_SIZE );
Clearable  reg_lock2_re ( "REG_LOCK2_READ_EXECUTE", REG_SIZE );
Clearable  mem_lock_re ( "MEM_LOCK_READ_EXECUTE", REG_SIZE );


// EXECUTE Stage
Counter    pc_e ( "PC_EXECUTE", ADDR_SIZE );
BusALU     alu_e ( "ALU_EXECUTE", REG_SIZE );
Clearable  out_e ( "OUT_EXECUTE", REG_SIZE );
Clearable  reg_lock1_e ( "REG_LOCK1_EXECUTE", REG_SIZE );
Clearable  reg_lock2_e ( "REG_LOCK2_EXECUTE", REG_SIZE );
Clearable  mem_lock_e ( "MEM_LOCK_EXECUTE", REG_SIZE );
Bus  exec_bus ( "EXECUTE_BUS", ADDR_SIZE );


// EXECUTE-MEMORY Pipeline
Counter    pc_em ( "PC_EXECUTE_MEMORY", ADDR_SIZE );
Clearble   out_em ( "OUT_EXECUTE_MEMORY", REG_SIZE );
Clearable  addr_em ( "ADDR_EXECUTE_MEMORY", ADDR_SIZE )
Clearable  mem_lock_em ( "MEM_LOCK_EXECUTE_MEMORY", REG_SIZE );

// MEMORY Stage
Counter    pc_m ( "PC_MEMORY", ADDR_SIZE );
Clearable  out_em ( "OUT_MEMORY", REG_SIZE );
Clearable  addr_m ( "ADDR_MEMORY", ADDR_SIZE );
Clearable  mem_lock_e ( "MEM_LOCK_MEMORY", REG_SIZE );
Bus  mem_bus ( "MEMORY_BUS", ADDR_SIZE );

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

/**
 * Busses
 */
Bus  addr_ibus ( "ADDR_INSTBUS", ADDR_SIZE );
Bus  data_ibus ( "DATA_INSTBUS", REG_SIZE );
Bus  addr_dbus ( "ADDR_DATABUS", ADDR_SIZE );
Bus  data_dbus ( "DATA_DATABUS", REG_SIZE );

/**
 * Cache
 */
// insstruction cache
Memory  instr_cache ( "INSTRUCTION_CACHE",
                      ADDR_SIZE, DATA_SIZE );
// data cache
Memory  data_cache ( "DATA_CACHE", ADDR_SIZE, DATA_SIZE );


/* Runtime control variables */
bool  done ( false ); // is the simulation over?

// $(filename) END
