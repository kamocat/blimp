
/* These are the definitions for color buffers on PORTB.
 * They aren't used by the display_row function, but they are useful
 * if you want to manually do simpler manipulations
 */
#ifndef RED
#define RED 0b01000000
#define GREEN 0b10000000
#define AMBER 0b11000000
#endif

#ifndef F_CPU
#define F_CPU 1000000UL
#endif
#include <util/delay.h>

#ifndef HORNM_LED_DISPLAY_COLUMN
#define HORNM_LED_DISPLAY_COLUMN
/*
 * This function displays a single row of LEDs.
 * If you need to use it to display multiple rows at the same time, it should
 * be placed in a loop so it can cycle through the rows quick enough that
 * the user doesn't notice the flicker.
 */
void display_row( char red, char green, char column ) {
	/* Clear both colors before changing the column */
	PORTC = 0x00;
	PORTB |= 0xc0;
	PORTE = column & 0x07;

	/*
	 * Set the red bits.
	 * Since the red is already enabled, we simply disabled the green
	 * Then we set PORTC.
	 */
	PORTB &= 0x7f;
	PORTC = red;

	/*
	 * Set the green bits.
	 * We disable the red so we don't overwrite what we just did.
	 * Then we set PORTC.
	 * Now we can enable the green without the wrong thing flashing up.
	 */
	PORTB &= 0xbf;
	PORTC = green;
	PORTB |= 0x80;

	/*
	 * Now we wait so the user has time to see the result.
	 */
	_delay_us(100);

}

#endif
