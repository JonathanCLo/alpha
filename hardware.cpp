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
 * INSTRUCTION OPCODE CONSTANTS;
 */
unsigned long OPC_NOOP	  = 0;
// MD instructions
unsigned long OPC_LDA	  = 8;
unsigned long OPC_LDAH	  = 9;
unsigned long OPC_LDBU	  = 10;
unsigned long OPC_LDL	  = 40;
unsigned long OPC_LDWU	  = 12;
unsigned long OPC_STL	  = 44;
unsigned long OPC_STW	  = 13;
// branch
unsigned long OPC_BEQ	  = 57;
unsigned long OPC_BGE	  = 62;
unsigned long OPC_BGT	  = 63;
unsigned long OPC_BLBC	  = 56;
unsigned long OPC_BLBS	  = 60;
unsigned long OPC_BLE	  = 59;
unsigned long OPC_BLT	  = 58;
unsigned long OPC_BNE	  = 61;
unsigned long OPC_BR	  = 48;
unsigned long OPC_BSR	  = 52;
// mf
unsigned long OPC_JMP	  = 26;
unsigned long OPC_JSR	  = 26;
unsigned long OPC_RET	  = 26;
unsigned long OPC_JSRC	  = 26;
unsigned long OPC_RPCC	  = 24;
// operate
unsigned long OPC_ADDL	  = 16;
unsigned long OPC_S4ADDL  = 16;
unsigned long OPC_S8ADDL  = 16;
unsigned long OPC_SUBL	  = 16;
unsigned long OPC_S4SUBL  = 16;
unsigned long OPC_S8SUBL  = 16;
unsigned long OPC_AND	  = 17;
unsigned long OPC_BIC	  = 17;
unsigned long OPC_BIS	  = 17;
unsigned long OPC_EQV	  = 17;
unsigned long OPC_ORNOT	  = 17;
unsigned long OPC_XOR	  = 17;
unsigned long OPC_CMOVEQ  = 17;
unsigned long OPC_CMOVGE  = 17;
unsigned long OPC_CMOVGT  = 17;
unsigned long OPC_CMOVLBC = 17;
unsigned long OPC_CMOVLBS = 17;
unsigned long OPC_CMOVLE  = 17;
unsigned long OPC_CMOVLT  = 17;
unsigned long OPC_CMOVNE  = 17;
unsigned long OPC_SLL	  = 17;
unsigned long OPC_SRL	  = 17;

/**
 * SPECIAL RESERVED REGISTERS
 */
Counter pcc ( "PCC", REG_SIZE );
Clearable noop ( "NOOP", REG_SIZE, 0 );
Clearable mult4 ( "MULT4", REG_SIZE, 2 );
Clearable shift11 ( "DISP11", REG_SIZE, 11 );
Clearable shift7 ( "DISP11", REG_SIZE, 7 );
/**
 * SPECIAL RESERVED BUSES FOR SRR
 */
Bus irfi_noop_bus ( "IRFI_NOOP_BUS", REG_SIZE );
Bus irir_noop_bus ( "IRIR_NOOP_BUS", REG_SIZE );
Bus irre_noop_bus ( "IRRE_NOOP_BUS", REG_SIZE );
Bus ire_noop_bus ( "IRE_NOOP_BUS", REG_SIZE );
Bus irem_noop_bus ( "IREM_NOOP_BUS", REG_SIZE );


/**
 * FETCH
 */
// REGISTERS
Counter pc_f ( "PC_FETCH", ADDR_SIZE );
// BUSES
Bus pcbus_f ( "PCBUS_FETCH", ADDR_SIZE );
// AUX COMPONENTS
// PIPELINE COMPONENTS
Counter pc_fi ( "PC_FETCH_ISSUE", ADDR_SIZE );
Clearable ir_fi ( "IR_FETCH_ISSUE", REG_SIZE );

/**
 * ISSUE
 */
// REGISTERS
Counter aux_i ( "AUX_ISSUE", ADDR_SIZE );
Clearable dispmask_i ( "DISP_MASK_ISSUE", REG_SIZE, 0x1fffff );
// BUSES
Bus pcbus_i ( "PCBUS_ISSUE", ADDR_SIZE );
Bus irbus_i ( "IRBUS_ISSUE", REG_SIZE );
// AUX COMPONENTS
BusALU mask_alu ( "MASK_ALU", REG_SIZE );
BusALU rightShift_alu ( "rightShift_ALU", REG_SIZE );
// PIPELINE COMPONENTS
Counter pc_ir ( "PC_ISSUE_READ", ADDR_SIZE );
Counter npc_ir ( "NPC_ISSUE_READ", ADDR_SIZE );
Clearable ir_ir ( "IR_ISSUE_READ", REG_SIZE );
Clearable lock_ir ( "LOCK_ISSUE_READ", REG_SIZE );

