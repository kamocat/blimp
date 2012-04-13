/*************************************************************************
 *
 * OrkADC.c
 * ORKWare ADC Library 2011
 * Library for use with 2011 OSURC Robotics Kit (ORK).
 *
 * This library converts analog inputs to digital values. 
 * For documentation, see the OSURC web site. 
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
 * Updated 10/7/2011
 *************************************************************************/
 
 void setupADCPin(unsigned char addr)
 {
	/*
	* Configure ADC Registers
	*/
	ADCSRA |= (1<<ADEN);
	ADMUX |= (1<<REFS0) | (0b00001111 & addr);
	
	/*
	* Set Selected ADC Pin to Input
	*/
	switch(addr)
	{
		case ADC0:
		{
			DDRF &= ~(1<<0);
			break;
		}
		case ADC1:
		{
			DDRF &= ~(1<<1);
			break;
		}
		case ADC4:
		{
			DDRF &= ~(1<<4);
			break;
		}
		case ADC5:
		{
			DDRF &= ~(1<<5);
			break;
		}
		case ADC6:
		{
			DDRF &= ~(1<<6);
			break;
		}
		case ADC7:
		{
			DDRF &= ~(1<<7);
			break;
		}
		case ADC8:
		{
			DDRD &= ~(1<<4);
			break;
		}
		case ADC9:
		{
			DDRD &= ~(1<<6);
			break;
		}
		case ADC10:
		{
			DDRD &= ~(1<<7);
			break;
		}
		case ADC11:
		{
			DDRB &= ~(1<<4);
			break;
		}
		case ADC12:
		{
			DDRB &= ~(1<<5);
			break;
		}
		case ADC13:
		{
			DDRB &= ~(1<<6);
			break;
		}
		default:
			break;
	}
 }
 
 unsigned short readADC(unsigned char adcAddress)
 {
	/*
	* Select ADC Channel
	*/
	ADMUX |= (0b00001111 & addr);
	if((1<<5)& addr)
	{
		ADCSRB |= (1<<5);
	} else
	{
		ADCSRB &= ~(1<<5);
	}
	
	/*
	* Start Analog to Digital Conversion
	*/
	ADCSRA |= (1<<ADSC);
	
	/*
	* Wait for Conversion to complete
	*/
	while ((ADCSRA & (1<<ADIF))==0);	
	return (ADCL) | (ADCH<<8);
 }
 