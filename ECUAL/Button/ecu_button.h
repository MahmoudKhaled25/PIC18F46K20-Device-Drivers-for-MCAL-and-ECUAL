/* 
 * File:   push_button.h
 * Author: Mahmoud Khaled
 *
 * Created on October 2, 2023, 1:46 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/*Section: Includes*/
#include "../../MCAL/GPIO/hal_gpio.h"
#include "ecu_button_cfg.h"

/*Section: Macros*/


/*Section: Function Like Macro Declarations*/

/*Section: Data Types Declarations*/
typedef enum button_state
{
    BUTTON_RELEASED,
    BUTTON_PRESSED
}button_state_t;

typedef enum button_active
{
    BUTTON_ACTIVE_LOW,
    BUTTON_ACTIVE_HIGH
}button_active_t;

typedef struct button
{
    uint8 port_index   : 3;    // Index of the GPIO port used for the Button.
    uint8 pin_index    : 3;    // Index of the GPIO pin used for the Button.
    uint8 button_state : 1;        // Current state of the button (pressed or released)
    uint8 button_connection : 1;  // Active level of the button (active low or active high)
}button_t;

/*Section: Functions Declarations*/

/**
 * Initializes a button with the given configuration.
 * 
 * @param button A pointer to a button_t struct containing the button's configuration.
 * @return Standard Return Type (@ref Std_ReturnType):
 *         - @ref E_OK: The button was initialized successfully.
 *         - @ref E_NOT_OK: Initialization of the button failed.
 */
Std_ReturnType button_init(const button_t *const button);

/**
 * Reads the state of a button (pressed or released).
 * 
 * @param button A pointer to a button_t struct representing the button.
 * @param button_state A pointer to a button_state_t variable where the button state will be stored.
 *  * @return Standard Return Type (@ref Std_ReturnType):
 *         - @ref E_OK: The button status was read successfully.
 *         - @ref E_NOT_OK: Reading button status failed.
 */
Std_ReturnType button_read_state(button_t *const button, button_state_t *const button_state);

#endif	/* ECU_BUTTON_H */

