#include <stdint.h>
#include "tm4c123gh6pm.h"

/**
 * main.c
 */

void GPIO_PORTF_Init(void);
void SystickHandler(void);
void Systick_Init(void);

volatile uint32_t systick_count = 1;
volatile uint32_t global_counter = 0;


int main(void)
{

    GPIO_PORTF_Init();
    //Systick_Init();
     while(1);

}

void SW2_Handler(void)
{
    //Start with some nops and then try some dela

    //GPIO_PORTF_DATA_R ^= 0x2;
    global_counter ++;
    //GPIO_PORTF_ICR_R = 0x10;
    GPIO_PORTF_ICR_R = 0x10;
    __asm(" DSB");
}


void SystickHandler(void)
{
    systick_count++;
    if(systick_count==1000)
    {
        systick_count = 0;
        GPIO_PORTF_DATA_R ^= 0x2;
    }
}

void Systick_Init()
{
    NVIC_ST_RELOAD_R = 0x9C4;
    NVIC_ST_CURRENT_R = 0x0;
    //Enable Systick:
    // SYST_CSR = 0x00000101 -- 0x5
    NVIC_ST_CTRL_R = 0x5;
}


void GPIO_PORTF_Init(void)
{
    //PF0 <-- SW2
    //PF4 <-- SW1
    //Need to enable interrupt on SW1

    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
    GPIO_PORTF_DEN_R  = 0x1F;
    GPIO_PORTF_PUR_R  = 0x11;
    GPIO_PORTF_DIR_R  = 0x0E;

    //Shut off all LEDs:
    GPIO_PORTF_DATA_R=0x0;

    // Enabling Interrupts

    //GPIOIS -- Interrupt Sense    --> 0 for edge              --> 0x0
    GPIO_PORTF_IS_R = 0x0;

    //GPIOIBE -- Both Edges       --> 0 for single edge       --> 0x0
    GPIO_PORTF_IBE_R = 0x0;

    //GPIOIEV -- Interropt Event  --> 0 for falling edge      --> 0x00
    GPIO_PORTF_IEV_R = 0x0;

    //GPIOICR -- Interript clear -- must be cleared by writing 1 to corresponding bit --> 0xff
    GPIO_PORTF_ICR_R = 0xff;

    //GPIOIM -- Interrupt Mask    --> 1 for unmasked (enabled)--> 0x01
    GPIO_PORTF_IM_R = 0x10;

    //GPIORIS -- Raw Int Status
    //GPIOMIS -- Masked Int Status

    //Interrupt Number = 30
    // EN0 -- 0x40000000
   NVIC_EN0_R = 0x40000000;

}
