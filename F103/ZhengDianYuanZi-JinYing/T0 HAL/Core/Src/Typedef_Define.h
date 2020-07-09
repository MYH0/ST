#ifndef SRC_TYPEDEF_DEFINE_H_
#define SRC_TYPEDEF_DEFINE_H_

#include "stm32f103xe.h"
/***************************Typedef********************************/

typedef long int lint;

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long int ulint;

/****************************Define********************************/

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




#endif /* SRC_TYPEDEF_DEFINE_H_ */
