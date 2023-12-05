/*
 * File:   application.c
 * Author: Blu-Ray
 *
 * Created on September 19, 2023, 5:01 AM
 */
#include "application.h"

Std_ReturnType ret_val;

uint8 counter;
uint8 nums[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; 
uint8 keypad_read = '0';

int main() 
{ 
    app_init();
    while (1)
    {
        ret_val = keypad_read_button(&keypad, &keypad_read);
        ret_val = segment_write_number(&seg, nums[keypad_read - '0']);
    }
    return (EXIT_SUCCESS);
}

void app_init()
{
    ret_val = ecu_layer_initialize();
}
