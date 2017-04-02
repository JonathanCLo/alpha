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
const unsigned int	ADDR_SIZE ( 32 );   // ADDRESS SIZE
const unsigned int	OPC_SIZE ( 6 );     // OP SIZE
const unsigned int	REG_SIZE ( 32 );    // REGISTER SIZE
const unsigned int	DATA_SIZE ( 32 );   // DATA SIZE

/**
 * SPECIAL RESERVED REGISTERS
 */
Counter		pc ( "PC",
                 ADDR_SIZE );
Counter		lr0 ( "LOCK_REG_1",
                  REG_SIZE );
Counter		lr1 ( "LOCK_REG_2",
                  REG_SIZE );
Counter		pcc ( "PCC",
                  REG_SIZE );
Clearable	ir0 ( "IR0",
                  REG_SIZE );
Clearable	ir1 ( "IR1",
                  REG_SIZE );
Clearable	ir2 ( "IR2",
                  REG_SIZE );
Clearable	ir3 ( "IR3",
                  REG_SIZE );

/**
 * Programmer-viewable registers
 */
Counter		r0 ( "R0",
                 REG_SIZE );
Counter		r1 ( "R1",
                 REG_SIZE );
Counter		r2 ( "R2",
                 REG_SIZE );
Counter		r3 ( "R3",
                 REG_SIZE );
Counter		r4 ( "R4",
                 REG_SIZE );
Counter		r5 ( "R5",
                 REG_SIZE );
Counter		r6 ( "R6",
                 REG_SIZE );
Counter		r7 ( "R7",
                 REG_SIZE );
Counter		r8 ( "R8",
                 REG_SIZE );
Counter		r9 ( "R9",
                 REG_SIZE );
Counter		r10 ( "R10",
                  REG_SIZE );
Counter		r11 ( "R11",
                  REG_SIZE );
Counter		r12 ( "R12",
                  REG_SIZE );
Counter		r13 ( "R13",
                  REG_SIZE );
Counter		r14 ( "R14",
                  REG_SIZE );
Counter		r15 ( "R15",
                  REG_SIZE );
Counter		r16 ( "R16",
                  REG_SIZE );
Counter		r17 ( "R17",
                  REG_SIZE );
Counter		r18 ( "R18",
                  REG_SIZE );
Counter		r19 ( "R19",
                  REG_SIZE );
Counter		r20 ( "R20",
                  REG_SIZE );
Counter		r21 ( "R21",
                  REG_SIZE );
Counter		r22 ( "R22",
                  REG_SIZE );
Counter		r23 ( "R23",
                  REG_SIZE );
Counter		r24 ( "R24",
                  REG_SIZE );
Counter		r25 ( "R25",
                  REG_SIZE );
Counter		r26 ( "R26",
                  REG_SIZE );
Counter		r27 ( "R27",
                  REG_SIZE );
Counter		r28 ( "R28",
                  REG_SIZE );
Counter		r29 ( "R29",
                  REG_SIZE );
Counter		r30 ( "R30",
                  REG_SIZE );
Clearable	r31 ( "R31",
                  REG_SIZE );

/**
 * Busses
 */
Bus ibus ( "INSTRUCTION_BUS",
           DATA_SIZE );
Bus abus ( "ADDR_MEMORY_BUS",
           DATA_SIZE );
Bus dbus ( "DATA_MEMORY_BUS",
           DATA_SIZE );

/**
 * ALUs
 */
BusALU	alu_addr0 ( "ALU_ADDRESS0",
                    DATA_SIZE + DATA_SIZE );
BusALU	alu_addr1 ( "ALU_ADDRESS1",
                    DATA_SIZE + DATA_SIZE );
BusALU	alu_op0 ( "ALU_OP0",
                  DATA_SIZE + DATA_SIZE );
BusALU	alu_op1 ( "ALU_OP1",
                  DATA_SIZE + DATA_SIZE );

/**
 * Cache
 */

// insstruction cache
Memory instr_cache ( "INSTRUCTION_CACHE",
                     ADDR_SIZE,
                     DATA_SIZE );

// data cache
Memory data_cache ( "DATA_CACHE",
                    ADDR_SIZE,
                    DATA_SIZE );

/**
 * Modules
 */

// IBox
//

/* Runtime control variables */
bool done ( false ); // is the simulation over?
// $(filename) END
