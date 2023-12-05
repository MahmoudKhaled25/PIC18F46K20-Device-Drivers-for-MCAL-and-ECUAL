/* 
 * File:   mcal_std_types.h
 * Author: Blu-Ray
 *
 * Created on September 19, 2023, 8:33 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/*Section: Includes*/
#include "std_libraries.h"
#include "compiler.h"

/*Section: Macros*/

/*Section: Function Like Macro Declarations*/

/*Section: Data Types Declarations*/
typedef unsigned char      uint8;
typedef signed char        sint8;
typedef unsigned short     uint16;
typedef signed short       sint16;
typedef unsigned long      uint32;
typedef signed long        sint32;
typedef enum
{
    E_NOT_OK,    // Operation not successful
    E_OK         // Operation successful
}Std_ReturnType;

/*Section: Functions Declarations*/

#endif	/* MCAL_STD_TYPES_H */

