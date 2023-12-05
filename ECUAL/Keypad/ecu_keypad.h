/* 
 * File:   ecu_keypad.h
 * Author: Blu-Ray
 *
 * Created on October 25, 2023, 2:38 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/*Section: Includes*/
#include "../../MCAL/GPIO/hal_gpio.h"
#include "ecu_keypad_cfg.h"

/*Section: Macros*/
#define KEYPAD_ROWS 4
#define KEYPAD_COLUMNS 3

#if (KEYPAD_ROWS * KEYPAD_COLUMNS) == SIXTEEN_BUTTON
#define KEYPAD_4X4_CONFIG CONFIG_ENABLE
#define KEYPAD_4X3_CONFIG CONFIG_DISABLE
#elif (KEYPAD_ROWS * KEYPAD_COLUMNS) == TWELVE_BUTTON
#define KEYPAD_4X4_CONFIG CONFIG_DISABLE
#define KEYPAD_4X3_CONFIG CONFIG_ENABLE
#else
#define KEYPAD_4X4_CONFIG CONFIG_DISABLE
#define KEYPAD_4X3_CONFIG CONFIG_DISABLE
#error Undefined Keypad Configuration
#endif

/*Section: Function Like Macro Declarations*/

/*Section: Data Types Declarations*/
typedef enum
{
    R0,
    R1,
    R2,
    R3
}row_index_t;

typedef enum
{
    C0,
    C1,
    C2,
    C3
}column_index_t;

typedef enum
{
    KEYPAD_ACTIVE_LOW,
    KEYPAD_ACTIVE_HIGH
}keypad_type_t;

typedef struct 
{
    uint8 port_index : 3;
    uint8 pin_index : 3;
    uint8 reserved : 2;
}keypad_pin_t;


typedef struct 
{
    keypad_pin_t keypad_row_pins[KEYPAD_ROWS];
    keypad_pin_t keypad_column_pins[KEYPAD_COLUMNS];
    keypad_type_t keypad_type;
}keypad_t;

/*Section: Functions Declarations*/

/**
 * 
 * @param keypad
 * @return 
 */
Std_ReturnType keypad_init(const keypad_t *const keypad);

/**
 * 
 * @param keypad
 * @param read
 * @return 
 */
Std_ReturnType keypad_read_button(const keypad_t *const keypad, uint8 *read);
#endif	/* ECU_KEYPAD_H */

