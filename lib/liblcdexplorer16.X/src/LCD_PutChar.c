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

void LCD_PutChar(LCD_REGs_st *LCD_REGs, char inputCharacter) {
   switch (inputCharacter) {
      case '\r':
         if (LCD_REGs->BF_AC.BF_ACbits.AC >= 40) {
            LCD_REGs->DD_RAM_ADDR.DD_RAM_ADDR_OFFSETbits.OFFSET = 0;
         } else {
            LCD_REGs->DD_RAM_ADDR.DD_RAM_ADDR_OFFSETbits.OFFSET = 40;
         }
         LCD_SendCommand(&(LCD_REGs->BF_AC), LCD_REGs->DD_RAM_ADDR.REG);
         /* Check Address Counter */
         while (LCD_REGs->BF_AC.BF_ACbits.AC != LCD_REGs->DD_RAM_ADDR.DD_RAM_ADDR_ADDRRESSbits.ADDR) {
            LCD_REGs->BF_AC.REG = LCD_ReceiveBusyAC();
         };
         break;
      case '\n':
         LCD_REGs->DD_RAM_ADDR.DD_RAM_ADDR_ADDRRESSbits.ADDR = LCD_REGs->BF_AC.BF_ACbits.AC;
         LCD_REGs->DD_RAM_ADDR.DD_RAM_ADDRbits.ROW ^= 1;
         LCD_SendCommand(&(LCD_REGs->BF_AC), LCD_REGs->DD_RAM_ADDR.REG);
         /* Check Address Counter */
         while (LCD_REGs->BF_AC.BF_ACbits.AC != LCD_REGs->DD_RAM_ADDR.DD_RAM_ADDR_ADDRRESSbits.ADDR) {
            LCD_REGs->BF_AC.REG = LCD_ReceiveBusyAC();
         };
         break;
      case '\b':
         LCD_MoveCursor_Left(LCD_REGs);
         LCD_PutChar(LCD_REGs, ' ');
         LCD_MoveCursor_Left(LCD_REGs);
         break;
      default:
         LCD_SendData(&(LCD_REGs->BF_AC), inputCharacter);
         break;
   }
}