/**
 This is the code for the tekpet, which uses an AT90USB646
 Currently we are testing to make sure servo control works
 */

/** Includes */
#include <avr/io.h>
#include <util/delay.h>

/** Constants */
#define F_CPU 1000000U

/** Global Variables */

/** Functions */

void initialize (void) {
	/*
	 * We are using port B here for PWM outputs on Timer/Counter1.
	 * Bits 5:7 are PWM outputs A:C, so those are the ones we enable
	 * as outputs.
	 */
	DDRB = 0b11100000;

	/*
	 * Set PWM A:C to clear at OCR match and set at TOP
	 * Set mode to high-resolution fast-PWM
	 */
	TCCR1A = 0b10101010;

	/*
	 * Set PWM top to be ICR1
	 * Set clock to be system clock, prescaled to 1/256
	 */
	TCCR1B = 0b00011001;

	/* Set TOP.  We want 16,000, or 16 seconds */
	ICR1H = 0x4000;


	/* Make sure the timer isn't disabled in Power Reduction Mode */
	PRR0 = 0;

}


void update_pwm( char a, char b, char c ) {
	/* Use a 16 bit integer to do the 16 bit write */ 
	unsigned int tmp = (a << 4);

	/* Write out the PWM, so it's between 1 and 2ms */
	OCR1A = 16 + tmp;

	/* Implement the others after we check that this works */

}
	

int main( void ) {
	initialize();
	

	char i = 0;
	while( 1 ) {
		update_pwm( i, 0, 0 );
		i += 1;
		_delay_ms( 16 );
	}
	return 0;
}
