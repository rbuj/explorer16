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
#ifndef PRINT_LCD_H
#define PRINT_LCD_H

#include <stdbool.h>
#include <lcd.h>

typedef enum {
    PRINT_CONFIGURATION_LCD
} PRINT_CONFIGURATION;

bool PRINT_SetConfiguration(PRINT_CONFIGURATION configuration);
#define PRINT_SetConfiguration(configuration) LCD_Initialize()

void PRINT_String(char* string, uint16_t length);
#define PRINT_String(string, length) LCD_PutString(string, length)

void PRINT_Char(char charToPrint);
#define PRINT_Char(charToPrint) LCD_PutChar(charToPrint)

void PRINT_ClearScreen(void);
#define PRINT_ClearScreen() LCD_ClearScreen()

#endif // PRINT_LCD_H
