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

#define SERVO_CENTER 0x0580

uint8_t init_servos (void) {
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

	return 0;

}

/* 
 * This function is used for user interface stuff - it will
 * increment or decrement the servo value.  Instead of just
 * letting a rollover happen, it will detect that and set it
 * to the appropriate extreme value (max or min).
 */
int8_t inc_servo( int8_t increment, int8_t *servo ) {
	int8_t new_angle = *servo + increment;

	/* Catch overflows */
	if( (increment > 0) && (new_angle < *servo) ) {
		new_angle = 127;
	} else if( (increment < 0) && (new_angle > *servo) ) {
		new_angle = -128;
	}
	
	*servo = new_angle;
	return new_angle;
}


/*
 * This function sets an individual servo, using the pointer to the
 * address of the servo.  Here's an example:
 * set_servo( 128, &OCR1A );
 * This sets servo A to be centered.
 * There are three servos: OCR1A, OCR1B, and OCR1C.
 */
uint8_t set_servo( int8_t angle, volatile uint16_t *servo ) {
	/* 
	 * Write out the PWM, so it's between 1 and 2ms 
	 * This probably needs to be recalibrated when you switch
	 * servos, as does the servo center.  
	 * This feature could be added without too much difficulty.
	 */
	*servo = SERVO_CENTER + (int16_t)(angle) * 6;

	return 0;
}

/*
 * This function disables the servo, by stopping output to it.
 * When you use set_servo, it will start the servo again
 */
uint8_t stop_servo( uint16_t *servo ) {
	*servo = 0;
	return 0;
}


#endif
