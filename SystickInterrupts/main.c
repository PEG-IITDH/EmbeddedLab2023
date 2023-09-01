#include <stdint.h>
#include "tm4c123gh6pm.h"

/**
 * main.c
 */

void GPIO_PORTF_Init(void);
void SystickHandler(void);

volatile uint32_t systick_count = 1;

int main(void)
{

    GPIO_PORTF_Init();
    NVIC_ST_RELOAD_R = 0x9C4;
    NVIC_ST_CURRENT_R = 0x0;
    //Enable Systick:
    // SYST_CSR = 0x00000111 -- 0x7
    NVIC_ST_CTRL_R = 0x7;
    while(1);

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


void GPIO_PORTF_Init(void)
{
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
    GPIO_PORTF_DEN_R  = 0x1F;
    GPIO_PORTF_PUR_R  = 0x11;
    GPIO_PORTF_DIR_R  = 0x0E;
}
