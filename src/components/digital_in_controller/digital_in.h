
/**
 * @file    digital_in.h
 * @author  Jose Miguel Rios Rubio <jrios.github@gmail.com>
 * @date    26-09-2020
 * @version 1.0.0
 *
 * @section DESCRIPTION
 *
 * GPIO Digital Input Controller.
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

/* Component Enabled/Disabled Guard */
#if THE_HAL_COMPONENT_DIGITAL_IN == 1

/* Include Guard */
#ifndef THE_HAL_DIGITAL_IN_H_
#define THE_HAL_DIGITAL_IN_H_

/*****************************************************************************/

/* Component Configurations */


/*****************************************************************************/

/* HAL Selection */

#if defined(ARDUINO)
    #include "arduino/arduino_digital_in.h"
#elif defined(ESP_IDF)
    #include "espidf/espidf_digital_in.h"
#elif defined(SAM_ASF)
    #include "sam_asf/sam_asf_digital_in.h"
#elif defined(__AVR__)
    #include "avr/avr_digital_in.h"
#else
    #include "dummy/dummy_digital_in.h"
#endif

/*****************************************************************************/

#endif // THE_HAL_DIGITAL_IN_H_
#endif // THE_HAL_COMPONENT_DIGITAL_IN
