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

#ifndef LCD_REGS_H
#define LCD_REGS_H

#include <xc.h>
#include <stdint.h> /* Includes uint16_t definition */

/* ENTRY_MODE */

typedef struct {
   unsigned S : 1;  /* S = 1 : Display Shift On. S = 0 : Display Shift Off. */
   unsigned ID : 1; /* ID = 1 : Increment. ID = 0 : Decrement. */
   unsigned : 6;
} ENTRY_MODEbits_st;

typedef union {
   unsigned char     REG;
   ENTRY_MODEbits_st ENTRY_MODEbits;
} ENTRY_MODE_u;

/* DISPLAY_CURSOR_BLINK_ACT */

typedef struct {
   unsigned B : 1; /* Blink. B = 1 : Cursor Blink On. Blink. B = 0 : Cursor Blink
                Off. */
   unsigned C : 1; /* Cursor. C = 1 : Cursor Display On. C = 0 : Cursor Display
                     Off. */
   unsigned D : 1; /* Display. D = 1 : Display On. D = 1 : Display Off. */
   unsigned : 5;
} DISPLAY_CURSOR_BLINK_ACTbits_st;

typedef union {
   unsigned char                   REG;
   DISPLAY_CURSOR_BLINK_ACTbits_st DISPLAY_CURSOR_BLINK_ACTbits;
} DISPLAY_CURSOR_BLINK_ACT_u;

/* SHIFT_DISPLAY_MOVE_CURSOR */

typedef struct {
   unsigned : 2;
   unsigned RL : 1; /* RL = 1 : Shift Right. RL = 0 : Shift Left. */
   unsigned SC : 1; /* SC = 1 : Shift Display. S/C = 0 : Move Cursor. */
   unsigned : 4;
} SHIFT_DISPLAY_MOVE_CURSORbits_st;

typedef union {
   unsigned char                    REG;
   SHIFT_DISPLAY_MOVE_CURSORbits_st SHIFT_DISPLAY_MOVE_CURSORbits;
} SHIFT_DISPLAY_MOVE_CURSOR_u;

/* FUNCTION_MODE */

typedef struct {
   unsigned : 2;
   unsigned F : 1;  /* character font. F = 1 : 5x10 dots. F = 0 : 5X8 dots. */
   unsigned N : 1;  /* Number of display line. N = 1 : DualLine. N =0 :
                      SignalLine. */
   unsigned DL : 1; /* Data Length. DL = 1 : 8-Bit. DL = 0 : 4-Bit. */
   unsigned : 3;
} FUNCTION_MODEbits_st;

typedef union {
   unsigned char        REG;
   FUNCTION_MODEbits_st FUNCTION_MODEbits;
} FUNCTION_MODE_u;

/* RAM_ADDR */

typedef struct {
   unsigned ADDR : 6;
   unsigned : 2;
} RAM_ADDRbits_st;

typedef union {
   unsigned char   REG;
   RAM_ADDRbits_st RAM_ADDRbits;
} RAM_ADDR_u;

/* SET_DD_RAM_ADDR */

typedef struct {
   unsigned COL : 4;
   unsigned BLK : 2;
   unsigned ROW : 1;
   unsigned : 1;
} DD_RAM_ADDRbits_st;

typedef struct {
   unsigned OFFSET : 6;
   unsigned : 2;
} DD_RAM_ADDR_OFFSETbits_st;

typedef struct {
   unsigned ADDR : 7;
   unsigned : 1;
} DD_RAM_ADDR_ADDRRESSbits_st;

typedef union {
   unsigned char               REG;
   DD_RAM_ADDRbits_st          DD_RAM_ADDRbits;
   DD_RAM_ADDR_OFFSETbits_st   DD_RAM_ADDR_OFFSETbits;
   DD_RAM_ADDR_ADDRRESSbits_st DD_RAM_ADDR_ADDRRESSbits;
} DD_RAM_ADDR_u;

/* BF_AC */

typedef struct {
   unsigned AC : 7;
   unsigned BF : 1;
} BF_ACbits_st;

typedef union {
   unsigned char REG;
   BF_ACbits_st  BF_ACbits;
} BF_AC_u;

typedef struct {
   ENTRY_MODE_u                ENTRY_MODE;
   DISPLAY_CURSOR_BLINK_ACT_u  DISPLAY_CURSOR_BLINK_ACT;
   SHIFT_DISPLAY_MOVE_CURSOR_u SHIFT_DISPLAY_MOVE_CURSOR;
   FUNCTION_MODE_u             FUNCTION_MODE;
   RAM_ADDR_u                  RAM_ADDR;
   DD_RAM_ADDR_u               DD_RAM_ADDR;
   BF_AC_u                     BF_AC;
#ifdef LCD_CG_RAM
   unsigned short CG_RAM[64];
#endif
} LCD_REGs_st;

#endif /* LCD_REGS_H */