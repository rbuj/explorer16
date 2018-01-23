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

#include "lcd.h"

inline char LCD_ReceiveBusyAC() {
   char dummy;
   LCD_ConfigureDataInput();
   LCD_RWSignal_Set();   /* select read operation */
   LCD_RSSignal_Clear(); /* select BF/AC register */
   delay_gt70ns();       /* Delay must be greater than Min. RS, R/W Address Setup Time (60us) + Hold Time (10us) */
   LCD_EnableSignal_Set();
   delay_gt300ns();
   LCD_EnableSignal_Clear();
   delay_gt200ns();
   delay_gt1000ns();
   dummy = LCD_DATA_PORT & 0x00FF;
   return dummy;
}