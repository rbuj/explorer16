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

#ifndef LCD_H
#define LCD_H

#include <xc.h>
#include <stdbool.h>  /* Includes true/false definition */
#include <stdint.h>   /* Includes uint16_t definition */
#include <libpic30.h> /* Includes __delay32 */
#include "lcd_regs.h"

#define LCD_STARTUP \
   120000UL /* Start up delay = 30ms -> cycles for __delay32 \
            */

#define INCREMENT 1
#define DECREMENT 0
#define DISPLAY_SHIFT_ON 1
#define DISPLAY_SHIFT_OFF 0
#define DISPLAY_ON 1
#define DISPLAY_OFF 0
#define CURSOR_DISPLAY_ON 1
#define CURSOR_DISPLAY_OFF 0
#define CURSOR_BLINK_ON 1
#define CURSOR_BLINK_OFF 0
#define SHIFT_DISPLAY 1
#define MOVE_CURSOR 0
#define SHIFT_RIGHT 1
#define SHIFT_LEFT 0
#define EIGHT_BIT 1
#define FOUR_BIT 0
#define DUAL_LINE 1
#define SINGLE_LINE 0
#define TEN_DOTS 1
#define FIVE_DOTS 0

#define LCD_CursorMoviment_Inc(ptr) LCD_SetIncCursor_CursorMoviment(ptr, INCREMENT)
#define LCD_CursorMoviment_Dec(ptr) LCD_SetIncCursor_CursorMoviment(ptr, DECREMENT)
#define LCD_DisplayShift_On(ptr) LCD_SetEntryMode_Shift(ptr, DISPLAY_SHIFT_ON)
#define LCD_DisplayShift_Off(ptr) LCD_SetEntryMode_Shift(ptr, DISPLAY_SHIFT_OFF)
#define LCD_Display_On(ptr) LCD_DisplayCursorBlinkActivation_Display(ptr, DISPLAY_ON)
#define LCD_Display_Off(ptr) LCD_DisplayCursorBlinkActivation_Display(ptr, DISPLAY_OFF)
#define LCD_CursorDisplay_On(ptr) LCD_DisplayCursorBlinkActivation_Cursor(ptr, CURSOR_DISPLAY_ON)
#define LCD_CursorDisplay_Off(ptr) LCD_DisplayCursorBlinkActivation_Cursor(ptr, CURSOR_DISPLAY_OFF)
#define LCD_CursorBlink_On(ptr) LCD_DisplayCursorBlinkActivation_Blink(ptr, CURSOR_BLINK_ON)
#define LCD_CursorBlink_Off(ptr) LCD_DisplayCursorBlinkActivation_Blink(ptr, CURSOR_BLINK_OFF)
#define LCD_ShiftDisplay_Right(ptr) LCD_ShiftDisplayMoveCursor(ptr, SHIFT_DISPLAY, SHIFT_RIGHT)
#define LCD_ShiftDisplay_Left(ptr) LCD_ShiftDisplayMoveCursor(ptr, SHIFT_DISPLAY, SHIFT_LEFT)
#define LCD_MoveCursor_Righ(ptr) LCD_ShiftDisplayMoveCursor(ptr, MOVE_CURSOR, SHIFT_RIGHT)
#define LCD_MoveCursor_Left(ptr) LCD_ShiftDisplayMoveCursor(ptr, MOVE_CURSOR, SHIFT_LEFT)
#define LCD_FunctionMode_EightBit(ptr) LCD_SetFunctionMode_DataLenght(ptr, EIGHT_BIT)
#define LCD_FunctionMode_FourBit(ptr) LCD_SetFunctionMode_DataLenght(ptr, FOUR_BIT)
#define LCD_FunctionMode_TwoLines(ptr) LCD_SetFunctionMode_Lines(ptr, DUAL_LINE)
#define LCD_FunctionMode_OneLine(ptr) LCD_SetFunctionMode_Lines(ptr, SINGLE_LINE)
#define LCD_FunctionMode_TenBitFont(ptr) LCD_SetFunctionMode_Font(ptr, TEN_DOTS)
#define LCD_FunctionMode_EightBitFont(ptr) LCD_SetFunctionMode_Font(ptr, FIVE_DOTS)

bool LCD_Initialize(LCD_REGs_st *) __attribute__((section(".liblcdexplorer16")));
void LCD_InitializeCGRAM(LCD_REGs_st *) __attribute__((section(".liblcdexplorer16")));
void LCD_ClearScreen(BF_AC_u *) __attribute__((section(".liblcdexplorer16")));
void LCD_ReturnHome(BF_AC_u *) __attribute__((section(".liblcdexplorer16")));
void LCD_PutString(LCD_REGs_st *, char *, uint16_t) __attribute__((section(".liblcdexplorer16")));
void LCD_PutChar(LCD_REGs_st *, char) __attribute__((section(".liblcdexplorer16")));

void LCD_ShiftDisplayMoveCursor(LCD_REGs_st *, bool, bool) __attribute__((section(".liblcdexplorer16")));
void LCD_SetEntryMode_CursorMoviment(LCD_REGs_st *, bool) __attribute__((section(".liblcdexplorer16")));
void LCD_SetEntryMode_Shift(LCD_REGs_st *, bool) __attribute__((section(".liblcdexplorer16")));
void LCD_DisplayCursorBlinkActivation(LCD_REGs_st *, bool, bool, bool) __attribute__((section(".liblcdexplorer16")));
void LCD_DisplayCursorBlinkActivation_Display(LCD_REGs_st *, bool) __attribute__((section(".liblcdexplorer16")));
void LCD_DisplayCursorBlinkActivation_Cursor(LCD_REGs_st *, bool) __attribute__((section(".liblcdexplorer16")));
void LCD_DisplayCursorBlinkActivation_Blink(LCD_REGs_st *, bool) __attribute__((section(".liblcdexplorer16")));
void LCD_SetFunctionMode(LCD_REGs_st *, bool, bool, bool) __attribute__((section(".liblcdexplorer16")));
void LCD_SetFunctionMode_DataLenght(LCD_REGs_st *, bool) __attribute__((section(".liblcdexplorer16")));
void LCD_SetFunctionMode_Lines(LCD_REGs_st *, bool) __attribute__((section(".liblcdexplorer16")));
void LCD_SetFunctionMode_Font(LCD_REGs_st *, bool) __attribute__((section(".liblcdexplorer16")));

#ifdef LCD_CG_RAM
void LCD_SetDDRAMAdrress(LCD_REGs_st *, unsigned char) __attribute__((section(".liblcdexplorer16")));
#endif
#endif /* LCD_H */