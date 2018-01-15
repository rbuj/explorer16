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
#include <xc.h>
#include <lcd.h>
#include <stdint.h> /* Includes uint8_t definition */
#include <libpic30.h> /* Includes __delay32 */

/* Private variables ************************************************/
static union {
    unsigned char CMD;

    struct {
        unsigned S : 1; // S = 1 : Display Shift On. S = 0 : Display Shift Off.
        unsigned ID : 1; // ID = 1 : Increment. ID = 0 : Decrement.
        unsigned : 6;
    };
} SET_ENTRY_MODEbits = {.CMD = 0x04};

static union {
    unsigned char CMD;

    struct {
        unsigned B : 1; // Blink. B = 1 : Cursor Blink On. Blink. B = 0 : Cursor Blink Off.
        unsigned C : 1; // Cursor. C = 1 : Cursor Display On. C = 0 : Cursor Display Off.
        unsigned D : 1; // Display. D = 1 : Display On. D = 1 : Display Off.
        unsigned : 5;
    };
} DISPLAY_CURSOR_BLINK_ACTbits = {.CMD = 0x0C};

static union {
    unsigned char CMD;

    struct {
        unsigned : 2;
        unsigned RL : 1; // RL = 1 : Shift Right. RL = 0 : Shift Left.
        unsigned SC : 1; // SC = 1 : Shift Display. S/C = 0 : Move Cursor.
        unsigned : 4;
    };
} SHIFT_DISPLAY_MOVE_CURSORbits = {.CMD = 0x10};

static union {
    unsigned char CMD;

    struct {
        unsigned : 2;
        unsigned F : 1; // character font. F = 1 : 5x10 dots. F = 0 : 5X8 dots.
        unsigned N : 1; // Number of display line. N = 1 : DualLine. N =0 : SignalLine.
        unsigned DL : 1; // Data Length. DL = 1 : 8-Bit. DL = 0 : 4-Bit.
        unsigned : 3;
    };
} SET_FUNCTION_MODEbits = {.CMD = 0x3C};

static union {
    unsigned char CMD;

    struct {
        unsigned COL : 4;
        unsigned BLK : 2;
        unsigned ROW : 1;
        unsigned : 1;
    };

    struct {
        unsigned ADDR : 7;
        unsigned : 1;
    };
} SET_DD_RAM_ADDRbits = {.CMD = 0x80};

/* Private Definitions ***********************************************/
#define LCD_F_INSTR        160UL // Fast instruction delay = 40us -> cycles for __delay32
#define LCD_S_INSTR       6560UL // Slow instruction delay = 1.64ms -> cycles for __delay32
#define LCD_STARTUP     120000UL // Start up delay = 30ms -> cycles for __delay32
#define LCD_MAX_COLUMN        16

/* LCD Instructions **************************************************/
#define LCD_COMMAND_CLEAR_SCREEN              0x01
#define LCD_COMMAND_RETURN_HOME               0x02
#define LCD_COMMAND_SET_ENTRY_MODE            SET_ENTRY_MODEbits.CMD
#define LCD_COMMAND_DISPLAY_CURSOR_BLINK_ACT  DISPLAY_CURSOR_BLINK_ACTbits.CMD
#define LCD_COMMAND_SHIFT_DISPLAY_MOVE_CURSOR SHIFT_DISPLAY_MOVE_CURSORbits.CMD
#define LCD_COMMAND_SET_DD_RAM_ADDR           SET_DD_RAM_ADDRbits.CMD
#define LCD_COMMAND_SET_FUNCTION_MODE         SET_FUNCTION_MODEbits.CMD

#define LCD_COL                               SET_DD_RAM_ADDRbits.COL
#define LCD_ROW                               SET_DD_RAM_ADDRbits.ROW
#define LCD_DD_RAM_ADDRESS                    SET_DD_RAM_ADDRbits.ADDR

/* Private Functions *************************************************/
static void LCD_ShiftCursorLeft(void);
static void LCD_ShiftCursorRight(void);

static inline void LCD_SendData(unsigned char data) {
    PMADDR = 0x0001;
    PMDIN1 = data;
    __delay32(LCD_F_INSTR);
}

static inline void LCD_SendCommand(unsigned char command, unsigned long delay) {
    PMADDR = 0x0000;
    PMDIN1 = command;
    __delay32(delay);
}

bool LCD_Initialize(void) {
    /*
     * PMMODE
     * 
     * BUSY:   Port is not busy
     * IRQM:   No Interrupt generated
     * INCM:   No increment or decrement of address
     * MODE16: 8-bit mode: a read or write to the data register invokes a single 8-bit transfer
     * MODE:   Master mode 1 (PMCSx, PMRD/PMWR, PMENB, PMA<x:0>, PMD<7:0>, PMD<8:15>)
     * WAITB:  Data Setup to Read/Write Strobe Wait States bits = 1 Tpb (1/FCY = 250ns)
     * WAITM:  Data Read/Write Strobe Wait States bits = 2 Tpb (2/FCY = 500ns)
     * WAITE:  Data Hold After Read/Write Strobe Wait States bits = 1 Tpb (1/FCY = 250ns)
     */
    PMMODE = 0x0340;
    // Enable PMP Module, No Address & Data Muxing,
    // Enable RdWr Port, Enable Enb Port, No Chip Select,
    // Select RdWr and Enb signals Active High
    PMCON = 0x8383;
    // Enable A0
    PMAEN = 0x0001;

    /* LCD: Wait for more than 30ms after VDD on */
    __delay32(LCD_STARTUP);

    LCD_SendCommand(LCD_COMMAND_SET_FUNCTION_MODE, LCD_F_INSTR);
    LCD_SendCommand(LCD_COMMAND_DISPLAY_CURSOR_BLINK_ACT, LCD_F_INSTR);
    LCD_SendCommand(LCD_COMMAND_SET_ENTRY_MODE, LCD_F_INSTR);

    LCD_ClearScreen();

    return true;
}

