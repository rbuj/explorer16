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
#include <stdlib.h> /* Includes EXIT_SUCCESS definition */
#include <stddef.h> /* Includes the type yielded by sizeof */
#include <stdbool.h> /* Includes true/false definition */

#include "app.h"

void SYS_Initialize(void);

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
int main(void) {
    /* Call the System Initialize routine */
    SYS_Initialize();

    /* Infinite Loop */
    while (true) {
        while (!BUTTON_IsPressed(BUTTON_S3));
        LED_On(LED_D10);
        while (BUTTON_IsPressed(BUTTON_S3));
        LED_Off(LED_D10);
    };

    return EXIT_SUCCESS;
}