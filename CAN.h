#ifndef CAN_H_
#define CAN_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "tm4c123gh6pm.h"
#include <stdbool.h>
#include "inc/hw_can.h"
#include "inc/hw_uart.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "driverlib/can.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/fpu.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "Platform_Types.h"

#define GPIO_PORTA_BASE         0x40004000  // GPIO Port A
#define GPIO_PORTB_BASE         0x40005000  // GPIO Port B
#define GPIO_PORTC_BASE         0x40006000  // GPIO Port C
#define GPIO_PORTD_BASE         0x40007000  // GPIO Port D


/*description: CAN HANDLER*/
void CANIntHandler(void);

/*description: CAN initialization*/
void CAN_INIT(void);

/*description: sending using tx1*/
void CAN_Send1(uint8 data);

/*description: sending using tx2*/
void CAN_Send2(uint8 data);

/*description: Receive from CAN*/
uint8 CAN_Receiver(void);

#endif