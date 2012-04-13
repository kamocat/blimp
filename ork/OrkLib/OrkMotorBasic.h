/*************************************************************************
 *
 * OrkMotorBasic.h
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
 
 #ifndef ORK_MOTOR_H
 #define ORK_MOTOR_H
 
 #define LeftMotor 0
 #define RightMotor 1
 
 #include "OrkCore.h"
  
 void initializeMotorDriver();
 
 void setMotor(unsigned char motorAddress, char speed);
 
 #endif
 