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

#define LCD_DATA_LAT              LATE
#define LCD_DATA_TRIS             TRISE
#define LCD_RSSignal_Set()        LATBbits.LATB15 = 1 //set Register Select bit
#define LCD_RSSignal_Clear()      LATBbits.LATB15 = 0 //clear Register Select bit
#define LCD_RWSignal_Set()        LATDbits.LATD5 = 1  //set Read/Write bit
#define LCD_RWSignal_Clear()      LATDbits.LATD5 = 0  //clear Read/Write bit
#define LCD_EnableSignal_Set()    LATDbits.LATD4 = 1  //set Enable bit
#define LCD_EnableSignal_Clear()  LATDbits.LATD4 = 0  //clear Enable bit
#define LCD_RSSignal_Input()      TRISBbits.TRISB15 = 1 //set Register Select bit
#define LCD_RSSignal_Output()     TRISBbits.TRISB15 = 0 //clear Register Select bit
#define LCD_RWSignal_Input()      TRISDbits.TRISD5 = 1  //set Read/Write bit
#define LCD_RWSignal_Output()     TRISDbits.TRISD5 = 0  //clear Read/Write bit
#define LCD_EnableSignal_Input()  TRISDbits.TRISD4 = 1  //set Enable bit
#define LCD_EnableSignal_Output() TRISDbits.TRISD4 = 0  //clear Enable bit

/* Private Functions *************************************************/
static void LCD_CarriageReturn(void);
static void LCD_ShiftCursorLeft(void);
static void LCD_ShiftCursorRight(void);
static void LCD_ShiftCursorUp(void);
static void LCD_ShiftCursorDown(void);
static void LCD_SendData(char);
static void LCD_SendCommand(char, unsigned long);

/* Private variables ************************************************/
static uint8_t row;
static uint8_t column;

bool LCD_Initialize(void) {
    LCD_DATA_LAT &= 0xFF00;
    LCD_DATA_TRIS &= 0xFF00;

    // Control signal data pins
    LCD_RWSignal_Clear(); // LCD R/W signal
    LCD_RSSignal_Clear(); // LCD RS signal
    LCD_EnableSignal_Clear(); // LCD E signal

    // Control signal pin direction
    LCD_RSSignal_Output();
    LCD_RWSignal_Output();
    LCD_EnableSignal_Output();

    LCD_EnableSignal_Set();

    /* LCD: Wait for more than 30ms after VDD on */
    __delay32(LCD_STARTUP);

    LCD_SendCommand(LCD_COMMAND_SET_MODE_8_BIT_10_DOTS, LCD_F_INSTR + LCD_STARTUP);
    LCD_SendCommand(LCD_COMMAND_CURSOR_OFF, LCD_F_INSTR);
    LCD_SendCommand(LCD_COMMAND_ENTER_DATA_MODE, LCD_F_INSTR);

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

static void LCD_SendData(char data) {
    LCD_RWSignal_Clear();
    LCD_RSSignal_Set();
    LCD_DATA_LAT &= 0xFF00;
    LCD_DATA_LAT |= data;
    LCD_EnableSignal_Set();
    Nop();
    Nop();
    Nop();
    LCD_EnableSignal_Clear();
    LCD_RSSignal_Clear();
    __delay32(LCD_F_INSTR);
    Nop();
}

static void LCD_SendCommand(char command, unsigned long delay) {
    LCD_DATA_LAT &= 0xFF00;
    LCD_DATA_LAT |= command;
    LCD_RWSignal_Clear();
    LCD_RSSignal_Clear();
    LCD_EnableSignal_Set();
    Nop();
    Nop();
    Nop();
    LCD_EnableSignal_Clear();
    LCD_EnableSignal_Clear();
    __delay32(delay);
}
