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
/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include <xc.h>
#include <stdio.h>  /* Includes EXIT_SUCCESS definition */
#include <stdlib.h> /* Includes EXIT_SUCCESS definition */
#include <stddef.h> /* Includes the type yielded by sizeof */
#include <stdbool.h> /* Includes true/false definition */

#include "app.h"

void SYS_Initialize(void);

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/
APP_DATA appData = {
    .messageLine1 = "00:00:00\n\r",
    .messageLine2 = "S3 start/reset\n\r",
};

/******************************************************************************/
/* Main Program                                                               */

/******************************************************************************/
int main(void) {
    /* Call the System Initialize routine*/
    SYS_Initialize();

    /* Display welcome message */
    LCD_PutString(appData.messageLine1, sizeof (appData.messageLine1) - 1);
    LCD_PutString(appData.messageLine2, sizeof (appData.messageLine2) - 1);

    /* Change notification for S3 */
    BUTTON_CN_Configuration(BUTTON_S3);

    /* Initialize Timer */
    TIMER_Configuration();

    /* Infinite Loop */
    while (true) {
        if (appData.lcd_clear_flag) {
            /* Reset software flag */
            appData.lcd_clear_flag = 0;
            /* Reset software variables */
            appData.hours = 0;
            appData.seconds = 0;
            appData.minutes = 0;
            /* Clear LCD & show initial message */
            LCD_ClearScreen();
            sprintf(appData.messageLine1, "00:00:00\n\r");
            LCD_PutString(appData.messageLine1, sizeof (appData.messageLine1) - 1);
            LCD_PutString(appData.messageLine2, sizeof (appData.messageLine2) - 1);
        }
        if (appData.lcd_update_flag) {
            /* Reset software flag */
            appData.lcd_update_flag = 0;
            /* Refresh clock in LCD */
            LCD_SetCol(0x00);
            sprintf(appData.messageLine1, "%02u:%02u:%02u", appData.hours, appData.minutes, appData.seconds);
            LCD_PutString(appData.messageLine1, sizeof (appData.messageLine1) - 1);
        }
        Sleep();
    };

    return EXIT_SUCCESS;
}