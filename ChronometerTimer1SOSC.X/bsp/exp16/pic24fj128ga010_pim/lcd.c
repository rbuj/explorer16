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

/* Private Definitions ***********************************************/
#define LCD_F_INSTR        160UL // Fast instruction delay = 40us -> cycles for __delay32
#define LCD_S_INSTR       6560UL // Slow instruction delay = 1.64ms -> cycles for __delay32
#define LCD_STARTUP     120000UL // Start up delay = 30ms -> cycles for __delay32
#define LCD_MAX_COLUMN        16

/* LCD Instructions **************************************************/
#define LCD_COMMAND_CLEAR_SCREEN           0b00000001
#define LCD_COMMAND_RETURN_HOME            0b00000010
#define LCD_COMMAND_ENTER_DATA_MODE        0b00000110
#define LCD_COMMAND_CURSOR_OFF             0b00001100
#define LCD_COMMAND_CURSOR_OFF_BLINK       0b00001101
#define LCD_COMMAND_CURSOR_ON              0b00001110
#define LCD_COMMAND_CURSOR_ON_BLINK        0b00001111
#define LCD_COMMAND_MOVE_CURSOR_LEFT       0b00010000
#define LCD_COMMAND_MOVE_CURSOR_RIGHT      0b00010100
#define LCD_COMMAND_MOVE_DISPLAY_LEFT      0b00011000
#define LCD_COMMAND_MOVE_DISPLAY_RIGHT     0b00011100
#define LCD_COMMAND_SET_MODE_4_BIT_8_DOTS  0b00101000
#define LCD_COMMAND_SET_MODE_4_BIT_10_DOTS 0b00101100
#define LCD_COMMAND_SET_MODE_8_BIT_8_DOTS  0b00111000
#define LCD_COMMAND_SET_MODE_8_BIT_10_DOTS 0b00111100
#define LCD_COMMAND_ROW_0_HOME             0b10000000
#define LCD_COMMAND_ROW_1_HOME             0b11000000

/* Private Functions *************************************************/
static void LCD_CarriageReturn(void);
static void LCD_ShiftCursorLeft(void);
static void LCD_ShiftCursorRight(void);
static void LCD_ShiftCursorUp(void);
static void LCD_ShiftCursorDown(void);

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

/* Private variables ************************************************/
static uint8_t row;
static uint8_t column;

bool LCD_Initialize(void) {
    /*
     * PMMODE = 0x03ff
     * 
     * BUSY:   Port is not busy
     * IRQM:   No Interrupt generated
     * INCM:   No increment or decrement of address
     * MODE16: 8-bit mode: a read or write to the data register invokes a single 8-bit transfer
     * MODE:   Master mode 1 (PMCSx, PMRD/PMWR, PMENB, PMA<x:0>, PMD<7:0>, PMD<8:15>)
     * WAITB:  Data Setup to Read/Write Strobe Wait States bits = 1 Tpb (250)
     * WAITM:  Data Read/Write Strobe Wait States bits = 2 Tpb (500ns)
     * WAITE:  Data Hold After Read/Write Strobe Wait States bits = 1 Tpb (250ns)
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

    LCD_SendCommand(LCD_COMMAND_SET_MODE_8_BIT_10_DOTS, LCD_F_INSTR);
    LCD_SendCommand(LCD_COMMAND_CURSOR_OFF, LCD_F_INSTR);
    LCD_SendCommand(LCD_COMMAND_ENTER_DATA_MODE, LCD_S_INSTR);

    LCD_ClearScreen();

    return true;
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
            LCD_CarriageReturn();
            break;
        case '\n':
            if (row == 0) {
                LCD_ShiftCursorDown();
            } else {
                LCD_ShiftCursorUp();
            }
            break;
        case '\b':
            LCD_ShiftCursorLeft();
            LCD_PutChar(' ');
            LCD_ShiftCursorLeft();
            break;
        default:
            LCD_SendData(inputCharacter);
            column++;
            if (column == LCD_MAX_COLUMN) {
                column = 0;
                if (row == 0) {
                    LCD_SendCommand(LCD_COMMAND_ROW_1_HOME, LCD_F_INSTR);
                    row = 1;
                } else {
                    LCD_SendCommand(LCD_COMMAND_ROW_0_HOME, LCD_F_INSTR);
                    row = 0;
                }
            }
            break;
    }
}

void LCD_ReturnHome(void) {
    column = 0;
    if (row == 0) {
        LCD_SendCommand(LCD_COMMAND_ROW_0_HOME, LCD_F_INSTR);
    } else {
        LCD_SendCommand(LCD_COMMAND_ROW_1_HOME, LCD_F_INSTR);
    }
}

void LCD_ClearScreen(void) {
    LCD_SendCommand(LCD_COMMAND_CLEAR_SCREEN, LCD_S_INSTR);
    LCD_SendCommand(LCD_COMMAND_RETURN_HOME, LCD_S_INSTR);
    row = 0;
    column = 0;
}

static void LCD_CarriageReturn(void) {
    if (row == 0) {
        LCD_SendCommand(LCD_COMMAND_ROW_0_HOME, LCD_F_INSTR);
    } else {
        LCD_SendCommand(LCD_COMMAND_ROW_1_HOME, LCD_F_INSTR);
    }
    column = 0;
}

static void LCD_ShiftCursorLeft(void) {
    uint8_t i;
    if (column == 0) {
        if (row == 0) {
            LCD_SendCommand(LCD_COMMAND_ROW_1_HOME, LCD_F_INSTR);
            row = 1;
        } else {
            LCD_SendCommand(LCD_COMMAND_ROW_0_HOME, LCD_F_INSTR);
            row = 0;
        }
        //Now shift to the end of the row
        for (i = 0; i < (LCD_MAX_COLUMN - 1); i++) {
            LCD_ShiftCursorRight();
        }
    } else {
        column--;
        LCD_SendCommand(LCD_COMMAND_MOVE_CURSOR_LEFT, LCD_F_INSTR);
    }
}

static void LCD_ShiftCursorRight(void) {
    LCD_SendCommand(LCD_COMMAND_MOVE_CURSOR_RIGHT, LCD_F_INSTR);
    column++;
    if (column == LCD_MAX_COLUMN) {
        column = 0;
        if (row == 0) {
            LCD_SendCommand(LCD_COMMAND_ROW_1_HOME, LCD_F_INSTR);
            row = 1;
        } else {
            LCD_SendCommand(LCD_COMMAND_ROW_0_HOME, LCD_F_INSTR);
            row = 0;
        }
    }
}

static void LCD_ShiftCursorUp(void) {
    uint8_t i;
    for (i = 0; i < LCD_MAX_COLUMN; i++) {
        LCD_ShiftCursorLeft();
    }
}

static void LCD_ShiftCursorDown(void) {
    uint8_t i;
    for (i = 0; i < LCD_MAX_COLUMN; i++) {
        LCD_ShiftCursorRight();
    }
}

void LCD_CursorEnable(bool enable) {
    if (enable == true) {
        LCD_SendCommand(LCD_COMMAND_CURSOR_ON, LCD_F_INSTR);
    } else {
        LCD_SendCommand(LCD_COMMAND_CURSOR_OFF, LCD_F_INSTR);
    }
}
