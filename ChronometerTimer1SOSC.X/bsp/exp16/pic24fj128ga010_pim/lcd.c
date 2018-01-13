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

/* Private Definitions ***********************************************/
// Define a fast instruction execution time in terms of loop time
// typically > 43us
#define LCD_F_INSTR         250 // 62.5us

// Define a slow instruction execution time in terms of loop time
// typically > 1.35ms
#define LCD_S_INSTR         5400 // 1.35ms

// Define the startup time for the LCD in terms of loop time
// typically > 30ms
#define LCD_STARTUP         120000 // 30ms

#define LCD_MAX_COLUMN      16

#define LCD_SendData(data) { PMADDR = 0x0001; PMDIN1 = data; LCD_Wait(LCD_F_INSTR); }
#define LCD_SendCommand(command, delay) { PMADDR = 0x0000; PMDIN1 = command; LCD_Wait(delay); }
#define LCD_COMMAND_CLEAR_SCREEN        0x01
#define LCD_COMMAND_RETURN_HOME         0x02
#define LCD_COMMAND_ENTER_DATA_MODE     0x06
#define LCD_COMMAND_CURSOR_OFF          0x0C
#define LCD_COMMAND_CURSOR_ON           0x0F
#define LCD_COMMAND_MOVE_CURSOR_LEFT    0x10
#define LCD_COMMAND_MOVE_CURSOR_RIGHT   0x14
#define LCD_COMMAND_SET_MODE_8_BIT      0x38
#define LCD_COMMAND_ROW_0_HOME          0x80
#define LCD_COMMAND_ROW_1_HOME          0xC0

/* Private Functions *************************************************/
static void LCD_CarriageReturn(void);
static void LCD_ShiftCursorLeft(void);
static void LCD_ShiftCursorRight(void);
static void LCD_ShiftCursorUp(void);
static void LCD_ShiftCursorDown(void);
static void LCD_Wait(unsigned long);

/* Private variables ************************************************/
static uint8_t row;
static uint8_t column;

bool LCD_Initialize(void) {
    PMMODE = 0x03ff;
    // Enable PMP Module, No Address & Data Muxing,
    // Enable RdWr Port, Enable Enb Port, No Chip Select,
    // Select RdWr and Enb signals Active High
    PMCON = 0x8383;
    // Enable A0
    PMAEN = 0x0001;

    LCD_Wait(LCD_STARTUP);
    LCD_Wait(LCD_STARTUP);

    LCD_SendCommand(LCD_COMMAND_SET_MODE_8_BIT, LCD_F_INSTR + LCD_STARTUP);
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
                    LCD_SendCommand(LCD_COMMAND_ROW_1_HOME, LCD_S_INSTR);
                    row = 1;
                } else {
                    LCD_SendCommand(LCD_COMMAND_ROW_0_HOME, LCD_S_INSTR);
                    row = 0;
                }
            }
            break;
    }
}

void LCD_ReturnHome(void) {
    LCD_SendCommand(LCD_COMMAND_RETURN_HOME, LCD_S_INSTR);
    row = 0;
    column = 0;
}

void LCD_ClearScreen(void) {
    LCD_SendCommand(LCD_COMMAND_CLEAR_SCREEN, LCD_S_INSTR);
    LCD_ReturnHome();
}

static void LCD_CarriageReturn(void) {
    if (row == 0) {
        LCD_SendCommand(LCD_COMMAND_ROW_0_HOME, LCD_S_INSTR);
    } else {
        LCD_SendCommand(LCD_COMMAND_ROW_1_HOME, LCD_S_INSTR);
    }
    column = 0;
}

static void LCD_ShiftCursorLeft(void) {
    uint8_t i;
    if (column == 0) {
        if (row == 0) {
            LCD_SendCommand(LCD_COMMAND_ROW_1_HOME, LCD_S_INSTR);
            row = 1;
        } else {
            LCD_SendCommand(LCD_COMMAND_ROW_0_HOME, LCD_S_INSTR);
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
            LCD_SendCommand(LCD_COMMAND_ROW_1_HOME, LCD_S_INSTR);
            row = 1;
        } else {
            LCD_SendCommand(LCD_COMMAND_ROW_0_HOME, LCD_S_INSTR);
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

static void LCD_Wait(unsigned long delay) {
    while (delay) {
        delay--;
    }
}

void LCD_CursorEnable(bool enable) {
    if (enable == true) {
        LCD_SendCommand(LCD_COMMAND_CURSOR_ON, LCD_S_INSTR);
    } else {
        LCD_SendCommand(LCD_COMMAND_CURSOR_OFF, LCD_S_INSTR);
    }
}
