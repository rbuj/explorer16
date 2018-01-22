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

/* CONFIG2 */
#pragma config POSCMOD = XT   /* Primary Oscillator Select (XT Oscillator mode selected) */
#pragma config OSCIOFNC = OFF /* Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as CLKO (FOSC/2)) */
#pragma config FCKSM = \
    CSDCMD                 /* Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled) */
#pragma config FNOSC = PRI /* Oscillator Select (Primary Oscillator (XT, HS, EC)) */
#pragma config IESO = ON   /* Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) enabled) */

/* CONFIG1 */
#pragma config WDTPS = PS32768 /* Watchdog Timer Postscaler (1:32,768) */
#pragma config FWPSA = PR128   /* WDT Prescaler (Prescaler ratio of 1:128) */
#pragma config WINDIS = ON     /* Watchdog Timer Window (Standard Watchdog Timer enabled,(Windowed-mode is disabled)) */
#pragma config FWDTEN = OFF    /* Watchdog Timer Enable (Watchdog Timer is disabled) */
#pragma config ICS = PGx2      /* Comm Channel Select (Emulator/debugger uses EMUC2/EMUD2) */
#pragma config GWRP = OFF      /* General Code Segment Write Protect (Writes to program memory are allowed) */
#pragma config GCP = OFF       /* General Code Segment Code Protect (Code protection is disabled) */
#pragma config JTAGEN = OFF    /* JTAG Port Enable (JTAG port is disabled) */

/******************************************************************************/
/* Trap Function Prototypes                                                   */
/******************************************************************************/
/* <editor-fold defaultstate="collapsed" desc="Interrupt Vector Table: Use if ALTIVT=0 (INTCON2<15>)"> */
void __attribute__((__interrupt__, auto_psv)) _OscillatorFail(void);
void __attribute__((__interrupt__, auto_psv)) _AddressError(void);
void __attribute__((__interrupt__, auto_psv)) _StackError(void);
void __attribute__((__interrupt__, auto_psv)) _MathError(void);
/* </editor-fold> */
/* <editor-fold defaultstate="collapsed" desc="Alternate Interrupt Vector Table: Use if ALTIVT=1 (INTCON2<15>)"> */
#if defined(__PIC24F__) || defined(__PIC24H__)
void __attribute__((__interrupt__, auto_psv)) _AltOscillatorFail(void);
void __attribute__((__interrupt__, auto_psv)) _AltAddressError(void);
void __attribute__((__interrupt__, auto_psv)) _AltStackError(void);
void __attribute__((__interrupt__, auto_psv)) _AltMathError(void);
#endif
/* </editor-fold> */
/* <editor-fold defaultstate="collapsed" desc="Additional traps in the 24E family. No Alternate Vectors in the 24E family. "> */
#if defined(__PIC24E__)

void __attribute__((interrupt, no_auto_psv)) _HardTrapError(void);
void __attribute__((interrupt, no_auto_psv)) _DMACError(void);
void __attribute__((interrupt, no_auto_psv)) _SoftTrapError(void);

#endif
/* </editor-fold> */
/* <editor-fold defaultstate="collapsed" desc="Default interrupt handler"> */
void __attribute__((interrupt, no_auto_psv)) _DefaultInterrupt(void);
/* </editor-fold> */

void SYS_Initialize(void) {
   /* Enable D10 */
   LED_Enable(LED_D10);

   /* Turn Off D10 */
   LED_Off(LED_D10);

   /* Enable Switch S3 */
   BUTTON_Enable(BUTTON_S3);

   /* Enable ADC to the Potentiometer channel */
   ADC_ChannelEnable(ADC_CHANNEL_POTENTIOMETER);

   /* Initialize LCD */
   LCD_Initialize(&LCD_REGs);

   /* Low-Power Secondary Oscillator (SOSC) */
   __builtin_write_OSCCONL(0x02); /* Continuous Secondary Oscillator Operation */
}

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void) {
   if (IFS1bits.CNIF == 1) {
      if (BUTTON_IsPressed(BUTTON_S3)) {
         appData.lcd_clear_flag = 1;
         if (IEC0bits.T1IE == 1) {
            IEC0bits.T1IE = 0; /* disable timer1 interrupts */
         } else {
            IEC0bits.T1IE = 1; /* enable timer1 interrupts */
         }
         TMR1 = 0;          /* clear timer1 register */
         IFS0bits.T1IF = 0; /* reset Timer 1 interrupt flag */
      }
      IFS1bits.CNIF = 0; /* Reset CN interrupt */
   }
}

void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void) {
   if (appData.seconds < 59) {
      appData.seconds++;
   } else {
      appData.seconds = 0x00;
      if (appData.minutes < 59) {
         appData.minutes++;
      } else {
         appData.minutes = 0x00;
         if (appData.hours < 23) {
            appData.hours++;
         } else {
            appData.hours = 0x00;
         }
      }
   }
   appData.lcd_update_flag = 1; /* Update LCD in main loop */
   IFS0bits.T1IF = 0;           /* reset Timer 1 interrupt flag */
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

/* </editor-fold> */
/* <editor-fold defaultstate="collapsed" desc="Alternate address error trap function declarations"> */
#if defined(__PIC24F__) || defined(__PIC24H__)

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

#endif
/* </editor-fold> */
/* <editor-fold defaultstate="collapsed" desc="Specific traps for PIC24E family"> */
#if defined(__PIC24E__)

void __attribute__((interrupt, no_auto_psv)) _HardTrapError(void) {
   while (true)
      ;
}

void __attribute__((interrupt, no_auto_psv)) _DMACError(void) {
   while (1)
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