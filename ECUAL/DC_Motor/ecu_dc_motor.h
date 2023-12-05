/*
 * File:   dc_motor.h
 * Author: Mahmoud Khaled
 *
 * Created on October 11, 2023, 3:43 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

/* Section: Includes */
#include "../../MCAL/GPIO/hal_gpio.h"
#include "ecu_dc_motor_cfg.h"

/* Section: Macros */

/* Section: Function Like Macro Declarations */

/* Section: Data Types Declarations */

/**
 * @enum dc_motor_status_t
 * @brief Enumeration representing the status of a DC motor pin.
 */
typedef enum
{
    DC_MOTOR_PIN_OFF, /**< DC motor pin is turned off. */
    DC_MOTOR_PIN_ON   /**< DC motor pin is turned on. */
} dc_motor_status_t;

/**
 * @enum dc_motor_pin_index_t
 * @brief Enumeration representing the index of DC motor pins.
 */
typedef enum
{
    IN1, /**< Index for the first input pin of the DC motor module. */
    IN2  /**< Index for the second input pin of the DC motor module. */
} dc_motor_pin_index_t;

/**
 * @struct dc_motor_pin_t
 * @brief Structure representing a DC motor pin configuration.
 */
typedef struct
{
    uint8 dc_motor_port : 3;       /**< Port to which the DC motor pin is connected. */
    uint8 dc_motor_pin : 3;        /**< Pin number on the selected port. */
    uint8 dc_motor_pin_status : 1; /**< Status of the DC motor pin (ON or OFF). */
    uint8 reserved : 1;            /**< Reserved for future use. */
} dc_motor_pin_t;

/**
 * @struct dc_motor_t
 * @brief Structure representing a DC motor configuration, including two pins.
 */
typedef struct
{
    dc_motor_pin_t motor_pins[2]; /**< Array of two DC motor pins for control. */
} dc_motor_t;

/* Section: Functions Declarations */

/**
 * @brief Initializes the DC motor configuration.
 *
 * This function initializes the DC motor pins and associated configuration.
 *
 * @param dc_motor Pointer to the DC motor configuration to initialize.
 * @return Standard Return Type (@ref Std_ReturnType):
 *         - @ref E_OK: The motor was initialized successfully.
 *         - @ref E_NOT_OK: Initialization of the motor failed.
 *  */
Std_ReturnType dc_motor_init(const dc_motor_t *const dc_motor);

/**
 * @brief Moves the DC motor to the right.
 *
 * This function controls the DC motor to move in the right direction.
 *
 * @param dc_motor Pointer to the DC motor configuration to control.
 * @return Standard Return Type (@ref Std_ReturnType):
 *         - @ref E_OK: The motor is turning right successfully.
 *         - @ref E_NOT_OK: Turning motor to right failed.
 *  */
Std_ReturnType dc_motor_move_right(dc_motor_t *const dc_motor);

/**
 * @brief Moves the DC motor to the left.
 *
 * This function controls the DC motor to move in the left direction.
 *
 * @param dc_motor Pointer to the DC motor configuration to control.
 * @return Standard Return Type (@ref Std_ReturnType):
 *         - @ref E_OK: The motor is turning left successfully.
 *         - @ref E_NOT_OK: Turning motor to left failed. 
 */
Std_ReturnType dc_motor_move_left(dc_motor_t *const dc_motor);

/**
 * @brief Stops the DC motor.
 *
 * This function stops the DC motor, halting its movement.
 *
 * @param dc_motor Pointer to the DC motor configuration to control.
 * @return Standard Return Type (@ref Std_ReturnType):
 *         - @ref E_OK: The motor is stopped successfully.
 *         - @ref E_NOT_OK: Stopping the motor failed. 
 *  */
Std_ReturnType dc_motor_stop(dc_motor_t *const dc_motor);

#endif  /* ECU_DC_MOTOR_H */
