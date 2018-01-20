/* Samples for Explorer 16 Development Board of Microchip

   Copyright (C) 2018  Robert Buj <rbuj@fedoraproject.org>

   This file is part of explorer16 - https://github.com/rbuj/explorer16

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef LED_H
#define LED_H

#include <xc.h>
#include <stdbool.h> /* Includes true/false definition */

#define LED_D3_LAT LATAbits.LATA0
#define LED_D4_LAT LATAbits.LATA1
#define LED_D5_LAT LATAbits.LATA2
#define LED_D6_LAT LATAbits.LATA3
#define LED_D7_LAT LATAbits.LATA4
#define LED_D8_LAT LATAbits.LATA5
#define LED_D9_LAT LATAbits.LATA6
#define LED_D10_LAT LATAbits.LATA7 /* Overlaps with S5 */

#define LED_D3_TRIS TRISAbits.TRISA0
#define LED_D4_TRIS TRISAbits.TRISA1
#define LED_D5_TRIS TRISAbits.TRISA2
#define LED_D6_TRIS TRISAbits.TRISA3
#define LED_D7_TRIS TRISAbits.TRISA4
#define LED_D8_TRIS TRISAbits.TRISA5
#define LED_D9_TRIS TRISAbits.TRISA6
#define LED_D10_TRIS TRISAbits.TRISA7 /* Overlaps with S5 */

#define INPUT 1
#define OUTPUT 0

typedef enum { LED_NONE, LED_D3, LED_D4, LED_D5, LED_D6, LED_D7, LED_D8, LED_D9, LED_D10 } LED;

void LED_Enable(LED);
void LED_OnOff(LED, bool);
void LED_Toggle(LED);
void LEDs_Enable();
void LEDs_On();
void LEDs_Off();

#endif /* LED_H */