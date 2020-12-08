
/**
 * @file    dummy_digital_out.h
 * @author  Jose Miguel Rios Rubio <jrios.github@gmail.com>
 * @date    26-09-2020
 * @version 1.0.0
 *
 * @section DESCRIPTION
 *
 * Dummy GPIO Digital Output Controller.
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

/* Build Guard */
#if !defined(ARDUINO) and !defined(ESP_IDF) and !defined(SAM_ASF) and \
    !defined(__AVR__)

/*****************************************************************************/

/* Libraries */

#include "dummy_digital_out.h"

/*****************************************************************************/

/* Constructor */

/* DigitalOut constructor */
DigitalOut::DigitalOut()
{}

/* DigitalOut destructor */
DigitalOut::~DigitalOut()
{}

/*****************************************************************************/

/* Public Methods */

/* Initialize GPIO as digital output and set them to an initial logic value */
bool DigitalOut::setup(const int8_t _io_pin, const uint8_t initial_value)
{ return true; }

/* Set GPIO digital out value to logical low */
bool DigitalOut::set_low(void)
{ return true; }

/* Set GPIO digital out value to logical high */
bool DigitalOut::set_high(void)
{ return true; }

/*****************************************************************************/

/* Private Methods */


/*****************************************************************************/

#endif /* !defined(ARDUINO) and !defined(ESP_IDF) and ... */
