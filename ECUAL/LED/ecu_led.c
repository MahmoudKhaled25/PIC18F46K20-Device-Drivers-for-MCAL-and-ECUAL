#include "ecu_led.h"

Std_ReturnType led_initialize(const led_t *const led)
{
    Std_ReturnType retVal = E_OK;
    
    
    if (NULL == led)
    {
        retVal = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = 
        {
           .port_index    = led->port_index,
           .pin_index     = led->pin_index,
           .pin_direction = GPIO_OUTPUT,
           .logic         = led->led_status
        };
        
        retVal = gpio_pin_initialize(&pin_obj);
    }
    
    return retVal;
}

Std_ReturnType led_turn_off(led_t *const led)
{
    Std_ReturnType retVal = E_OK;
    
    if (NULL == led)
    {
        retVal = E_NOT_OK;
    }
    else
    {
        led->led_status = LED_OFF;
        pin_config_t pin_obj = 
        {
           .port_index    = led->port_index,
           .pin_index     = led->pin_index,
           .pin_direction = GPIO_OUTPUT,
           .logic         = led->led_status
        };
        
        retVal = gpio_pin_write_logic(&pin_obj, GPIO_LOW);
    }
    
    return retVal;
}

Std_ReturnType led_turn_on(led_t *const led)
{
    Std_ReturnType retVal = E_OK;
    
    if (NULL == led)
    {
        retVal = E_NOT_OK;
    }
    else
    {
        led->led_status = LED_ON;
        pin_config_t pin_obj = 
        {
           .port_index    = led->port_index,
           .pin_index     = led->pin_index,
           .pin_direction = GPIO_OUTPUT,
           .logic         = led->led_status
        };
        
        retVal = gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }
    
    return retVal;
}

Std_ReturnType led_toggle(led_t *const led)
{
    Std_ReturnType retVal = E_OK;
    
    if (NULL == led)
    {
        retVal = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = 
        {
           .port_index    = led->port_index,
           .pin_index     = led->pin_index,
           .pin_direction = GPIO_OUTPUT,
           .logic         = led->led_status
        };
        
        retVal = gpio_pin_toggle_logic(&pin_obj);
        
        if(retVal)
            led->led_status = pin_obj.logic;
    }
    
    return retVal;
}
