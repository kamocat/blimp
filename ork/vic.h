#ifndef ORK_VIC
#define ORK_VIC

#include <avr/io.h>
uint8_t init_vic( void ) {
	DDRB |= 0xE0;	// turn on PWM outputs
	DDRC |= 1<<6;

	TCCR1A = 0b10101010;	// fast PWM, 16 bit
	TCCR3A = 0b10000010;

	TCCR1B = 0b00011010;	// prescaler of 1/8
	TCCR3B = 0b00011010;

	ICR1 = 40000;	// update every 20 ms
	ICR3 = 40000;

	// Make sure the registers aren't disabled for sleep mode
	PRR0 &= ~(1<<PRTIM1);
	PRR0 &= ~(1<<PRTIM3);


	return 0;
}


/*
 * This set_motor function takes a range from -1000 to 1000, where
 * -1000 is full-reverse, 1000 is full-forward, and 0 is stopped.
 *  If you give it a value out of this range, it won't complain or
 *  catch the error.
 */
uint8_t set_vic( volatile uint16_t *motor, int16_t speed ) {
	// We want a range from 1 to 2 ms.  1.5ms is 3000
	*motor = speed + 3000;
	return 0;
}


#endif
