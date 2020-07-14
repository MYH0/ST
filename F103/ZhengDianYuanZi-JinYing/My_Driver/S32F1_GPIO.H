#pragma once

/*************************Define********************************/

//GPIO--PORT
#define PA GPIOA
#define PB GPIOB
#define PC GPIOC
#define PD GPIOD
#define PE GPIOE
#define PF GPIOF
#define PG GPIOG

//GPIO--PIN-BIT
#define BIT0 1<<0
#define BIT1 1<<1
#define BIT2 1<<2
#define BIT3 1<<3
#define BIT4 1<<4
#define BIT5 1<<5
#define BIT6 1<<6
#define BIT7 1<<7

#define BIT8 1<<8
#define BIT9 1<<9
#define BIT10 1<<10
#define BIT11 1<<11
#define BIT12 1<<12
#define BIT13 1<<13
#define BIT14 1<<14
#define BIT15 1<<15

#define BIT_Low8 0x00ff
#define BIT_High8 0xff00
#define BIT_ALL16 0xffff

//进一步精简
#define B0 BIT0
#define B1 BIT1
#define B2 BIT2
#define B3 BIT3
#define B4 BIT4
#define B5 BIT5
#define B6 BIT6
#define B7 BIT7

#define B8 BIT8
#define B9 BIT9
#define B10 BIT10
#define B11 BIT11
#define B12 BIT12
#define B13 BIT13
#define B14 BIT14
#define B15 BIT15

#define B8L BIT_Low8
#define B8H BIT_High8
#define B16A BIT_ALL16


//LED Operate

//LED0-Red
#define LED0_ON HAL_GPIO_WritePin(PB,B5,0)
#define LED0_OFF HAL_GPIO_WritePin(PB,B5,1)
#define LED0_Toggle HAL_GPIO_TogglePin(PB, B5)

//LED1-Green
#define LED1_ON HAL_GPIO_WritePin(PE,B5,0)
#define LED1_OFF HAL_GPIO_WritePin(PE,B5,1)
#define LED1_Toggle HAL_GPIO_TogglePin(PE, B5)

//BEEP
#define BEEP_ON HAL_GPIO_WritePin(PB,B8,1)
#define BEEP_OFF HAL_GPIO_WritePin(PB,B8,0)