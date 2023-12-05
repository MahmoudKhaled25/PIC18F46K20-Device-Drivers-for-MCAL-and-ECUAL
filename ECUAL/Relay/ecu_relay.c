/* 
 * File:   ecu_relay.c
 * Author: Mahmoud Khaled
 *
 * Created on October 5, 2023, 7:22 PM
 */

#include "ecu_relay.h"

Std_ReturnType relay_init(const relay_t *const relay)
{
    Std_ReturnType ret_val = E_OK;
    
    if (NULL == relay)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        pin_config_t pin = 
            {
              .port_index = relay->port_index,
              .pin_index = relay->pin_index,
              .pin_direction = GPIO_OUTPUT,
            };
        switch (relay->relay_status)
        {
            case RELAY_OFF:
                pin.logic = GPIO_LOW;
                ret_val = gpio_pin_initialize(&pin);
                break;
            case RELAY_ON:
                pin.logic = GPIO_HIGH;
                ret_val = gpio_pin_initialize(&pin);
                break;
            default :
                ret_val = E_NOT_OK;
        }
    }
    
    return ret_val;
}

Std_ReturnType relay_turn_off(relay_t *const relay)
{
    Std_ReturnType ret_val = E_OK;
    
    if (NULL == relay)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        pin_logic_t logic = (RELAY_ON == relay->relay_status ? GPIO_HIGH : GPIO_LOW);
        pin_config_t pin = 
        {
          .port_index = relay->port_index,
          .pin_index = relay->pin_index,
          .pin_direction = GPIO_OUTPUT,
          .logic = logic
        };
       ret_val = gpio_pin_write_logic(&pin, GPIO_LOW);
       if (E_OK == ret_val)
           relay->relay_status = RELAY_OFF;
    }
    
    return ret_val;
}

Std_ReturnType relay_turn_on(relay_t *const relay)
{
    Std_ReturnType ret_val = E_OK;
    
    if (NULL == relay)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        pin_logic_t logic =  (RELAY_ON == relay->relay_status ? GPIO_HIGH : GPIO_LOW);
        pin_config_t pin = 
        {
          .port_index = relay->port_index,
          .pin_index = relay->pin_index,
          .pin_direction = GPIO_OUTPUT,
          .logic = logic
        };
       ret_val = gpio_pin_write_logic(&pin, GPIO_HIGH);
       if (E_OK == ret_val)
           relay->relay_status = RELAY_ON;
    }
    
    return ret_val;
}

Std_ReturnType relay_toggle(relay_t *const relay)
{
    Std_ReturnType ret_val = E_OK;
    
    if (NULL == relay)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        pin_logic_t logic =  (RELAY_ON == relay->relay_status ? GPIO_HIGH : GPIO_LOW);
        pin_config_t pin = 
        {
          .port_index = relay->port_index,
          .pin_index = relay->pin_index,
          .pin_direction = GPIO_OUTPUT,
          .logic = logic
        };
       ret_val = gpio_pin_toggle_logic(&pin);
       if (E_OK == ret_val)
           relay->relay_status = !relay->relay_status;
    }
    
    return ret_val;
}