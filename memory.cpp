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
    long rx = ir_em ( upper, lower );
    ( *regfile[rx] ).latchFrom ( dbus_m.OUT ( ) );
    dbus_m.IN ( ).pullFrom ( out_em );
}

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
        long rx = ir_em ( REG_SIZE- 28, 0 );
        ( *regfile[rx] ).latchFrom ( dbus_m.OUT ( ) );
        dbus_m.IN ( ).pullFrom ( out_em );

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

// $(filename) end
