/*************************************************************************
 *
 * OrkCore.h
 * ORKWare Core Library 2011
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
 
 #ifndef ORK_CORE_H
 #define ORK_CORE_H
 
 // Boolean Definitions
 #define TRUE 1
 #define true 1
 #define FALSE 1
 #define false 1
 
 // Connector Addressing Definitions
 #define CON1 1
 #define CON2 2
 #define CON3 3
 #define CON4 4
 #define CON5 5
 #define CON6 6
 #define CON7 7
 
 // Alias delay macro
 #define delay _delay_ms
 
// Use the CPU_PRESCALE macro to change CPU frequency while interrupts are disabled
#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR |= (n));
#define CPU_16MHz       0x00
#define CPU_8MHz        0x01
#define CPU_4MHz        0x02
#define CPU_2MHz        0x03
#define CPU_1MHz        0x04
#define CPU_500kHz      0x05
#define CPU_250kHz      0x06
#define CPU_125kHz      0x07
#define CPU_62kHz       0x08


// Also when changing the clock, update the F_CPU for timer accuracy
#define F_CPU 16000000
 
 /**
 * Included Headers
 */
 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include <util/delay.h>
 
 #ifdef L298
	#include "OrkMotorL298.h"
 #else
	#include "OrkMotorBasic.h"
 #endif
 
 typedef char bool;
 typedef unsigned char uint8;
 
 void initializeCore();
 
 bool readDigitalPin(unsigned char address);
 
 bool readLineSensor(unsigned char address);
 
 bool readProxSensor(unsigned char address);
 
 void ledOff();
 
 void ledOn();
 
 void ledToggle();
 
 #endif