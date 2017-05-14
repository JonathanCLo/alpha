/**
 * hardware.cpp
 *
 * Author   Nathan Castle < >
 *          Jonathan Lo <jcl5201>
 */

#include "includes.h"

/**
 * DEPENDENCY TABLE
 */

/**
 * CONSTANTS
 */
unsigned int ADDR_SIZE ( 32 );    // ADDRESS SIZE
unsigned int OPC_SIZE ( 6 );      // OP SIZE
unsigned int REG_SIZE ( 32 );     // REGISTER SIZE
unsigned int DATA_SIZE ( 16 );    // DATA SIZE

/**
 * SPECIAL RESERVED REGISTERS
 */
Clearable noop_g ( "NOOP_G", REG_SIZE, 0 );
Clearable mult4_g ( "MULT4_G", REG_SIZE, 2 );
Clearable shift11_g ( "SHIFT11_G", REG_SIZE, 11 );
Clearable literalmask_g ( "LITERALMASK_G", REG_SIZE, 0x1FE000 );
Clearable dispmask_g ( "DISPMASK_G", REG_SIZE, 0x1FFFFF ); //2097151
Clearable const2_g ( "CONST2_G", REG_SIZE, 2 );
Clearable const3_g ( "CONST3_G", REG_SIZE, 3 );
Clearable not3_g ( "NOT3_G", REG_SIZE, ~3 );
Clearable const16_g ( "CONST16_G", REG_SIZE, 16 );

/**
 * FETCH
 */
// REGISTERS
Counter pc_load ( "PC_LOAD", ADDR_SIZE );
Counter pc_f ( "PC_FETCH", ADDR_SIZE );
// BUSES
Bus pcbus_f ( "PCBUS_FETCH", ADDR_SIZE );
// AUX COMPONENTS
// PIPELINE COMPONENTS
Counter pc_fi ( "PC_FETCH_ISSUE", ADDR_SIZE );
Counter ir_fi ( "IR_FETCH_ISSUE", REG_SIZE );

/**
 * ISSUE
 */
// REGISTERS
Counter pc_i ( "PC_ISSUE", ADDR_SIZE );
Counter ir_i ( "IR_ISSUE", ADDR_SIZE );
Counter aux_i ( "AUX_ISSUE", ADDR_SIZE );

// BUSES
Bus pcbus_i ( "PCBUS_ISSUE", ADDR_SIZE );
// AUX COMPONENTS
BusALU mask_alu ( "MASK_ALU", REG_SIZE );
BusALU leftShift_alu ( "leftShift_ALU", REG_SIZE );
BusALU rightShift_alu ( "rightShift_ALU", REG_SIZE );
BusALU destalu_i ( "DESTALU_ISSUE", REG_SIZE );
// PIPELINE COMPONENTS
Counter pc_ir ( "PC_ISSUE_READ", ADDR_SIZE );
Counter npc_ir ( "NPC_ISSUE_READ", ADDR_SIZE );
Clearable ir_ir ( "IR_ISSUE_READ", REG_SIZE );

/**
 * READ
 */
// REGISTERS
// AUX COMPONENTS
// PIPELINE COMPONENTS
Counter pc_re ( "PC_READ_EXECUTE", ADDR_SIZE );
Counter pc_r ( "PC_READ_EXECUTE", ADDR_SIZE );
Clearable ir_re ( "IR_READ_EXECUTE", REG_SIZE );
Counter ra_re ( "RA_READ_EXECUTE", REG_SIZE );
Counter rb_re ( "RB_READ_EXECUTE", REG_SIZE );
Counter rc_re ( "RC_READ_EXECUTE", REG_SIZE );
Counter aux_re ( "AUX_READ_EXECUTE", REG_SIZE );
Clearable disp_re ( "DISPLACE_READ_EXECUTE", DATA_SIZE );
Counter li_re ( "LITERAL_READ_EXECUTE", DATA_SIZE );
Clearable func_re ( "FUNC_READ_EXECUTE", DATA_SIZE );
Counter literal_re ( "LITERALRE", REG_SIZE );
/**
 * EXECUTE
 */
// REGISTERS
Counter ex_out_addr ( "OUT_EXECUTE_ADDR", REG_SIZE );
Counter ex_out_arith ( "OUT_EXECUTE_ARTH", REG_SIZE );
Counter ex_internal_arith ( "EX_INT_ARTH", REG_SIZE );
Counter ex_internal_shift ( "EX_INT_SHFT", REG_SIZE );
Counter ex_internal_addr ( "EX_INT_ADDR", REG_SIZE );
Counter ex_internal_ir ( "EX_INT_IR", REG_SIZE );

