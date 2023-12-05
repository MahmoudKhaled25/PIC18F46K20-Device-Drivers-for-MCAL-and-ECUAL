/* 
 * File:   ecu_led.h
 * Author: Mahmoud Khaled
 *
 * Created on September 19, 2023, 9:45 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section: Includes */
#include "../../MCAL/GPIO/hal_gpio.h"   // Include the GPIO hardware abstraction layer header.
#include "ecu_led_cfg.h"                 // Include the configuration header for ECU LED settings.

/* Section: Macros */

/* Section: Function Like Macro Declarations */

/* 
 * Section: Data Types Declarations
 *
 * This section defines the data types used in the ECU LED module.
 */

// Enumeration representing LED status (ON or OFF).
typedef enum 
{
    LED_OFF, // LED is turned off.
    LED_ON   // LED is turned on.
} led_status_t;

// Structure representing an LED.
typedef struct LED
{
    uint8 port_index   : 3;    // Index of the GPIO port used for the LED.
    uint8 pin_index    : 3;    // Index of the GPIO pin used for the LED.
    uint8 led_status   : 1;    // Current status of the LED (ON or OFF). See @ref led_status_t.
    uint8 reserved     : 1;    // Reserved for future use.
} led_t;

/* 
 * Section: Functions Declarations
 *
 * This section declares functions provided by the ECU LED module for LED control.
 */

/**
 * @brief Initialize an LED.
 *
 * This function initializes the specified LED using the provided LED structure.
 *
 * @param  led A pointer to the LED structure representing the LED to be initialized.
  * @return Standard Return Type (@ref Std_ReturnType):
 *         - @ref E_OK: The led was initialized successfully.
 *         - @ref E_NOT_OK: Initialization of the led failed.
 */
Std_ReturnType led_initialize(const led_t *const led);

/**
 * @brief Turn off an LED.
 *
 * This function turns off the specified LED.
 *
 * @param  led A pointer to the LED structure representing the LED to be turned off.
  * @return Standard Return Type (@ref Std_ReturnType):
 *         - @ref E_OK: The led was turned off successfully.
 *         - @ref E_NOT_OK: Turning off the led failed.
 */
Std_ReturnType led_turn_off(led_t *const led);

/**
 * @brief Turn on an LED.
 *
 * This function turns on the specified LED.
 *
 * @param  led A pointer to the LED structure representing the LED to be turned on.
  * @return Standard Return Type (@ref Std_ReturnType):
 *         - @ref E_OK: The led was turned on successfully.
 *         - @ref E_NOT_OK: Turning on the led failed.
 */
Std_ReturnType led_turn_on(led_t *const led);

/**
 * @brief Toggle an LED.
 *
 * This function toggles the state of the specified LED, turning it on if it's off and vice versa.
 *
 * @param  led A pointer to the LED structure representing the LED to be toggled.
  * @return Standard Return Type (@ref Std_ReturnType):
 *         - @ref E_OK: The led state was toggled successfully.
 *         - @ref E_NOT_OK: Toggling the led state failed
 */
Std_ReturnType led_toggle(led_t *const led);

#endif	/* ECU_LED_H */
