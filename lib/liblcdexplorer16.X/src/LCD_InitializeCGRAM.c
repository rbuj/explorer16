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

void LCD_InitializeCGRAM(LCD_REGs_st *LCD_REGs) {
   /* Backup software register for DD RAM: used in LCD_PutChar '\n', '\r' */
   uint8_t ac_dd = LCD_REGs->BF_AC.BF_ACbits.AC;

   uint8_t i;

   LCD_SetCGRAMAddress(LCD_REGs, 0x00);
   for (i = 0; i < 64; i++) {
      LCD_SendData(&(LCD_REGs->BF_AC), LCD_REGs->CG_RAM[i]);
   }

   /* Restore DD RAM Address from backup */
   LCD_SetDDRAMAddress(LCD_REGs, ac_dd);
}