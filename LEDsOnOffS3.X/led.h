/* Explorer 16 Examples
 * Copyright (C) 2018  Robert Buj <rbuj@fedoraproject.org>
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
 */

#ifndef LED_H
#define LED_H

#include <xc.h>

#define LEDs_LAT        LATA
#define LEDs_TRIS       TRISA

#define LEDs_Enable() LEDs_TRIS &= 0xFF00 // PORTA<7:0> as outputs
#define LEDs_On() LEDs_LAT &= 0xFF00; LEDs_LAT += 0x00FF
#define LEDs_Off() LEDs_LAT &= 0xFF00
#define LEDs_Toggle() LEDs_LAT ^= 0x00FF

#endif // LED_H
