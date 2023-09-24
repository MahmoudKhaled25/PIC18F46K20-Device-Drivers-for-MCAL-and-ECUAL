/* 
 * File:   hal_gpio.h
 * Author: Blu-Ray
 *
 * Created on September 19, 2023, 8:13 PM
 */

#include "hal_gpio.h"

volatile uint8 *const (tris_regs[]) = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
volatile uint8 *const (lat_regs[]) = {&LATA, &LATB, &LATC, &LATD, &LATE};
volatile uint8 *const (port_regs[]) = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};

#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_direction_initialize (const pin_config_t *_pin_config)
{
    Std_ReturnType ret_State = E_OK;
    
    if (NULL == _pin_config || _pin_config->port_index > PORT_MAX_NUM || _pin_config->pin_index > PIN_MAX_NUM)
    { 
        ret_State = E_NOT_OK; 
    }
    else
    {
        switch (_pin_config->pin_direction)
        {           
            case GPIO_OUTPUT :
                CLEAR_BIT(*tris_regs[_pin_config->port_index], _pin_config->pin_index);
                break;
                    
            case GPIO_INPUT :
                SET_BIT(*tris_regs[_pin_config->port_index], _pin_config->pin_index);
                break;
                    
            default :
                ret_State = E_NOT_OK;
        } 
    }
    
    return ret_State;
}
#endif

#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_get_direction (const pin_config_t *_pin_config, pin_direction_t *direction_status)
{
    Std_ReturnType ret_State = E_OK;
    
    if (NULL == _pin_config || NULL == direction_status || _pin_config->port_index > PORT_MAX_NUM || _pin_config->pin_index > PIN_MAX_NUM)
    { 
        ret_State = E_NOT_OK; 
    }
    else
    {
        if (GPIO_INPUT == _pin_config->pin_direction || GPIO_OUTPUT == _pin_config->pin_direction)
            *direction_status = _pin_config->pin_direction;
        else
            ret_State = E_NOT_OK;
    }
    
    return ret_State;
}
#endif

#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_write_logic (pin_config_t *_pin_config, pin_logic_t logic)
{
    Std_ReturnType ret_State = E_OK;
    
    if (NULL == _pin_config || _pin_config->port_index > PORT_MAX_NUM || _pin_config->pin_index > PIN_MAX_NUM)
    { 
        ret_State = E_NOT_OK; 
    }
    else
    {
        switch (logic) 
        {
            case GPIO_LOW:
                CLEAR_BIT(*lat_regs[_pin_config->port_index], _pin_config->pin_index);
                break;
                
            case GPIO_HIGH:
                SET_BIT(*lat_regs[_pin_config->port_index], _pin_config->pin_index);
                break;
                
            default :
                ret_State = E_NOT_OK; 
        }
        _pin_config->logic = READ_BIT(*port_regs[_pin_config->port_index], _pin_config->pin_index);
    }
    
    return ret_State;
}
#endif

#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_read_logic (const pin_config_t *_pin_config, pin_logic_t *logic)
{
    Std_ReturnType ret_State = E_OK;
    
    if (NULL == _pin_config || NULL == logic || _pin_config->port_index > PORT_MAX_NUM || _pin_config->pin_index > PIN_MAX_NUM)
    { 
        ret_State = E_NOT_OK; 
    }
    else
    {
        *logic = READ_BIT(*port_regs[_pin_config->port_index], _pin_config->pin_index);
    }
    
    return ret_State;
}
#endif

#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_toggle_logic (pin_config_t *_pin_config)
{
     Std_ReturnType ret_State = E_OK;
    
    if (NULL == _pin_config || _pin_config->port_index > PORT_MAX_NUM || _pin_config->pin_index > PIN_MAX_NUM || GPIO_INPUT == _pin_config->pin_direction)
    { 
        ret_State = E_NOT_OK; 
    }
    else
    {
        TOGGLE_BIT(*lat_regs[_pin_config->port_index], _pin_config->pin_index);
        _pin_config->logic = READ_BIT(*port_regs[_pin_config->port_index], _pin_config->pin_index);
    }
    
    return ret_State;
}
#endif

#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_initialize (pin_config_t *_pin_config)
{
    Std_ReturnType ret_State = E_OK;
    
    ret_State &= gpio_pin_direction_initialize (_pin_config);
    ret_State &= gpio_pin_write_logic (_pin_config, _pin_config->logic);
    
    return ret_State;
}
#endif

#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_direction_initialize (port_index_t port, uint8 direction)
{
     Std_ReturnType ret_State = E_OK;
    
    if (port > PORT_MAX_NUM)
    { 
        ret_State = E_NOT_OK; 
    }
    else
    {
        *tris_regs[port] = direction;
    }
    
    return ret_State;
}
#endif

#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_get_direction (port_index_t port, uint8 *direction_status)
{
      Std_ReturnType ret_State = E_OK;
    
    if (NULL == direction_status || port > PORT_MAX_NUM)
    { 
        ret_State = E_NOT_OK; 
    }
    else
    {
        *direction_status = *tris_regs[port];
    }
    
    return ret_State;
}
#endif

#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_write_logic (port_index_t port, uint8 logic)
{
    Std_ReturnType ret_State = E_OK;
    
    if (port > PORT_MAX_NUM)
    { 
        ret_State = E_NOT_OK; 
    }
    else
    {
        *lat_regs[port] = logic;
    }
    
    return ret_State;
}
#endif

#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_read_logic (port_index_t port, uint8 *logic)
{
     Std_ReturnType ret_State = E_OK;
    
    if (NULL == logic || port > PORT_MAX_NUM)
    { 
        ret_State = E_NOT_OK; 
    }
    else
    {
        *logic = *port_regs[port];
    }
    
    return ret_State;
}
#endif

#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_toggle_logic (port_index_t port)
{
    Std_ReturnType ret_State = E_OK;
    
    if (port > PORT_MAX_NUM)
    { 
        ret_State = E_NOT_OK; 
    }
    else
    {
        *lat_regs[port] = ~(*lat_regs[port]);
    }
    
    return ret_State;
}
#endif

#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_initialize (port_index_t port, uint8 direction, uint8 logic)
{
    Std_ReturnType ret_State = E_OK;
    
    ret_State &= gpio_port_direction_initialize(port, direction);
    ret_State &= gpio_port_write_logic(port, logic);
    
    return ret_State;
}
#endif