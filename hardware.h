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

/**
 * SPECIAL RESERVED REGISTERS
 * */
extern Counter              pcc;
extern Clearable            ir_f; //IR-Fetch
extern Counter              pc; //PC
extern Clearable            ir_fi; //IR-Fetch-Issue
extern Clearable            pc_fi; //PC-Fetch-Issue
extern Counter              pc_i; //PC - Issue
extern BusALU               alu_i;//ALU - Issue
extern Clearable            reg_lock1_i; //RegLock 1 - Issue
extern Clearable            reg_lock2_i; //Reglock 2 - Issue
extern Clearable            mem_lock_i; //MemLock - Issue
extern Clearable            ir_ir; //IR - Issue Read
extern Clearable            reg_lock1_ir; //reglock1 - Issue Read
extern Clearable            reg_lock2_ir; //reglock2 - Issue Read
extern Clearable            mem_lock_ir; //memlock - Issue Read
extern Clearable            reg_lock1_r; //reglock - Read
extern Clearable            reg_lock2_r; //reglock2 - Read
extern Clearable            mem_lock_r; //memlock - read
extern Counter              ra_re; //RA - Read Execute
extern Counter              rb_re; //RB - Read Execute
extern Clearable            reg_lock1_re; //reglock1 - Read Execute
extern Clearable            reg_lock2_re; //reglock2 - Read Execute
extern Clearable            mem_lock_re; //memlock - Read Execute
extern BusALU               alu_e; //ALU - execute
extern Clearable            out_e; //OUT - execute
extern Clearable            reg_lock1_e; //reglock 1 - execute
extern Clearable            reg_lock2_e; //reglock 2 - execute
extern Clearable            mem_lock_e; //memlock - execute
extern Clearable            addr_ed; //address - execute memory
extern Clearable            mem_lock_ed; //memlock - execute memory
extern Clearable            addr_m; //address - memory
extern Clearable            mem_lock_e; //memlock - memory

/** special pipeline buses **/
extern Bus                  fetch_bus;
extern Bus                  issue_bus;
extern Bus                  read_bus;
extern Bus                  exec_bus;
extern Bus                  mem_bus;

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
extern Clearable			r31;        // used as a 'zero' register

/* busses */
extern Bus                  addr_ibus; //address - instruction bus
extern Bus                  data_ibus; //data - instruction bus
extern Bus                  addr_dbus; //address - data bus
extern Bus                  data_dbus; //data - data bus
/* cache */
extern Memory				instr_cache;
extern Memory				data_cache;

#endif

// $(filename) END
