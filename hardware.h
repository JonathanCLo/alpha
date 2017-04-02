/**
 * hardware.h
 *
 * Author   Nathan Castle < >
 *          Jonathan Lo <jcl5201>
 * global hardware instantiations
 */
#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "includes.h"

/* GLOBAL SIZES */
extern const unsigned int	ADDR_SIZE;  //
extern const unsigned int	OPC_SIZE;   // OP SIZE
extern const unsigned int	REG_SIZE;   // REGISTER SIZE
extern const unsigned int	DATA_SIZE;  // DATA SIZE

/* RESERVED REGISTERS */
extern Counter				pc;
extern Counter				lr0;
extern Counter				lr1;
extern Counter				pcc;
extern Clearable			ir0;
extern Clearable			ir1;
extern Clearable			ir2;
extern Clearable			ir3;

/* Programmer-viewable registers */
extern Counter				r0;
extern Counter				r1;
extern Counter				r2;
extern Counter				r3;
extern Counter				r4;
extern Counter				r5;
extern Counter				r6;
extern Counter				r7;
extern Counter				r8;
extern Counter				r9;
extern Counter				r10;
extern Counter				r11;
extern Counter				r12;
extern Counter				r13;
extern Counter				r14;
extern Counter				r15;
extern Counter				r16;
extern Counter				r17;
extern Counter				r18;
extern Counter				r19;
extern Counter				r20;
extern Counter				r21;
extern Counter				r22;
extern Counter				r23;
extern Counter				r24;
extern Counter				r25;
extern Counter				r26;
extern Counter				r27;
extern Counter				r28;
extern Counter				r29;
extern Counter				r30;
extern Clearable			r31;     // used as a 'zero' register

/* busses */
extern Bus					ibus;
extern Bus					abus;
extern Bus					dbus;

/* cache */
extern Memory				instr_cache;
extern Memory				data_cache;

#endif

// $(filename) END
