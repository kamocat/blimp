/*
 * This header file is to implement RC servo style Pulse Period Modulation 
 * control on the ATmega32U4.  The interrupt vector is in a define so it 
 * can just bepasted into the main file, with no issues.
 *
 * Created by Marshal Horn
 */

/* 
 * I think the register names are defined by the avr compiler,
 * so all we have to worry about are the interrupts
 */
#include <avr/interrupt.h>


#ifndef ATMEGA32U4_PPM
#define ATMEGA32U4_PPM

void setup_ppm( void ) {
	/* Fast PWM.  Set A and B on match; clear on overflow */
	TCCR0A = 0b11110011;

	/* stop and reset the counter */
	TCCR0B = 0;
	TCNT0 = 0;

	/* Enable counter overflow interrupt ( TIMER0_OVF_vect ) */
	TIMSK0 = 0b001;

	sei();	// enable interrupts
}


void update_ppm( char a, char b ) {
	/* Will add scaling later - just send straight through for now */
	OCR0A = a; // update a
	OCR0B = b; // update b

	/* 
	 * Start timer, using 1/256 as a prescaler.
	 * This gives a pulse period between 0 and 4ms
	 */
	TCCR0B = 0b00000100;
}


/* START OF INTERRUPT DEFINE */
#define PPM_INT ISR ( TIMER0_OVF_vect ) { \
	/* \
	 * Stop the timer \
	 * (It will be started when the ppm is updated again) \
	 */ \
	TCCR0B = 0; \
}
/* END OF INTERRUPT DEFINE */


#endif