// BUSES
// AUX COMPONENTS
BusALU arith_alu ( "ARITHOP", REG_SIZE );
BusALU shift_alu ( "SHIFT_ALU", REG_SIZE );
BusALU addr_alu ( "ADDR_ALU", ADDR_SIZE );
Bus irbus_e ( "IRBUS_EXEC", REG_SIZE );
// PIPELINE COMPONENTS
Counter pc_em ( "PC_EXECUTE_MEMORY", REG_SIZE );
Counter out_em ( "OUT_EXECUTE_MEMORY", REG_SIZE );
Counter addr_em ( "ADDR_EXECUTE_MEMORY", ADDR_SIZE );
Clearable ir_em ( "IR_EXECUTE_MEMORY", ADDR_SIZE );
Bus outbus_em ( "OUTBUS_EXECUTE_MEMORY", REG_SIZE );
Bus addrbus_em ( "ADDRBUS_EXECUTE_MEMORY", ADDR_SIZE );


Constant no_mem ( "CONST_NO_MEM", REG_SIZE, 0 );
Constant read_mem ( "CONST_RD_MEM", REG_SIZE, 1 );
Constant write_mem ( "CONST_WR_MEM", REG_SIZE, 2 );
Constant writeback ( "CONST_WB_MEM", REG_SIZE, 3 );
/**
 * MEMORY
 */
// REGISTERS
Counter mm_internal_type ( "MMINTTYPE", REG_SIZE );
Counter mm_internal_arith ( "MMINTARITH", REG_SIZE );
Bus mm_controlbus ( "MM_CTRL_BUS", REG_SIZE );

Clearable data_m ( "DATA_MEMORY", DATA_SIZE );
// Clearable  out_m ( "OUT_MEMORY", REG_SIZE );
// BUSES
Bus addrbus_m ( "ADDRBUS_MEMORY", REG_SIZE ); // TODO CONFLICTING SIZE!
Bus dbus_m ( "DATABUS_MEMORY", REG_SIZE );    // TODO CONFLICTING SIZE!
// AUX COMPONENTS
// PIPELINE COMPONENTS

/**
 * Programmer-viewable registers
 */
Counter r0 ( "R0", REG_SIZE );
Counter r1 ( "R1", REG_SIZE );
Counter r2 ( "R2", REG_SIZE );
Counter r3 ( "R3", REG_SIZE );
Counter r4 ( "R4", REG_SIZE );
Counter r5 ( "R5", REG_SIZE );
Counter r6 ( "R6", REG_SIZE );
Counter r7 ( "R7", REG_SIZE );
Counter r8 ( "R8", REG_SIZE );
Counter r9 ( "R9", REG_SIZE );
Counter r10 ( "R10", REG_SIZE );
Counter r11 ( "R11", REG_SIZE );
Counter r12 ( "R12", REG_SIZE );
Counter r13 ( "R13", REG_SIZE );
Counter r14 ( "R14", REG_SIZE );
Counter r15 ( "R15", REG_SIZE );
Counter r16 ( "R16", REG_SIZE );
Counter r17 ( "R17", REG_SIZE );
Counter r18 ( "R18", REG_SIZE );
Counter r19 ( "R19", REG_SIZE );
Counter r20 ( "R20", REG_SIZE );
Counter r21 ( "R21", REG_SIZE );
Counter r22 ( "R22", REG_SIZE );
Counter r23 ( "R23", REG_SIZE );
Counter r24 ( "R24", REG_SIZE );
Counter r25 ( "R25", REG_SIZE );
Counter r26 ( "R26", REG_SIZE );
Counter r27 ( "R27", REG_SIZE );
Counter r28 ( "R28", REG_SIZE );
Counter r29 ( "R29", REG_SIZE );
Counter r30 ( "R30", REG_SIZE );
Clearable r31 ( "R31", REG_SIZE );

//forwarding
Bus forward_bus_nodelay ( "F_BUS_ND", REG_SIZE );
Bus forward_bus_delay ( "F_BUS_D", REG_SIZE );
Clearable forward_delay_slot ( "f_delay_slot", REG_SIZE );

/**
 * Cache
 */
// insstruction cache
Memory instr_cache ( "INSTRUCTION_CACHE", ADDR_SIZE, DATA_SIZE,
                     0xffff );

// data cache
Memory data_cache ( "DATA_CACHE", ADDR_SIZE, DATA_SIZE,
                    0xffff );

/* Runtime control variables */
bool done ( false );  // is the simulation over?

// $(filename) END
