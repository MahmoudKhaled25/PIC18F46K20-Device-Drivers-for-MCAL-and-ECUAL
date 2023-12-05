/* 
 * File:   hal_gpio.h
 * Author: Mahmoud_Khaled
 *
 * Created on September 19, 2023, 8:13 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/* Section: Includes */
#include "../device_config.h"
#include "../mcal_std_types.h"
#include "hal_gpio_cfg.h"

/* Section: Macros */
#define MASK_BIT 0x01
#define PORT_MAX_NUM PORTE_INDEX
#define PIN_MAX_NUM  PIN7


// Configurations
#define GPIO_PORT_PIN_CONFIGURATION CONFIG_ENABLE
#define GPIO_PORT_CONFIGURATION     CONFIG_ENABLE

/* Section: Function-like Macro Declarations */

// Sets a bit at the specified position in a memory location
#define SET_BIT(MEMORY, POS)    ((MEMORY) |= (MASK_BIT << (POS)))  

// Clears a bit at the specified position in a memory location
#define CLEAR_BIT(MEMORY, POS)  ((MEMORY) &= ~(MASK_BIT << (POS)))   

// Toggles a bit at the specified position in a memory location
#define TOGGLE_BIT(MEMORY, POS) ((MEMORY) ^= (MASK_BIT << (POS))) 

// Reads the value of a bit at the specified position in a memory location
#define READ_BIT(MEMORY, POS)   (((MEMORY) >> (POS)) & MASK_BIT)      

/* Section: Data Types Declarations */
typedef enum 
{
    PORTA_INDEX,    // Port A index
    PORTB_INDEX,    // Port B index
    PORTC_INDEX,    // Port C index
    PORTD_INDEX,    // Port D index
    PORTE_INDEX     // Port E index
} port_index_t;

typedef enum 
{
    PIN0,   // Pin 0 index
    PIN1,   // Pin 1 index
    PIN2,   // Pin 2 index
    PIN3,   // Pin 3 index
    PIN4,   // Pin 4 index
    PIN5,   // Pin 5 index
    PIN6,   // Pin 6 index
    PIN7    // Pin 7 index
} pin_index_t;

typedef enum 
{
    GPIO_OUTPUT,    // GPIO pin as output
    GPIO_INPUT      // GPIO pin as input
} pin_direction_t;

typedef enum 
{
    GPIO_LOW,   // GPIO pin logic low
    GPIO_HIGH   // GPIO pin logic high
} pin_logic_t;

typedef struct
{
    uint8 port_index     : 3;  /* Port index (@ref port_index_t) */
    uint8 pin_index      : 3;  /* Pin index (@ref pin_index_t) */
    uint8 pin_direction  : 1;  /* Pin direction (@ref pin_direction_t) */
    uint8 logic          : 1;  /* Pin logic (@ref pin_logic_t) */
} pin_config_t;

/* Section: Functions Declarations */

/**
 * @brief Initializes the direction of a GPIO pin as input or output.
 *
 * @param _pin_config Pointer to the configuration structure for the GPIO pin (@ref pin_config_t).
 *
 * @return Status of the operation (@ref Std_ReturnType).
 *      Returns E_OK if the GPIO pin direction is successfully initialized.
 *      Returns E_NOT_OK if an error occurs during the initialization process.  
 */
Std_ReturnType gpio_pin_direction_initialize(const pin_config_t* _pin_config);

/**
 * @brief Retrieves the direction status of a GPIO pin.
 *
 * @param _pin_config Pointer to the configuration structure for the GPIO pin (@ref pin_config_t).
 * @param direction_status Pointer to store the direction status (@ref pin_direction_t).
 *
 * @return Status of the operation (@ref Std_ReturnType).
 *      Returns E_OK if the GPIO pin direction is successfully retrieved.
 *      Returns E_NOT_OK if an error occurs during the retrieval process.
 */
Std_ReturnType gpio_pin_get_direction(const pin_config_t* _pin_config, pin_direction_t* direction_status);

/**
 * @brief Writes the logic level (high or low) to a GPIO pin.
 *
 * @param _pin_config Pointer to the configuration structure for the GPIO pin (@ref pin_config_t).
 * @param logic The logic level to be written to the pin (@ref pin_logic_t).
 *
 * @return Status of the operation (@ref Std_ReturnType).
 *      Returns E_OK if the logic level is successfully written to the GPIO pin.
 *      Returns E_NOT_OK if an error occurs during the write operation.
 */
Std_ReturnType gpio_pin_write_logic(pin_config_t* _pin_config, pin_logic_t logic);

