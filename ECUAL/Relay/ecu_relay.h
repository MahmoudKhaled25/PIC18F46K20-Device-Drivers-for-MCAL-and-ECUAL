/* 
 * File:   ecu_relay.h
 * Author: Mahmoud Khaled
 *
 * Created on October 5, 2023, 7:22 PM
 */

#ifndef _ECU_RELAY_H_
#define _ECU_RELAY_H_

/* Section: Includes */
#include "ecu_relay_cfg.h"      // Include the configuration header for the relay module.
#include "../../MCAL/GPIO/hal_gpio.h"  // Include the GPIO hardware abstraction layer header.

/* Section: Macros */

/* Section: Function Like Macro Declarations */

/* Section: Data Types Declaration */

/**
 * @enum relay_status
 * @brief Enumeration representing the possible states of a relay.
 */
typedef enum relay_status
{
    RELAY_OFF,   // Relay is in the OFF state.
    RELAY_ON     // Relay is in the ON state.
} relay_status_t;

/**
 * @struct relay
 * @brief Structure representing a relay module.
 */
typedef struct relay
{
    uint8 port_index : 3;       // Index of the GPIO port used for the relay.
    uint8 pin_index : 3;        // Index of the GPIO pin used for the relay.
    uint8 relay_status : 1;     // Current status of the relay (ON or OFF).
    uint8 reserved : 1;         // Reserved for future use.
} relay_t;

/* Section: Functions Declarations */

/**
 * @brief Initialize a relay module.
 *
 * This function initializes a relay module based on the provided relay_t structure.
 *
 * @param relay A pointer to a relay_t structure representing the relay to initialize.
 * @return Standard Return Type (@ref Std_ReturnType):
 *         - @ref E_OK: The relay was initialized successfully.
 *         - @ref E_NOT_OK: Initialization of the relay failed.
 */
Std_ReturnType relay_init(const relay_t *const relay);

/**
 * @brief Turn off a relay module.
 *
 * This function turns off the relay specified in the relay_t structure.
 *
 * @param relay A pointer to a relay_t structure representing the relay to turn off.
 * @return Standard Return Type (@ref Std_ReturnType):
 *         - @ref E_OK: The relay was turned off successfully.
 *         - @ref E_NOT_OK: Turning off the relay failed.
 */
Std_ReturnType relay_turn_off(relay_t *const relay);

/**
 * @brief Turn on a relay module.
 *
 * This function turns on the relay specified in the relay_t structure.
 *
 * @param relay A pointer to a relay_t structure representing the relay to turn on.
 * @return Standard Return Type (@ref Std_ReturnType):
 *         - @ref E_OK: The relay was turned on successfully.
 *         - @ref E_NOT_OK: Turning on the relay failed.
 */
Std_ReturnType relay_turn_on(relay_t *const relay);

/**
 * @brief Toggle the state of a relay module.
 *
 * This function toggles the state (ON to OFF or OFF to ON) of the relay specified in the relay_t structure.
 *
 * @param relay A pointer to a relay_t structure representing the relay to toggle.
 * @return Standard Return Type (@ref Std_ReturnType):
 *         - @ref E_OK: The relay state was toggled successfully.
 *         - @ref E_NOT_OK: Toggling the relay state failed.
 */
Std_ReturnType relay_toggle(relay_t *const relay);

#endif /* _ECU_RELAY_H_ */
