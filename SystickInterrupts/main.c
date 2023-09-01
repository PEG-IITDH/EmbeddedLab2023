#include <stdint.h>
#include "tm4c123gh6pm.h"

/**
 * main.c
 */


void GPIO_PORTF_Init(void);

int main(void)
{

    NVIC_ST_RELOAD_R = 0x10;
    NVIC_ST_CURRENT_R = 0x0;
    //Enable Systick:
    // SYST_CSR = 0x00000101 -- 0x5
    NVIC_ST_CTRL_R = 0x5;

    while(1);

}



void GPIO_PORTF_Init(void)
{
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
    GPIO_PORTF_DEN_R  = 0x1F;
    GPIO_PORTF_PUR_R  = 0x11;
    GPIO_PORTF_DIR_R  = 0x0E;
}
