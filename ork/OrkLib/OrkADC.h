/*************************************************************************
 *
 * OrkADC.h
 * ORKWare ADC Library 2011
 * Library for use with 2011 OSURC Robotics Kit (ORK).
 *
 * This library converts analog inputs to digital values. 
 * For documentation, see the OSURC web site. 
 *
 * Written by Cody Hyman <hymanc@onid.orst.edu>
 
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
 
 #ifndef ORKADC_H
 #define ORKADC_H
 
 #include "OrkCore.h"
 
 #define CON1 0x20
 #define CON2 0x21
 #define CON3 0x23
 #define CON4 0x05
 #define CON5 0x04
 #define CON6 0x01
 #define CON7 0x00
 
 #define ADC0 0x00
 #define ADC1 0x01
 #define ADC4 0x04
 #define ADC5 0x05
 #define ADC6 0x06
 #define ADC7 0x07
 #define ADC8 0x20
 #define ADC9 0x21
 #define ADC10 0x22
 #define ADC11 0x23
 #define ADC12 0x24
 #define ADC13 0x25
 
 /**
 * Initializes the onboard analog-to-digital converter for reads
 */
 void setupADCPin();
 
 /**
 * Reads an analog-to-digital converter input with 10-bit resolution
 * @param adcAddress Address of the ADC to read
 * @return Concatenated ADC low and high register values after read process
 */
 unsigned short readADC(unsigned char adcAddress);
 
 #endif
 