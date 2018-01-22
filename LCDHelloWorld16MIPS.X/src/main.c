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

#include <xc.h>
#include <stdbool.h>  /* Includes true/false definition */
#include <stddef.h>   /* Includes the type yielded by sizeof */
#include <stdint.h>   /* Includes int8_t definition */
#include <stdlib.h>   /* Includes EXIT_SUCCESS definition */
#include <string.h>   /* Includes strlen definition */
#include <libpic30.h> /* Includes __delay_ms */
#include "app.h"

void SYS_Initialize(void);

/* Global Variable Declaration */
LCD_REGs_st LCD_REGs = {.ENTRY_MODE.REG = 0x04,
                        .DISPLAY_CURSOR_BLINK_ACT.REG = 0x0C,
                        .SHIFT_DISPLAY_MOVE_CURSOR.REG = 0x10,
                        .FUNCTION_MODE.REG = 0x3C,
                        .RAM_ADDR.REG = 0x40,
                        .DD_RAM_ADDR.REG = 0x80,
                        .BF_AC.REG = 0x00};

APP_DATA appData = {.messageLine1 = "Explorer 16 Demo\n\r", .messageLine2 = "An example of printing on a LCD"};

/* Main Program */
int main(void) {
   int8_t i;
   int8_t size_msg;

   /* Call the System Initialize routine */
   SYS_Initialize();

   /* Infinite Loop */
   while (true) {
      /* Display welcome message */
      LCD_PutString(&LCD_REGs, appData.messageLine1, sizeof(appData.messageLine1) - 1);
      __delay_ms(2000);

      for (i = 0; i < 4; i++) {
         LCD_Display_Off(&LCD_REGs);
         __delay_ms(500);
         LCD_Display_On(&LCD_REGs);
         __delay_ms(500);
      }

      size_msg = strlen(appData.messageLine2);
      LCD_CursorBlink_On(&LCD_REGs);
      for (i = 0; i < size_msg; i++) {
         LCD_PutChar(&LCD_REGs, appData.messageLine2[i]);
         if (i >= LCD_MAX_COLUMN - 1) {
            LCD_ShiftDisplay_Left(&LCD_REGs);
         }
         __delay_ms(500);
      }
      __delay_ms(2000);
      LCD_CursorBlink_Off(&LCD_REGs);

      LCD_ReturnHome(&(LCD_REGs.BF_AC));
      __delay_ms(3000);
      for (i = 0; i < LCD_MAX_COLUMN; i++) {
         LCD_ShiftDisplay_Right(&LCD_REGs);
         __delay_ms(500);
      }

      LCD_ClearScreen(&(LCD_REGs.BF_AC));
      __delay_ms(1000);
   };

   return EXIT_SUCCESS;
}