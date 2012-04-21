/**
 This is the code for the tekpet, which uses an AT90USB646
 Currently we are testing to make sure servo control works
 */

/** Includes */
#include <avr/io.h>
#include <util/delay.h>
#include "rc_servo.h"	// enables sevo control
#include "dc_motor.h"	// enables control of DC motors

/** Constants */
#define F_CPU 1000000U

/** Global Variables */

/** Functions */

int main( void ) {
	init_servos();
	init_dcmotors( 0 );
	

	uint8_t i = 128;
	int8_t inc = 1;
	while( 1 ) {
		update_servos( i, i, i );
		//run_dcmotors( -128, 127 );
		OCR2A = i;
		OCR2B = 255;

		_delay_ms( 10 );

		switch( i ) {
			case 0:
				inc = 1;
				break;
			case 255:
				inc = -1;
				break;
			default:
				break;
		}
		i += inc;
	}
	return 0;
}
