/* 
 * This file configures the watchdog timer
 * If the macro WD_TIMEOUT is defined, then it will configure the timeout
 * according to the time specified.
 * WD_TIMEOUT is the timeout in miliseconds, rounded up.
 */

#include <avr/wdt.h>
#include <avr/interrupt.h>

#ifndef AT90USB686_WATCHDOG
#define AT90USB686_WATCHDOG

uint8_t init_watchdog( void ) {
#ifdef WD_TIMEOUT
	uint8_t prescale = 0;
	uint16_t timeout = ((WD_TIMEOUT - 1) >> 4);
	for( ; (timeout != 0); timeout >>= 1 ) {
		++prescale;
	}

	/* 
	 * Make sure it is a valid value, even if the user entered an
	 * excessively large number.  Since bit 3 of the clock select
	 * is not in bit 3 of the byte, we have to do this a little
	 * weird.*/
	if( prescale >= 9 ) {
		prescale = 1 | (1<<WDP3);
	} else if ( prescale == 8 ) {
		prescale = 1<<WDP3;
	}

	/* Set watchdog to interrupt only, not system reset */

	wdt_reset();
	WDTCSR |= (1<<WDCE) | (1<<WDE);
	WDTCSR = (1<<WDIE) | prescale;
	// wdt_enable( WDTO_2S );

#else
	/* Disable the watchdog */
	// WDTCSR = 0b00100000;
	wdt_disable();

#endif
	return 0;
}
#endif


#ifdef DO_NOT_DEFINE
/*
 * Template for watchdog interrupt.
 * Copy this into your main.c file so it does something when the watchdog
 * timer times out. 
 * (Do not include this comment)
 */


ISR( WDT_vect ) {
	/* 
	 * The watchdog has timed out, which means wdt_reset() hasn't 
	 * been called recently, so something isn't happening as often as we 
	 * think it should (depending on where wds_reset() is called).
	 * Do something to respond to that:
	 */
#ifdef WUNDERBOARD
	PORTC = 0x0C;
	send_string("WDT ");
#else

#endif


}

#endif
