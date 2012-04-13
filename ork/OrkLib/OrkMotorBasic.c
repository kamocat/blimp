/*************************************************************************
 *
 * OrkMotorBasic.c
 * ORKWare Motor Library for Standard Motor Driver (TDA7073AT)
 * Library for use with 2011 OSURC Robotics Kit (ORK).
 *
 * This library controls the onboard TDA7073 Motor Driver.
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
 
 #include "OrkMotorBasic.h"
 
 /**
 * Function to initialize IO and timer-counters for motor driving
 */
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
	
	OCR4C = 0xFF; //Set TOP for timer-counter 4
	
	OCR1A = 0x00;
	OCR1B = 0x00;
	OCR4A = 0x00;
	OCR4D = 0x00;
	
	//Set IO Data Direction for Motor Outputs
	DDRB |= (1<<5) | (1<<6);
	DDRC |= (1<<7);
	DDRD |= (1<<7);
 }
 
 /**
 * Function to set the speed of the desired motor using differential PWM on the TDA7073AT
 * @param motorAddress Selected motor for speed setting, LeftMotor or RightMotor
 * @param speed Speed to set the motor to -128 to +127
 */
 void setMotor(unsigned char motorAddress, char speed)
 {
	unsigned char speedPlus;
	unsigned char speedMinus;
	
	if(speed>0)
	{
		speedPlus = 128+speed;
		speedMinus = 127-speed;
	}
	else if(speed<0)
	{
		speedPlus = 128+speed;
		speedMinus = 127-speed;
	}
	else
	{
		speedPlus = 255;
		speedMinus = 255;
	}
	
	if(motorAddress == LeftMotor)
	{
		OCR1A = speedMinus;
		OCR1B = speedPlus;
	} 
	else if(motorAddress == RightMotor)
	{
		OCR4A = speedMinus;
		OCR4D = speedPlus;
	}
 }
 