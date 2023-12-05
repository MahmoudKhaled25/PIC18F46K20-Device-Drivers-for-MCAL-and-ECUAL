#include "ecu_keypad.h"

uint8 counter;
static pin_config_t row_pins[KEYPAD_ROWS];
static pin_config_t column_pins[KEYPAD_COLUMNS];
static pin_logic_t enable_logic, disable_logic;


#if KEYPAD_4X4_CONFIG==CONFIG_ENABLE
static const uint8 keypad_buttons[KEYPAD_ROWS][KEYPAD_COLUMNS] = 
{
    {'7', '8', '9', '/'},
    {'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {'c', '0', '=', '+'}
};
#elif KEYPAD_4X3_CONFIG==CONFIG_ENABLE
static const uint8 keypad_buttons[KEYPAD_ROWS][KEYPAD_COLUMNS] = 
{
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};
#endif

static Std_ReturnType assign_pins(const keypad_t *const keypad);

static Std_ReturnType assign_pins(const keypad_t *const keypad)
{
    Std_ReturnType ret_val = E_OK;
    
    switch (keypad->keypad_type)
    {
        case KEYPAD_ACTIVE_HIGH:
            disable_logic = GPIO_LOW;
            enable_logic = GPIO_HIGH;
            break;
        case KEYPAD_ACTIVE_LOW:
            disable_logic = GPIO_HIGH;
            enable_logic = GPIO_LOW;
            break;
        default:
            ret_val = E_NOT_OK;
    }
    
    if (E_OK == ret_val)
    {
        for (counter = 0; counter < KEYPAD_ROWS; counter++)
        {
            row_pins[counter].port_index = keypad->keypad_row_pins[counter].port_index;
            row_pins[counter].pin_index = keypad->keypad_row_pins[counter].pin_index;
            row_pins[counter].pin_direction = GPIO_OUTPUT;
            row_pins[counter].logic = disable_logic;
        }

        for (counter = 0; counter < KEYPAD_COLUMNS; counter++)
        {
            column_pins[counter].port_index = keypad->keypad_column_pins[counter].port_index;
            column_pins[counter].pin_index = keypad->keypad_column_pins[counter].pin_index;
            column_pins[counter].pin_direction = GPIO_INPUT;
        }
    }
    
    return ret_val;
}

Std_ReturnType keypad_init(const keypad_t *const keypad)
{
    Std_ReturnType ret_val = E_OK;
    
    if(NULL == keypad)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        ret_val = assign_pins(keypad);        
        if (E_OK == ret_val)
        {
            for (counter = 0; counter < KEYPAD_ROWS; counter++)
                ret_val = gpio_pin_initialize(&row_pins[counter]);

            for (counter = 0; counter < KEYPAD_COLUMNS; counter++)
                ret_val = gpio_pin_direction_initialize(&column_pins[counter]);          
        }
    }
    
    return ret_val;
}

Std_ReturnType keypad_read_button(const keypad_t *const keypad, uint8 *read)
{
    Std_ReturnType ret_val = E_OK;
    uint8 row_counter, column_counter;
    
    if(NULL == keypad || NULL == read)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        pin_logic_t logic_read;
        ret_val = assign_pins(keypad);
        if (E_OK == ret_val)
        {
            for (row_counter = 0; row_counter < KEYPAD_ROWS; row_counter++)
            {
                ret_val &= gpio_pin_write_logic(&row_pins[row_counter], enable_logic);
                for (column_counter = 0; column_counter < KEYPAD_COLUMNS; column_counter++)
                {
                    ret_val &= gpio_pin_read_logic(&column_pins[column_counter], &logic_read);
                    if (logic_read == enable_logic)
                        *read = keypad_buttons[row_counter][column_counter];
                }
                ret_val &= gpio_pin_write_logic(&row_pins[row_counter], disable_logic);
            }
        }
        
            
    }
    
    return ret_val;
}