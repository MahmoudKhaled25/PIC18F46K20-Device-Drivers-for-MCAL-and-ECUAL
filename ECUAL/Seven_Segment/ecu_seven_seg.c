#include "ecu_seven_seg.h"

static uint8 counter; 
static pin_config_t pins[4];
static void assign_pins (const segment_t *const segment);

static void assign_pins (const segment_t *const segment)
{
    for (counter = 0; counter < 4; counter++)
    {
        pins[counter].port_index = segment->segment_pins[counter].segment_port;
        pins[counter].pin_index = segment->segment_pins[counter].segment_pin;
        pins[counter].pin_direction = GPIO_OUTPUT;
        pins[counter].logic = segment->segment_pins[counter].segment_pin_status;
    }
}

Std_ReturnType segment_init(const segment_t *const segment)
{
    Std_ReturnType ret_val = E_OK;
    
    if (NULL == segment)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
       assign_pins(segment);
       for (counter = 0; counter < 4; counter++)
           ret_val &= gpio_pin_initialize(&pins[counter]);
    }
    
    return ret_val;
}

Std_ReturnType segment_write_number(segment_t *const segment, uint8 number)
{
    Std_ReturnType ret_val = E_OK;
    
    if ((NULL == segment) || (number < 0) || (number > 9))
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        assign_pins(segment);
        for (counter = 0; counter < 4; counter++)
           ret_val &= gpio_pin_write_logic(&pins[counter], (number >> counter) & 0x01);
    }
    
    return ret_val;
}


Std_ReturnType multiplex(segment_t *const segment, uint8 number_pins, uint8 *values,...)
{
    Std_ReturnType ret_val = E_OK;
    uint8 counter;
    pin_logic_t enable_logic;
    va_list arg;
    
    if (NULL == segment)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        va_start(arg, values);
        pin_config_t *pin;
        switch (segment->segment_type)
        {
            case SEGMENT_COMMON_ANODE:
                enable_logic = GPIO_HIGH;
                break;
            case SEGMENT_COMMON_CATHODE:
                enable_logic = GPIO_LOW;
                break;
            default :
                ret_val = E_NOT_OK;
        }
        
        for (counter = 0; counter < number_pins; counter++)
        {
            pin = va_arg(arg, pin_config_t *);
            if (E_OK == ret_val)
            {
                ret_val &= segment_write_number(segment, values[counter]);
                ret_val &= gpio_pin_write_logic(pin, enable_logic);
                __delay_us(500);
                ret_val &= gpio_pin_write_logic(pin, !enable_logic);
            }
            else 
            {
                break;
            }
        }
        
        va_end(arg);
    }
    
    return ret_val;
}
