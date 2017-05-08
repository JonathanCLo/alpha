/**
 * execute.cpp
 *
 * Author   Jonathan Lo < >
 * Contributor: Nathan Castle
 */
#include "includes.h"

void execute ( );

void operate_exec(int opcode, int func){
    switch(func){
        case 0: //ADDL
            arith_alu.OP1().pullFrom(ra_re);
            arith_alu.perform(BusALU::op_add);
            rc_re.latchFrom(arith_alu.OUT());
            if (opcode < 0) { //immediate
                //temp
                arith_alu.OP2().pullFrom(li_re);
                //temp <- Ra + Li
            } else { //register
                arith_alu.OP2().pullFrom(rb_re);
                //temp <- Ra + Rb
            }
            break;
        case 2: // S4ADDL
        case 11: //S4SUBL 
            shift_alu.OP1().pullFrom(ra_re);
            shift_alu.OP2().pullFrom(exec_const_2);
            rc_re.latchFrom(arith_alu.OUT());
            arith_alu.perform(BusALU::op_lshift);
            //temp <- leftShift(Ra, 2)
            break;
        case 18: // S8ADDL
        case 27: // S8SUBL 
            shift_alu.OP1().pullFrom(ra_re);
            shift_alu.OP2().pullFrom(exec_const_3);
            rc_re.latchFrom(arith_alu.OUT());
            arith_alu.perform(BusALU::op_lshift);
            //temp <- leftShift(Ra, 3)
            break;
        case 9: // SUBL
            arith_alu.OP1().pullFrom(ra_re);
            arith_alu.perform(BusALU::op_sub);
            rc_re.latchFrom(arith_alu.OUT());
            if (opcode < 0) { //immediate
                arith_alu.OP2().pullFrom(li_re);
                //temp <- Ra - Li
            } else { //register
                arith_alu.OP2().pullFrom(rb_re);
                //temp <- Ra - Rb
            }
            break;
        case 15: //CMPBGE Note: this was removed after implementation started.
            //???
            break;
        default:
            break;
    }
}

void operate_move(int opcode, int func){
    switch(func){
        case 0: //ADDL //Note this may not actually be necessary
            break;
        case 9: //SUBL //Do nothing here - assume rc_re is temp 
            //Rc <- temp<31:0>
            break;
        case 2: // S4ADDL
        case 18: //S8ADDL 
            arith_alu.OP1().pullFrom(ra_re);
            arith_alu.perform(BusALU::op_add);
            rc_re.latchFrom(arith_alu.OUT());
            if (opcode < 0) { //immediate
                arith_alu.OP2().pullFrom(li_re);
                //Rc <- SignExt(temp + Li)<31:0>
            } else { //register
                arith_alu.OP2().pullFrom(rb_re);
                //Rc <- SignExt(temp + Rb)<31:0>
            }
            break;
        case 11: //S4SUBL
        case 27: //S8SUBL
            arith_alu.OP1().pullFrom(rc_re);
            arith_alu.perform(BusALU::op_sub);
            rc_re.latchFrom(arith_alu.OUT());
            if (opcode < 0) { //immediate
                arith_alu.OP2().pullFrom(li_re);
                //Rc <- SignExt(temp - Li)<31:0>
            } else { //register
                arith_alu.OP2().pullFrom(rb_re);
                //Rc <- SignExt(temp - Rb)<31:0>
            }
            break;
        case 15: //CMPBGE
            //???
            break;
        default:
            break;
    }
}

