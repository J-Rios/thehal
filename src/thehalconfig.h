
/**
 * @file    thehalconfig.h
 * @author  Jose Miguel Rios Rubio <jrios.github@gmail.com>
 * @date    08-12-2020
 * @version 1.0.0
 *
 * @section DESCRIPTION
 *
 * TheHal Project Genral Configuration File to enable/disable components.
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

/**
 * You can create a custom thehalconfig.h in your project with the specific
 * configuration that you needs in your project (to save memory, only enable
 * the components that you need). Note that you need to include thehalconfig.h
 * before thehal.h.
 * 
 * If you don't specify a custom thehalconfig.h, a built-in default one with
 * all components enabled will be used.
 * 
 * The use of the next include guards allows the user to use a custom
 * thehalconfig.h file in their project with specific components enabled, and
 * it will have an higher priority than the default one.
*/

/*****************************************************************************/

/* Include Guard */
#ifndef THE_HAL_CONFIG_H_
#define THE_HAL_CONFIG_H_

#warning "thehalconfig.h default"

/*****************************************************************************/

/* TheHal General Configurations */

/* Enable/Disable "Digital Output Controller" Component */
#ifndef THE_HAL_COMPONENT_DIGITAL_OUT
    #define THE_HAL_COMPONENT_DIGITAL_OUT 1
#endif

/* Enable/Disable "Digital Input Controller" Component */
#ifndef THE_HAL_COMPONENT_DIGITAL_IN
    #define THE_HAL_COMPONENT_DIGITAL_IN 1
#endif

/* Enable/Disable "Time Controller" Component */
#ifndef THE_HAL_COMPONENT_TIME
    #define THE_HAL_COMPONENT_TIME 1
#endif

/* Enable/Disable "RF Controller" Component */
#ifndef THE_HAL_COMPONENT_RF
    #define THE_HAL_COMPONENT_RF 1
#endif

/*****************************************************************************/

#endif /* THE_HAL_CONFIG_H_ */
