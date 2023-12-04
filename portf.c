# include "portf.h"


void GPIO_Pins_Init(void)
{
    /* Enable clock for PORTF and allow time for clock to start*/  
    volatile unsigned long delay = 0;
    SYSCTL_REGCGC2_REG |= 0x00000020;
    delay = SYSCTL_REGCGC2_REG;
    while((SYSCTL_REGCGC2_REG & 0x00000020) == 0){}; 
    GPIO_PORTF_LOCK_REG    = 0x4C4F434B;    /* Unlock the GPIO_PORTF_CR_REG */
    GPIO_PORTF_CR_REG     = 0x01f;        /* Enable changes on PF0 */
    //GPIO_PORTF_AMSEL_REG  &= 0xE8;          /* Disable Analog on PF0, PF1, PF2 and PF4 */
    //GPIO_PORTF_PCTL_REG   &= 0xFFF0F000;    /* Clear PMCx bits for PF0, PF1, PF2 and PF4 to use it as GPIO pin */
    GPIO_PORTF_DIR_REG    = 0x0E ;      /* Configure PF0 & PF1 as input pin and Configure PF1 & PF2 as output pins */
   // GPIO_PORTF_AFSEL_REG  &= 0xE8;          /* Disable alternative function on PF0, PF1, PF2 and PF4 */
    GPIO_PORTF_PUR_REG    |= 0x11;          /* Enable pull-up on PF0 and PD4 */
    GPIO_PORTF_DEN_REG    |= 0x1f;          /* Enable Digital I/O on PF0, PF1, PF2 and PF4 */
}