void logical_calc(int opcode, int func){
    switch (func) {
        case 0: //AND
            arith_alu.OP1().pullFrom(ra_re);
            arith_alu.perform(BusALU::op_and);
            rc_re.latchFrom(arith_alu.OUT());
            if (opcode < 0) { //immediate
                arith_alu.OP2().pullFrom(li_re);
                //Rc <- Ra AND Li
            } else {
                arith_alu.OP2().pullFrom(rb_re);
                //Rc <- Ra AND Rb
            }
            break;
        case 8: // BIC
            rc_re.latchFrom(arith_alu.OUT());
            arith_alu.perform(BusALU::op_not);
            if (opcode < 0) { //immediate 
                arith_alu.OP1().pullFrom(li_re);
                //Rc <- Ra AND NOT Li
            } else {
                arith_alu.OP1().pullFrom(rb_re);
                //Rc <- Ra AND NOT Rb
            }
            break;
        case 32: //BIS 
            rc_re.latchFrom(arith_alu.OUT());
            arith_alu.OP1().pullFrom(ra_re);
            arith_alu.perform(BusALU::op_or);
            if (opcode < 0) { //immediate
                arith_alu.OP2().pullFrom(li_re);
                //Rc <- Ra logical OR Li
            } else { //register
                arith_alu.OP2().pullFrom(rb_re);
                //Rc <- Ra logical OR Rb
            }
            break;
        case 72: //EQV 
            rc_re.latchFrom(arith_alu.OUT());
            arith_alu.perform(BusALU::op_not);
            if (opcode < 0) { //immediate
                arith_alu.OP1().pullFrom(li_re);
                //Rc <- Ra XOR (NOT Li)
            } else { //register
                arith_alu.OP1().pullFrom(rb_re);
                //Rc <- Ra XOR (NOT Rb)
            }
            break;
        case 40: // ORNOT 
            rc_re.latchFrom(arith_alu.OUT());
            arith_alu.perform(BusALU::op_not);
            if (opcode < 0) {
                arith_alu.OP1().pullFrom(li_re);
                //Rc <- Ra OR NOT Li
            } else {
                arith_alu.OP1().pullFrom(rb_re);
                //Rc <- Ra OR NOT Rb
            }
            break;
        case 64: //XOR
            rc_re.latchFrom(arith_alu.OUT());
            arith_alu.perform(BusALU::op_xor);
            arith_alu.OP1().pullFrom(ra_re);
            if (opcode < 0) {
                arith_alu.OP2().pullFrom(li_re);
                //Rc <- Ra XOR Li
            } else {
                arith_alu.OP2().pullFrom(rb_re);
                //Rc <- Ra XOR Rb
            }
            break;
        case 36: //CMOVEQ
            rc_re.latchFrom(arith_alu.OUT());
            if (ra_re.zero()) {
                arith_alu.perform(BusALU::op_one);
            } else {
                arith_alu.perform(BusALU::op_zero);
            }
            //temp <- Ra == 0
            break;
        case 70: //CMOVGE
            rc_re.latchFrom(arith_alu.OUT());
            if (ra_re(31) == 0 || ra_re.zero()) {
                arith_alu.perform(BusALU::op_one);
            } else {
                arith_alu.perform(BusALU::op_zero);
            }
            //temp <- Ra >=0
            break;
        case 102: //CMOVGT
            rc_re.latchFrom(arith_alu.OUT());
            if (ra_re(31) == 0 && !ra_re.zero()) {
                arith_alu.perform(BusALU::op_one);
            } else {
                arith_alu.perform(BusALU::op_zero);
            }
            //temp <- Ra >0
            break;
        case 22: //CMOVLBC
            rc_re.latchFrom(arith_alu.OUT());
            if (ra_re(0) == 0) {
                arith_alu.perform(BusALU::op_one);
            } else {
                arith_alu.perform(BusALU::op_zero);
            }
            //temp <- Ra<0:0> == 0
            break;
        case 20: //CMOVLBS
            rc_re.latchFrom(arith_alu.OUT());
            if (ra_re(0) != 0) {
                arith_alu.perform(BusALU::op_one);
            } else {
                arith_alu.perform(BusALU::op_zero);
            }
            //temp <- Ra<0:0> == 1
            break;
        case 100: //CMOVLE
            rc_re.latchFrom(arith_alu.OUT());
            if (ra_re(31) != 0 || ra_re.zero()) {
                arith_alu.perform(BusALU::op_one);
            } else {
                arith_alu.perform(BusALU::op_zero);
            }
            //temp <- Ra <= 0
            break;
        case 68: //CMOVLT
            rc_re.latchFrom(arith_alu.OUT());
            if (ra_re(31) != 0 && !ra_re.zero()) {
                arith_alu.perform(BusALU::op_one);
            } else {
                arith_alu.perform(BusALU::op_zero);
            }
            //temp <- Ra < 0
            break;
        case 38: //CMOVNE
            rc_re.latchFrom(arith_alu.OUT());
            if (!ra_re.zero()) {
                arith_alu.perform(BusALU::op_one);
            } else {
                arith_alu.perform(BusALU::op_zero);
            }
            //temp <- Ra != 0
            break;
        default:
            break;
    }
}

void logical_move(int opcode, int func) {
    switch (func) {
        case 0: //AND
            break; //no extra work needed
        case 8: // BIC
            rc_re.latchFrom(arith_alu.OUT());
            arith_alu.OP1().pullFrom(ra_re);
            arith_alu.OP2().pullFrom(rc_re);
            arith_alu.perform(BusALU::op_and);
            //RC <- Ra AND RC (see part above)
            break;
        case 32: //BIS
            break; //no extra work needed
        case 72: //EQV
            rc_re.latchFrom(arith_alu.OUT());
            arith_alu.OP1().pullFrom(ra_re);
            arith_alu.OP2().pullFrom(rc_re);
            arith_alu.perform(BusALU::op_xor);
            break;
        case 40: // ORNOT
            rc_re.latchFrom(arith_alu.OUT());
            arith_alu.OP1().pullFrom(ra_re);
            arith_alu.OP2().pullFrom(rc_re);
            arith_alu.perform(BusALU::op_or);
            break;
        case 64: //XOR
        case 36: //CMOVEQ
        case 70: //CMOVGE
        case 102: //CMOVGT
        case 22: //CMOVLBC
        case 20: //CMOVLBS
        case 100: //CMOVLE
        case 68: //CMOVLT
            break; //no extra work needed for these instructions
        case 38: //CMOVNE
            rc_re.latchFrom(arith_alu.OUT());
            arith_alu.OP1().pullFrom(li_re);
            arith_alu.OP2().pullFrom(rb_re);
            if (opcode < 0) { //immediate
                if (rc_re.zero()){
                    arith_alu.perform(BusALU::op_rop1);
                }
                //if (temp.zero()) { Rc <- Li}
            } else { //register
                if (rc_re.zero()) {
                    arith_alu.perform(BusALU::op_rop2);
                }
                //if (temp.zero()) { Rc <- Rb}
            }
            break;
        default:
            break;
    }
}

