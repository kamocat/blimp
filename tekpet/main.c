/**
 This is the code for the tekpet, which uses an AT90USB646
 Currently we are testing to make sure servo control works
 */

/** Constants */
#define F_CPU 1000000U
#define MOTOR_DIVIDE 3

/** Includes */
#include <avr/io.h>
#include <util/delay.h>
#include "rc_servo.h"	// enables sevo control
#include "dc_motor.h"	// enables control of DC motors

/** Global Variables */

/** Functions */

int main( void ) {
	init_servos();
	init_dcmotors( 0 );
	

	int8_t i = 0;
	int8_t inc = 1;

	while( 1 ) {
		set_servo( i, &OCR1A );
		run_dcmotors( i, i );

		_delay_ms( 100 );

		switch( i ) {
			case -127:
				inc = 1;
				break;
			case 127:
				inc = -1;
				break;
			default:
				break;
		}
		i += inc;
	}
	return 0;
}
