/* 
 * File:   ecu_seven_seg.h
 * Author: Blu-Ray
 *
 * Created on October 13, 2023, 8:31 PM
 */

#ifndef ECU_SEVEN_SEG_H
#define	ECU_SEVEN_SEG_H

/* Section: Includes */
#include "ecu_seven_seg_cfg.h"
#include "../../MCAL/GPIO/hal_gpio.h"

/* Section: Macros */

/* Section: Function Like Macro Declarations */

/* Section: Data Types Declarations */

/**
 * @enum segment_pin_status_t
 * @brief Enumeration representing the status of a segment pin (ON or OFF).
 */
typedef enum
{
    SEGMENT_PIN_OFF, /**< Segment pin is turned off. */
    SEGMENT_PIN_ON   /**< Segment pin is turned on. */
} segment_pin_status_t;

/**
 * @enum segment_pin_index_t
 * @brief Enumeration representing the indexes of segment pins (A, B, C, D).
 */
typedef enum
{
    A, /**< Segment pin A. */
    B, /**< Segment pin B. */
    C, /**< Segment pin C. */
    D  /**< Segment pin D. */
} segment_pin_index_t;

/**
 * @enum segment_type_t
 * @brief Enumeration representing the type of seven-segment display (common anode or common cathode).
 */
typedef enum
{
    SEGMENT_COMMON_ANODE,   /**< Common anode seven-segment display. */
    SEGMENT_COMMON_CATHODE, /**< Common cathode seven-segment display. */
} segment_type_t;

/**
 * @struct segment_pin_t
 * @brief Structure representing a single segment pin's configuration.
 */
typedef struct 
{
    uint8 segment_port : 3;       /**< Port to which the segment pin is connected. */
    uint8 segment_pin : 3;        /**< Pin number within the port. */
    uint8 segment_pin_status : 1; /**< Status of the segment pin (ON or OFF). */
    uint8 reserved : 1;           /**< Reserved field. */
} segment_pin_t;

/**
 * @struct segment_t
 * @brief Structure representing the configuration of a seven-segment display.
 */
typedef struct
{
    segment_pin_t segment_pins[4]; /**< Configuration for each of the four segment pins. */
    segment_type_t segment_type;   /**< Type of seven-segment display (common anode or common cathode). */
} segment_t;

/* Section: Functions Declarations */

/**
 * @brief Initialize a seven-segment display with the given configuration.
 * @param segment A pointer to a segment_t structure containing the configuration.
 * @return Status of the operation (@ref Std_ReturnType).
 *      Returns E_OK if the segment is successfully initialized.
 *      Returns E_NOT_OK if an error occurs during the initialization process.  
 */
Std_ReturnType segment_init(const segment_t *const segment);

/**
 * @brief Write a number to the seven-segment display.
 * @param segment A pointer to a segment_t structure representing the seven-segment display.
 * @param number The number to be displayed.
 * @return Status of the operation (@ref Std_ReturnType).
 *      Returns E_OK if writing the number is done successfully.
 *      Returns E_NOT_OK if an error occurs during the process.  
 */
Std_ReturnType segment_write_number(segment_t *const segment, uint8 number);

/**
 * @brief Multiplex one or more seven-segment displays using the same set of 4 pins.
 * @param segment A pointer to a segment_t structure representing the seven-segment display(s).
 * @param number_pins The number of pins to be used for multiplexing.
 * @param values An array of values to be displayed on the selected pins.
 * @param ... pin_config_t structures if multiple displays are connected.
 * @return Status of the operation (@ref Std_ReturnType).
 *      Returns E_OK if the multiplexing is done successfully.
 *      Returns E_NOT_OK if an error occurs during the multiplexing process.  
 */
Std_ReturnType multiplex(segment_t *const segment, uint8 number_pins, uint8 *values, ...);

#endif	/* ECU_SEVEN_SEG_H */