void LCD_DisplayCursorBlinkActivation(bool display, bool cursor, bool blink){
    DISPLAY_CURSOR_BLINK_ACTbits.D = display;
    DISPLAY_CURSOR_BLINK_ACTbits.C = cursor;
    DISPLAY_CURSOR_BLINK_ACTbits.B = blink;
    LCD_SendCommand(LCD_COMMAND_DISPLAY_CURSOR_BLINK_ACT, LCD_F_INSTR);
}

void LCD_ShiftDisplayMoveCursor(bool shiftDisplayCursor, bool rightLeft){
    SHIFT_DISPLAY_MOVE_CURSORbits.SC = shiftDisplayCursor;
    SHIFT_DISPLAY_MOVE_CURSORbits.RL = rightLeft;
    LCD_SendCommand(LCD_COMMAND_SHIFT_DISPLAY_MOVE_CURSOR, LCD_F_INSTR);
}

void LCD_SetFunctionMode(bool eightBitsDataLenght, bool twoLines, bool tenDots){
    SET_FUNCTION_MODEbits.DL = eightBitsDataLenght;
    SET_FUNCTION_MODEbits.F = twoLines;
    SET_FUNCTION_MODEbits.N = tenDots;
    LCD_SendCommand(LCD_COMMAND_SET_FUNCTION_MODE, LCD_F_INSTR);
}

void LCD_PutString(char* inputString, uint16_t length) {
    while (length--) {
        switch (*inputString) {
            case 0x00:
                return;
            default:
                LCD_PutChar(*inputString++);
                break;
        }
    }
}

void LCD_PutChar(char inputCharacter) {
    switch (inputCharacter) {
        case '\r':
            LCD_COL = 0;
            LCD_SendCommand(LCD_COMMAND_SET_DD_RAM_ADDR, LCD_F_INSTR);
            break;
        case '\n':
            LCD_ROW ^= 1;
            LCD_SendCommand(LCD_COMMAND_SET_DD_RAM_ADDR, LCD_F_INSTR);
            break;
        case '\b':
            LCD_ShiftCursorLeft();
            LCD_PutChar(' ');
            LCD_ShiftCursorRight();
            break;
        default:
            LCD_SendData(inputCharacter);
            if (LCD_COL == LCD_MAX_COLUMN - 1) {
                LCD_ROW ^= 1;
                LCD_COL = 0;
                LCD_SendCommand(LCD_COMMAND_SET_DD_RAM_ADDR, LCD_F_INSTR);
            } else {
                LCD_COL++;
            }
            break;
    }
}

void LCD_ReturnHome(void) {
    LCD_SendCommand(LCD_COMMAND_RETURN_HOME, LCD_S_INSTR);
    SET_DD_RAM_ADDRbits.ADDR = 0x00;
}

void LCD_ClearScreen(void) {
    LCD_SendCommand(LCD_COMMAND_CLEAR_SCREEN, LCD_S_INSTR);
    SET_DD_RAM_ADDRbits.ADDR = 0x00;
}

void LCD_SetCol(unsigned char column) {
    LCD_COL = column;
    LCD_SendCommand(LCD_COMMAND_SET_DD_RAM_ADDR, LCD_F_INSTR);
}

void LCD_SetRow(unsigned char row) {
    LCD_ROW = row;
    LCD_SendCommand(LCD_COMMAND_SET_DD_RAM_ADDR, LCD_F_INSTR);
}

void LCD_SetDDRAMAdrress(unsigned char address) {
    LCD_DD_RAM_ADDRESS = address;
    LCD_SendCommand(LCD_COMMAND_SET_DD_RAM_ADDR, LCD_F_INSTR);
}

static void LCD_ShiftCursorLeft(void) {
    if (LCD_COL == 0) {
        LCD_ROW ^= 1;
        LCD_COL = LCD_MAX_COLUMN - 1;
    } else {
        LCD_COL--;
    }
    LCD_SendCommand(LCD_COMMAND_SET_DD_RAM_ADDR, LCD_F_INSTR);
}

static void LCD_ShiftCursorRight(void) {
    if (LCD_COL == LCD_MAX_COLUMN - 1) {
        LCD_COL = 0;
        LCD_ROW ^= 1;
    } else {
        LCD_COL++;
    }
    LCD_SendCommand(LCD_COMMAND_SET_DD_RAM_ADDR, LCD_F_INSTR);
}
