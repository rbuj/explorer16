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

#include "../../include/lcd.h"

bool LCD_Initialize(LCD_REGs_st *LCD_REGs) {
    /* Initialize data pins to zero */
    LCD_WriteData(0x00);

    /* Initialize the control signal data pins */
    LCD_RWSignal_Clear();
    LCD_RSSignal_Clear();
    LCD_EnableSignal_Clear();

    /* Pin direction */
    LCD_ConfigureDataInput(); // Configure the data pins as input
    LCD_RSSignal_Output();
    LCD_RWSignal_Output();
    LCD_EnableSignal_Output();

    /* LCD: Wait for more than 30ms after VDD on */
    __delay32(LCD_STARTUP);

    LCD_SendCommand(&(LCD_REGs->BF_AC), LCD_REGs->FUNCTION_MODE.REG);
    LCD_SendCommand(&(LCD_REGs->BF_AC), LCD_REGs->DISPLAY_CURSOR_BLINK_ACT.REG);
    LCD_SendCommand(&(LCD_REGs->BF_AC), LCD_REGs->ENTRY_MODE.REG);

    LCD_ClearScreen(&(LCD_REGs->BF_AC));
    __delay32(LCD_CLEANUP);

    return true;
}