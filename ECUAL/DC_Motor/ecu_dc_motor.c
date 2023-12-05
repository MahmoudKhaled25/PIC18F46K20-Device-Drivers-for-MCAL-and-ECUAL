#include "ecu_dc_motor.h"

static pin_config_t pin_1;
static pin_config_t pin_2;
static void assign_pins (const dc_motor_t *const dc_motor);

static void assign_pins (const dc_motor_t *const dc_motor)
{
    pin_1.port_index = dc_motor->motor_pins[IN1].dc_motor_port;
    pin_1.pin_index = dc_motor->motor_pins[IN1].dc_motor_pin;
    pin_1.pin_direction = GPIO_OUTPUT;
    pin_1.logic = dc_motor->motor_pins[IN1].dc_motor_pin_status;
        
    pin_2.port_index = dc_motor->motor_pins[IN2].dc_motor_port;
    pin_2.pin_index = dc_motor->motor_pins[IN2].dc_motor_pin;
    pin_2.pin_direction = GPIO_OUTPUT;
    pin_2.logic = dc_motor->motor_pins[IN2].dc_motor_pin_status;
}

Std_ReturnType dc_motor_init(const dc_motor_t *const dc_motor)
{
    Std_ReturnType ret_val = E_OK;
   
    if(NULL == dc_motor)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        assign_pins(dc_motor);
        ret_val = gpio_pin_initialize(&pin_1);
        ret_val &= gpio_pin_initialize(&pin_2);
    }
    
    return ret_val;
}

Std_ReturnType dc_motor_move_right(dc_motor_t *const dc_motor)
{
    Std_ReturnType ret_val = E_OK;
   
    if(NULL == dc_motor)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        assign_pins(dc_motor);
        ret_val = gpio_pin_write_logic(&pin_1, GPIO_HIGH);
        ret_val &= gpio_pin_write_logic(&pin_2, GPIO_LOW);
        
        if (E_OK == ret_val)
        {
            dc_motor->motor_pins[IN1].dc_motor_pin_status = DC_MOTOR_PIN_ON;
            dc_motor->motor_pins[IN2].dc_motor_pin_status = DC_MOTOR_PIN_OFF;
        }
    }
    
    return ret_val;
}

Std_ReturnType dc_motor_move_left(dc_motor_t *const dc_motor)
{
    Std_ReturnType ret_val = E_OK;
   
    if(NULL == dc_motor)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        assign_pins(dc_motor);
        ret_val = gpio_pin_write_logic(&pin_1, GPIO_LOW);
        ret_val &= gpio_pin_write_logic(&pin_2, GPIO_HIGH);
        
        if (E_OK == ret_val)
        {
            dc_motor->motor_pins[IN1].dc_motor_pin_status = DC_MOTOR_PIN_OFF;
            dc_motor->motor_pins[IN2].dc_motor_pin_status = DC_MOTOR_PIN_ON;
        }
    }
    
    return ret_val;
}

Std_ReturnType dc_motor_stop(dc_motor_t *const dc_motor)
{
    Std_ReturnType ret_val = E_OK;
   
    if(NULL == dc_motor)
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        assign_pins(dc_motor);
        ret_val = gpio_pin_write_logic(&pin_1, GPIO_LOW);
        ret_val &= gpio_pin_write_logic(&pin_2, GPIO_LOW);
        
        if (E_OK == ret_val)
        {
            dc_motor->motor_pins[IN1].dc_motor_pin_status = DC_MOTOR_PIN_OFF;
            dc_motor->motor_pins[IN2].dc_motor_pin_status = DC_MOTOR_PIN_OFF;
        }
    }
    
    return ret_val;
}
