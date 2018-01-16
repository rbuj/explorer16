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
#include <stdint.h>
#include <stdbool.h>

#ifndef LCD_H
#define LCD_H

#define INCREMENT          1
#define DECREMENT          0
#define DISPLAY_SHIFT_ON   1
#define DISPLAY_SHIFT_OFF  0
#define DISPLAY_ON         1
#define DISPLAY_OFF        0
#define CURSOR_DISPLAY_ON  1
#define CURSOR_DISPLAY_OFF 0
#define CURSOR_BLINK_ON    1
#define CURSOR_BLINK_OFF   0
#define SHIFT_DISPLAY      1
#define MOVE_CURSOR        0
#define SHIFT_RIGHT        1
#define SHIFT_LEFT         0
#define EIGHT_BIT          1
#define FOUR_BIT           0
#define DUAL_LINE          1
#define SINGLE_LINE        0
#define TEN_DOTS           1
#define FIVE_DOTS          0

bool LCD_Initialize(void);
void LCD_PutString(char*, uint16_t);
void LCD_PutChar(char);

void LCD_ClearScreen(void);
void LCD_ReturnHome(void);

void LCD_SetEntryMode(bool, bool);
void LCD_SetIncCursor_CursorMoviment(bool);
void LCD_SetEntryMode_Shift(bool);
void LCD_DisplayCursorBlinkActivation(bool, bool, bool);
void LCD_DisplayCursorBlinkActivation_Display(bool);
void LCD_DisplayCursorBlinkActivation_Cursor(bool);
void LCD_DisplayCursorBlinkActivation_Blink(bool);
void LCD_SetFunctionMode(bool, bool, bool);
void LCD_SetFunctionMode_DataLenght(bool);
void LCD_SetFunctionMode_Lines(bool);
void LCD_SetFunctionMode_Font(bool);
void LCD_ShiftDisplayMoveCursor(bool, bool);
void LCD_SetDDRAMAdrress(unsigned char);
char LCD_GetChar(unsigned char);

#define LCD_CursorMoviment_Inc() LCD_SetIncCursor_CursorMoviment(INCREMENT)
#define LCD_CursorMoviment_Dec() LCD_SetIncCursor_CursorMoviment(DECREMENT)
#define LCD_DisplayShift_On() LCD_SetEntryMode_Shift(DISPLAY_SHIFT_ON)
#define LCD_DisplayShift_Off() LCD_SetEntryMode_Shift(DISPLAY_SHIFT_OFF)
#define LCD_Display_On() LCD_DisplayCursorBlinkActivation_Display(DISPLAY_ON)
#define LCD_Display_Off() LCD_DisplayCursorBlinkActivation_Display(DISPLAY_OFF)
#define LCD_CursorDisplay_On() LCD_DisplayCursorBlinkActivation_Cursor(CURSOR_DISPLAY_ON)
#define LCD_CursorDisplay_Off() LCD_DisplayCursorBlinkActivation_Cursor(CURSOR_DISPLAY_OFF)
#define LCD_CursorBlink_On() LCD_DisplayCursorBlinkActivation_Blink(CURSOR_BLINK_ON)
#define LCD_CursorBlink_Off() LCD_DisplayCursorBlinkActivation_Blink(CURSOR_BLINK_OFF)
#define LCD_ShiftDisplay_Right() LCD_ShiftDisplayMoveCursor(SHIFT_DISPLAY, SHIFT_RIGHT)
#define LCD_ShiftDisplay_Left() LCD_ShiftDisplayMoveCursor(SHIFT_DISPLAY, SHIFT_LEFT)
#define LCD_MoveCursor_Righ() LCD_ShiftDisplayMoveCursor(MOVE_CURSOR, SHIFT_RIGHT)
#define LCD_MoveCursor_Left() LCD_ShiftDisplayMoveCursor(MOVE_CURSOR, SHIFT_LEFT)
#define LCD_FunctionMode_EightBit() LCD_SetFunctionMode_DataLenght(EIGHT_BIT)
#define LCD_FunctionMode_FourBit() LCD_SetFunctionMode_DataLenght(FOUR_BIT)
#define LCD_FunctionMode_TwoLines() LCD_SetFunctionMode_Lines(DUAL_LINE)
#define LCD_FunctionMode_OneLine() LCD_SetFunctionMode_Lines(SINGLE_LINE)
#define LCD_FunctionMode_TenBitFont() LCD_SetFunctionMode_Font(TEN_DOTS)
#define LCD_FunctionMode_EightBitFont() LCD_SetFunctionMode_Font(FIVE_DOTS)

#endif // LCD_H
