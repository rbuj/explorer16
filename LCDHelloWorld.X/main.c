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
#define Fosc 8000000ULL /* Primary oscillator frequency 8 MHz (external) */
#define FCY Fosc/2 /* Required for __delay_ms(value) */

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include <xc.h>
#include <stdint.h> /* Includes int8_t definition */
#include <stdlib.h> /* Includes EXIT_SUCCESS definition */
#include <stddef.h> /* Includes the type yielded by sizeof */
#include <string.h> /* Includes strlen definition */
#include <stdbool.h> /* Includes true/false definition */
#include <libpic30.h> /* Includes __delay_ms */
#include "app.h"

void SYS_Initialize(void);

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/
APP_DATA appData = {
    .messageLine1 = "Explorer 16 Demo\n\r",
    .messageLine2 = "An example of printing on a LCD"
};

/******************************************************************************/
/* Main Program                                                               */

/******************************************************************************/
int main(void) {
    int8_t i;
    int8_t size_msg;

    /* Call the System Initialize routine */
    SYS_Initialize();

    /* Infinite Loop */
    while (true) {
        /* Display welcome message */
        LCD_PutString(appData.messageLine1, sizeof (appData.messageLine1) - 1);
        __delay_ms(2000);

        for (i = 0; i < 4; i++) {
            LCD_Display_Off();
            __delay_ms(500);
            LCD_Display_On();
            __delay_ms(500);
        }

        size_msg = strlen(appData.messageLine2);
        LCD_CursorBlink_On();
        for (i = 0; i < size_msg; i++) {
            LCD_PutChar(appData.messageLine2[i]);
            if (i >= LCD_MAX_COLUMN - 1) {
                LCD_ShiftDisplay_Left();
            }
            __delay_ms(500);
        }
        __delay_ms(2000);
        LCD_CursorBlink_Off();

        LCD_ReturnHome();
        __delay_ms(3000);
        for (i = 0; i < LCD_MAX_COLUMN; i++) {
            LCD_ShiftDisplay_Right();
            __delay_ms(500);
        }

        LCD_ClearScreen();
        __delay_ms(1000);
    };

    return EXIT_SUCCESS;
}
