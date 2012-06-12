/**
 * This is code for the ORK, which uses an AtMega32U4 running at 16MHz.
 */

/** Constants */
#define F_CPU 16000000U
#define INTERRUPT_DRIVEN_UART
#define MSG_LENGTH 3

/** Includes */
#include <avr/io.h>
#include <util/delay.h>
#include "vic.h"	// enables sevo-style PWM control
#include "uart.h"

/** Global Variables */
volatile int16_t lspeed = 0;
volatile int16_t rspeed = 0;

/** Functions */

uint8_t init( void ) {
	DDRB |= 0x01;
	PORTB = 0;
	init_vic();
	init_uart();

	sei(); 	// enable interrupts

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
	if( byte_received == 254 ) {
		// Reset the counter and clear the array
		for( byte_index = 0; byte_index < MSG_LENGTH; ++byte_index ) {
			uart_rcvd[ (int) byte_index ] = 0;
		}
		byte_index = 0;
	} else if( byte_index < MSG_LENGTH ){
		// update the data
		uart_rcvd[ (int) byte_index ] = byte_received;
		++byte_index;

		// If this is the last byte, update the buffered data.
		if( byte_index == MSG_LENGTH ) {
			lspeed = (uart_rcvd[0] - 127) * 8;	// centers on 127
			rspeed = (uart_rcvd[1] - 127) * -8;	// centers on 127

			PORTB ^= 1;
			//send_string("Packet received\r\n");
		}
	}


}
/*********** End interrupt-driven UART ***********/
#endif



int main( void ) {
	init();

	while( 1 ) {
		set_vic( &OCR1A, lspeed );
		set_vic( &OCR1B, rspeed );
		set_vic( &OCR1C, lspeed );
		set_vic( &OCR3A, rspeed );
		_delay_ms(20);
	}
	return 0;
}
