
/**
 * @file    arduino_time_controller.cpp
 * @author  Jose Miguel Rios Rubio <jrios.github@gmail.com>
 * @date    08-12-2020
 * @version 1.0.0
 *
 * @section DESCRIPTION
 *
 * Time related functionalities Controller for Arduino devices.
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

/* Build Guard */

#if defined(ARDUINO)

/*****************************************************************************/

/* Libraries */

#include "arduino_time_controller.h"

#include <Arduino.h>

/*****************************************************************************/

/* Constants */


/*****************************************************************************/

/* Constructor & Destructor */

/* Time constructor */
Time::Time()
{}

/* Time destructor */
Time::~Time()
{}

/*****************************************************************************/

/* Public Methods */

/**
  * @brief  Setup and initialize timers for system tick control.
  */
void Time::setup(void)
{}

/**
  * @brief  Get current system tick in microseconds.
  * @return How many microseconds has passed after system tick initialization.
  */
uint32_t Time::micros(void)
{
    return (uint32_t)(micros());
}

/**
  * @brief  Get current system tick in milliseconds.
  * @return How many milliseconds has passed after system tick initialization.
  */
uint32_t Time::millis(void)
{
    return (uint32_t)(millis());
}

/**
  * @brief  Delay execution for some microseconds.
  * @param  t_delay_us Number of microseconds to delay.
  */
void Time::delay_us(const uint32_t t_delay_us)
{
    delayMicroseconds((unsigned int)(t_delay_us));
}

/**
  * @brief  Delay execution for some milliseconds.
  * @param  t_delay_ms Number of milliseconds to delay.
  */
void Time::delay_ms(const uint32_t t_delay_ms)
{
    delay((unsigned long)(t_delay_ms));
}

/*****************************************************************************/

/* Private Methods */


/*****************************************************************************/

#endif /* defined(ARDUINO) */

/*****************************************************************************/
