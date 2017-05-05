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

/* GLOBAL SIZES */
extern const unsigned int  ADDR_SIZE;  //
extern const unsigned int  OPC_SIZE;   // OP SIZE
extern const unsigned int  REG_SIZE;   // REGISTER SIZE
extern const unsigned int  DATA_SIZE;  // DATA SIZE

/**
 * SPECIAL RESERVED REGISTERS
 */
extern Counter    pc_f; // pc fetch
extern Counter    pc_fi; // pc fetch issue
extern Counter    pc_i; // pc issue
extern Counter    pc_ir; // pc issue read
extern Counter    pc_r; // pc read
extern Counter    pc_re; // pc read execute
extern Counter    pc_em; // pc execute memory
extern Clearable  ir_fi; // ir fetch issue
extern Clearable  ir_i; // ir issue
extern Clearable  ir_ir; // ir issue read
extern Clearable  ir_r; // ir read
extern Clearable  ir_re; // ir read execute
extern Counter    aux_i; // aux issue
extern Clearable  lock_ir; // lock issue read
extern Clearable  lock_re; // lock read execute
extern Clearable  disp_r; // disp read
extern Clearable  disp_re; // disp read execute
extern Clearable  li_r; // literal read
extern Counter    li_re; // literal read execute
extern Clearable  func_r; // func read
extern Clearable  func_re; // func read execute
extern Counter    ra_re; // ra read execute
extern Counter    rb_re; // rb read execute
extern Counter    rc_re; // rc read execute
extern Counter    aux_re; // aux read execute
extern Counter    fout_e; // fout execute
extern Counter    arith_op1; // execute
extern Counter    arith_op2; // execute
extern Counter    shift_op1; // execute
extern Counter    shift_op2; // execute
extern Counter    addr_op1; // execute
extern Counter    addr_op2; // execute
extern Counter    out_em; // out execute memory
extern Clearable  out_m; // out memory
extern Counter    addr_em; // addr execute memory
extern Clearable  data_m; // data memory

extern StorageObject exec_const_2;
extern StorageObject exec_const_3;
extern StorageObject exec_const_4;

/**
 * BUSES
 */
extern Bus  pcbus_f; // pcbus fetch
extern Bus  pcbus_i; // pcbus issue
extern Bus  pcbus_r; // pcbus read
extern Bus  pcbus_e; // pcbus execute
extern Bus  irbus_i; // irbus issue
extern Bus  pcbus_r; // pcbus read
extern Bus  irbus_r; // irbus read
extern Bus  rabus_r; // rabus read
extern Bus  rbbus_r; // rbbus read
extern Bus  rcbus_r; // rcbus read
extern Bus  auxbus_r; // auxbus read
extern Bus  lockbus_r; // lockbus read
extern Bus  arithop1_ebus; // arith op1 ebus execute
extern Bus  arithop2_ebus; // arith op2 ebus execute
extern Bus  shiftop1_ebus; // shift op1 ebus execute
extern Bus  shiftop2_ebus; // shift op2 ebus execute
extern Bus  addrop1_ebus; // addr op1 ebus execute
extern Bus  addrop2_ebus; // addr op2 ebus execute
extern Bus  shift_ebus; // shift ebus execute
extern Bus  addr_ebus; // addr ebus execute
extern Bus  outbus_em; // out bus execute memory
extern Bus  addrbus_em; // addr bus execute memory
extern Bus  addrbus_m; // addr bus memory
extern Bus  dbus_m; // dbus memory
extern Bus  sbus1; // stage buses
extern Bus  sbus2;
extern Bus  sbus3;
extern Bus  sbus4;
extern Bus  sbus5;

/**
 * ALU
 */
extern BusALU  pc_alu; // pc alu
extern BusALU  arith_alu; // arith alu
extern BusALU  shift_alu; // shift alu
extern BusALU  addr_alu; // addr alu

/**
 * Programmer-viewable registers
 */
extern Counter    r0;
extern Counter    r1;
extern Counter    r2;
extern Counter    r3;
extern Counter    r4;
extern Counter    r5;
extern Counter    r6;
extern Counter    r7;
extern Counter    r8;
extern Counter    r9;
extern Counter    r10;
extern Counter    r11;
extern Counter    r12;
extern Counter    r13;
extern Counter    r14;
extern Counter    r15;
extern Counter    r16;
extern Counter    r17;
extern Counter    r18;
extern Counter    r19;
extern Counter    r20;
extern Counter    r21;
extern Counter    r22;
extern Counter    r23;
extern Counter    r24;
extern Counter    r25;
extern Counter    r26;
extern Counter    r27;
extern Counter    r28;
extern Counter    r29;
extern Counter    r30;
extern Clearable  r31;        // used as a 'zero' register

/* cache */
extern Memory  instr_cache;
extern Memory  data_cache;

extern bool    done;

#endif

// $(filename) END
