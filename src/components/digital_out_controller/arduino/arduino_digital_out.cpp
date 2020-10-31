
/**
 * @file    arduino_digital_out.cpp
 * @author  Jose Miguel Rios Rubio <jrios.github@gmail.com>
 * @date    26-09-2020
 * @version 1.0.0
 *
 * @section DESCRIPTION
 *
 * GPIO Digital Output Controller for Arduino devices.
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

#include "arduino_digital_out.h"

/*****************************************************************************/

/* Constants */

typedef enum
{
    UNDEFINED = -1
} the_hal_digital_out_constants;

/*****************************************************************************/

/* Constructor */

/* DigitalOut constructor */
DigitalOut::DigitalOut(const int8_t io_pin)
{
    this->io_pin = io_pin;
    this->io_val = UNDEFINED;
}

/* DigitalOut destructor */
DigitalOut::~DigitalOut()
{}

/*****************************************************************************/

/* Public Methods */

/* Initialize GPIO as digital output and set them to an initial logic value */
bool DigitalOut::setup(const uint8_t initial_value)
{
    if(is_a_invalid_digital_value(initial_value))
        return false;

    this->io_val = initial_value;
    digitalWrite((uint8_t)this->io_pin, (uint8_t)this->io_val);
    pinMode((uint8_t)this->io_pin, OUTPUT);

    return true;
}

/* Set GPIO digital out value to logical low */
bool DigitalOut::set_low(void)
{
    if(gpio_is_not_initialized())
        return false;

    this->io_val = LOW;
    digitalWrite((uint8_t)this->io_pin, (uint8_t)this->io_val);

    return true;
}

/* Set GPIO digital out value to logical high */
bool DigitalOut::set_high(void)
{
    if(gpio_is_not_initialized())
        return false;

    this->io_val = HIGH;
    digitalWrite((uint8_t)this->io_pin, (uint8_t)this->io_val);

    return true;
}

/*****************************************************************************/

/* Private Methods */

/* Check if GPIO is not configured (setup() was not called). */
bool DigitalOut::gpio_is_not_initialized(void)
{
    if(this->io_val != UNDEFINED)
        return false;
    return true;
}

/* Check if provided value is not a valid digital value */
bool DigitalOut::is_a_invalid_digital_value(const uint8_t value)
{
    if((value == LOW) || (value == HIGH))
        return false;
    return true;
}

/*****************************************************************************/

#endif

/*****************************************************************************/
