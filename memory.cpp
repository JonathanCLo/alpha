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

/**
 * write_ra
 *
 *
 */
void write_ra ( )
{
	long ra = ir_em ( REG_SIZE - 7, REG_SIZE - 11 );

	switch ( ra ) {
		case 0:
			r0.latchFrom ( data_cache.READ ( ) );
			break;
		case 1:
			r1.latchFrom ( data_cache.READ ( ) );
			break;
		case 2:
			r2.latchFrom ( data_cache.READ ( ) );
			break;
		case 3:
			r3.latchFrom ( data_cache.READ ( ) );
			break;
		case 4:
			r4.latchFrom ( data_cache.READ ( ) );
			break;
		case 5:
			r5.latchFrom ( data_cache.READ ( ) );
			break;
		case 6:
			r6.latchFrom ( data_cache.READ ( ) );
			break;
		case 7:
			r7.latchFrom ( data_cache.READ ( ) );
			break;
		case 8:
			r8.latchFrom ( data_cache.READ ( ) );
			break;
		case 9:
			r9.latchFrom ( data_cache.READ ( ) );
			break;
		case 10:
			r10.latchFrom ( data_cache.READ ( ) );
			break;
		case 11:
			r11.latchFrom ( data_cache.READ ( ) );
			break;
		case 12:
			r12.latchFrom ( data_cache.READ ( ) );
			break;
		case 13:
			r13.latchFrom ( data_cache.READ ( ) );
			break;
		case 14:
			r14.latchFrom ( data_cache.READ ( ) );
			break;
		case 15:
			r15.latchFrom ( data_cache.READ ( ) );
			break;
		case 16:
			r16.latchFrom ( data_cache.READ ( ) );
			break;
		case 17:
			r17.latchFrom ( data_cache.READ ( ) );
			break;
		case 18:
			r18.latchFrom ( data_cache.READ ( ) );
			break;
		case 19:
			r19.latchFrom ( data_cache.READ ( ) );
			break;
		case 20:
			r20.latchFrom ( data_cache.READ ( ) );
			break;
		case 21:
			r21.latchFrom ( data_cache.READ ( ) );
			break;
		case 22:
			r22.latchFrom ( data_cache.READ ( ) );
			break;
		case 23:
			r23.latchFrom ( data_cache.READ ( ) );
			break;
		case 24:
			r24.latchFrom ( data_cache.READ ( ) );
			break;
		case 25:
			r25.latchFrom ( data_cache.READ ( ) );
			break;
		case 26:
			r26.latchFrom ( data_cache.READ ( ) );
			break;
		case 27:
			r27.latchFrom ( data_cache.READ ( ) );
			break;
		case 28:
			r28.latchFrom ( data_cache.READ ( ) );
			break;
		case 29:
			r29.latchFrom ( data_cache.READ ( ) );
			break;
		case 30:
			r30.latchFrom ( data_cache.READ ( ) );
			break;
		case 31:
			r31.latchFrom ( data_cache.READ ( ) );
			break;
	}
}

/**
 * write_rc
 *
 *
 */
void write_rc ( )
{
	long rc = ir_em ( REG_SIZE - 28, 0 );

	switch ( ra ) {
		case 0:
			r0.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 1:
			r1.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 2:
			r2.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 3:
			r3.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 4:
			r4.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 5:
			r5.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 6:
			r6.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 7:
			r7.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 8:
			r8.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 9:
			r9.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 10:
			r10.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 11:
			r11.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 12:
			r12.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 13:
			r13.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 14:
			r14.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 15:
			r15.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 16:
			r16.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 17:
			r17.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 18:
			r18.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 19:
			r19.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 20:
			r20.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 21:
			r21.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 22:
			r22.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 23:
			r23.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 24:
			r24.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 25:
			r25.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 26:
			r26.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 27:
			r27.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 28:
			r28.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 29:
			r29.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 30:
			r30.latchFrom ( dbus_m.OUT ( ) );
			break;
		case 31:
			r31.latchFrom ( dbus_m.OUT ( ) );
			break;
	}
}

/**
 * memory
 * memory stage of pipeline. writes/read to/from memory. Writes to registers
 *
 */
void memory ( )
{
	long mem_type = mem_flag.value ( );

	switch ( mem_type ) {
		case 0: // doesn't use memory
			dbus_m.IN ( ).pullsFrom ( out_em ); // write to register
			write_rc ( );
			Clock::tick ( );
			Clock::tick ( );
		case 1: // read from memory
			// set up MAR for read
			addrbus_m.IN ( ).pullsFrom ( addr_em );
			data_cache.MAR ( ).latchFrom ( addrbus_m.OUT ( ) );
			Clock::tick ( );

			// read
			data_cache.read ( );

		case 2: // write to memory
			// set up MAR for write
			addrbus_m.IN ( ).pullsFrom ( addr_em );
			data_cache.MAR ( ).latchFrom ( addrbus_m.OUT ( ) );
			Clock::tick ( );

			// perform write
			data_cache.WRITE ( ).pulllFrom ( out_em );
			data_cache.WRITE ( );
			Clock::tick ( );
		default: // shouldn't happen
	}

	// PIPELINE IS DONE
	char buff [ 32 ];


	sprintf ( buff, "|pc=%02lx mf=%02lx out=%02lx addr=%04lx        |\n",
	          pc_em.value ( ),
	          out_em.value ( ),
	          addr_em.value ( ) );
	cout << buff;
} // memory

// $(filename) end
