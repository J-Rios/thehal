
/**
 * @file    espidf_time_controller.h
 * @author  Jose Miguel Rios Rubio <jrios.github@gmail.com>
 * @date    08-12-2020
 * @version 1.0.0
 *
 * @section DESCRIPTION
 *
 * Time related functionalities Controller for ESP-IDF devices (i.e. ESP32).
 *
 * @section LICENSE
 *
 * Copyright (c) 2020 Jose Miguel Rios Rubio. All right reserved.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

/*****************************************************************************/

/* Guards */

/* Include Guard */
#ifndef THE_HAL_ESPIDF_TIME_H_
#define THE_HAL_ESPIDF_TIME_H_

/*****************************************************************************/

/* Libraries */

#include <stdint.h>

/*****************************************************************************/

/* Constants */


/*****************************************************************************/

/* Class */

class Time
{
    public:
        Time();
        ~Time();

        void setup(void);
        uint32_t micros(void);
        uint32_t millis(void);
        void delay_us(const uint32_t t_delay_us);
        void delay_ms(const uint32_t t_delay_ms);
};

/*****************************************************************************/

#endif /* THE_HAL_ESPIDF_TIME_H_ */
