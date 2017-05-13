/**
 * execute.cpp
 *
 * Author   Jonathan Lo < >
 * Contributor: Nathan Castle
 */
#include "includes.h"

void execute ( );

void ex_mem_s1(int opcode) {
    ex_internal_shift.latchFrom(shift_alu.OUT());
    shift_alu.OP1().pullFrom(disp_re);
    shift_alu.OP2().pullFrom(exec_const_16);
    if ( opcode == OPC_LDAH) { shift_alu.perform(BusALU::op_lshift); return; }
    else { shift_alu.perform(BusALU::op_rop1); return; } //disp already in position
    ex_internal_addr.latchFrom(addr_alu.OUT());
    addr_alu.OP1().pullFrom(rb_re);
    addr_alu.perform(BusALU::op_rop1);
}

void ex_mem_s2(int opcode) {
    addr_alu.OP1().pullFrom(ex_internal_addr);
    addr_alu.OP2().pullFrom(ex_internal_shift);
    addr_alu.perform(BusALU::op_add);
    //ex_out_addr.latchFrom(addr_alu.OUT()); - cheating in mem
    data_cache.MAR().latchFrom(addr_alu.OUT());
    return;
}

void __disp_4 () {
    addr_alu.OP1().pullFrom(disp_re);
    addr_alu.OP2().pullFrom(exec_const_2);
    addr_alu.perform(BusALU::op_lshift);
    ex_internal_addr.latchFrom(addr_alu.OUT());
    return;
}

void ex_br_s1(int opcode, int func) {
    //TODO - where to put decision? guess below:
    //Note: its beginning to look like execute can just ignore branch instrs...
    ex_internal_arith.latchFrom(arith_alu.OUT());

    //also put forwarding destination here...
    
    //move value over just in case...
    ex_internal_shift.latchFrom(shift_alu.OUT());
    shift_alu.perform(BusALU::op_rop1);
    if (opcode == OPC_BR || opcode == OPC_BSR) { //move right value
        shift_alu.OP1().pullFrom(pc_re);
    } else { shift_alu.OP1().pullFrom(disp_re); 
    }
    //addr calc:
    if (opcode != 26 ) { __disp_4(); } //JMP exception 
    //branch calc
    switch(opcode) {
        case OPC_BEQ: 
            if (ra_re.zero()) { arith_alu.perform(BusALU::op_one); return;}
            arith_alu.perform(BusALU::op_zero);
            return;
        case OPC_BGE:
            if (ra_re.zero()) {arith_alu.perform(BusALU::op_one); return; }
            if (ra_re(31) == 0) {
                arith_alu.perform(BusALU::op_one); return; }
            arith_alu.perform(BusALU::op_zero);
            return;
        case OPC_BGT:
            if (ra_re.zero()) { arith_alu.perform(BusALU::op_zero); return ; }
            if (ra_re(31) == 0) { arith_alu.perform(BusALU::op_one); return; }
            arith_alu.perform(BusALU::op_zero);
            return;
        case OPC_BLBC: 
            if (ra_re(0) == 0) {arith_alu.perform(BusALU::op_one); return; }
            else { arith_alu.perform(BusALU::op_zero); return; }
            break;
        case OPC_BLBS: 
            if (ra_re(0) == 0) {arith_alu.perform(BusALU::op_zero); return; }
            else { arith_alu.perform(BusALU::op_zero); return; }
            break;
        case OPC_BLT:
            if (ra_re(31) == 1) {arith_alu.perform(BusALU::op_one); return; }
            else { arith_alu.perform(BusALU::op_zero); }
            break;
        case OPC_BLE:
            if (ra_re.zero()) { arith_alu.perform(BusALU::op_one); return; }
            if (ra_re(31) == 1) { arith_alu.perform(BusALU::op_one); return; }
            arith_alu.perform(BusALU::op_zero); 
            return;
        case OPC_BNE: 
            if (ra_re.zero()) {arith_alu.perform(BusALU::op_zero); return;}
            arith_alu.perform(BusALU::op_one);
            return;
        case OPC_BR: case OPC_BSR: 
            arith_alu.OP1().pullFrom(pc_re);
            arith_alu.perform(BusALU::op_rop1);
            break;
        case OPC_JMP:
        default: //__disp_4 has NOT been called...
            arith_alu.OP1().pullFrom(pc_re);
            arith_alu.perform(BusALU::op_rop1);
            addr_alu.OP1().pullFrom(rb_re);
            addr_alu.OP2().pullFrom(exec_const_not_3);
            addr_alu.perform(BusALU::op_not);
            ex_internal_addr.latchFrom(addr_alu.OUT());
            break;
    }
}

void ex_br_s2(int opcode) {
    arith_alu.OP1().pullFrom(ex_internal_arith);
    arith_alu.perform(BusALU::op_rop1);
    ex_out_arith.latchFrom(arith_alu.OUT());

    addr_alu.OP1().pullFrom(ex_internal_addr);
    addr_alu.OP2().pullFrom(ex_internal_shift);

    //TODO/NOTE: because the target for branches is calculated earlier, 
    //this actual calc may not be necessary
    //ex_out_addr.latchFrom(addr_alu.OUT()); - cheating for mem stage
    //data_cache.MAR().latchFrom(addr_alu.OUT()); - actually treating this as a mem addr is wrong - it is a pc addr
    if (opcode != OPC_BR && opcode != OPC_BSR && opcode != OPC_JSR) {
        addr_alu.perform(BusALU::op_add); return; }
    if (opcode == OPC_BR || opcode == OPC_BSR) {
        addr_alu.perform(BusALU::op_add); return; }
    if (opcode == OPC_JMP) { addr_alu.perform(BusALU::op_rop1); }
    return;
};

