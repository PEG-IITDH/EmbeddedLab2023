#include <stdint.h>
#include "tm4c123gh6pm.h"

#define ZERO_DEF 0

/**
 * main.c
 */

void counter_loop (void);
void GPIO_PORTF_Init(void);

int main(void)

/*
 * GPIODATA ->> 0xE
 * GPIODIR ->> COnfigure each pin as I/P or O/P >> <0000 1110> = 0xE
 * GPIOPCTL
    GPIOSLR -- Slew Rate Control
x    GPIOPUR -- Pull Up Enable -- 0x11
x    GPIOPDR -- Pull Down Enable
x    GPIOODR -- OpenDrain
x   GPIODEN -- GPIO Digital Enable -- 0x00011111 >> 0x1F
 */



{

    GPIO_PORTF_Init();
    register uint32_t x = ZERO_DEF;


    GPIO_PORTF_DATA_R = 0xE;
    while(1)
    {
        GPIO_PORTF_DATA_R = 0x0;
        GPIO_PORTF_DATA_R = 0x2;
        GPIO_PORTF_DATA_R = 0x4;
        GPIO_PORTF_DATA_R = 0x8;
        GPIO_PORTF_DATA_R = 0xE;
    }



    while (1)
    {
        x++;
        counter_loop();
    }
}

void GPIO_PORTF_Init(void)
{
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
    GPIO_PORTF_DEN_R  = 0x1F;
    GPIO_PORTF_PUR_R  = 0x11;
    GPIO_PORTF_DIR_R  = 0x0E;
}

void counter_loop (void)
{
    register uint32_t count=10;
    while(count>0)
        count--;

}
