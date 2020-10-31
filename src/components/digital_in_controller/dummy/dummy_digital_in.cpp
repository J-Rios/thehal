
/**
 * @file    arduino_digital_in.h
 * @author  Jose Miguel Rios Rubio <jrios.github@gmail.com>
 * @date    26-09-2020
 * @version 1.0.0
 *
 * @section DESCRIPTION
 *
 * Dummy GPIO Digital Input Controller.
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

#if !defined(ARDUINO) and !defined(ESP_IDF) and !defined(SAM_ASF) and \
    !defined(__AVR__)

/*****************************************************************************/

/* Libraries */

#include "dummy_digital_in.h"

/*****************************************************************************/

/* Constants */

typedef enum
{
    UNDEFINED = -1,
    NONE = 0,
    PULLUP = 1,
    PULLDOWN = 2
} the_hal_digital_in_constants;

/*****************************************************************************/

/* Constructor */

/* DigitalIn constructor */
DigitalIn::DigitalIn(const int8_t _io_pin)
{}

/* DigitalIn destructor */
DigitalIn::~DigitalIn()
{}

/*****************************************************************************/

/* Public Methods */

/* Initialize GPIO as digital input and set internal pull resistor */
bool DigitalIn::setup(const uint8_t pull_resistor_mode)
{ return true; }

/* Get GPIO digital input logical value */
bool DigitalIn::read(void)
{ return true; }

/*****************************************************************************/

/* Private Methods */


/*****************************************************************************/

#endif /* !defined(ARDUINO) and !defined(ESP_IDF) and .. */

/*****************************************************************************/
