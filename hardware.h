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
extern unsigned int ADDR_SIZE;   //
extern unsigned int OPC_SIZE;    // OP SIZE
extern unsigned int REG_SIZE;    // REGISTER SIZE
extern unsigned int DATA_SIZE;   // DATA SIZE

/**
 * INSTRUCTION OPCODE CONSTANTS
 */
enum INSTRS {
    OPC_NOOP = 0, OPC_LDA = 8,
    OPC_LDAH = 9, OPC_LDBU = 10,
    OPC_LDL	 = 40, OPC_LDWU = 12,
    OPC_STL	 = 44, OPC_STW = 13,
    OPC_JMP	 = 26, OPC_RPCC = 24,
    OPC_ADDL = 16,
    OPC_AND	 = 17,
    OPC_BGE	 = 62, OPC_JSR = 260,
    OPC_RET	 = 2600, OPC_JSRC = 26000,
    OPC_BGT	 = 63, OPC_BEQ = 57,
    OPC_BLBS = 60, OPC_BLE = 58,
    OPC_BLBC = 56, OPC_BLT = 59,

    OPC_BNE	 = 61, OPC_BR = 48,
    OPC_BSR	 = 52
};
//Note: because these instructions all share opcodes, decisions should not be made based on their values
//eg. reading an opcode of 16 could mean many things. Once you decode the true function, store it separately
#define OPC_ADDL 16
#define OPC_S4ADDL 16
#define OPC_S8ADDL 16
#define OPC_S4SUBL 16
#define OPC_S8SUBL 16
#define OPC_BIC 17
#define OPC_BIS 17
#define OPC_EQV 17
#define OPC_ORNOT 17
#define OPC_XOR 17
#define OPC_CMOVEQ 17
#define OPC_CMOVGE 17
#define OPC_CMOVGT 17
#define OPC_CMOVBLC 17
#define OPC_CMOVBLS 17
#define OPC_CMOVLE 17
#define OPC_CMOVLT 17
#define OPC_CMOVNE 17
#define OPC_SLL 17
#define OPC_SRL 17
/**
 * SPECIAL RESERVED REGISTERS
 */
extern Clearable noop_g;
extern Clearable not3_g;
extern Clearable mult4_g;
extern Clearable shift11_g;
extern Clearable shift7_g;
extern Clearable literalmask_g;
extern Clearable literalShift_g;
extern Clearable dispmask_g; //2097151
extern Clearable const2_g;
extern Clearable const3_g;
extern Clearable const16_g;

extern Constant no_mem;
extern Constant read_mem;
extern Constant write_mem;
extern Constant writeback;

/**
 * Programmer-viewable registers
 */
extern Counter* regfile[];

extern Bus irbus_e;
/* cache */
extern Memory instr_cache;
extern Memory data_cache;

extern bool done;

#endif

// $(filename) END
