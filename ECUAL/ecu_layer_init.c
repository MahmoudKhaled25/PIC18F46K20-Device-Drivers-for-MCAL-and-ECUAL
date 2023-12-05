#include "ecu_layer_init.h"

keypad_t keypad = 
{
  .keypad_row_pins[R0].port_index = PORTC_INDEX, 
  .keypad_row_pins[R1].port_index = PORTC_INDEX,
  .keypad_row_pins[R2].port_index = PORTC_INDEX,
  .keypad_row_pins[R3].port_index = PORTC_INDEX,
  
  .keypad_row_pins[R0].pin_index = PIN0, 
  .keypad_row_pins[R1].pin_index = PIN1,
  .keypad_row_pins[R2].pin_index = PIN2,
  .keypad_row_pins[R3].pin_index = PIN3,
  
  .keypad_column_pins[C0].port_index = PORTC_INDEX, 
  .keypad_column_pins[C1].port_index = PORTC_INDEX,
  .keypad_column_pins[C2].port_index = PORTC_INDEX,
  
  .keypad_column_pins[C0].pin_index = PIN4, 
  .keypad_column_pins[C1].pin_index = PIN5,
  .keypad_column_pins[C2].pin_index = PIN6,
  
  .keypad_type = KEYPAD_ACTIVE_HIGH
};

segment_t seg = 
{
    .segment_pins[A].segment_port  = PORTD_INDEX,
    .segment_pins[A].segment_pin  = PIN4,
    .segment_pins[A].segment_pin_status = SEGMENT_PIN_ON,
    .segment_pins[B].segment_port  = PORTD_INDEX,
    .segment_pins[B].segment_pin  = PIN5,
    .segment_pins[B].segment_pin_status = SEGMENT_PIN_ON,
    .segment_pins[C].segment_port  = PORTD_INDEX,
    .segment_pins[C].segment_pin  = PIN6,
    .segment_pins[C].segment_pin_status = SEGMENT_PIN_ON,
    .segment_pins[D].segment_port  = PORTD_INDEX,
    .segment_pins[D].segment_pin  = PIN7,
    .segment_pins[D].segment_pin_status = SEGMENT_PIN_ON,
    .segment_type = SEGMENT_COMMON_ANODE
};

Std_ReturnType ecu_layer_initialize()
{
    Std_ReturnType ret_val = E_OK;
    
    ret_val = keypad_init(&keypad);
    ret_val &= segment_init(&seg);
    
    return ret_val;
}
