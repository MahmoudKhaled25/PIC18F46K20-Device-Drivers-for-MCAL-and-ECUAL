#include "ecu_button.h"

Std_ReturnType button_init(const button_t *const button)
{
    Std_ReturnType ret_val = E_OK;
  
    if (NULL == button)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        pin_logic_t logic = (BUTTON_ACTIVE_LOW == button->button_connection ? GPIO_LOW : GPIO_HIGH);
        pin_config_t pin = {button->port_index, button->pin_index, GPIO_INPUT, logic};
        ret_val = gpio_pin_direction_initialize(&pin);
    }
    
    return ret_val;
}

Std_ReturnType button_read_state(button_t *const button, button_state_t *const button_state)
{
    Std_ReturnType ret_val = E_OK;
    pin_logic_t logic;
    
    if (NULL == button)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        pin_config_t pin = {button->port_index, button->pin_index, GPIO_INPUT, logic};
        ret_val = gpio_pin_read_logic(&pin, &logic);
        
        switch (button->button_connection)
        {
            case BUTTON_ACTIVE_LOW:
                if (GPIO_LOW == logic)
                    *button_state = BUTTON_PRESSED;
                else if (GPIO_HIGH == logic)
                    *button_state = BUTTON_RELEASED;
                else
                    ret_val = E_NOT_OK;
                break;
                    
            case BUTTON_ACTIVE_HIGH:
                if (GPIO_HIGH == logic)
                    *button_state = BUTTON_PRESSED;
                else if (GPIO_LOW == logic)
                    *button_state = BUTTON_RELEASED;
                else
                    ret_val = E_NOT_OK;
                break;
                    
            default:
                ret_val = E_NOT_OK;
        }                
    }
    
    return ret_val;
}