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

#ifndef BUTTON_H
#define BUTTON_H

#include <xc.h>
#include <stdbool.h>

/* S1  is MCLR button */
#define S3_PORT PORTDbits.RD6
#define S6_PORT PORTDbits.RD7
#define S5_PORT PORTAbits.RA7 /*!< Overlaps with D10 */
#define S4_PORT PORTDbits.RD13

#define S3_TRIS TRISDbits.TRISD6
#define S6_TRIS TRISDbits.TRISD7
#define S5_TRIS TRISAbits.TRISA7
#define S4_TRIS TRISDbits.TRISD13

#define BUTTON_PRESSED 0     /**< This macro is used for getting the status of a button */
#define BUTTON_NOT_PRESSED 1 /**< This macro is used for getting the status of a button */
#define PIN_INPUT 1          /**< This macro is used for setting a pin as input pin. */
#define PIN_OUTPUT 0         /**< This macro is used for setting a pin as output pin. */

/**
 * enum of buttons.
 * An enumeration that is used for identifying each one of the buttons. S1 is MCLR.
 */
typedef enum {
   BUTTON_DISABLED, /**< disabled */
   BUTTON_S3,       /**< S3 */
   BUTTON_S4,       /**< S4 */
   BUTTON_S5,       /**< S5 */
   BUTTON_S6        /**< S6 */
} BUTTON;

/**
 * Check if a button is pressed.
 */
bool BUTTON_IsPressed(BUTTON);

/**
 * Set a button pin as input pin.
 */
void BUTTON_Enable(BUTTON);

/**
 * Set up change notification for a given button.
 */
bool BUTTON_CN_Configuration(BUTTON);

#endif /* BUTTON_H */