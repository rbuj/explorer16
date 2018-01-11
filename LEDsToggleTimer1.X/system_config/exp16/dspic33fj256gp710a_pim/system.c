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
#include <stdbool.h> /* Includes true/false definition */
#include "app.h"

// FBS
#pragma config BWRP = WRPROTECT_OFF     // Boot Segment Write Protect (Boot Segment may be written)
#pragma config BSS = NO_FLASH           // Boot Segment Program Flash Code Protection (No Boot program Flash segment)
#pragma config RBS = NO_RAM             // Boot Segment RAM Protection (No Boot RAM)

// FSS
#pragma config SWRP = WRPROTECT_OFF     // Secure Segment Program Write Protect (Secure Segment may be written)
#pragma config SSS = NO_FLASH           // Secure Segment Program Flash Code Protection (No Secure Segment)
#pragma config RSS = NO_RAM             // Secure Segment Data RAM Protection (No Secure RAM)

// FGS
#pragma config GWRP = OFF               // General Code Segment Write Protect (User program memory is not write-protected)
#pragma config GSS = OFF                // General Segment Code Protection (User program memory is not code-protected)

// FOSCSEL
#pragma config FNOSC = FRC              // Oscillator Mode (Internal Fast RC (FRC))
#pragma config IESO = OFF               // Two-speed Oscillator Start-Up Enable (Start up with user-selected oscillator)

// FOSC
#pragma config POSCMD = XT              // Primary Oscillator Source (XT Oscillator Mode)
#pragma config OSCIOFNC = ON            // OSC2 Pin Function (OSC2 pin has digital I/O function)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Both Clock Switching and Fail-Safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler (1:32,768)
#pragma config WDTPRE = PR128           // WDT Prescaler (1:128)
#pragma config PLLKEN = ON              // PLL Lock Enable bit (Clock switch to PLL source will wait until the PLL lock signal is valid.)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog timer enabled/disabled by user software)

// FPOR
#pragma config FPWRT = PWR128           // POR Timer Value (128ms)

// FICD
#pragma config ICS = PGD1               // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)

void SOSC_Configuration(void);
void __attribute__((__interrupt__, auto_psv)) _OscillatorFail(void);
void __attribute__((__interrupt__, auto_psv)) _AddressError(void);
void __attribute__((__interrupt__, auto_psv)) _StackError(void);
void __attribute__((__interrupt__, auto_psv)) _MathError(void);
void __attribute__((__interrupt__, auto_psv)) _AltOscillatorFail(void);
void __attribute__((__interrupt__, auto_psv)) _AltAddressError(void);
void __attribute__((__interrupt__, auto_psv)) _AltStackError(void);
void __attribute__((__interrupt__, auto_psv)) _AltMathError(void);

void SYS_Initialize(void) {
    /* Enable LEDs */
    LEDs_Enable();

    /* Turn Off LEDs */
    LEDs_Off();

    /* Enable ADC to the Potentiometer channel */
    ADC_ChannelEnable(ADC_CHANNEL_POTENTIOMETER);

    /* Initialize LCD*/
    PRINT_SetConfiguration(PRINT_CONFIGURATION_LCD);

    /* Configure Secondary Oscillator for Timer 1 to work as RTC counter */
    SOSC_Configuration();
}

void SOSC_Configuration(void) {
    char a, b, c, *p;

    a = 2;
    b = 0x46;
    c = 0x57;
    p = (char *) &OSCCON;

    asm volatile ("mov.b %1,[%0] \n"
            "mov.b %2,[%0] \n"
            "mov.b %3,[%0] \n" : /* no outputs */ : "r"(p), "r"(b), "r"(c),
            "r"(a));
}

void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void) {
    LEDs_Toggle(); /* Toggle LED at 1 Hz rate */
    IFS0bits.T1IF = 0; /* reset Timer 1 interrupt flag */
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

void __attribute__((__interrupt__, auto_psv)) _DMACError(void) {
    DMACS0 = 0;
    INTCON1bits.DMACERR = 0;
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

void __attribute__((__interrupt__, auto_psv)) _AltDMACError(void) {
    DMACS0 = 0;
    INTCON1bits.DMACERR = 0;
    while (true);
}
