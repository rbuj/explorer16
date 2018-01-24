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

#ifndef LED_H
#define LED_H

#include <xc.h>
#include <stdbool.h> /* Includes true/false definition */

#define LEDs_LAT LATA
#define LEDs_TRIS TRISA

#define LED_D3_LAT LATAbits.LATA0
#define LED_D4_LAT LATAbits.LATA1
#define LED_D5_LAT LATAbits.LATA2
#define LED_D6_LAT LATAbits.LATA3
#define LED_D7_LAT LATAbits.LATA4
#define LED_D8_LAT LATAbits.LATA5
#define LED_D9_LAT LATAbits.LATA6
#define LED_D10_LAT LATAbits.LATA7 /*!< Overlaps with S5 */

#define LED_D3_TRIS TRISAbits.TRISA0
#define LED_D4_TRIS TRISAbits.TRISA1
#define LED_D5_TRIS TRISAbits.TRISA2
#define LED_D6_TRIS TRISAbits.TRISA3
#define LED_D7_TRIS TRISAbits.TRISA4
#define LED_D8_TRIS TRISAbits.TRISA5
#define LED_D9_TRIS TRISAbits.TRISA6
#define LED_D10_TRIS TRISAbits.TRISA7 /*!< Overlaps with S5 */

#define LED_ON 1  /**< This macro is used for switching ON a led. */
#define LED_OFF 0 /**< This macro is used for switching OFF a led. */
#define INPUT 1   /**< This macro is used for setting a pin as input pin. */
#define OUTPUT 0  /**< This macro is used for setting a pin as output pin. */

/**
 * enum of LEDs.
 * An enumeration that is used for identifying each one of the leds.
 */
typedef enum {
   LED_NONE, /**< none */
   LED_D3,   /**< LED D3 */
   LED_D4,   /**< LED D4 */
   LED_D5,   /**< LED D5 */
   LED_D6,   /**< LED D6 */
   LED_D7,   /**< LED D7 */
   LED_D8,   /**< LED D8 */
   LED_D9,   /**< LED D9 */
   LED_D10   /**< LED D10 */
} LED;

/**
 * Set a LED's pin as output for switching it ON/OFF.
 * @param led The led to enable.
 */
void LED_Enable(LED);

/**
 * Switch ON/OFF a LED.
 */
void LED_OnOff(LED led, bool io);

/**
 * Switch ON a LED.
 */
#define LED_On(LED) LED_OnOff(LED, LED_ON);

/**
 * Switch OFF a LED.
 */
#define LED_Off(LED) LED_OnOff(LED, LED_OFF);

/**
 * Toggle a led ON/OFF.
 */
void LED_Toggle(LED);

/**
 * Set the pins of all the LEDs as output pins for switching them ON/OFF.
 */
#define LEDs_Enable() LEDs_TRIS &= 0xFF00 /* PORTA<7:0> as outputs */

/**
 * Switch ON all the LEDs.
 */
#define LEDs_On()      \
   LEDs_LAT &= 0xFF00; \
   LEDs_LAT += 0x00FF

/**
 * Switch OFF all the LEDs.
 */
#define LEDs_Off() LEDs_LAT &= 0xFF00

/**
 * Toggle ON/OFF all the LEDs.
 */
#define LEDs_Toggle() LEDs_LAT ^= 0x00FF

#endif /* LED_H */