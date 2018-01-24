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
 * @param button The button to check.
 */
bool BUTTON_IsPressed(BUTTON button) __attribute__((section(".libexplorer16")));

/**
 * Set a button pin as input.
 * @param button The button to enable.
 */
void BUTTON_Enable(BUTTON button) __attribute__((section(".libexplorer16")));

/**
 * Set up change notification for a given button.
 * @param button The button to enable CN.
 */
bool BUTTON_CN_Configuration(BUTTON button) __attribute__((section(".libexplorer16")));

#endif /* BUTTON_H */
