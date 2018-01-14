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
#include <stdio.h>  /* Includes sprintf */
#include <stdlib.h> /* Includes EXIT_SUCCESS definition */
#include <stddef.h> /* Includes the type yielded by sizeof */
#include <stdbool.h> /* Includes true/false definition */

#include "app.h"

void SYS_Initialize(void);

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/
APP_DATA appData = {
    .messageLine1 = "S3 start/reset  ",
    .messageLine2 = "00:00.000",
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
            appData.seconds = 0;
            appData.minutes = 0;
            appData.microseconds = 0;
            appData.lcd_update_flag = 0;
        }
        if (appData.lcd_update_flag) {
            /* Reset software flag */
            appData.lcd_update_flag = 0;
            /* Refresh clock in LCD */
            LCD_ReturnHome();
            LCD_ReturnHome();
            sprintf(appData.messageLine2, "%02u:%02u.%03lu", appData.minutes, appData.seconds, (((unsigned long) appData.microseconds)*1000)/32);
            LCD_PutString(appData.messageLine2, sizeof (appData.messageLine2) - 1);
        }
        Sleep();
    };

    return EXIT_SUCCESS;
}