/**
 * read.cpp
 *
 * Author   Jonathan Lo < >
 */

#include "includes.h"
int write_reg (int upper, int lower, void (*f)(StorageObject& rx))
{
    long reg = ir_re ( upper, lower);
    switch ( reg ) {
        case 0: return f(r0); break; case 1: return f(r1); break;
        case 2: return f(r2); break; case 3: return f(r3); break;
        case 4: return f(r4); break; case 5: return f(r5); break;
        case 6: return f(r6); break; case 7: return f(r7); break;
        case 8: return f(r8); break; case 9: return f(r9); break;
        case 10:return f(r10);break;case 11: return f(r11);break;
        case 12:return f(r12);break;case 13: return f(r13);break;
        case 14:return f(r14);break;case 15: return f(r15);break;
        case 16:return f(r16);break;case 17: return f(r17);break;
        case 18:return f(r18);break;case 19: return f(r19);break;
        case 20:return f(r20);break;case 21: return f(r21);break;
        case 22:return f(r22);break;case 23: return f(r23);break;
        case 24:return f(r24);break;case 25: return f(r25);break;
        case 26:return f(r26);break;case 27: return f(r27);break;
        case 28:return f(r28);break;case 29: return f(r29);break;
        case 30:return f(r30);break;case 31: return f(r31);break;
    }
    return 0;
}

/**
 * read1
 */
void read1 ( )
{
    // reset indicator. this does not get used until tick2
    ir_purge = false;
    // move ir
    irbus_r1.IN ( ).pullFrom ( ir_ir );
    ir_r.latchFrom ( irbus_r1.OUT ( ) );
    // move pc
    pcbus_r1.IN ( ).pullFrom ( pc_ir );
    pc_r.latchFrom ( pcbus_r1.OUT ( ) );
    long opc = ir_re ( REG_SIZE - 1, REG_SIZE - 6 );
    switch ( opc ) {
        case OPC_NOOP:
            noop1 ( );
            break;
        case OPC_LDA:  case OPC_LDAH:
        case OPC_LDWU: case OPC_LDL:
        case OPC_STL:
            memdisp1 ( );
            break;
        case OPC_BEQ: case OPC_BGE:
        case OPC_BGT: case OPC_BLBC:
        case OPC_BLBS:case OPC_BLE:
        case OPC_BLT: case OPC_BNE:
        case OPC_BR:  case OPC_BSR: // B
            branch1 ( );
            break;
        case OPC_JMP:
            jump1 ( );
            break;
        case OPC_RPCC: // pcc
            // pcc ( );
            break;
        case OPC_ADDL:
            operate1 ( );
            break;
        default: // unknown
            done = true;

    } // switch

    execute1 ( );
} // read1

/**
 * read2
 */
void read2 ( )
{
    long opc = ir_r ( REG_SIZE - 1, REG_SIZE - 6 );
    switch ( opc ) {
        case OPC_NOOP:
            noop2 ( );
            break;
        case OPC_LDA:  case OPC_LDAH:
        case OPC_LDWU: case OPC_LDL:
        case OPC_STL:
            memdisp2 ( );
            break;
        case OPC_BEQ:  case OPC_BGE:
        case OPC_BGT:  case OPC_BLBC:
        case OPC_BLBS: case OPC_BLE:
        case OPC_BLT:  case OPC_BNE:
        case OPC_BR:   case OPC_BSR: // B
            branch2 ( );
            break;
        case OPC_JMP:
            jump2 ( );
            break;
        case OPC_RPCC: // pcc
            // pcc ( );
            break;
        case OPC_ADDL:
            operate2 ( );
            break;
        default: // unknown
            done = true;
    } // switch
    execute2 ( );
} // read

/**
 * memdisp1
 */
void memdisp1 ( )
{
    // sign extend
    signExtalu_r.OP1 ( ).pullFrom ( npc_ir );
    signExtalu_r.OP2 ( ).pullFrom ( dispmask_g );
    dest_r.latchFrom ( signExtalu_r.OUT ( ) );
    signExtalu_r.perform ( BusALU::op_extendSign );
}

/**
 * memdisp2
 *
 *
 */
