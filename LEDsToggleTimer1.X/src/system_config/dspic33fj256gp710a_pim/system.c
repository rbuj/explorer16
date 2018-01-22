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

#include <xc.h>
#include <stdbool.h> /* Includes true/false definition */
#include "adc.h"
#include "app.h"

/* FBS */
#pragma config BWRP = WRPROTECT_OFF /* Boot Segment Write Protect (Boot Segment may be written) */
#pragma config BSS = NO_FLASH       /* Boot Segment Program Flash Code Protection (No Boot program Flash segment) */
#pragma config RBS = NO_RAM         /* Boot Segment RAM Protection (No Boot RAM) */

/* FSS */
#pragma config SWRP = WRPROTECT_OFF /* Secure Segment Program Write Protect (Secure Segment may be written) */
#pragma config SSS = NO_FLASH       /* Secure Segment Program Flash Code Protection (No Secure Segment) */
#pragma config RSS = NO_RAM         /* Secure Segment Data RAM Protection (No Secure RAM) */

/* FGS */
#pragma config GWRP = OFF /* General Code Segment Write Protect (User program memory is not write-protected) */
#pragma config GSS = OFF  /* General Segment Code Protection (User program memory is not code-protected) */

/* FOSCSEL */
#pragma config FNOSC = FRC /* Oscillator Mode (Internal Fast RC (FRC)) */
#pragma config IESO = OFF  /* Two-speed Oscillator Start-Up Enable (Start up with user-selected oscillator) */

/* FOSC */
#pragma config POSCMD = XT    /* Primary Oscillator Source (XT Oscillator Mode) */
#pragma config OSCIOFNC = OFF /* OSC2 Pin Function (OSC2 pin has digital I/O function) */
#pragma config FCKSM = \
    CSDCMD /* Clock Switching and Monitor (Both Clock Switching and Fail-Safe Clock Monitor are disabled) */

/* FWDT */
#pragma config WDTPOST = PS32768 /* Watchdog Timer Postscaler (1:32,768) */
#pragma config WDTPRE = PR128    /* WDT Prescaler (1:128) */
#pragma config PLLKEN = \
    ON /* PLL Lock Enable bit (Clock switch to PLL source will wait until the PLL lock signal is valid.) */
#pragma config WINDIS = OFF /* Watchdog Timer Window (Watchdog Timer in Non-Window mode) */
#pragma config FWDTEN = OFF /* Watchdog Timer Enable (Watchdog timer enabled/disabled by user software) */

/* FPOR */
#pragma config FPWRT = PWR128 /* POR Timer Value (128ms) */

/* FICD */
#pragma config ICS = PGD1   /* Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1) */
#pragma config JTAGEN = OFF /* JTAG Port Enable (JTAG is Disabled) */

/******************************************************************************/
/* Trap Function Prototypes                                                   */
/******************************************************************************/
/* <editor-fold defaultstate="collapsed" desc="Interrupt Vector Table: Use if ALTIVT=0 (INTCON2<15>)"> */
void __attribute__((__interrupt__, auto_psv)) _OscillatorFail(void);
void __attribute__((__interrupt__, auto_psv)) _AddressError(void);
void __attribute__((__interrupt__, auto_psv)) _StackError(void);
void __attribute__((__interrupt__, auto_psv)) _MathError(void);
#if defined(__HAS_DMA__)
void __attribute__((interrupt, no_auto_psv)) _DMACError(void);
#endif
/* </editor-fold> */
/* <editor-fold defaultstate="collapsed" desc="Alternate Interrupt Vector Table: Use if ALTIVT=1 (INTCON2<15>)"> */
#if defined(__dsPIC33F__)
void __attribute__((__interrupt__, auto_psv)) _AltOscillatorFail(void);
void __attribute__((__interrupt__, auto_psv)) _AltAddressError(void);
void __attribute__((__interrupt__, auto_psv)) _AltStackError(void);
void __attribute__((__interrupt__, auto_psv)) _AltMathError(void);
#if defined(__HAS_DMA__)
void __attribute__((interrupt, no_auto_psv)) _AltDMACError(void);
#endif
#endif
/* </editor-fold> */
/* <editor-fold defaultstate="collapsed" desc="Additional traps in the 33E family. No Alternate Vectors in the 33E family. "> */
#if defined(__dsPIC33E__)
void __attribute__((interrupt, no_auto_psv)) _HardTrapError(void);
void __attribute__((interrupt, no_auto_psv)) _SoftTrapError(void);
#endif
/* </editor-fold> */
/* <editor-fold defaultstate="collapsed" desc="Default interrupt handler"> */
void __attribute__((interrupt, no_auto_psv)) _DefaultInterrupt(void);
/* </editor-fold> */

