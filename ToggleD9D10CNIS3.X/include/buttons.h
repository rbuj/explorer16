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

typedef enum {
    BUTTON_DISABLED,
    BUTTON_S3,
    BUTTON_S6,
    BUTTON_S5,
    BUTTON_S4
    //S1 is MCLR
} BUTTON;

bool BUTTON_IsPressed(BUTTON) __attribute__ ((section (".libexplorer16")));
void BUTTON_Enable(BUTTON) __attribute__ ((section (".libexplorer16")));
bool BUTTON_CN_Configuration(BUTTON) __attribute__ ((section (".libexplorer16")));

#endif /* BUTTON_H */
