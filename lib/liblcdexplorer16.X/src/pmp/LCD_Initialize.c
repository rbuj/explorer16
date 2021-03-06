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

bool LCD_Initialize(LCD_REGs_st *LCD_REGs) {
   PMCON = 0x8383;
   PMMODE = 0x030C;
   PMAEN = 0x0001;

   /* LCD: Wait for more than 30ms after VDD on */
   __delay_us(30UL);

   LCD_SendCommand(&(LCD_REGs->BF_AC), LCD_REGs->FUNCTION_MODE.REG);
   LCD_SendCommand(&(LCD_REGs->BF_AC), LCD_REGs->DISPLAY_CURSOR_BLINK_ACT.REG);
   LCD_SendCommand(&(LCD_REGs->BF_AC), LCD_REGs->ENTRY_MODE.REG);

   LCD_ClearScreen(&(LCD_REGs->BF_AC));

   return true;
}