void SYS_Initialize(void) {
   /* Enable LEDs */
   LEDs_Enable();

   /* Turn Off LEDs */
   LEDs_Off();

   /* Enable ADC to the Potentiometer channel */
   ADC_ChannelEnable(ADC_CHANNEL_POTENTIOMETER);

   /* Initialize LCD*/
   LCD_Initialize(&LCD_REGs);

   /* Low-Power Secondary Oscillator (SOSC) */
   __builtin_write_OSCCONL(0x02); /* Continuous Secondary Oscillator Operation */
}

void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void) {
   LEDs_Toggle();     /* Toggle LED at 1 Hz rate */
   IFS0bits.T1IF = 0; /* reset Timer 1 interrupt flag */
}

/******************************************************************************/
/* Trap Handling                                                              */
/******************************************************************************/
/* <editor-fold defaultstate="collapsed" desc="Primary (non-alternate) address error trap function declarations"> */

void __attribute__((__interrupt__, auto_psv)) _OscillatorFail(void) {
   INTCON1bits.OSCFAIL = 0; /* Clear the trap flag */
   while (true)
      ;
}

void __attribute__((__interrupt__, auto_psv)) _AddressError(void) {
   INTCON1bits.ADDRERR = 0; /* Clear the trap flag */
   while (true)
      ;
}

void __attribute__((__interrupt__, auto_psv)) _StackError(void) {
   INTCON1bits.STKERR = 0; /* Clear the trap flag */
   while (true)
      ;
}

void __attribute__((__interrupt__, auto_psv)) _MathError(void) {
   INTCON1bits.MATHERR = 0; /* Clear the trap flag */
   while (true)
      ;
}

#if defined(__HAS_DMA__)

void __attribute__((interrupt, no_auto_psv)) _DMACError(void) {
   INTCON1bits.DMACERR = 0; /* Clear the trap flag */
   while (true)
      ;
}

#endif

/* </editor-fold> */
/* <editor-fold defaultstate="collapsed" desc="Alternate address error trap function declarations"> */
#if defined(__dsPIC33F__)

void __attribute__((__interrupt__, auto_psv)) _AltOscillatorFail(void) {
   INTCON1bits.OSCFAIL = 0; /* Clear the trap flag */
   while (true)
      ;
}

void __attribute__((__interrupt__, auto_psv)) _AltAddressError(void) {
   INTCON1bits.ADDRERR = 0; /* Clear the trap flag */
   while (true)
      ;
}

void __attribute__((__interrupt__, auto_psv)) _AltStackError(void) {
   INTCON1bits.STKERR = 0; /* Clear the trap flag */
   while (true)
      ;
}

void __attribute__((__interrupt__, auto_psv)) _AltMathError(void) {
   INTCON1bits.MATHERR = 0; /* Clear the trap flag */
   while (true)
      ;
}

#if defined(__HAS_DMA__)

void __attribute__((interrupt, no_auto_psv)) _AltDMACError(void) {
   INTCON1bits.DMACERR = 0; /* Clear the trap flag */
   while (true)
      ;
}

#endif

#endif
/* </editor-fold> */
/* <editor-fold defaultstate="collapsed" desc="Specific traps for dsPIC33E family"> */
#if defined(__dsPIC33E__)

void __attribute__((interrupt, no_auto_psv)) _HardTrapError(void) {
   while (true)
      ;
}

void __attribute__((interrupt, no_auto_psv)) _SoftTrapError(void) {
   while (true)
      ;
}

#endif
/* </editor-fold> */
/* <editor-fold defaultstate="collapsed" desc="Default Interrupt Handler"> */

void __attribute__((interrupt, no_auto_psv)) _DefaultInterrupt(void) {
   while (true)
      ;
}

/* </editor-fold> */