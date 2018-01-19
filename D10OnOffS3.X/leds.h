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

#ifndef LEDS_H
#define LEDS_H

#define LEDs_LAT        LATA
#define LEDs_TRIS       TRISA
#define LED_ON          1
#define LED_OFF         0

#include <xc.h>
#include <stdbool.h> /* Includes true/false definition */

typedef enum {
    LED_NONE,
    LED_D3,
    LED_D4,
    LED_D5,
    LED_D6,
    LED_D7,
    LED_D8,
    LED_D9,
    LED_D10
} LED;

void LED_Enable(LED) __attribute__ ((section (".libexplorer16")));
void LED_OnOff(LED, bool) __attribute__ ((section (".libexplorer16")));
void LED_Toggle(LED) __attribute__ ((section (".libexplorer16")));

#define LED_On(LED) LED_OnOff(LED, LED_ON);
#define LED_Off(LED) LED_OnOff(LED, LED_OFF);
#define LEDs_Enable() LEDs_TRIS &= 0xFF00 // PORTA<7:0> as outputs
#define LEDs_On() LEDs_LAT &= 0xFF00; LEDs_LAT += 0x00FF
#define LEDs_Off() LEDs_LAT &= 0xFF00
#define LEDs_Toggle() LEDs_LAT ^= 0x00FF

#endif // LEDS_H
