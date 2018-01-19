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

#ifndef LCD_CONST_H
#define LCD_CONST_H

#include <xc.h>

#define LCD_STARTUP        120000UL // Start up delay = 30ms -> cycles for __delay32

#define INCREMENT          1
#define DECREMENT          0
#define DISPLAY_SHIFT_ON   1
#define DISPLAY_SHIFT_OFF  0
#define DISPLAY_ON         1
#define DISPLAY_OFF        0
#define CURSOR_DISPLAY_ON  1
#define CURSOR_DISPLAY_OFF 0
#define CURSOR_BLINK_ON    1
#define CURSOR_BLINK_OFF   0
#define SHIFT_DISPLAY      1
#define MOVE_CURSOR        0
#define SHIFT_RIGHT        1
#define SHIFT_LEFT         0
#define EIGHT_BIT          1
#define FOUR_BIT           0
#define DUAL_LINE          1
#define SINGLE_LINE        0
#define TEN_DOTS           1
#define FIVE_DOTS          0

#endif // LCD_CONST_H
