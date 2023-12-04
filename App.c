  /******************************************************************************
 * Module: application
 * File Name: App.c
 * Description: Header file for Application Tasks.
 * Author: Team 8 
 ******************************************************************************/

#include "App.h"
#include "Button.h"
#include "Led.h"
#include "Dio.h"
#include "Port.h"
#include  "CAN.h"
#include "Os.h"

/*Counter used to set the colour state*/
uint8 color_count=0; 

/*Counter for how many times the button was pressed to set the state*/
uint8 btn_count=0;
/*Variable that receives the data from the can*/
uint8 data=0;
/*Variable that sets the button count either with 1 or 2  */
uint8 dummy=0;

uint8 status=0;

/************************************************************************************
* Function Name: Init_Task
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* inputs : None
* outputs : None
* Description: Function to Initialize Dio, CAN and PORTS
************************************************************************************/

void Init_Task(void)
{
    /* Initialize Port Driver */
    Port_Init(&Port_pinConfigurationSet); 
    /* Initialize Dio Driver */
    Dio_Init(&Dio_Configuration);
    /* Initialize CAN */
    CAN_INIT();

}



/************************************************************************************
* Function Name: Red_state
* Sync/Async: Synchronous
* Reentrancy:  reentrant
* inputs : None
* outputs : None
* Description: Function to Turn Red Led on
************************************************************************************/

void Red_state (void){
        /* Turn red led on */
        Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX,LED_ON);  
        /* Turn blue led off */
        Dio_WriteChannel(DioConf_LED2_CHANNEL_ID_INDEX,LED_OFF);
        /* Turn green led off */
        Dio_WriteChannel(DioConf_LED3_CHANNEL_ID_INDEX,LED_OFF);
}

/************************************************************************************
* Function Name: Green_state
* Sync/Async: Synchronous
* Reentrancy:  reentrant
* inputs : None
* outputs : None
* Description: Function to Turn Green Led on
************************************************************************************/

void Green_state (void){
        /* Turn red led off */
        Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX,LED_OFF);  
        /* Turn blue led off */
        Dio_WriteChannel(DioConf_LED2_CHANNEL_ID_INDEX,LED_OFF);
        /* Turn green led on */
        Dio_WriteChannel(DioConf_LED3_CHANNEL_ID_INDEX,LED_ON);
        
  
}

/************************************************************************************
* Function Name: Blue_state
* Sync/Async: Synchronous
* Reentrancy:  reentrant
* inputs : None
* outputs : None
* Description: Function to Turn blue Led on
************************************************************************************/

void Blue_state (void){
        /* Turn red led off */
        Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX,LED_OFF);  
        /* Turn blue led on */
        Dio_WriteChannel(DioConf_LED2_CHANNEL_ID_INDEX,LED_ON);
        /* Turn green led off */
        Dio_WriteChannel(DioConf_LED3_CHANNEL_ID_INDEX,LED_OFF);
}

/***************************************************************************************
* Function Name: App_Task
* Sync/Async: Synchronous
* Reentrancy:  reentrant
* inputs : None
* outputs : None
* Description: Function to set the state based on the button counter and colour counter
****************************************************************************************/

void App_Task(void)
{
 
  switch(status){
  
  case r1: 
          if(color_count<3){
            /*Increase the colour count by 1*/
            color_count++;
          }
          else { color_count=0; }
          colors(color_count); 
          dummy=0;
          
          break;
          
  case rt: 
          if(color_count ==0 || color_count==3 ){
          color_count=2;
          }
   
          /*if green set it to red*/
          else if (color_count==1){
          color_count=3;
          }
   
          /*if blue set it to green*/
          else if(color_count==2){
          color_count=1;
          }
          colors(color_count);
          dummy=0;
          
          break;
  
  case r2: 
           color_count=0;
           colors(color_count);
           dummy=0;
           break;
  }
      status=r;   
}

/***************************************************************************************
* Function Name: Receive_state
* Sync/Async: Synchronous
* Reentrancy:  reentrant
* inputs : None
* outputs : None
* Description: Function to receive from CAN
****************************************************************************************/


void Receive_state (void){
  /*receive data*/
  data  = CAN_Receiver();
          /*check if data = 1*/
            if (data==1){
            dummy++;  
              /*check number of presses*/
              if(dummy==1){
                           status =r1;
                           }
              else if(dummy==2){
                status=rt;
                }
            }
          
            /*if data =2 it means that both buttons where pressed*/
            if(data ==2){
             status = r2;
             
            }
  
}


void colors(uint8 x){
  
  
  switch (x){
        
        /*red state*/
        case 0:
        case 3: Red_state();
                color_count=0;
                break;
                
        /*Green state*/        
        case 1: Green_state();
                break;
                
        /*blue state*/        
        case 2: Blue_state();
                break;      
  
  
}
}