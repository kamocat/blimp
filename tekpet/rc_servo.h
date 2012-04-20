/*
 * This code works, but I don't understand why.
 * The prescaler is set to one.  The servo signal
 * centers weird (I don't think it's from 1 - 2ms)
 * 
 * Anyways, it should be well commented, but if it looks weird,
 * it probably is.
 *
 * Created by Marshal Horn
 * kamocat@gmail.com
 */

#include <avr/io.h>


#ifndef TEKPET_SERVO
#define TEKPET_SERVO

#define SERVO_CENTER 0x05E0

void init_servos (void) {
	/*
	 * We are using port B here for PWM outputs on Timer/Counter1.
	 * Bits 5:7 are PWM outputs A:C, so those are the ones we enable
	 * as outputs.
	 */
	DDRB |= 0b11100000;

	/*
	 * Set PWM A:C to clear at OCR match and set at TOP
	 * Set mode to high-resolution fast-PWM
	 */
	TCCR1A = 0b10101010;

	/*
	 * Set PWM top to be ICR1
	 * Set clock to be system clock, prescaled to 1/256
	 * NOTE: somehow that was too slow??? Currently scaled 1:1
	 */
	TCCR1B = 0b00011001;

	/* Set TOP.  We want 16,000, or 16 seconds */
	ICR1 = 0x4000;


	/* Make sure the timer isn't disabled in Power Reduction Mode */
	PRR0 = 0;

}


void update_servos( uint8_t a, uint8_t b, uint8_t c ) {
	/* Use a 16 bit integer to do the 16 bit write */ 
	signed int tmp = ((int)a << 0) - 0x0080;

	/* Write out the PWM, so it's between 1 and 2ms */
	OCR1A = SERVO_CENTER + tmp;

	/* 
	 * Implement the others after we check that this works 
	 * This is a simplified version of the code above
	 */

	OCR1B = SERVO_CENTER + b - 0x80;
	OCR1C = SERVO_CENTER + c - 0x80;

}

#endif
