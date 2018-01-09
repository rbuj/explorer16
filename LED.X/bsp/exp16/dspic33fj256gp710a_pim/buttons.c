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
#include <stdbool.h>
#include <buttons.h>

// S1  is MCLR button
#define S3_PORT  PORTDbits.RD6
#define S6_PORT  PORTDbits.RD7
#define S5_PORT  PORTAbits.RA7       // Overlaps with D10
#define S4_PORT  PORTDbits.RD13

#define S3_TRIS  TRISDbits.TRISD6
#define S6_TRIS  TRISDbits.TRISD7
#define S5_TRIS  TRISAbits.TRISA7
#define S4_TRIS  TRISDbits.TRISD13

#define BUTTON_PRESSED      0
#define BUTTON_NOT_PRESSED  1

#define PIN_INPUT           1
#define PIN_OUTPUT          0

bool BUTTON_IsPressed(BUTTON button) {
    switch (button) {
        case BUTTON_S3:
            return ( (S3_PORT == BUTTON_PRESSED) ? true : false);
        case BUTTON_S6:
            return ( (S6_PORT == BUTTON_PRESSED) ? true : false);
        case BUTTON_S5:
            return ( (S5_PORT == BUTTON_PRESSED) ? true : false);
        case BUTTON_S4:
            return ( (S4_PORT == BUTTON_PRESSED) ? true : false);
        case BUTTON_DISABLED:
            return false;
    }
    return false;
}

void BUTTON_Enable(BUTTON button) {
    switch (button) {
        case BUTTON_S3:
            S3_TRIS = PIN_INPUT;
            break;
        case BUTTON_S6:
            S6_TRIS = PIN_INPUT;
            break;
        case BUTTON_S5:
            S5_TRIS = PIN_INPUT;
            break;
        case BUTTON_S4:
            S4_TRIS = PIN_INPUT;
            break;
        case BUTTON_DISABLED:
            break;
    }
}
