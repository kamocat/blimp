/**
 This is the code for the tekpet, which uses an AT90USB646
 Currently we are making sure the serial communication works
 */

/** Constants */
#define F_CPU 1000000U

/** Includes */
#include <avr/io.h>
#include <util/delay.h>
#include "vic.h"	// enables sevo-style PWM control

/** Global Variables */

/** Functions */

uint8_t init( void ) {
	init_vic();



	return 0;
}


int main( void ) {
	int16_t lspeed = 1000;
	int16_t rspeed = -1000;

	while( 1 ) {
		set_motor( &OCR1A, lspeed );
		set_motor( &OCR1B, rspeed );
		set_motor( &OCR1C, lspeed );
		set_motor( &OCR3A, rspeed );
		_delay_ms(100);
	}
	return 0;
}
