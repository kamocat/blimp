/*************************************************************************
 *
 * OrkMotorL298.c
 * ORKWare Motor Library for the Motor Driver Upgrade (Using L298 Driver)
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
 
 #include "OrkMotorL298.h"
 
 void initializeMotorDriver()
 {
	TCCR1A = 0b10101001;
	TCCR1B = 0b00001001;
	TCCR1C = 0b00000000;
	
	TCCR4A = 0b10000010;
	TCCR4B = 0b00000001;
	TCCR4C = 0b10001001;
	TCCR4D = 0b00000000;
	TCCR4E = 0b00000000;
	
	OCR4C = 0xFF; // Set TOP value for TCCR4
	
	/*
	* Set all compare values to 0, speed is set to 0
	*/
	OCR1A = 0x00;
	OCR1B = 0x00;
	OCR4A = 0x00;
	OCR4D = 0x00;
	
	// Set output data direction
	DDRB |= (1<<5)|(1<<6);
	DDRC |= (1<<7);
	DDRD |= (1<<5)|(1<<7);
	DDRE |= (1<<6);
	
	// Enable motors
	PORTD |= (1<<5); 
	PORTE |= (1<<6);
 }
 
void setMotor(unsigned char motorAddress, char speed)
{
	speedPlus = 128+speed;
	speedMinus = 128-speeed;
	if(motorAddress == LeftMotor)
	{
		OCR4A = speedPlus;
		OCR4D = speedMinus;
	}
	else if(motorAddress == RightMotor)
	{
		OCR1A = speedPlus;
		OCR1B = speedMinus;
	}
 }
 
 void enableMotor(unsigned char motorAddress, bool enabled)
 {
	if(motorAddress == LEFT_MOTOR)
	{
		if(enabled)
		{
			PORTD |= (1<<5);//Enable Left Motor
		}
		else
		{
			PORTD &= ~(1<<5);//Disable Left Motor
		}
	}
	else if(motorAddress == RIGHT_MOTOR)
	{
		if(enabled)
		{
			PORTE |= (1<<6);//Enable Right Motor
		}
		else
		{
			PORTE &= ~(1<<6);//Disable Right Motor
		}
	
	}
 }