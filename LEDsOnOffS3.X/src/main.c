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
#include <stdbool.h> /* Includes true/false definition */
#include <stddef.h>  /* Includes the type yielded by sizeof */
#include <stdlib.h>  /* Includes EXIT_SUCCESS definition */
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

APP_DATA appData = {.messageLine1 = "Explorer 16 Demo\n\r", .messageLine2 = "S3: LEDs ON"};

/* Main Program */
int main(void) {
   /* Call the System Initialize routine */
   SYS_Initialize();

   /* Display welcome message */
   LCD_PutString(&LCD_REGs, appData.messageLine1, sizeof(appData.messageLine1) - 1);
   LCD_PutString(&LCD_REGs, appData.messageLine2, sizeof(appData.messageLine2) - 1);

   /* Infinite Loop */
   while (true) {
      while (!BUTTON_IsPressed(BUTTON_S3))
         ;
      LEDs_On();
      while (BUTTON_IsPressed(BUTTON_S3))
         ;
      LEDs_Off();
   };

   return EXIT_SUCCESS;
}