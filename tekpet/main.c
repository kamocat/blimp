/**
 This is the code for the tekpet, which uses an AT90USB646
 Currently we are testing to make sure servo control works
 */

/** Includes */
#include <avr/io.h>
#include <util/delay.h>
#include "rc_servo.h"	// enables sevo control

/** Constants */
#define F_CPU 1000000U

/** Global Variables */

/** Functions */

int main( void ) {
	init_servos();
	

	char i = 0;
	while( 1 ) {
		update_servos( i, 2i, -i );
		_delay_ms( 10 );
		++i;
	}
	return 0;
}
