#include "CAN.h"

/*Flag of tx1 */
volatile bool g_bRXFlag1 = 0;

/*Flag of tx2 */
volatile bool g_bRXFlag2 = 0;

/*error flag */
volatile bool g_bErrFlag = 0;

/*type define unsignedint*/
typedef uint32 unsignedint;

/*received data variable*/
uint8 r_data=0;

/*array for the objects sent by CAN*/
uint8_t pui8MsgData[6];

/*initialize struct tx1*/
tCANMsgObject sCANMessage_tx1;

/*initialize struct tx1*/
tCANMsgObject sCANMessage_tx2;

/*initialize struct rx*/
tCANMsgObject sCANMessage_rx;


/************************************************************************************
* Function Name: CANIntHandler
* inputs : None
* outputs : None
* Description: CAN handler
************************************************************************************/

void CANIntHandler(void)
{
    /* initialize a variable*/  
    uint32_t ui32Status;
    /*get the interrupt status*/
    ui32Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);
    /*check if there is a error*/
    if(ui32Status == CAN_INT_INTID_STATUS)
    {
        ui32Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
        g_bErrFlag = 1;
    }
    /*if status = object 1*/
    else if(ui32Status == 1)
    {   
        /*clear interrupt*/
        CANIntClear(CAN0_BASE, 1);
        /*raise tx1 flag*/
        g_bRXFlag1 = 1;
        /*erase error flag*/
        g_bErrFlag = 0;
    }
     
    /*if status = object 2*/
    else if(ui32Status == 2)
    {
        /*clear interrupt*/
        CANIntClear(CAN0_BASE, 2);
        
        /*raise tx2 flag*/
        g_bRXFlag2 = 1;
        
        /*erase error flag*/
        g_bErrFlag = 0;
    }
}

/************************************************************************************
* Function Name: CAN_INIT
* inputs : None
* outputs : None
* Description: CAN initialization
************************************************************************************/


void CAN_INIT(void)
{
   /*initalize the clock*/
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);
    /*peripheral enable*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    
    /*set tx and rx*/
    GPIOPinConfigure(GPIO_PB4_CAN0RX);
    GPIOPinConfigure(GPIO_PB5_CAN0TX);
    GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    
    /*enable Can0*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
    CANInit(CAN0_BASE);
#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
    CANBitRateSet(CAN0_BASE, ui32SysClock, 500000);
#else
    CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);
#endif
    /*interrupt enable for can0*/
    CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
    IntEnable(INT_CAN0);
    
    /*CAN enable*/
    CANEnable(CAN0_BASE);
    
    /*set the rx id as tx2*/
    sCANMessage_rx.ui32MsgID =0x2001; sCANMessage_tx1.ui32MsgID=0x1001; sCANMessage_tx2.ui32MsgID=0x2001;
    
    /*setting the masks*/
    sCANMessage_rx.ui32MsgIDMask = 0xfffff;  sCANMessage_tx1.ui32MsgIDMask = 0; sCANMessage_tx1.ui32MsgIDMask = 0; 
    
    /*setting flags*/
    sCANMessage_rx.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
    sCANMessage_tx1.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
    
    /*message length*/
    sCANMessage_rx.ui32MsgLen = 8; sCANMessage_tx1.ui32MsgLen = 8; sCANMessage_tx2.ui32MsgLen = 8;
    
    /*message array*/
    sCANMessage_tx1.pui8MsgData = pui8MsgData;
    sCANMessage_tx2.pui8MsgData = pui8MsgData;
    /*setting message objects 1 and 2*/
    CANMessageSet(CAN0_BASE, 1, &sCANMessage_rx, MSG_OBJ_TYPE_RX);
    CANMessageSet(CAN0_BASE, 2, &sCANMessage_rx, MSG_OBJ_TYPE_RX);
}


/************************************************************************************
* Function Name: CAN_Send1
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* inputs : data
* outputs : None
* Description: Sends data using tx1
************************************************************************************/

void CAN_Send1(uint8 data){
  /*setting the first element of the array to be equal the data*/
  pui8MsgData[0]=data;
  /*sending the message*/
  CANMessageSet(CAN0_BASE, 1, &sCANMessage_tx1, MSG_OBJ_TYPE_TX);
}

/************************************************************************************
* Function Name: CAN_Send2
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* inputs : data
* outputs : None
* Description: Sends data using tx2
************************************************************************************/

void CAN_Send2(uint8 data){
  /*setting the first element of the array to be equal the data*/
  pui8MsgData[0]=data;
  /*sending the message*/
  CANMessageSet(CAN0_BASE, 2, &sCANMessage_tx2, MSG_OBJ_TYPE_TX);
}


/************************************************************************************
* Function Name: CAN_Receiver
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* inputs : None
* outputs : None
* Description: checks the data received using the rx id to get the message
************************************************************************************/

uint8 CAN_Receiver(void){
        /*message sent using tx1*/
        if(g_bRXFlag1==1)
        {   
            /*set the rx to receive the array*/
            sCANMessage_rx.pui8MsgData = pui8MsgData;
            
            /*receive the array*/
            CANMessageGet(CAN0_BASE, 1, &sCANMessage_rx, 0);
            
            /*get the first element of the array*/
            r_data=pui8MsgData[0];
            
            /*reset the array*/
            pui8MsgData[0]=NULL;
            
            /*erase the flag*/
            g_bRXFlag1 = 0;
            
            /*return the received data*/
            return r_data;
            
        }
        
         if(g_bRXFlag2==1)
        {
            /*set the rx to receive the array*/
            sCANMessage_rx.pui8MsgData = pui8MsgData;
            
            /*receive the array*/
            CANMessageGet(CAN0_BASE, 2, &sCANMessage_rx, 0);
            
            /*get the first element of the array*/
            r_data=pui8MsgData[0];
            
            /*reset the array*/
            pui8MsgData[0]=NULL;
            
            /*erase the flag*/
            g_bRXFlag2 = 0;
            
            /*return the received data*/
        return r_data;    
        }
         
}