void memdisp2 ( )
{
    // move ir
    irbus_r2.IN ( ).pullFrom ( ir_ir );
    ir_r.latchFrom ( irbus_r2.OUT ( ) );
    // move pc
    pcbus_r2.IN ( ).pullFrom ( pc_ir );
    pc_r.latchFrom ( pcbus_r2.OUT ( ) );
    // move disp
    destbus_r.IN ( ).pullFrom ( dest_r );
    disp_re.latchFrom ( destbus_r.OUT ( ) );
} // memdisp2

int sf_copy_ra(StorageObject& rx) { return rx.value(); } 
/**
 * branch1
 * calculates the possible npc
 */
void branch1 ( )
{
    // sign extend
    signExtalu_r.OP1 ( ).pullFrom ( npc_ir );
    signExtalu_r.OP2 ( ).pullFrom ( shift7_g );
    dest_r.latchFrom ( signExtalu_r.OUT ( ) );
    signExtalu_r.perform ( BusALU::op_rashift );

    // get ra for comparison
    long ra_value = write_reg(REG_SIZE - 7, REG_SIZE -11, sf_copy_ra);
    // grab the ra_value
    //TODO???
} // branch1

/**
 * branch2
 * calculates if we take the branch
 *
 */
void branch2 ( )
{
    long branch = ir_re ( REG_SIZE - 1, REG_SIZE - 6 );

    // calculate if we are taking branch
    switch ( branch ) {
        case OPC_BEQ:
            if ( ra_value == 0 ) { // take the branch
                use_npc ( );
            } else { // not taken... continue onward
                use_pc ( );
            }
            break;
        case OPC_BGE:
            if ( ra_value >= 0 ) { // take the branch
                use_npc ( );
            } else { // not taken... continue onward
                use_pc ( );
            }
            break;
        case OPC_BGT:
            if ( ra_value > 0 ) { // take the branch
                use_npc ( );
            } else { // not taken... continue onward
                use_pc ( );
            }
            break;
        case OPC_BLBC:
            if ( ( ra_value & 1 ) == 0 ) { // take the branch
                use_npc ( );
            } else { // not taken... continue onward
                use_pc ( );
            }
            break;
        case OPC_BLBS:
            if ( ( ra_value & 1 ) == 1 ) { // take the branch
                use_npc ( );
            } else { // not taken... continue onward
                use_pc ( );
            }
            break;
        case OPC_BLE:
            if ( ra_value <= 0 ) { // take the branch
                use_npc ( );
            } else { // not taken... continue onward
                use_pc ( );
            }
            break;
        case OPC_BLT:
            if ( ra_value < 0 ) { // take the branch
                use_npc ( );
            } else { // not taken... continue onward
                use_pc ( );
            }
            break;
        case OPC_BNE:
            if ( ra_value != 0 ) { // take the branch
                use_npc ( );
            } else { // not taken... continue onward
                use_pc ( );
            }
            break;
        case OPC_BR:
        case OPC_BSR:
            use_npc ( );
            break;
        default: // dont care
            break;
    } // switch

} // branch2

/**
 * use_npc
 * change the pc in fetch to fetch the good instr and purge useless ones.
 */
void use_npc ( )
{
    // change pc_load
    changePC_bus.IN ( ).pullFrom ( npc_r );
    pc_load.latchFrom ( changePC_bus.OUT ( ) );
    // discard pc_re // TODO do we?

    // indicate stage that it should purge instruction
    ir_purge = true;
    // toss curr inst
    ir_noop_bus_r.IN ( ).pullFrom ( noop );
    ir_re.latchFrom ( ir_noop_bus_r.OUT ( ) );

} // use_npc

/**
 * use_pc
 * use the old pc and move forward
 */
void use_pc ( )
{
    // move pc
    pcbus_r.IN ( ).pullFrom ( pc_r );
    pc_re.latchFrom ( pcbus_r.OUT ( ) );
    // move ir
    irbus_r.IN ( ).pullFrom ( ir_r );
    ir_re.latchFrom ( irbus_r.OUT ( ) );
}

/**
 * jumps
 */
