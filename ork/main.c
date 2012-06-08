/**
 * This is code for the ORK, which uses an AtMega32U4 running at 16MHz.
 * Currently we are testing the communication to the Victor 884 motor
 * controllers to make sure it will work for our project.
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
		set_vic( &OCR1A, lspeed );
		set_vic( &OCR1B, rspeed );
		set_vic( &OCR1C, lspeed );
		set_vic( &OCR3A, rspeed );
		_delay_ms(100);
	}
	return 0;
}
