/**
 * hardware.h
 *
 * Author   Nathan Castle < >
 *          Jonathan Lo <jcl5201>
 * global hardware instantiations
 */
#ifndef _HARDWARE_H
#define _HARDWARE_H

#include "includes.h"

/**
 * GLOBAL SIZES
 */
extern const unsigned int ADDR_SIZE;   //
extern const unsigned int OPC_SIZE;    // OP SIZE
extern const unsigned int REG_SIZE;    // REGISTER SIZE
extern const unsigned int DATA_SIZE;   // DATA SIZE

/**
 * INSTRUCTION OPCODE CONSTANTS
 */
extern const unsigned long OPC_NOOP;
// MD instructions
extern const unsigned long OPC_LDA;
extern const unsigned long OPC_LDAH;
extern const unsigned long OPC_LDBU;
extern const unsigned long OPC_LDL;
extern const unsigned long OPC_LDWU;
extern const unsigned long OPC_STL;
extern const unsigned long OPC_STW;
// branch
extern const unsigned long OPC_BEQ;
extern const unsigned long OPC_BGE;
extern const unsigned long OPC_BGT;
extern const unsigned long OPC_BLBC;
extern const unsigned long OPC_BLBS;
extern const unsigned long OPC_BLE;
extern const unsigned long OPC_BLT;
extern const unsigned long OPC_BNE;
extern const unsigned long OPC_BR;
extern const unsigned long OPC_BSR;
// mf
extern const unsigned long OPC_JMP;
extern const unsigned long OPC_JSR;
extern const unsigned long OPC_RET;
extern const unsigned long OPC_JSRC;
extern const unsigned long OPC_RPCC;
// operate
extern const unsigned long OPC_ADDL;
extern const unsigned long OPC_S4ADDL;
extern const unsigned long OPC_S8ADDL;
extern const unsigned long OPC_SUBL;
extern const unsigned long OPC_S4SUBL;
extern const unsigned long OPC_S8SUBL;
extern const unsigned long OPC_AND;
extern const unsigned long OPC_BIC;
extern const unsigned long OPC_BIS;
extern const unsigned long OPC_EQV;
extern const unsigned long OPC_ORNOT;
extern const unsigned long OPC_XOR;
extern const unsigned long OPC_CMOVEQ;
extern const unsigned long OPC_CMOVGE;
extern const unsigned long OPC_CMOVGT;
extern const unsigned long OPC_CMOVLBC;
extern const unsigned long OPC_CMOVLBS;
extern const unsigned long OPC_CMOVLE;
extern const unsigned long OPC_CMOVLT;
extern const unsigned long OPC_CMOVNE;
extern const unsigned long OPC_SLL;
extern const unsigned long OPC_SRL;

/**
 * SPECIAL RESERVED REGISTERS
 */
extern Constant noop;
extern Constant mult4;
extern Constant shift11;
extern Constant shift7;

/**
 * SPECIAL RESERVED BUSES FOR SRR
 */
extern Bus noopbus;

/**
 * PIPELINE REGISTERS
 */
extern Counter pc_f;       // pc fetch
extern Counter pc_fi;      // pc fetch issue
extern Counter pc_i;       // pc issue
extern Counter pc_ir;      // pc issue read
extern Counter npc_ir;     // npc issue read
extern Counter pc_re;      // pc read execute
extern Counter pc_em;      // pc execute memory
extern Clearable ir_fi;    // ir fetch issue
extern Clearable ir_i;     // ir issue
extern Clearable ir_ir;    // ir issue read
extern Clearable ir_re;    // ir read execute
extern Counter aux_i;      // aux issue
extern Counter aux_r;      // aux read
extern Clearable lock_ir;  // lock issue read
extern Clearable lock_re;  // lock read execute
extern Clearable disp_r;   // disp read
extern Clearable disp_re;  // disp read execute
extern Clearable li_r;     // literal read
extern Counter li_re;      // literal read execute
extern Clearable func_r;   // func read
extern Clearable func_re;  // func read execute
extern Counter ra_re;      // ra read execute
extern Counter rb_re;      // rb read execute
extern Counter rc_re;      // rc read execute
extern Counter aux_re;     // aux read execute
extern Counter fout_e;     // fout execute
extern Counter arith_op1;  // execute
extern Counter arith_op2;  // execute
extern Counter shift_op1;  // execute
extern Counter shift_op2;  // execute
extern Counter addr_op1;   // execute
extern Counter addr_op2;   // execute
extern Counter out_em;     // out execute memory
extern Counter pc_em;      // pc execute memory
extern Clearable ir_em;    // reg_addr execute memory
extern Clearable mem_flag; // memory write store flag
// extern Clearable  out_m; // out memory
extern Counter addr_em;   // addr execute memory
extern Clearable data_m;  // data memory

extern StorageObject exec_const_2;
extern StorageObject exec_const_3;
extern StorageObject exec_const_4;

/**
 * BUSES
 */
extern Bus pcbus_f;       // pcbus fetch
extern Bus pcbus_i;       // pcbus issue
extern Bus pcbus_r;       // pcbus read
extern Bus pcbus_e;       // pcbus execute
extern Bus irbus_i;       // irbus issue
extern Bus irbus_r;       // irbus read
extern Bus irbus_e;       // irbus execute
extern Bus rabus_r;       // rabus read
extern Bus rbbus_r;       // rbbus read
extern Bus rcbus_r;       // rcbus read
extern Bus auxbus_r;      // auxbus read
extern Bus lockbus_r;     // lockbus read
extern Bus arithop1_ebus; // arith op1 ebus execute
extern Bus arithop2_ebus; // arith op2 ebus execute
extern Bus shiftop1_ebus; // shift op1 ebus execute
extern Bus shiftop2_ebus; // shift op2 ebus execute
extern Bus addrop1_ebus;  // addr op1 ebus execute
extern Bus addrop2_ebus;  // addr op2 ebus execute
extern Bus shift_ebus;    // shift ebus execute
extern Bus addr_ebus;     // addr ebus execute
extern Bus outbus_em;     // out bus execute memory
extern Bus addrbus_em;    // addr bus execute memory
extern Bus addrbus_m;     // addr bus memory
extern Bus dbus_m;        // dbus memory
extern Bus sbus1;         // stage buses
extern Bus sbus2;
extern Bus sbus3;
extern Bus sbus4;
extern Bus sbus5;

/**
 * ALU
 */
extern BusALU mask_alu;       // mask alue
extern BusALU leftShift_alu;  // left shift alu
extern BusALU rightShift_alu; // right shift alu
extern BusALU dest_alu;       // pc alu
extern BusALU arith_alu;      // arith alu
extern BusALU shift_alu;      // shift alu
extern BusALU addr_alu;       // addr alu

/**
 * Programmer-viewable registers
 */
extern Counter r0;
extern Counter r1;
extern Counter r2;
extern Counter r3;
extern Counter r4;
extern Counter r5;
extern Counter r6;
extern Counter r7;
extern Counter r8;
extern Counter r9;
extern Counter r10;
extern Counter r11;
extern Counter r12;
extern Counter r13;
extern Counter r14;
extern Counter r15;
extern Counter r16;
extern Counter r17;
extern Counter r18;
extern Counter r19;
extern Counter r20;
extern Counter r21;
extern Counter r22;
extern Counter r23;
extern Counter r24;
extern Counter r25;
extern Counter r26;
extern Counter r27;
extern Counter r28;
extern Counter r29;
extern Counter r30;
extern Clearable r31;         // used as a 'zero' register

/* cache */
extern Memory instr_cache;
extern Memory data_cache;

extern bool done;

#endif

// $(filename) END
