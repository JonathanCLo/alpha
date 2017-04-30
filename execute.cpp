/**
 * execute.cpp
 *
 * Author   Jonathan Lo < >
 */
#include "includes.h"

void execute ( );

void operate_exec(int opcode, int func){
    switch(func){
        case 0: //ADDL
            if (opcode < 0) { //immediate
                //temp <- Ra + Li
            } else { //register
                //temp <- Ra + Rb
            }
            break;
        case 2: // S4ADDL
        case 11: //S4SUBL
            //temp <- leftShift(Ra, 2)
            break;
        case 18: // S8ADDL
        case 27: // S8SUBL
            //temp <- leftShift(Ra, 3)
            break;
        case 9: // SUBL
            if (opcode < 0) { //immediate
                //temp <- signExt(Ra - Li)
            } else { //register
                //temp <- signExt(Ra - Rb)
            }
            break;
        case 15: //CMPBGE
            //???
            break;
        default:
            break;
    }
}

void operate_move(int opcode, int func){
    switch(func){
        case 0: //ADDL
            //Rc <- SignExt(temp)<31:0>
            break;
        case 9: //SUBL
            //Rc <- temp<31:0>
            break;
        case 2: // S4ADDL
        case 18: //S8ADDL
            if (opcode < 0) { //immediate
                //Rc <- SignExt(temp + Li)<31:0>
            } else { //register
                //Rc <- SignExt(temp + Rb)<31:0>
            }
            break;
        case 11: //S4SUBL
        case 27: //S8SUBL
            if (opcode < 0) { //immediate
                //Rc <- SignExt(temp - Li)<31:0>
            } else { //register
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
            if (opcode < 0) { //immediate
                //Rc <- Ra AND Li
            } else {
                //Rc <- Ra AND Rb
            }
            break;
        case 8: // BIC
            if (opcode < 0) { //immediate
                //Rc <- Ra AND NOT Li
            } else {
                //Rc <- Ra AND NOT Rb
            }
            break;
        case 32: //BIS
            if (opcode < 0) { //immediate
                //Rc <- Ra logical OR Li
            } else { //register
                //Rc <- Ra logical OR Rb
            }
            break;
        case 72: //EQV
            if (opcode < 0) { //immediate
                //Rc <- Ra XOR (NOT Li)
            } else { //register
                //Rc <- Ra XOR (NOT Rb)
            }
            break;
        case 40: // ORNOT
            if (opcode < 0) {
                //Rc <- Ra OR NOT Li
            } else {
                //Rc <- Ra OR NOT Rb
            }
            break;
        case 64: //XOR
            if (opcode < 0) {
                //Rc <- Ra XOR Li
            } else {
                //Rc <- Ra XOR Rb
            }
            break;
        case 36: //CMOVEQ
            //temp <- Ra == 0
            break;
        case 70: //CMOVGE
            //temp <- Ra >=0
            break;
        case 102: //CMOVGT
            //temp <- Ra >0
            break;
        case 22: //CMOVLBC
            //temp <- Ra<0:0> == 0
            break;
        case 20: //CMOVLBS
            //temp <- Ra<0:0> == 1
            break;
        case 100: //CMOVLE
            //temp <- Ra <= 0
            break;
        case 68: //CMOVLT

            //temp <- Ra < 0
            break;
        case 38: //CMOVNE
            //temp <- Ra != 0
            break;
        default:
            break;
    }
}

void logical_move(int opcode, int func) {
    switch (func) {
        case 0: //AND
        case 8: // BIC
        case 32: //BIS
        case 72: //EQV
        case 40: // ORNOT
        case 64: //XOR
            break;
        case 36: //CMOVEQ
        case 70: //CMOVGE
        case 102: //CMOVGT
        case 22: //CMOVLBC
        case 20: //CMOVLBS
        case 100: //CMOVLE
        case 68: //CMOVLT
        case 38: //CMOVNE
            if (opcode < 0) { //immediate
                //if (temp.zero()) { Rc <- Li}
            } else { //register
                //if (temp.zero()) { Rc <- Rb}
            }
            break;
        default:
            break;
    }
}

void mie_calc(int opcode, int func) {
    switch (func) {
        case 22: //Extract Word Low EXTWL
            break;
        case 38: //Extract Longword Low EXTLL
            break;
        case 90: //Extract Word high EXTWH
            break;
        case 106: //Extract Lonword High EXTLH
            break;
        case 27: //Insert Word Low INSWL
            break;
        case 43: //Insert Longword Low INSLL
            break;
        case 87: //Insert Word high
            break;
        case 103: //Insert Longword High INSLH
            break;
        case 18: //Mask Word Low
            break;
        case 34: //Mask Longword Low
            break;
        case 82: //Mask Word High
            break;
        case 98: //Mask Longword High
            break;
        default:
            break;
    }
}
void exec_calc(int opcode, int func){
    switch(opcode) {
        case 9: //LDAH
            //Rb <- Rb + signExt(disp * 65536)
            break;
        case 8: //LDA
        case 10:  //LDBU
        case 40: //LDL
        case 12: //LDWU
            //Rb <- Rb + signExt(disp0
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
        case 52: //BSR
            //temp <- 4 * signExt(disp)
            break;
        case 26: //JMP, JSR, RET, JSRC
            //temp <- Rb AND NOT 3
            //Ra <- PC
            break;
        case 16: //operations - register
        case -16: //operations - immediate
            operate_exec(opcode);
            break;
        case 28: //CLTZ, CTPOP, CTTZ, SEXTW
        case -28: //immediate version of above
            //???
            break;
        case 19: //MULL
            //temp <- Ra * Rb
            break;
        case -19: //MULL
            //temp <- Ra * Li
            break;
        case 17:
        case -17:
            logical_calc(opcode, func);
            break;
        case 18: //mask, insert, extract
        case -18:
            mie_calc(opcode, func);
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
            //Note: no break, should fall through to MAR<-Rb
        case 8:
        case 9:
        case 10:
        case 40:
        case 12:
            //MAR <- Rb
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
            break;
        case 26: //JMP, JSR, RET, JSRC
            //PC <- temp
            break;
        case 16: //operations - Register
        case -16: //Operations - Immediate
            operate_move(opcode);
            break;
        case 28: //CLTZ, CTPOP, CTTZ, SEXTW
        case -28:
            //???
            break;
        case 19: //MULL
        case -19:
            //Rc <- signExt(temp)<31:0>
            break;
        case 17:
        case -17:
            logical_move(opcode, func);
            break;
        case 18: //mask, insert, extract
        case -18:
            mie_move(opcode, func);
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
    exec_calc(opcode, func);
    Clock::tick ( );
    exec_move(opcode, func);
    Clock::tick ( );

    memory ( );
} // execute

// $(filename) end