void jump1 ( )
{
    // write to ra the pc
    write_ra ( );
    // TODO Data hazard?
    move_rb ( ); //get rb
} // jump1

/**
 * jump2
 *
 *
 */
void jump2 ( )
{
    destalu_r.OP1 ( ).pullFrom ( rb_r );
    destalu_r.OP2 ( ).pullFrom ( not3_g );
    pc_load.latchFrom ( destalu_r.OUT ( ) );
    destalu_r.perform ( BusALU::op_and );

    // purge curr instr
    // indicate stage that it should purge instruction
    ir_purge = true;
    // toss curr inst
    ir_noop_bus_r.IN ( ).pullFrom ( noop );
    ir_re.latchFrom ( ir_noop_bus_r.OUT ( ) );
} // jump2

/**
 * operate1
 */
void operate1 ( )
{
    long ind = ir_r ( REG_SIZE - 20 );
    move_ra();
    move_rc();
    switch ( ind ) {
        case 0; // register
            move_rb ( );
            break;
        case 1; // literal
            // get value
            litalu_r.OP1 ( ).pullFrom ( ir_r );
            litalu_r.OP2 ( ).pullFrom ( literalmask_g );
            literal_r.latchFrom ( litalu_r.OUT ( ) );
            litalu_r.peform ( BusALU::op_and );
            break;
    } // switch

} // operate1

/**
 * operate2
 */
void operate2 ( )
{
    long ind = ir_r ( REG_SIZE - 20 );
    rabus_r.IN().pullFrom(ra_r);
    ra_re.latchFrom(rabus_r.OUT());
    rcbus_r.IN().pullFrom(rc_r);
    rc_re.latchFrom(rcbus_r.OUT());
    switch ( ind ) {
        case 0; // register
            rbbus_r.IN ( ).pullFrom ( rb_r );
            rb_re.latchFrom ( rbbus_r.OUT ( ) );
            break;
        case 1; // literal
            litalu_r.OP1 ( ).pullFrom ( literal_r );
            litalu_r.OP2 ( ).pullFrom ( literalShift_g );
            literal_re.latchFrom ( litalu_r.OUT ( ) );
            litalu_r.perform ( BusALU::op_rshift );
            break;
    } // switch

} // operate2

/**
 * move_ra
 * support function to move a PVR's ddata to ra_r
 */

int fs_simp_ra(StorgeObject& rx) { return rabus_r.IN().pullFrom(rx); }
void move_ra ( )
{
    long ra = ir_re ( REG_SIZE - 7, REG_SIZE - 11 ); // move ra
    ra_r.latchFrom ( rabus_r.OUT ( ) );
    reg_write(REG_SIZE - 7, REG_SIZE -11, fs_simp_ra);

} // move_ra

/**
 * write_ra
 */
int fs_simp_ra2(StorgeObject& rx) { rx.latchFrom(rabus_r.OUT()); return; }
void write_ra ( )
{
    long ra = ir_re ( REG_SIZE - 7, REG_SIZE - 11 );

    // move ra
    rabus_r.IN ( ).pullFrom ( pc_r );

    reg_write(REG_SIZE - 7, REG_SIZE - 11, fs_simp_ra2); 
}
/**
 * move_rb
 * support function to move a PVR's ddata to ra_r
 */
 int fs_simp_rb(StorgeObject& rx) { rbbus_r.IN().pullFrom(rx); return; }

void move_rb ( )
{
    long rb = ir_re ( REG_SIZE - 12, REG_SIZE - 16 );

    // move ra
    rb_r.latchFrom ( rbbus_r.OUT ( ) );
    reg_write(REG_SIZE - 12, REG_SIZE - 16, fs_simp_rb);
} // move_rb
 int fs_simp_rc(StorgeObject& rx) { rcbus_r.IN().pullFrom(rx); return; }

/**
 * move_rc
 */
void move_rc ( )
{
    long rc = ir_re ( REG_SIZE - 28, 0 );

    // move ra
    rc_r.latchFrom ( rcbus_r.OUT ( ) );
    reg_write(REG_SIZE-28, 0, fs_simp_rc);

} // move_rc

// read.cpp end
