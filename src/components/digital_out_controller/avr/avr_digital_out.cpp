
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

/* Libraries */

#include "avr_digital_out.h"

#include <avr/io.h>

/*****************************************************************************/

/* Ease Macros */

#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define getDDR(port_pin) ((uint8_t)((port_pin >> 8 ) & 0x00ff))
#define getPORT(port_pin) ((uint8_t)((port_pin >> 8 ) & 0x00ff))
#define getPIN(port_pin) ((uint8_t)(port_pin & 0x00ff))

/* Defines */

#define OUTPUT 1
#define LOW  0
#define HIGH 1
#define UNDEFINED -1

/*****************************************************************************/

/* Constructor */

/* DigitalOut constructor */
DigitalOut::DigitalOut(const uint16_t io_pin)
{
    this->io_pin = io_pin;
    this->io_val = -1;
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
    this->digitalWrite(this->io_pin, (uint8_t)this->io_val);
    this->pinMode(this->io_pin, 1);

    return true;
}

/* Set GPIO digital out value to logical low */
bool DigitalOut::set_low(void)
{
    if(gpio_is_not_initialized())
        return false;

    this->io_val = LOW;
    this->digitalWrite(this->io_pin, (uint8_t)this->io_val);

    return true;
}

/* Set GPIO digital out value to logical high */
bool DigitalOut::set_high(void)
{
    if(gpio_is_not_initialized())
        return false;

    this->io_val = HIGH;
    this->digitalWrite(this->io_pin, (uint8_t)this->io_val);

    return true;
}

/*****************************************************************************/

/* Private Methods */

/* Check if GPIO is not configured (setup() was not called). */
bool DigitalOut::gpio_is_not_initialized(void)
{
    if(this->io_val == UNDEFINED)
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

/* Low Level function to setup pin through Registers */
void DigitalOut::pinMode(const uint16_t port_pin, const uint8_t val)
{
    // "DDR" should be specified in MSB byte of "port_pin"
    // "Pin" should be specified in LSB byte of "port_pin"
    // i.e. port_pin = ((DDRB) << 8) | PB0);
    uint8_t data_direction_register = getDDR(port_pin);
    if(val == 0)
        bitClear(data_direction_register, pin);
    else
        bitSet(data_direction_register, pin);
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
        bitClear(port, pin);
    else
        bitSet(port, pin);
}

/*****************************************************************************/