void ex_arith_s1(int opcode, int func, bool imm) {
    //accounts for all arithmetic instructions
    if (imm) { //immediate
        addr_alu.OP1().pullFrom(li_re);
    } else {
        addr_alu.OP1().pullFrom(rb_re);
    }
    ex_internal_addr.latchFrom(addr_alu.OUT());
    //handle manipulation of Rb/Li at this pointer
    if (opcode == 17 && (func==8||func==72||func==40)) { 
        addr_alu.perform(BusALU::op_not); 
    }//BIC, EQV/ORNOT
    else if (opcode == 17) { addr_alu.perform(BusALU::op_rop1); }

    //Handle Ra at this point - all
    arith_alu.OP1().pullFrom(ra_re);
    ex_internal_arith.latchFrom(arith_alu.OUT());
    //first conditional
    if (opcode == 17) { //conditional moves
        arith_alu.perform(BusALU::op_rop1);
    }
    //  then normal
    else if (opcode != 16 || (func !=18 && func != 2 && func != 11 && func != 27)) { //everything else
        arith_alu.perform(BusALU::op_rop1);
    } else if (opcode == 16 && (func == 2 || func == 11)){ //Scaled 4
        arith_alu.OP2().pullFrom(exec_const_2);
        arith_alu.perform(BusALU::op_lshift);
    } else if (opcode == 16 && (func == 18|| func == 27)) { //scaled 8
        arith_alu.OP2().pullFrom(exec_const_3);
        arith_alu.perform(BusALU::op_lshift);
    }
}

void ex_arith_s2(int opcode, int func) {
    if (opcode == 17) {
        if (func == 36 && !ex_internal_arith.zero()) { return; } //CMOVEQ //TODO tell memory to no-op
        if (func == 70 && !ex_internal_arith.zero() && ex_internal_arith(31) == 1) { return; } //CMOVGE
        if (func == 102 && (ex_internal_arith.zero() || ex_internal_arith(31) == 1)) { return; } //CMOVGT
        if (func == 22 && ex_internal_arith(0) == 1) { return; } //CMOVLBC
        if (func == 20 && ex_internal_arith(0) == 0) { return; } //CMOVLBS
        if (func == 100 && !ex_internal_arith.zero() && ex_internal_arith(31) == 0) { return; } //CMOVLE
        if (func == 68 && (ex_internal_arith.zero() || ex_internal_arith(31) == 0)) { return; } //CMOVLT
        if (func == 38 && ex_internal_arith.zero()) { return; } //CMOVNE
    }
    arith_alu.OP1().pullFrom(ex_internal_arith);
    arith_alu.OP2().pullFrom(ex_internal_addr);
    ex_out_arith.latchFrom(arith_alu.OUT());
    if (opcode == 16 && (func == 0 || func == 2 || func == 18)) { arith_alu.perform(BusALU::op_add); }
    else if (opcode == 16 && (func == 9 || func == 11 || func == 27)) { arith_alu.perform(BusALU::op_sub); }
    else if (opcode == 17 && (func == 8 || func == 0)) { arith_alu.perform(BusALU::op_and); }
    else if (opcode == 17 && (func == 32 || func == 40)) {arith_alu.perform(BusALU::op_or); }
    else if (opcode == 17 && (func == 72 || func == 64)) { arith_alu.perform(BusALU::op_xor); }
    return;
}
/**
 * execute
 *  executes the instruction
 */
void execute1 ( )
{
    int opcode = ir_re(31, 26);
    bool imm = ir_re(12) == 0;
    int func = ir_re(11, 5);
    //preserve re for cycle 2
    switch (opcode) {
        case OPC_LDA: case OPC_LDAH: case OPC_LDBU:
        case OPC_LDL: case OPC_LDWU:
        case OPC_STL: case OPC_STW:
            ex_mem_s1(opcode);
            break;
        case OPC_ADDL: case OPC_AND:
            ex_arith_s1(opcode, func, imm);
            break;
        case OPC_BGE: case OPC_BGT: case OPC_BEQ: case OPC_BLBS:
        case OPC_BLE: case OPC_BLT: case OPC_BNE: case OPC_BR:
        case OPC_BSR:
            ex_br_s1(opcode, func);
            break;
        default:
            break;
    }
    irbus_e.IN().pullFrom(ir_re);
    ex_internal_ir.latchFrom(irbus_e.OUT());

} // execute1

void execute2 ( )
{
    int opcode = ex_internal_ir(31, 26);
    bool imm = ex_internal_ir(12) == 0;
    int func = ex_internal_ir(11, 5);
 
    switch (opcode) {
        case OPC_LDA: case OPC_LDAH: 
        case OPC_LDL: case OPC_LDWU:
        case OPC_STW: case OPC_LDBU:
            mem_flag.latchFrom(read_mem.OUT());
            ex_mem_s2(opcode);
            break;
        case OPC_STL: 
            mem_flag.latchFrom(write_mem.OUT());
            ex_mem_s2(opcode);
            break;
        case OPC_ADDL: case OPC_AND:
            mem_flag.latchFrom(writeback.OUT());
            ex_arith_s2(opcode, func);
            break;
        case OPC_BGE: case OPC_BGT: case OPC_BEQ: case OPC_BLBS:
        case OPC_BLE: case OPC_BLT: case OPC_BNE: case OPC_BR:
        case OPC_BSR:
            mem_flag.latchFrom(no_mem.OUT());
            ex_br_s2(opcode);
            break;
        default:
            break;
    }
}
// $(filename) end
