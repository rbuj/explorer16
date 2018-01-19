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

#include "../../../include/pmp_lcd.h"

void LCD_SetFunctionMode_DataLenght(LCD_REGs_st *LCD_REGs, bool eightBitsDataLenght) {
    LCD_REGs->FUNCTION_MODE.FUNCTION_MODEbits.DL = eightBitsDataLenght;
    LCD_SendCommand(&(LCD_REGs->BF_AC), LCD_REGs->FUNCTION_MODE.REG);
}