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

#define LCD_COMMAND_CLEAR_SCREEN 0x01
#define LCD_COMMAND_RETURN_HOME 0x02

#define LCD_DATA_LAT LATE
#define LCD_DATA_TRIS TRISE
#define LCD_DATA_PORT PORTE
#define LCD_RSSignal_Set() LATBbits.LATB15 = 1 /* set Register Select bit */
#define LCD_RSSignal_Clear() \
   LATBbits.LATB15 = 0                              /* clear Register Select bit \
                                                     */
#define LCD_RWSignal_Set() LATDbits.LATD5 = 1       /* set Read/Write bit */
#define LCD_RWSignal_Clear() LATDbits.LATD5 = 0     /* clear Read/Write bit */
#define LCD_EnableSignal_Set() LATDbits.LATD4 = 1   /* set Enable bit */
#define LCD_EnableSignal_Clear() LATDbits.LATD4 = 0 /* clear Enable bit */
#define LCD_RSSignal_Input() \
   TRISBbits.TRISB15 = 1                               /* set Register Select bit \
                                                        */
#define LCD_RSSignal_Output() TRISBbits.TRISB15 = 0    /* clear Register Select bit */
#define LCD_RWSignal_Input() TRISDbits.TRISD5 = 1      /* set Read/Write bit */
#define LCD_RWSignal_Output() TRISDbits.TRISD5 = 0     /* clear Read/Write bit */
#define LCD_EnableSignal_Input() TRISDbits.TRISD4 = 1  /* set Enable bit */
#define LCD_EnableSignal_Output() TRISDbits.TRISD4 = 0 /* clear Enable bit */
/* Configure PORTE<7:0> as outputs/ inputs.
 * One instruction cycle is required between a port direction change.  */
#define LCD_WriteData(d)   \
   LCD_DATA_LAT &= 0xFF00; \
   LCD_DATA_LAT |= d
#define LCD_ConfigureDataOutput() \
   LCD_DATA_TRIS &= 0xFF00;       \
   Nop()
#define LCD_ConfigureDataInput() \
   LCD_DATA_TRIS |= 0x00FF;      \
   Nop()

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

bool LCD_Initialize(LCD_REGs_st *);
void LCD_ClearScreen(BF_AC_u *);
void LCD_ReturnHome(BF_AC_u *);
void LCD_PutString(LCD_REGs_st *, char *, uint16_t);
void LCD_PutChar(LCD_REGs_st *, char);

void LCD_ShiftDisplayMoveCursor(LCD_REGs_st *, bool, bool);
void LCD_SetEntryMode_CursorMoviment(LCD_REGs_st *, bool);
void LCD_SetEntryMode_Shift(LCD_REGs_st *, bool);
void LCD_DisplayCursorBlinkActivation(LCD_REGs_st *, bool, bool, bool);
void LCD_DisplayCursorBlinkActivation_Display(LCD_REGs_st *, bool);
void LCD_DisplayCursorBlinkActivation_Cursor(LCD_REGs_st *, bool);
void LCD_DisplayCursorBlinkActivation_Blink(LCD_REGs_st *, bool);
void LCD_SetFunctionMode(LCD_REGs_st *, bool, bool, bool);
void LCD_SetFunctionMode_DataLenght(LCD_REGs_st *, bool);
void LCD_SetFunctionMode_Lines(LCD_REGs_st *, bool);
void LCD_SetFunctionMode_Font(LCD_REGs_st *, bool);
void LCD_SetDDRAMAdrress(LCD_REGs_st *, unsigned char);

inline void LCD_SendData(BF_AC_u *, char);
inline void LCD_SendCommand(BF_AC_u *, char);

#endif /* LCD_H */