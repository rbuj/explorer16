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

#include "led.h"

/**
 * Switch ON/OFF a LED.
 * @param led The led which you want to switch ON/OFF.
 * @param value If true, switch ON the led, otherwise switch it OFF.
 */
void LED_OnOff(LED led, bool value) {
   switch (led) {
      case LED_D3:
         LED_D3_LAT = value;
         break;
      case LED_D4:
         LED_D4_LAT = value;
         break;
      case LED_D5:
         LED_D5_LAT = value;
         break;
      case LED_D6:
         LED_D6_LAT = value;
         break;
      case LED_D7:
         LED_D7_LAT = value;
         break;
      case LED_D8:
         LED_D8_LAT = value;
         break;
      case LED_D9:
         LED_D9_LAT = value;
         break;
      case LED_D10:
         LED_D10_LAT = value;
         break;
      case LED_NONE:
         break;
   }
}