void exec_calc(int opcode, int func){
    switch(opcode) {
        case 9: //LDAH
            //Rb <- Rb + signExt(disp lshift 16) TODO
            break;
        case 8: //LDA
        case 10:  //LDBU
        case 40: //LDL
        case 12: //LDWU
            rb_re.latchFrom(arith_alu.OUT());
            arith_alu.OP1().pullFrom(rb_re);
            arith_alu.OP2().pullFrom(disp_re);
            arith_alu.perform(BusALU::op_add);
            //Rb <- Rb + disp
            break;
        case 44: //STL
            break;
        case 13: //STW
            break;
        case 57: //BEQ
        case 62: //BGE
        case 63: //BGT
        case 56: //BLBC
        case 60: //BLBS
        case 59: //BLE
        case 58: //BLT
        case 61: //BNE
        case 48: //BR
        case 52: //BSR //NOTE: multiplication by 4 is just shift left by two
            rc_re.latchFrom(arith_alu.OUT());
            arith_alu.OP1().pullFrom(disp_re);
            arith_alu.OP2().pullFrom(exec_const_2);
            arith_alu.perform(BusALU::op_lshift);
            //temp <- 4 * signExt(disp)
            break;
        case 26: //JMP, JSR, RET, JSRC 
            rc_re.latchFrom(arith_alu.OUT());
            arith_alu.OP1().pullFrom(exec_const_3);
            arith_alu.perform(BusALU::op_not);
            //temp <- Rb AND NOT 3
            ra_re.latchFrom(pcbus_r.OUT());
            pcbus_r.IN().pullFrom(pc_re);
            //Ra <- PC
            break;
        case 16: //operations - register
        case -16: //operations - immediate
            operate_exec(opcode, func);
            break;
        case 17:
        case -17:
            logical_calc(opcode, func);
            break;
        case 18: //mask, insert, extract
        case -18: //selected for removal from spec
            //mie_calc(opcode, func);
            break;
        default:
            break;
    }
}
void exec_move(int opcode, int func){
    switch(opcode) {
        case 44:
        case 13:
            //MemInput <- Ra
            data_cache.WRITE().pullFrom(ra_re);
            //outbus_em.IN().pullFrom(ra_re);
            //Note: no break, should fall through to MAR<-Rb
        case 8:
        case 9:
        case 10:
        case 40:
        case 12:
            //MAR <- Rb
            addr_alu.OP1().pullFrom(rb_re);
            addr_alu.perform(BusALU::op_rop1);
            //TODO - figure out how memory stage is going to take this
            break;
        case 57: //BEQ
        case 62: //BGE
        case 63: //BGT
        case 56: //BLBC
        case 60: //BLBS
        case 59: //BLE
        case 58: //BLT
        case 61: //BNE
        case 48: //BR
        case 52: //BSR
            //PC <- PC + Temp
            pc_alu.OP1().pullFrom(pc_re);
            pc_alu.OP2().pullFrom(rc_re);
            pc_alu.perform(BusALU::op_add);
            break;
        case 26: //JMP, JSR, RET, JSRC
            pc_alu.OP1().pullFrom(rb_re);
            pc_alu.OP2().pullFrom(rc_re);
            pc_alu.perform(BusALU::op_add);
            break;
        case 16: //operations - Register
        case -16: //Operations - Immediate
            operate_move(opcode, func);
            break;
        case 17:
        case -17:
            logical_move(opcode, func);
            break;
        case 18: //mask, insert, extract
        case -18: //selected for removal from spec
            //mie_move(opcode, func);
        default:
            break;
    }
}
/**
 * execute
 *  executes the instruction
 */
void execute ( )
{
    int opcode;
    if (ir_re(12) == 0){
        opcode = ir_re(31, 26);
    } else {
        opcode = -ir_re(31, 26); //signals immediate value vs register value
    }
    int func = ir_re(11, 5); // note: won't always use this one
    exec_calc(opcode, func);
    Clock::tick ( );
    exec_move(opcode, func);
    Clock::tick ( );

    memory ( );
} // execute

// $(filename) end
