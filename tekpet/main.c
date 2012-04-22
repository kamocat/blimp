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
	init_dcmotors( 1 );
	

	/* 
	 * In this case, i is not quite an iterator.
	 * It counts up from 0 to 255 and then back down.
	 * The incrementor is used to make this happen.
	 */
	int8_t i = 0;
	int8_t inc = 1;
	uint8_t scaled = i;

	while( 1 ) {
		scaled = i + 128;
		update_servos( scaled, scaled, i );
		run_dcmotors( i, i );

		_delay_ms( 10 );

		switch( i ) {
			case 127:
				inc = -1;
				break;
			case -127:
				inc = 1;
				break;
			default:
				break;
		}
		i += inc;
	}
	return 0;
}
