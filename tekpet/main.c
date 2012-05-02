/**
 This is the code for the tekpet, which uses an AT90USB646
 Currently we are testing to make sure servo control works
 */

/** Includes */
#include <avr/io.h>
#include <util/delay.h>
#include "rc_servo.h"	// enables sevo control

#define INTERRUPT_DRIVEN_UART
#include "uart.h"	// for the serial communication

/** Constants */
#define F_CPU 1000000U

/** Global Variables */
int8_t lspeed;
int8_t rspeed;
uint8_t servo_angle = 127;

/** Functions */

uint8_t init( void ) {
	// start interrupts
	sei();

	return 0;
}

uint8_t inc_servo( int8_t increment, uint8_t *servo ) {
	uint8_t new_angle = *servo + increment;
	/* Catch overflows */
	if( (increment > 0) && (new_angle < *servo) ) {
		new_angle = 255;
	} else if( (increment < 0) && (new_angle > *servo) ) {
		new_angle = 0;
	}
	*servo = new_angle;
	return new_angle;
}


#ifdef INTERRUPT_DRIVEN_UART
/***************************************************
 * For interrupt handling, run sei() and paste this code into your 
 * main.c file.  The surrounding "ifdef" is neccessary because it
 * is used in the header to determine whether to enable the UART
 * RCV interrupts.  (Transmit is currently not interrupt-driven).
 */
#define MSG_LENGTH 3
uint8_t uart_rcvd[MSG_LENGTH];	// this data is live, and unsafe
uint8_t byte_index = 255;	// start off disabled

ISR( BADISR_vect ) {
	// Do nothing
}

ISR( USART1_RX_vect ) {
	byte_received = UDR1;	// copy the data before it goes away
	// Use -128 to signal a new message
	if( byte_received == -128 ) {
		// Reset the counter and clear the array
		for( byte_index = 0; byte_index < MSG_LENGTH; ++byte_index ) {
			uart_rcvd[ (int) byte_index ] = 0;
		}
		byte_index = 0;
	} else if( byte_index < MSG_LENGTH ){
		// update the data
		uart_rcvd[ (int) byte_index ] = byte_received;
		byte_index = ( byte_index + 1 );

		// If this is the last byte, update the buffered data.
		if( byte_index == MSG_LENGTH ) {
			lspeed = byte_rcvd[0];
			rspeed = byte_rcvd[1];
			inc_servo( byte_rcvd[2], *servo_angle );
			
			/* Reset the watchdog */
		}
	}


}
/*********** End interrupt-driven UART ***********/
#endif


int main( void ) {
	init();
	init_servos();

	while( 1 ) {
		/* Motor control not merged yet */
		set_servoA( servo_angle );
		_delay_ms( 10 );
	}
	return 0;
}
