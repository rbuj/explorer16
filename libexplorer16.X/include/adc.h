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

#ifndef ADC_H
#define ADC_H

#include <xc.h>
#include <stdbool.h>

/* ADC Channel Definitions */
#define ADC_CHANNEL_POTENTIOMETER ADC_CHANNEL_5
#define ADC_CHANNEL_TEMPERATURE_SENSOR ADC_CHANNEL_4

typedef enum { ADC_CHANNEL_5 = 5, ADC_CHANNEL_4 = 4 } ADC_CHANNEL;

bool ADC_ChannelEnable(ADC_CHANNEL channel);

#endif /* ADC_H */