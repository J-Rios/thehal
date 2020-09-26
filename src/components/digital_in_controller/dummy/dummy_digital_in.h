
/**
 * @file    dummy_digital_in.h
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

/* Guards */

/* Include Guard */
#ifndef THE_HAL_DUMMY_DIGITAL_IN_H_
#define THE_HAL_DUMMY_DIGITAL_IN_H_

/*****************************************************************************/

/* Libraries */

#include <stdint.h>
#include <stdbool.h>

/*****************************************************************************/

/* Constants */


/*****************************************************************************/

/* Class */

class DigitalIn
{
    public:
        DigitalIn(const int8_t _io_pin);
        ~DigitalIn();

        bool setup(const uint8_t pull_resistor_mode=NONE);
        bool read(void);
};

/*****************************************************************************/

#endif /* THE_HAL_DUMMY_DIGITAL_IN_H_ */
