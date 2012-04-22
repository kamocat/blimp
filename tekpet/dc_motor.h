/*
 * This file contains the functions to interface to the DC motor
 * controller on the TekPet.
 * It uses Timer/Counter 2 to modulate the speed.
 */


/* 
 * IO Description:
 * Enable2		PB4
 * Enable1		PD1
 * Direction2	PC0
 * Direction1	PC1
 * Mode2		PC2
 * Mode1		PC3
 *
 */

#include <avr/io.h>

#ifndef TEKPET_DC_MOTOR_CONTROL
#define TEKPET_DC_MOTOR_CONTROL

void init_dcmotors( char mode ) {

	/* Make sure the timer isn't disabled for power saving */
	PRR0 &= ~(1 << PRTIM2);

	/* Set both compares in fast PWM, so ORC2n / 256 is the duty cycle */
	TCCR2A = 0b10100011;

	/* Don't prescale - we want this FAST */
	TCCR2B = 0b0001;

	/*
	 * The pins for the external clock aren't connected on the TekPet.
	 * So, we use the system clock.
	 */
	ASSR &= ~( 1<<EXCLK | 1<<AS2 );

	/* We aren't using an interrupts here */
	TIMSK2 = 0;

	/* Enable the PWM outputs (start with 0 PWM) */
	OCR2A = 0;
	OCR2B = 0;
	DDRB |= 1<<4;
	DDRD |= 1<<1;

	/* Enable the mode and direction outputs */
	DDRC |= 0b00001111;
	if( mode == 1 ) {
		// Put motor controller in slow decay mode
		PORTC |= ( 0b11 << 2 );
	} else {
		// Put motor controller in fast decay mode
		PORTC &= ~ ( 0b11 << 2 );
	}

	/* 
	 * We don't change the direction pins here because they will be
	 * changed when the speed is updated
	 */
}


/*
 * This function takes the absolute value of the speed, and increases
 * the magnitude by one bit
 */
uint8_t unsigned_speed( int8_t signed_speed ) {
	if( signed_speed == -127 ) {
		signed_speed = 127;
	} else if( signed_speed < 0 ) {
		signed_speed = -signed_speed;
	}
	return signed_speed << 1;
}


/*
 * If you can figure out a good way to not have duplicate code here,
 * please change this to be more elegant.  Thanks! -Marshal
 */
void run_dcmotors( int8_t m1, int8_t m2 ) {

	/******** Motor 2 *************/
	/* Update the speed */
	OCR2A = unsigned_speed( m1 );

	/* Update the direction */
	if( m1 < 0 ) {
		PORTC &= ~(0b01);
	} else {
		PORTC |= 0b01;
	}
	

	/*********** Motor 1 ************/
	/* Update the speed */
	OCR2B = unsigned_speed( m2 );

	/* Update the direction */
	if( m1 < 0 ) {
		PORTC &= ~(0b10);
	} else {
		PORTC |= 0b10;
	}

}

#endif
