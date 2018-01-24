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

#include "button.h"

/**
 * Set up change notification for a given button.
 * @param button The button to enable CN.
 */
bool BUTTON_CN_Configuration(BUTTON button) {
   switch (button) {
      case BUTTON_S3:
         CNEN1bits.CN15IE = 1;
         break;
      case BUTTON_S4:
         CNEN2bits.CN19IE = 1;
         break;
      case BUTTON_S5:
#if defined(__dsPIC33FJ256GP710A__)
         CNEN2bits.CN23IE = 1; /* Overlaps with D10 */
#else
         return false;
#endif
         break;
      case BUTTON_S6:
         CNEN2bits.CN16IE = 1;
         break;
      case BUTTON_DISABLED:
         return false;
   }
   IEC1bits.CNIE = 1; /* Enable CN interrupts */
   IFS1bits.CNIF = 0; /* Reset CN interrupt */
   return true;
}
