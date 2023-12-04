 /******************************************************************************
 * Module: application
 * File Name: App.h
 * Description: Header file for Application Tasks.
 * Author: Team 8 
 ******************************************************************************/

#ifndef APP_H_
#define APP_H_

#include "Std_Types.h"

enum state {r, rt ,r1, r2};

/* Description: Task executes once to initialize all the Modules */
void Init_Task(void);

/* Description: Task executes every 1000 Mili-seconds to get the button status and toggle the led */
void App_Task(void);

/* Description: Task That turns the Red led on*/
void Red_state(void);

/* Description: Task That turns the Green led on*/
void Green_state(void);

/* Description: Task That turns the Blue led on*/
void Blue_state(void);

/* Description: Task executes every 10 Mili-seconds to receive from the CAN */
void Receive_state (void);

void colors(uint8 x);

#endif /* APP_H_ */
