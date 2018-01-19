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

#include "adc.h"

bool ADC_ChannelEnable(ADC_CHANNEL channel) {
    switch (channel) {
        case ADC_CHANNEL_5:
            AD1PCFGbits.PCFG5 = 0; /* ensure AN5/RB5 is analog (analog pot) */
            return true;
        case ADC_CHANNEL_4:
            AD1PCFGbits.PCFG4; /* ensure AN4/RB4 is analog (temp sensor) */
            return true;
        default:
            return false;
    }
}
