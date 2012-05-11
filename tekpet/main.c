/**
 This is the code for the tekpet, which uses an AT90USB646
 Currently we are making sure the serial communication works
 */

/** Constants */
#define F_CPU 1000000U
#define MOTOR_DIVIDE 3	// only use 1/3 full voltage
#define INTERRUPT_DRIVEN_UART	// use interrupts for UART receive
#define MSG_LENGTH 3	// there are only 3 bytes in our message
// #define WUNDERBOARD // we are testing on the tekpet right now
#define WD_TIMEOUT 1000 // watchdog timeout after about 1 second

/** Includes */
#include "watchdog.h"
#include <avr/io.h>
#include <util/delay.h>
#include "rc_servo.h"	// enables sevo control
#include "dc_motor.h"	// enables control of DC motors
#include "uart.h"	// for the serial communication

/** Global Variables */
int8_t lspeed;
int8_t rspeed;
int8_t servo_angle;

/** Functions */

uint8_t init( void ) {
	init_watchdog();
	init_UART();

#ifdef WUNDERBOARD
	DDRB = 0b11000000;
	DDRC = 0xFF;	// LEDs are all outputs

	/* Clear display */
	PORTB = 0b11000000;
	PORTC = 0;

	PORTB = 0b01000000;	//only display red
	PORTC = 0x80;	// display SOMETHING so we know it works

	/* Let programmer know what happened */
	send_string("Device was reset\r\n");
#else
	init_servos();
	init_dcmotors( 1 );
#endif

	// start interrupts
	sei();

	return 0;
}


#ifdef INTERRUPT_DRIVEN_UART
/***************************************************
 * For interrupt handling, run sei() and paste this code into your 
 * main.c file.  The surrounding "ifdef" is neccessary because it
 * is used in the header to determine whether to enable the UART
 * RCV interrupts.  (Transmit is currently not interrupt-driven).
 */

ISR( BADISR_vect ) {
	// Do nothing
}

ISR( USART1_RX_vect ) {
	byte_received = UDR1;	// copy the data before it goes away
	// Use 255 to signal a new message
	if( byte_received == 255 ) {
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
			lspeed = uart_rcvd[0] - 127;	// centers on 127
			rspeed = uart_rcvd[1] - 127;	// centers on 127
			inc_servo( (uart_rcvd[2] - 1),	// centers on 1
					&servo_angle );	
			
			// Reset the watchdog
			wdt_reset();
		}
	}


}
/*********** End interrupt-driven UART ***********/
#endif


ISR( WDT_vect ) {
	/* 
	 * The watchdog has timed out, which means wdt_reset() hasn't 
	 * been called recently, so something isn't happening as often as we 
	 * think it should (depending on where wds_reset() is called).
	 * Do something to respond to that:
	 */
#ifdef WUNDERBOARD
	send_string("WDT ");
#else
	/*
	 * We lost communication.
	 * Since this blimp is naturally heavy, we can just shut off the
	 * motors, and it should come down.  However, if it turns out the
	 * craft doesn't sink fast enough, we can change this to actually
	 * drive the motors down.  These values won't be overwritten by
	 * anything else until a new message is received.
	 */
	servo_angle = 0;
	lspeed = 0;
	rspeed = 0;
#endif


}


int main( void ) {
	init();

	while( 1 ) {
		/* Motor control not merged yet */
		set_servo( servo_angle, &OCR1A );
		run_dcmotors( lspeed, rspeed );
		_delay_ms( 20 );	// wait long enough for the servo to update
	}
	return 0;
}
