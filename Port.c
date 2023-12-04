/******************************************************************************
 * Module: Port
 * File Name: Port.c
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 * Author: Team 8
 ******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"


//STATIC const Dio_ConfigChannel * Dio_PortChannels = NULL_PTR;
static uint8 Port_Status = PORT_NOT_INITIALIZED;

static volatile uint32 * getPortBasePtr(Port_PinType PortPinId)
{
  /* calculating the PortId from the Port-Pin index */
  uint8 PortId = PortPinId / NUM_OF_PINS_SINGLE_PORT;
  
  /* according to PortId, the function will return the appropriate Base address */
  switch(PortId)
    {
        case  0: return (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
	case  1: return (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
	case  2: return (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
	case  3: return (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
        case  4: return (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
        case  5: return (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
    }
  
  /* if there's no such Port-Pin index in the MCU */
  return NULL_PTR;
}

static uint8 getPortId(Port_PinType PortPinId)
{
  return PortPinId / NUM_OF_PINS_SINGLE_PORT;
}

static uint8 getPinId(Port_PinType PortPinId)
{
  return PortPinId % NUM_OF_PINS_SINGLE_PORT;
}

/************************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to configuration set.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port Driver module.
************************************************************************************/
void Port_Init( const Port_ConfigType* ConfigPtr )
{
  Port_Status = PORT_INITIALIZED;
  uint8 Port_Pin_Index = 0;
  
  while(Port_Pin_Index < PORT_ALL_PINS_NUMBER)
  {
    /* if the configuration ptr is Null, head On to next Port-Pin Index */
    if(Port_pinConfigurationSet.Pins[Port_Pin_Index] == NULL_PTR)
    {
      /* Do Nothing.... */
       
    }
    /* if the configuration ptr is set to specific config, Configure the Pin */
    else
    {
      /* get the pin number (PinId) and the Port number (PortId) */
      uint8 PinId = getPinId(Port_Pin_Index);
      uint8 PortId = getPortId(Port_Pin_Index);
      volatile uint32 delay = 0;
      
      /* get the configuration struct for this specific Port-Pin */
      Port_ConfigPin PinConfig = *Port_pinConfigurationSet.Pins[Port_Pin_Index];
      
      /* get the Port registed of the selected Pin */
      volatile uint32 * PortGpio_Ptr = getPortBasePtr(Port_Pin_Index);
      
      if(PortGpio_Ptr == NULL_PTR)
      {
        /* do nothing */
      }
      else
      {
        /* Enable clock for PORT and allow time for clock to start*/
        SYSCTL_REGCGC2_REG |= (1<<PortId);
        delay = SYSCTL_REGCGC2_REG;
    
        if( ((PortId == 3) && (PinId == 7)) || ((PortId == 5) && (PinId == 0)) ) /* PD7 or PF0 */
        {
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */   
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , PinId);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
        }
        else
        {
            /* Do Nothing ... No need to unlock the commit register for this pin */
        }
        
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PinId);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PinId);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (PinId * 4));     /* Clear the PMCx bits for this pin */
            
            if(PinConfig.direction == PORT_PIN_OUT)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PinId);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                
                if(PinConfig.initial_value == STD_HIGH)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , PinId);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                }
                else
                {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , PinId);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                }
            }
            else if(PinConfig.direction == PORT_PIN_IN)
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PinId);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                
                if(PinConfig.resistor == PULL_UP)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , PinId);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                }
                else if(PinConfig.resistor == PULL_DOWN)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , PinId);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                }
                else
                {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , PinId);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , PinId);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                }
            }
            else
            {
                /* Do Nothing */
            }
            
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PinId);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */

        
        }
      }
    Port_Pin_Index++;
    }
    
  }

