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
#include <stdbool.h>  /* Includes true/false definition */
#include <stddef.h>   /* Includes the type yielded by sizeof */
#include <stdlib.h>   /* Includes EXIT_SUCCESS definition */
#include <libpic30.h> /* Includes __delay_ms */
#include "app.h"

void SYS_Initialize(void);

/* Main Program */
int main(void) {
   /* Call the System Initialize routine */
   SYS_Initialize();

   /* Infinite Loop */
   while (true) {
      LED_Off(LED_D10);
      __delay_ms(500);
      LED_On(LED_D10);
      __delay_ms(500);
   };

   return EXIT_SUCCESS;
}