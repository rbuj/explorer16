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

#include "lcd_no_pmp_8bit.h"

inline void LCD_SendCommand(BF_AC_u *BF_AC, char command) {
   LCD_RWSignal_Clear(); /* select write operation */
   LCD_RSSignal_Clear(); /* select instruction register */
   LCD_ConfigureDataOutput();
   LCD_EnableSignal_Set();
   LCD_WriteData(command);
   __delay_us(4);
   LCD_EnableSignal_Clear();
   __delay_us(4);

   /* Receive BF & AC */
   do {
      LCD_ConfigureDataInput();
      LCD_RSSignal_Clear(); /* select BF/AC register */
      LCD_RWSignal_Set();   /* select read operation */
      LCD_EnableSignal_Set();
      __delay_us(4);
      BF_AC->REG = LCD_DATA_PORT & 0x00FF;
      LCD_EnableSignal_Clear();
      __delay_us(4);
   } while (BF_AC->BF_ACbits.BF);
}
