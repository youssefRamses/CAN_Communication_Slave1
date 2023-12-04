/******************************************************************************
 * Module: Port
 * File Name: Port_PBcfg.c
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 * Author: Team 8
 ******************************************************************************/

#include "Port.h"


/* definitions of Indecies of the Multible Configuration array */
#define DIO_INPUT_PULLUP                       (0U)
#define DIO_INPUT_PULLDOWN                     (1U)
#define DIO_OUTPUT_LOW                         (2U)
#define DIO_OUTPUT_HIGH                        (3U)
  
/*
 * Selectable Multible Configuration sets definitions
   Config Item Consist of:
                    1. direction
                    2. internal resistor
                    3. initial value
                    4. mode
                    5. direction changeable
                    6. mode changeable
*/
const Port_ConfigPin Port_Configuration[]={
  
  {PORT_PIN_IN, PULL_UP, STD_HIGH}, /* DIO_INPUT_PULLUP */
  
  {PORT_PIN_IN, PULL_DOWN, STD_HIGH}, /* DIO_INPUT_PULLDOWN */
  
  {PORT_PIN_OUT, OFF, STD_LOW}, /* DIO_OUTPUT_LOW */
  
  {PORT_PIN_OUT, OFF, STD_HIGH}, /* DIO_OUTPUT_HIGH */
  
};

  
/*
 * PB structure used with Port_Init API,
 * Contains pointer to some Configuration for each Port-Pin Index in the MCU 
 */
const Port_ConfigType Port_pinConfigurationSet = {

  NULL_PTR,                 /* PORT_PA0 */
  NULL_PTR,                 /* PORT_PA1 */
  NULL_PTR,                 /* PORT_PA2 */
  NULL_PTR,                 /* PORT_PA3 */
  NULL_PTR,                 /* PORT_PA4 */
  NULL_PTR,                 /* PORT_PA5 */
  NULL_PTR,                 /* PORT_PA6 */
  NULL_PTR,                 /* PORT_PA7 */
  NULL_PTR,                 /* PORT_PB0 */
  NULL_PTR,                 /* PORT_PB1 */
  NULL_PTR,                 /* PORT_PB2 */
  NULL_PTR,                 /* PORT_PB3 */
  NULL_PTR,                 /* PORT_PB4 */
  NULL_PTR,                 /* PORT_PB5 */
  NULL_PTR,                 /* PORT_PB6 */
  NULL_PTR,                 /* PORT_PB7 */
  NULL_PTR,                  /* PORT_PC0 */
  NULL_PTR,                   /* PORT_PC1 */
  NULL_PTR,                   /* PORT_PC2 */
  NULL_PTR,                  /* PORT_PC3 */
  NULL_PTR,                 /* PORT_PC4 */
  NULL_PTR,                 /* PORT_PC5 */
  NULL_PTR,                 /* PORT_PC6 */
  NULL_PTR,                 /* PORT_PC7 */
  NULL_PTR,                 /* PORT_PD0 */
  NULL_PTR,                 /* PORT_PD1 */
  NULL_PTR,                 /* PORT_PD2 */
  NULL_PTR,                 /* PORT_PD3 */
  NULL_PTR,                 /* PORT_PD4 */
  NULL_PTR,                 /* PORT_PD5 */
  NULL_PTR,                 /* PORT_PD6 */
  NULL_PTR,                 /* PORT_PD7 */
  NULL_PTR,                 /* PORT_PE0 */
  NULL_PTR,                 /* PORT_PE1 */
  NULL_PTR,                 /* PORT_PE2 */
  NULL_PTR,                 /* PORT_PE3 */
  NULL_PTR,                 /* PORT_PE4 */
  NULL_PTR,                 /* PORT_PE5 */
  NULL_PTR,                                     /* PORT_PE6 */  
  NULL_PTR,                                     /* PORT_PE7 */  
  &Port_Configuration[DIO_INPUT_PULLUP],               /* PORT_PF0 */
  &Port_Configuration[DIO_OUTPUT_LOW],                 /* PORT_PF1 */
  &Port_Configuration[DIO_OUTPUT_LOW],                 /* PORT_PF2 */
  &Port_Configuration[DIO_OUTPUT_LOW],                 /* PORT_PF3 */
  &Port_Configuration[DIO_INPUT_PULLUP],              /* PORT_PF4 */
  NULL_PTR,                                     /* PORT_PF5 */
  NULL_PTR,                                     /* PORT_PF6 */
  NULL_PTR,                                     /* PORT_PF7 */
  
};