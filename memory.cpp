/**
 * memory.cpp
 *
 * Author   Jonathan Lo < >
 */
#include "includes.h"

void memory ( );
void memory1 ( );
void memory2 ( );
void memory_writeback ( );


void read_data_cache(){ data_cache.READ(); }
/**
 * write_ra
 * was data_cache.READ()
 * ra: REG_SIZE-7, REG_SIZE - 11
 * rc: REG_SIZE-28, 0
 * func
 */
void write_reg (int upper, int lower, void (*f)(StorageObject& rx))
{
    long reg = ir_em ( upper, lower);
    switch ( reg ) {
        case 0: f(r0); break; case 1: f(r1); break;
        case 2: f(r2); break; case 3: f(r3); break;
        case 4: f(r4); break; case 5: f(r5); break;
        case 6: f(r6); break; case 7: f(r7); break;
        case 8: f(r8); break; case 9: f(r9); break;
        case 10:f(r10);break;case 11: f(r11);break;
        case 12:f(r12);break;case 13: f(r13);break;
        case 14:f(r14);break;case 15: f(r15);break;
        case 16:f(r16);break;case 17: f(r17);break;
        case 18:f(r18);break;case 19: f(r19);break;
        case 20:f(r20);break;case 21: f(r21);break;
        case 22:f(r22);break;case 23: f(r23);break;
        case 24:f(r24);break;case 25: f(r25);break;
        case 26:f(r26);break;case 27: f(r27);break;
        case 28:f(r28);break;case 29: f(r29);break;
        case 30:f(r30);break;case 31: f(r31);break;
    }
}

void simple_rc(StorageObject& rx) { rx.latchFrom(dbus_m.OUT()); dbus_m.IN().pullFrom(out_em);}
void memory1() { //TODO - handle no-ops
    memory();
    int mem_type = mem_flag.value(); //keep this around
    mm_controlbus.IN().pullFrom(mem_flag);
    mm_internal_type.latchFrom(mm_controlbus.OUT());
    if (mem_type == 1 || mem_type == 2) {
        //data_cache.MAR().latchFrom(addr_bus.OUT()); - cheating in execute
        //addr_bus.IN().pullFrom(ex_out_addr);
        //store for next cycle - STL only
        dbus_m.IN().pullFrom(out_em);
        mm_internal_arith.latchFrom(dbus_m.OUT());
    } else if (mem_type == 3) {
        write_reg(REG_SIZE - 28, 0, simple_rc);
    }
}

void simple_mem(StorageObject& rx) { rx.latchFrom(data_cache.READ()); }
void memory2() {
    int mem_type = mem_flag.value();
    if (mem_type == 0) { return;  }
    
    if (mem_type == 2) {
        data_cache.WRITE().pullFrom(mm_internal_arith); 
        data_cache.write();
    }
    if (mem_type == 1) {
        write_reg(REG_SIZE - 7, REG_SIZE - 11, simple_mem);
        data_cache.read();
   }

}
/**
 * write_rc
 *
 * rc: reg_size - 28, 0
 * FUNC: dbus_m.OUT();
 */

/**
 * memory
 * memory stage of pipeline. writes/read to/from memory. Writes to registers
 *
 */
void memory ( )
{
    // PIPELINE IS DONE
    char buff [ 32 ];

    sprintf ( buff, "|pc=%02lx mf=undef out=%02lx addr=%04lx        |\n",
              pc_em.value ( ),
              out_em.value ( ),
              addr_em.value ( ) );
    cout << buff;
} // memory

// $(filename) end
