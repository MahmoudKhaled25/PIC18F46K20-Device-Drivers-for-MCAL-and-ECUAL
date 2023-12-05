/* 
 * File:   ecu_layer_init.h
 * Author: Blu-Ray
 *
 * Created on November 1, 2023, 4:04 PM
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H


/*Section: Includes*/
#include "LED/ecu_led.h"
#include "Button/ecu_button.h"
#include "Relay/ecu_relay.h"
#include "DC_Motor/ecu_dc_motor.h"
#include "Seven_Segment/ecu_seven_seg.h"
#include "Keypad/ecu_keypad.h"

/*Section: Macros*/

/*Section: Function Like Macro Declarations*/

/*Section: Data Types Declarations*/
extern keypad_t keypad;
extern segment_t seg;

/*Section: Functions Declarations*/
Std_ReturnType ecu_layer_initialize();

#endif	/* ECU_LAYER_INIT_H */

