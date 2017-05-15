#include "hazards.h"
#include "includes.h"

static int reg_deps[5][3] = {                          // Ra/Rc|Ra  | Rb
        { -1, -1, -1}, //instr1: [dest][dep1][dep2]
        { -1, -1, -1}, //instr2: [dest][dep1][dep2]
        { -1, -1, -1}, //instr3: [dest][dep1][dep2]
        { -1, -1, -1},
        { -1, -1, -1}
    };

void hazard_init() {
}
int instr_index = -1;
void advance_hd() {
    instr_index += 1;
    instr_index %= 5;
}
void load_dep_table(){
    //dest
    switch (ir_fi(31, 26)) { //all these instructions have Ra as dest 
        case OPC_LDA: case OPC_LDAH: case OPC_LDL: case OPC_BR: case OPC_BSR: case OPC_JMP: reg_deps[instr_index][0] = ir_fi(25, 21); break;
        //all of these instrs have pc as dest
        case OPC_BEQ: case OPC_BGE: case OPC_BLT: case OPC_BGT: case OPC_BLE: case OPC_BNE: case OPC_BLBC: case OPC_BLBS: reg_deps[instr_index][0] = -1; break;
        // all of these instrs have rc as dest
        default: reg_deps[instr_index][0] = ir_fi(4,0); break;
    }
    //dependency 1
    switch (ir_fi(31, 26)) {
        case OPC_LDA: case OPC_LDAH: case OPC_LDL: reg_deps[instr_index][1] = 100; break; //mem read
        case OPC_BEQ: case OPC_BGE: case OPC_BLT: case OPC_BGT: case OPC_BLE: case OPC_BNE: case OPC_BLBC: case OPC_BLBS: reg_deps[instr_index][1] = ir_fi(25, 21); break;//branches
        default: reg_deps[instr_index][1] = ir_fi(25, 21); break; //all other instrs (mostly operate)
    }
    //dependency 2
    switch (ir_fi(31, 26)) {
        case OPC_LDA: case OPC_LDAH: case OPC_LDL: case OPC_BR: case OPC_BSR: case OPC_BEQ: case OPC_BGE: case OPC_BLT: case OPC_BGT: case OPC_BLE: case OPC_JMP: break; //no other dep
        default: //all other ops
            if (ir_fi(12) == 0) {
                reg_deps[instr_index][2] = ir_fi(20, 16);
            } else { break; } //no dep; literal instr
            break;
    }
    reg_deps[instr_index][2] = ir_fi();
}

bool detect_read_after_write() {
    //newest instr is instr_index
    //previous instr is (instr_index - 1) % 3
    int current = (instr_index - 2) % 3;
    int past = (instr_index - 3) % 5;
    if (reg_deps[current][1] == -1) { return false; }
    if (reg_deps[current][1] == reg_deps[past][0]) {
        //we depend on the output of past instr for operand 1
        return true;
    }
    if (reg_deps[current][2] == reg_deps[past][0]){
        return true;
    }
    return false;
}

bool detect_read_after_load_dist() {
    int current = (instr_index - 2) % 5;
    int past = (instr_index - 4) % 5;
    int distpast = (instr_index -5) % 5;
    if (reg_deps[current][1] == -1) { return false; }
    if (reg_deps[current][1] == reg_deps[distpast][0]) {
        if (reg_deps[distpast][1] == 100) {
            return true;
        }
    } 
    if (reg_deps[current][2] == reg_deps[past][0]){
        if (reg_deps[distpast][1] == 100) {
            return true;
        }
    }
    return false;
}

void exec_read_after_write(bool imm){
    int current = (instr_index - 2) % 5;
    int past = (instr_index - 4) % 5;
    int distpast = (instr_index - 5) % 5;
    if (!detect_read_after_write()) { 
        arith_alu.OP1().pullFrom(ra_re);
        addr_alu.OP1().pullFrom(rb_re);
    }
    if (reg_deps[current][1] == reg_deps[past][0]) {
        //ra dependency
        if (reg_deps[past][1] == 100) {
            arith_alu.OP1().pullFrom(mm_external_load);
        } else {
            arith_alu.OP1().pullFrom(out_em);
        }
    } else if (reg_deps[current][1] == reg_deps[distpast][0]){
        if (reg_deps[distpast][1] == 100) { //mem
            arith_alu.OP1().pullFrom(mm_external_load);    
        } else {
            arith_alu.OP1().pullFrom(mm_external_arith);
        }
    } else {
        arith_alu.OP1().pullFrom(ra_re);
    }


    if (reg_deps[current][2] == reg_deps[past][0]) {
        //rb dependency
        if (reg_deps[past][1] == 100) { //mem
            addr_alu.OP1().pullFrom(mm_external_load);
        } else {
            addr_alu.OP1().pullFrom(out_em);
        }
    } else if (reg_deps[current][2] == reg_deps[distpast][0]) {
        if (reg_deps[distpast][1] == 100) { //mem
            addr_alu.OP1().pullFrom(mm_external_load);
        } else {
            addr_alu.OP1().pullFrom(mm_external_arith);
        }
    } else if (!imm) {
        addr_alu.OP1().pullFrom(rb_re);
    } else {
        addr_alu.OP1().pullFrom(literal_re);
    }
}

void memory_stall(){
    int current = (instr_index - 2) % 5;
    int past = (instr_index - 4) % 5;
    int distpast = (instr_index - 5) % 5;
    //turn exec into no-op
    ex_internal_ir.clear();
    //turn read into no-op
    ir_r.clear();
    //turn issue into no-op
    ir_i.clear(); 
    //reset pc in fetch stage
    pc_fi.decr();
    //reset dep table
    reg_deps[current][1] = -1;
    reg_deps[current][0] = -1;
    reg_deps[current][2] = -1;
}
