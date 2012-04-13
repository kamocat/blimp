/*************************************************************************
 *
 * OrkCore.c
 * ORKWare Core Library
 * Library for use with 2011 OSURC Robotics Kit (ORK).
 *
 * Written by Cody Hyman <hymanc@onid.orst.edu>
 *
 * Copyright (C) 2011 OSURC. Released under the GNU GPL3.
 * http://oregonstate.edu/groups/osurc/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Created 9/2/2011
 * Updated 10/9/2011
 *************************************************************************/
 
 
 #include "OrkCore.h"

/* Select desired motor library by uncommenting one of the following.
*  Comment out all unused motor libraries with //
*/

//#include "OrkMotorL298.h" 
 #include "OrkMotorBasic.h"
 
 void initializeCore()
 {
	// Initialize Clock Setting for 16.000 MHz Operation
	cli();
	CPU_PRESCALE(CPU_16MHz);
	sei();
	
	// Set Outputs
	DDRB |= (1<<0); // LED output
	
	initializeMotorDriver();
 }
 
 /*
 ** Read Digital Pin Index
 ** Index = Pin (Alias)
 ** 0= Currently Undefined
 ** 1= PD4(CON1)
 ** 2= PD6(CON2)
 ** 3= PB4(CON3)
 ** 4= PF5(CON4)
 ** 5= PF4(CON5)
 ** 6= PF0(CON6)
 ** 7= PF1(CON7)
 ** >7= Currently Undefined
 */
 
 /**
 * @param address The pin address from the numerical list
 * @return The digital value of the desired input pin
 */
 bool readDigitalPin(unsigned char address)
 {
	switch(address)
	{
		case CON1:
		{
			return (PIND & (1<<4)) != 0;
		}
		case CON2:
		{
			return (PIND & (1<<6)) != 0;
		}
		case CON3:
		{
			return (PINB & (1<<4)) != 0;
		}
		case CON4:
		{
			return (PINF & (1<<5)) != 0;
		}
		case CON5:
		{
			return (PINF & (1<<4)) != 0;
		}
		case CON6:
		{
			return (PINF & (1<<0)) != 0;
		}
		case CON7:
		{
			return (PINF & (1<<1)) != 0;
		}
		default:
		{
			break;
		}
	}
 }
 
 bool readLineSensor(unsigned char address)
 {
	return readDigitalPin(address);
 }
 
 bool readProxSensor(unsigned char address)
 {
	return readDigitalPin(address);
 }
 
 void ledOff()
 {
	PORTB &= ~(1<<0);
 }
 
 void ledOn()
 {
	PORTB |= (1<<0);
 }
 
 void ledToggle()
 {
	PORTB ^= (1<<0);
 }
 