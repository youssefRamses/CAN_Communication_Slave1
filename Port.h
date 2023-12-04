/******************************************************************************
 * Module: Port
 * File Name: Port.h
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver
 * Author: Team 8
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H



/* Standard AUTOSAR types */
#include "Std_Types.h"

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* Non AUTOSAR files */
#include "Common_Macros.h"

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Number of Pins in the Single Port (MCU Specific) */
#define NUM_OF_PINS_SINGLE_PORT         (8U)


/*
 * symbolic names of each Port-Pin in the Microcontroller (MCU SPECIFIC)
 * , must be as symbolic names provided by the configuration tool,
 * this Project doesn't have a configuration tool so it's up to you
 */
#define PORT_PA0                        (0U)
#define PORT_PA1                        (1U)
#define PORT_PA2                        (2U)
#define PORT_PA3                        (3U)
#define PORT_PA4                        (4U)
#define PORT_PA5                        (5U)
#define PORT_PA6                        (6U)
#define PORT_PA7                        (7U)
#define PORT_PB0                        (8U)
#define PORT_PB1                        (9U)
#define PORT_PB2                        (10U)
#define PORT_PB3                        (11U)
#define PORT_PB4                        (12U)
#define PORT_PB5                        (13U)
#define PORT_PB6                        (14U)
#define PORT_PB7                        (15U)
#define PORT_PC0                        (16U)
#define PORT_PC1                        (17U)
#define PORT_PC2                        (18U)
#define PORT_PC3                        (19U)
#define PORT_PC4                        (20U)
#define PORT_PC5                        (21U)
#define PORT_PC6                        (22U)
#define PORT_PC7                        (23U)
#define PORT_PD0                        (24U)
#define PORT_PD1                        (25U)
#define PORT_PD2                        (26U)
#define PORT_PD3                        (27U)
#define PORT_PD4                        (28U)
#define PORT_PD5                        (29U)
#define PORT_PD6                        (30U)
#define PORT_PD7                        (31U)
#define PORT_PE0                        (32U)
#define PORT_PE1                        (33U)
#define PORT_PE2                        (34U)
#define PORT_PE3                        (35U)
#define PORT_PE4                        (36U)
#define PORT_PE5                        (37U)
#define PORT_PE6                        (38U)
#define PORT_PE7                        (39U)
#define PORT_PF0                        (40U)
#define PORT_PF1                        (41U)
#define PORT_PF2                        (42U)
#define PORT_PF3                        (43U)
#define PORT_PF4                        (44U)
#define PORT_PF5                        (45U)
#define PORT_PF6                        (46U)
#define PORT_PF7                        (47U)



/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Data type for the symbolic name of a port pin */
typedef uint8 Port_PinType;

/* Possible directions of a port pin */
typedef enum{
  PORT_PIN_IN,          /* Sets port pin as input */
  PORT_PIN_OUT,         /* Sets port pin as output */
}Port_PinDirectionType;

/* Different port pin modes */
typedef uint8 Port_PinModeType;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;

/* Description: Structure to configure each individual PIN:
 *	1. the direction of pin --> INPUT or OUTPUT
 *      2. the internal resistor --> Disable, Pull up or Pull down
 *      3. the initial value in output case -> high or low
 *      4. pin's Mode -> DIO, Aletrnate Function 01, .... ,Analog
 *      5. pin direction changeability -> ON or OFF
 *      6. pin mode changeability -> ON or OFF
 */
typedef struct
{
    Port_PinDirectionType       direction;              /* PORT_PIN_IN, PORT_PIN_OUT */
    Port_InternalResistor       resistor;               /* OFF,PULL_UP,PULL_DOWN */
    uint8                       initial_value;          /* STD_HIGH, STD_LOW */
                /* STD_ON, STD_OFF */
}Port_ConfigPin;

/* structure that is required for initialization API */
typedef struct
{
  /* array of pointers to config struct to optimize memory storage */
  const Port_ConfigPin* Pins[PORT_ALL_PINS_NUMBER];
}Port_ConfigType;


/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* function for PORT initialization API */
void Port_Init( const Port_ConfigType* ConfigPtr );



/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Port and other modules */
extern const Port_ConfigType Port_pinConfigurationSet;

#endif /* PORT_H */