/**
 * READ
 */
// REGISTERS
Counter aux_r ( "AUX_READ", ADDR_SIZE );
// BUSES
Bus pcbus_r ( "PCBUS_READ", ADDR_SIZE );
Bus irbus_r ( "IRBUS_READ", REG_SIZE );
Bus rabus_r ( "RABUS_READ", REG_SIZE );
Bus rbbus_r ( "RBBUS_READ", REG_SIZE );
Bus rcbus_r ( "RCBUS_READ", REG_SIZE );
Bus auxbus_r ( "AUXBUS_READ", REG_SIZE );
Bus lockbus_r ( "LOCKBUS_READ", REG_SIZE );
// AUX COMPONENTS
BusALU dest_alu ( "DEST_ALU", REG_SIZE );
// PIPELINE COMPONENTS
Counter pc_re ( "PC_READ_EXECUTE", ADDR_SIZE );
Clearable ir_re ( "IR_READ_EXECUTE", REG_SIZE );
Counter ra_re ( "RA_READ_EXECUTE", REG_SIZE );
Counter rb_re ( "RB_READ_EXECUTE", REG_SIZE );
Counter rc_re ( "RC_READ_EXECUTE", REG_SIZE );
Counter aux_re ( "AUX_READ_EXECUTE", REG_SIZE );
Clearable disp_re ( "DISPLACE_READ_EXECUTE", DATA_SIZE );
Counter li_re ( "LITERAL_READ_EXECUTE", DATA_SIZE );
Clearable func_re ( "FUNC_READ_EXECUTE", DATA_SIZE );
Clearable lock_re ( "LOCK_READ_EXECUTE", DATA_SIZE );

/**
 * EXECUTE
 */
// REGISTERS
Counter fout_e ( "OUT_EXECUTE", REG_SIZE );
Counter arith_op1 ( "ARITH_OP1", REG_SIZE );
Counter arith_op2 ( "ARITH_OP2", REG_SIZE );
Counter shift_op1 ( "SHIFT_OP1", REG_SIZE );
Counter shift_op2 ( "SHIFT_OP2", REG_SIZE );
Counter addr_op1 ( "ADDR_OP1", ADDR_SIZE );
Counter addr_op2 ( "ADDR_OP2", ADDR_SIZE );
// BUSES
Bus pcbus_e ( "PCBUS_EXECUTE", ADDR_SIZE );
Bus irbus_e ( "IRBUS_EXECUTE", REG_SIZE );
Bus arithop1_ebus ( "ARITH_OP1_EBUS", REG_SIZE );
Bus arithop2_ebus ( "ARITH_OP2_EBUS", REG_SIZE );
Bus shiftop1_ebus ( "SHIFT_OP1_EBUS", REG_SIZE );
Bus shiftop2_ebus ( "SHIFT_OP2_EBUS", REG_SIZE );
Bus addrop1_ebus ( "ADDR_OP1_EBUS", REG_SIZE );
Bus addrop2_ebus ( "ADDR_OP2_EBUS", REG_SIZE );
// AUX COMPONENTS
BusALU arith_alu ( "ARITHOP", REG_SIZE );
BusALU shift_alu ( "SHIFT_ALU", REG_SIZE );
BusALU addr_alu ( "ADDR_ALU", ADDR_SIZE );
// PIPELINE COMPONENTS
Counter pc_em ( "PC_EXECUTE_MEMORY", REG_SIZE );
Counter out_em ( "OUT_EXECUTE_MEMORY", REG_SIZE );
Counter addr_em ( "ADDR_EXECUTE_MEMORY", ADDR_SIZE );
Clearable ir_em ( "IR_EXECUTE_MEMORY", ADDR_SIZE );
Clearable mem_flag ( "MEMORY_WRITE_STORE_FLAG", 2 );
Bus outbus_em ( "OUTBUS_EXECUTE_MEMORY", REG_SIZE );
Bus addrbus_em ( "ADDRBUS_EXECUTE_MEMORY", ADDR_SIZE );


StorageObject exec_const_2 ( "2", REG_SIZE, 2 );
StorageObject exec_const_3 ( "3", REG_SIZE, 3 );
StorageObject exec_const_4 ( "4", REG_SIZE, 4 );
/**
 * MEMORY
 */
// REGISTERS
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

// CROSS STAGE BUSES
Bus sbus1 ( "STAGE_BUS1", REG_SIZE );
Bus sbus2 ( "STAGE_BUS2", REG_SIZE );
Bus sbus3 ( "STAGE_BUS3", REG_SIZE );
Bus sbus4 ( "STAGE_BUS4", REG_SIZE );
Bus sbus5 ( "STAGE_BUS5", REG_SIZE );

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
