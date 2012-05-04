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
#define WUNDERBOARD

/** Global Variables */
int8_t lspeed;
int8_t rspeed;
uint8_t servo_angle = 127;

#ifdef WUNDERBOARD
int i;
#endif

/** Functions */

uint8_t init( void ) {
#ifdef WUNDERBOARD
	DDRB = 0xC0;
	DDRC = 0xFF;
	DDRE = 0x07;
	PORTB = 0b11000000;
	PORTC = 0;
	PORTB = 0b10000000;
#endif

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

#ifdef WUNDERBOARD
uint8_t buffered_rcv[MSG_LENGTH];	// this data is buffered, and actually printed to the screen
#endif

ISR( BADISR_vect ) {
	// Do nothing
}

ISR( USART1_RX_vect ) {
	byte_received = UDR1;	// copy the data before it goes away

	// Use -128 to signal a new message
	if( byte_received == 0x80 ) {
		byte_index = 0;	// reset the counter

	} else if( byte_index < MSG_LENGTH ){
		// update the data
		uart_rcvd[ (int) byte_index ] = byte_received;
		++byte_index;

		// If this is the last byte, update the buffered data.
		if( byte_index == MSG_LENGTH ) {
			lspeed = uart_rcvd[0];
			rspeed = uart_rcvd[1];
			inc_servo( uart_rcvd[2], &servo_angle );


#ifdef WUNDERBOARD
			/* Copy to buffered data for displaying */
			cli();
			for( i = 0; i < MSG_LENGTH; ++i ) {
				buffered_rcv[ (int) i ] = uart_rcvd[ (int) i ];
			}
			sei();
#endif

			
			// Reset the watchdog 
		}
	}
}
#ifdef WUNDERBOARD
/* Update the screen */
ISR( TIMER0_COMPA_vect ) {
	/* Increment the index and display the next row */
	i = (i + 1) % MSG_LENGTH;
	PORTE = i;
	PORTC = buffered_rcv[ (int) i];
}
#endif



/*********** End interrupt-driven UART ***********/
#endif


int main( void ) {
	init();
	init_servos();
	init_UART();
#ifdef WUNDERBOARD
	/* Set up timer0 to count up to OCRA, then reset */
	TCCR0A = 0x02;

	/* 
	 * Right now bleed from column to column is a significant issue,
	 * so we slow down the update as much as possible 
	 */
	TCCR0B = 0x05;	// prescale to 1/1024
	OCR0A = 255;

	TIMSK0 = 0b010;	// interrupt on timer compare A
#endif

	

	while( 1 ) {


		/* Motor control not merged yet */
		set_servoA( servo_angle );
		_delay_ms( 10 );
	}
	return 0;
}
