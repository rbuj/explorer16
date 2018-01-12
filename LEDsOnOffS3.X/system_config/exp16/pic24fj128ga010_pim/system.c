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
/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include <xc.h>
#include <stdbool.h> /* Includes true/false definition */
#include "app.h"

// CONFIG2
#pragma config POSCMOD = XT             // Primary Oscillator Select (XT Oscillator mode selected)
#pragma config OSCIOFNC = OFF           // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as CLKO (FOSC/2))
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = PRI              // Oscillator Select (Primary Oscillator (XT, HS, EC))
#pragma config IESO = ON                // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) enabled)

// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = ON              // Watchdog Timer Window (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config ICS = PGx2               // Comm Channel Select (Emulator/debugger uses EMUC2/EMUD2)
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG port is disabled)

/******************************************************************************/
/* Trap Function Prototypes                                                   */
/******************************************************************************/
/* Interrupt Vector Table: Use if ALTIVT=0 (INTCON2<15>) */
void __attribute__((__interrupt__, auto_psv)) _OscillatorFail(void);
void __attribute__((__interrupt__, auto_psv)) _AddressError(void);
void __attribute__((__interrupt__, auto_psv)) _StackError(void);
void __attribute__((__interrupt__, auto_psv)) _MathError(void);
/* Alternate Interrupt Vector Table: Use if ALTIVT=1 (INTCON2<15>) */
void __attribute__((__interrupt__, auto_psv)) _AltOscillatorFail(void);
void __attribute__((__interrupt__, auto_psv)) _AltAddressError(void);
void __attribute__((__interrupt__, auto_psv)) _AltStackError(void);
void __attribute__((__interrupt__, auto_psv)) _AltMathError(void);

void SYS_Initialize(void) {
    /* Enable LEDs */
    LEDs_Enable();

    /* Turn Off LEDs */
    LEDs_Off();

    /* Enable Switch S3 */
    BUTTON_Enable(BUTTON_S3);

    /* Enable ADC to the Potentiometer channel */
    ADC_ChannelEnable(ADC_CHANNEL_POTENTIOMETER);

    /* Initialize LCD */
    PRINT_SetConfiguration(PRINT_CONFIGURATION_LCD);
}

void __attribute__((__interrupt__, auto_psv)) _OscillatorFail(void) {
    INTCON1bits.OSCFAIL = 0; //Clear the trap flag
    while (true);
}

void __attribute__((__interrupt__, auto_psv)) _AddressError(void) {
    INTCON1bits.ADDRERR = 0; //Clear the trap flag
    while (true);
}

void __attribute__((__interrupt__, auto_psv)) _StackError(void) {
    INTCON1bits.STKERR = 0; //Clear the trap flag
    while (true);
}

void __attribute__((__interrupt__, auto_psv)) _MathError(void) {
    INTCON1bits.MATHERR = 0; //Clear the trap flag
    while (true);
}

void __attribute__((__interrupt__, auto_psv)) _AltOscillatorFail(void) {
    INTCON1bits.OSCFAIL = 0;
    while (true);
}

void __attribute__((__interrupt__, auto_psv)) _AltAddressError(void) {
    INTCON1bits.ADDRERR = 0;
    while (true);
}

void __attribute__((__interrupt__, auto_psv)) _AltStackError(void) {
    INTCON1bits.STKERR = 0;
    while (true);
}

void __attribute__((__interrupt__, auto_psv)) _AltMathError(void) {
    INTCON1bits.MATHERR = 0;
    while (true);
}