/**
 * @brief Reads the logic level (high or low) from a GPIO pin.
 *
 * @param _pin_config Pointer to the configuration structure for the GPIO pin (@ref pin_config_t).
 * @param logic Pointer to store the logic level read from the pin (@ref pin_logic_t).
 *
 * @return Status of the operation (@ref Std_ReturnType).
 *      Returns E_OK if the logic level is successfully read from the GPIO pin.
 *      Returns E_NOT_OK if an error occurs during the read operation.
 */
Std_ReturnType gpio_pin_read_logic(const pin_config_t* _pin_config, pin_logic_t* logic);

/**
 * @brief Toggles the logic level of a GPIO pin.
 *
 * @param _pin_config Pointer to the configuration structure for the GPIO pin (@ref pin_config_t).
 *
 * @return Status of the operation (@ref Std_ReturnType).
 *      Returns E_OK if the logic level of the GPIO pin is successfully toggled.
 *      Returns E_NOT_OK if an error occurs during the toggle operation.
 */
Std_ReturnType gpio_pin_toggle_logic(pin_config_t* _pin_config);

/**
 * @brief Initializes the configurationof a GPIO pin.
 *
 * @param _pin_config Pointer to the configuration structure for the GPIO pin (@ref pin_config_t).
 *
 * @return Status of the operation (@ref Std_ReturnType).
 *      Returns E_OK if the GPIO pin is successfully initialized.
 *      Returns E_NOT_OK if an error occurs during the initialization process.
 */
Std_ReturnType gpio_pin_initialize(pin_config_t* _pin_config);

/**
 * @brief Initializes the direction of a GPIO port as input or output.
 *
 * @param port The index of the GPIO port (@ref port_index_t).
 * @param direction The direction to be set for the GPIO port (@ref pin_direction_t).
 *
 * @return Status of the operation (@ref Std_ReturnType).
 *      Returns E_OK if the GPIO port direction is successfully initialized.
 *      Returns E_NOT_OK if an error occurs during the initialization process.
 */
Std_ReturnType gpio_port_direction_initialize(port_index_t port, uint8 direction);

/**
 * @brief Retrieves the direction status of a GPIO port.
 *
 * @param port The index of the GPIO port (@ref port_index_t).
 * @param direction_status Pointer to store the direction status of the GPIO port.
 *
 * @return Status of the operation (@ref Std_ReturnType).
 *      Returns E_OK if the GPIO port direction is successfully retrieved.
 *      Returns E_NOT_OK if an error occurs during the retrieval process.
 */
Std_ReturnType gpio_port_get_direction(port_index_t port, uint8* direction_status);

/**
 * @brief Writes the logic level (high or low) to a GPIO port.
 *
 * @param port The index of the GPIO port (@ref port_index_t).
 * @param logic The logic level to be written to the GPIO port.
 *
 * @return Status of the operation (@ref Std_ReturnType).
 *      Returns E_OK if the logic level is successfully written to the GPIO port.
 *      Returns E_NOT_OK if an error occurs during the write operation.
 */
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic);

/**
 * @brief Reads the logic level (high or low) from a GPIO port.
 *
 * @param port The index of the GPIO port (@ref port_index_t).
 * @param logic Pointer to store the logic level read from the GPIO port.
 *
 * @return Status of the operation (@ref Std_ReturnType).
 *      Returns E_OK if the logic level is successfully read from the GPIO port.
 *      Returns E_NOT_OK if an error occurs during the read operation.
 */
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8* logic);

/**
 * @brief Toggles the logic level of a GPIO port.
 *
 * @param port The index of the GPIO port (@ref port_index_t).
 *
 * @return Status of the operation (@ref Std_ReturnType).
 *      Returns E_OK if the logic level of the GPIO port is successfully toggled.
 *      Returns E_NOT_OK if an error occurs during the toggle operation.
 */
Std_ReturnType gpio_port_toggle_logic(port_index_t port);

/**
 * @brief Initializes the configuration of a GPIO port.
 *
 * @param port The index of the GPIO port (@ref port_index_t).
 * @param direction The direction to be set for the GPIO port.
 * @param logic The logic level to be set for the GPIO port.
 *
 * @return Status of the operation (@ref Std_ReturnType).
 *      Returns E_OK if the GPIO port is successfully initialized.
 *      Returns E_NOT_OK if an error occurs during the initialization process.
 */
Std_ReturnType gpio_port_initialize(port_index_t port, uint8 direction, uint8 logic);

#endif	/* HAL_GPIO_H */