/*
 * This header allows communication over serial (at least, one way)
 */
#include <string.h>	// for string manipulation functions
#include <stdio.h>	// for sprintf
#include <avr/io.h>	// for register macros

#ifdef INTERRUPT_DRIVEN_UART
#include <avr/interrupt.h> // allows interrupts to be used

#ifndef MSG_LENGTH
#define MSG_LENGTH 8
#endif

uint8_t byte_received;	// data copied from the UART data register
uint8_t uart_rcvd[MSG_LENGTH];	// this data is live, and unsafe
uint8_t byte_index = 255;	// start off disabled
uint8_t buffered_rcv[MSG_LENGTH];	// this data is only updated after vefiricaton
#endif






#ifdef PASTE_ME
/* This is just to keep the code from being included twice.
 * Don't include the PASTE_ME define, or the second "endif".
 */

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
	if( byte_received == ' ' ) {
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
			inc_servo( (uart_rcvd[2] - 2),	// centers on 2
					&servo_angle );	
			
			// Reset the watchdog
			// wdt_reset();
		}
	}


}
/*********** End interrupt-driven UART ***********/
#endif

#endif


#ifndef HORNM_SERIAL_DEBUG
#define HORNM_SERIAL_DEBUG

/** This function needs to setup the variables used by the UART to enable the UART and tramsmit at 9600bps. This 
function should always return 0. Remember, by defualt the Wunderboard runs at 1mHz for its system clock.*/
unsigned char init_uart( void ) {

	/* Set baud rate to 9600 */
	UBRR1H = 0;
	UBRR1L = 207;
	/* Set the U2X1 bit to get more reliable transmission at 9600 */
	UCSR1A = 0b00000010;
	/* Enable receiver and transmitter */
	UCSR1B = 0b00011000;
	/* Set frame format: 8data, 1stop bit */
	UCSR1C = 0b00000110;


#ifdef INTERRUPT_DRIVEN_UART
	UCSR1B |= 0x80;	// enable the receive interrupt
#endif
	return 0;

}

/** This function needs to write a single byte to the UART. It must check that the UART is ready for a new byte 
and return a 1 if the byte was not sent. 
@param [in] data This is the data byte to be sent.
@return The function returns a 1 or error and 0 on successful completion.*/

char send_byte(unsigned char data){
	signed char error = 1;

	if( UCSR1A & 0b00100000 ) {
		// ready to send new byte
		UDR1 = data;
		error = 0;
	}
	return error;

}

/* This function receives a single byte from UART.
 * Be careful, as the the byte can be overwritten if this isn't checked
 * often enough.
 * If no byte is received, this returns 0.
 */
char get_byte( void ) {
#ifdef INTERRUPT_DRIVEN_UART
	char received = byte_received;
	byte_received = 0;
#else
	char received = 0;
	if( UCSR1A & 1<<RXC1) {
		received = UDR1;
	}
#endif
	return received;
}


/** This function needs to writes a string to the UART. It must check that the UART is ready for a new byte and 
return a 1 if the string was not sent. 
@param [in] data This is a pointer to the data to be sent.
@return The function returns a 1 or error and 0 on successful completion.*/

char send_string(char *data ){
	uint8_t length = strlen( data );
	/* First check if the comm port is ready */
	char error = 0;
	if( length > 0 ) {
		error = send_byte( data[0] );
		if( !error ) {
			//PORTC = data[0];
			for( char i = 1; i < length; ++i ) {
				/* Wait until send is done */
				while( !(UCSR1A & 0b00100000) );
				
				/* Now we can send the data */
				UDR1 = data[ (int)i ];
			}
		}
	} else {
		error = 1;
	}
	return error;
}

#endif
