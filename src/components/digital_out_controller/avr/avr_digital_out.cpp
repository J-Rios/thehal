
/**
 * @file    avr_digital_out.cpp
 * @author  Jose Miguel Rios Rubio <jrios.github@gmail.com>
 * @date    26-09-2020
 * @version 1.0.0
 *
 * @section DESCRIPTION
 *
 * GPIO Digital Output Controller for AVR devices.
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
#if defined(__AVR__) and !defined(ARDUINO)

/*****************************************************************************/

/* Libraries */

#include "avr_digital_out.h"

#include <avr/io.h>

/*****************************************************************************/

/* Constants */
typedef enum
{
    UNDEFINED = -1
} the_hal_digital_out_constants;


/* Ease Macros */

#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define getDDR(port_pin) ((uint8_t)((port_pin >> 8 ) & 0x00ff))
#define getPORT(port_pin) ((uint8_t)((port_pin >> 8 ) & 0x00ff))
#define getPIN(port_pin) ((uint8_t)(port_pin & 0x00ff))

/*****************************************************************************/

/* Constructor */

/* DigitalOut constructor */
DigitalOut::DigitalOut()
{
    this->io_pin = 0;
    this->io_val = UNDEFINED;
}

/* DigitalOut destructor */
DigitalOut::~DigitalOut()
{}

/*****************************************************************************/

/* Public Methods */

/* Initialize GPIO as digital output and set them to an initial logic value */
bool DigitalOut::setup(const uint16_t io_pin, const uint8_t initial_value)
{
    if(is_a_invalid_digital_value(initial_value))
        return false;

    this->io_pin = io_pin;
    this->io_val = initial_value;
    this->digitalWrite(this->io_pin, (uint8_t)this->io_val);
    this->pinMode(this->io_pin, 1);

    return true;
}

/* Set GPIO digital out value to logical low */
bool DigitalOut::set_low(void)
{
    if(gpio_is_not_initialized())
        return false;

    this->io_val = 0;
    this->digitalWrite(this->io_pin, (uint8_t)this->io_val);

    return true;
}

/* Set GPIO digital out value to logical high */
bool DigitalOut::set_high(void)
{
    if(gpio_is_not_initialized())
        return false;

    this->io_val = 1;
    this->digitalWrite(this->io_pin, (uint8_t)this->io_val);

    return true;
}

/*****************************************************************************/

/* Private Methods */

/* Check if GPIO is not configured (setup() was not called). */
bool DigitalOut::gpio_is_not_initialized(void)
{
    if(this->io_val == UNDEFINED)
        return true;
    return false;
}

/* Check if provided value is not a valid digital value */
bool DigitalOut::is_a_invalid_digital_value(const uint8_t value)
{
    if((value != 0) && (value != 1))
        return true;
    return false;
}

/* Low Level function to setup pin through Registers */
void DigitalOut::pinMode(const uint16_t port_pin, const uint8_t val)
{
    // "DDR" should be specified in MSB byte of "port_pin"
    // "Pin" should be specified in LSB byte of "port_pin"
    // i.e. port_pin = ((DDRB) << 8) | PB0);
    uint8_t port = getPORT(port_pin);
    uint8_t pin = getPIN(port_pin);
    if(val == 0)
        bitClear(port, pin); // Digital Input
    else
        bitSet(port, pin); // Digital Output
}

/* Low Level function to setup digital out pin value through Registers */
void DigitalOut::digitalWrite(const uint16_t port_pin, const uint8_t val)
{
    // "Port" should be specified in MSB byte of "port_pin"
    // "Pin" should be specified in LSB byte of "port_pin"
    // i.e. port_pin = ((PORTB) << 8) | PB0);
    uint8_t port = getPORT(port_pin);
    uint8_t pin = getPIN(port_pin);
    if(val == 0)
        bitClear(port, pin); // Set to LOW
    else
        bitSet(port, pin); // Set to HIGH
}

/*****************************************************************************/

#endif /* defined(__AVR__) and !defined(ARDUINO) */
