/*
 * File:   application.c
 * Author: Blu-Ray
 *
 * Created on September 19, 2023, 5:01 AM
 */
#include "application.h"




#if DEBUGGING==PIN_APIS
void pin_test_cases (void);

pin_config_t led1 = {PORTC_INDEX, PIN0, GPIO_OUTPUT, GPIO_HIGH};
pin_config_t led2 = {PORTC_INDEX, PIN1, GPIO_OUTPUT, GPIO_LOW};
pin_config_t led3 = {PORTC_INDEX, PIN3, GPIO_OUTPUT, GPIO_HIGH};
pin_config_t led4 = {PORTC_INDEX, PIN4, GPIO_OUTPUT, GPIO_LOW};
pin_config_t led5 = {PORTC_INDEX, PIN5, GPIO_OUTPUT, GPIO_HIGH};
pin_config_t led6 = {PORTC_INDEX, PIN6, GPIO_OUTPUT, GPIO_LOW};
pin_config_t led7 = {PORTC_INDEX, PIN7, GPIO_OUTPUT, GPIO_HIGH};
pin_config_t switch1 = {PORTC_INDEX, PIN2, GPIO_INPUT, GPIO_HIGH};

pin_direction_t direction;
pin_logic_t     logic;

#elif DEBUGGING==PORT_APIS
void port_test_cases (void);

uint8 direction_written = 0b00000100;
uint8 logic_written = 0b01010010;

uint8 direction_readed;
uint8 logic_readed;
#endif


Std_ReturnType retVal;

int main(void) 
{
    #if DEBUGGING==PIN_APIS
    pin_test_cases ();
    #elif DEBUGGING==PORT_APIS
    port_test_cases ();
    #endif
    
    while (1)
    {
        
    }
    
    return (EXIT_SUCCESS);
}

#if DEBUGGING==PIN_APIS
void pin_test_cases (void)
{
    retVal = gpio_pin_initialize(&led1);
    retVal = gpio_pin_initialize(&led2);
    retVal = gpio_pin_initialize(&led3);
    retVal = gpio_pin_initialize(&led4);
    retVal = gpio_pin_initialize(&led5);
    retVal = gpio_pin_initialize(&led6);
    retVal = gpio_pin_initialize(&led7);
    retVal = gpio_pin_initialize(&switch1);
    
    retVal = gpio_pin_get_direction(&led1, &direction);
    retVal = gpio_pin_get_direction(&switch1, &direction);
    
    retVal = gpio_pin_write_logic(&led1, GPIO_LOW);
    
    retVal = gpio_pin_read_logic (&led5, &logic);
    
    retVal = gpio_pin_toggle_logic(&led1);
    retVal = gpio_pin_toggle_logic(&led2);
    retVal = gpio_pin_toggle_logic(&led3);
    retVal = gpio_pin_toggle_logic(&led4);
    retVal = gpio_pin_toggle_logic(&led5);
    retVal = gpio_pin_toggle_logic(&led6);
    retVal = gpio_pin_toggle_logic(&led7);
}
#elif DEBUGGING==PORT_APIS
void port_test_cases (void)
{
    retVal = gpio_port_initialize(PORTC_INDEX, direction_written, logic_written);
    retVal = gpio_port_get_direction(PORTC_INDEX, &direction_readed);
    retVal = gpio_port_read_logic(PORTC_INDEX, &logic_readed);
    retVal = gpio_port_toggle_logic(PORTC_INDEX);
}
#endif