#pragma once
/***********************************Define********************************/

/*********************************常数宏定义**********/

/********************************GPIO--PORT*/
#define PA GPIOA
#define PB GPIOB
#define PC GPIOC
#define PD GPIOD
#define PE GPIOE
#define PF GPIOF
#define PG GPIOG

/******************************GPIO--PIN-BIT*/
#define BIT0 GPIO_PIN_0
#define BIT1 GPIO_PIN_1
#define BIT2 GPIO_PIN_2
#define BIT3 GPIO_PIN_3
#define BIT4 GPIO_PIN_4
#define BIT5 GPIO_PIN_5
#define BIT6 GPIO_PIN_6
#define BIT7 GPIO_PIN_7

#define BIT8 GPIO_PIN_8
#define BIT9 GPIO_PIN_9
#define BIT10 GPIO_PIN_10
#define BIT11 GPIO_PIN_11
#define BIT12 GPIO_PIN_12
#define BIT13 GPIO_PIN_13
#define BIT14 GPIO_PIN_14
#define BIT15 GPIO_PIN_15

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

/*****************************************Key*/
/*//KEY0-PE4
#define KEY0_PORT PE
#define KEY0_PIN B4			
//KEY1-PE3
#define KEY1_PORT PE
#define KEY1_PIN B3			
//KEY_UP-PA0
#define KEYUP_PORT PA
#define KEYUP_PIN B0	

//KEY-Status
#define KEY0_UP 1
#define KEY1_UP 1
#define KEYUP_UP 0

#define KEY0_Down 0
#define KEY1_Down 0
#define KEYUP_Down 1
*/
/**********************************操作宏定义**********/

/*************************************LED*/
//LED0-Red
#define LED0_ON HAL_GPIO_WritePin(PB,B5,0)
#define LED0_OFF HAL_GPIO_WritePin(PB,B5,1)
#define LED0_Toggle HAL_GPIO_TogglePin(PB, B5)
//LED1-Green
#define LED1_ON HAL_GPIO_WritePin(PE,B5,0)
#define LED1_OFF HAL_GPIO_WritePin(PE,B5,1)
#define LED1_Toggle HAL_GPIO_TogglePin(PE, B5)

/************************************BEEP*/
#define BEEP_ON HAL_GPIO_WritePin(PB,B8,1)
#define BEEP_OFF HAL_GPIO_WritePin(PB,B8,0)
#define BEEP_Toggle HAL_GPIO_TogglePin(PB,B8)

/************************************操作**********/

/********************************KEY Function*/
//KEY0
/*
void KEY0_Function()
{
	LED0_Toggle;
}
*/
//KEY1
/*
void KEY1_Function()
{
	LED1_Toggle;
}
*/
//KEYUP
/*
void KEYUP_Function()
{
	BEEP_Toggle;
}
*/
/********************************外部中断按键检测*/
/*
void Key_Scan_Common(uint GPIO_Interrupt_PIN)
{
	Delay_ms(20);
	switch (GPIO_Interrupt_PIN)
	{
	case KEY0_PIN:
	{
		if (HAL_GPIO_ReadPin(KEY0_PORT, KEY0_PIN) == KEY0_Down)
			KEY0_Function();
		break;
	}
	case KEY1_PIN:
	{
		if (HAL_GPIO_ReadPin(KEY1_PORT, KEY1_PIN) == KEY1_Down)
			KEY1_Function();
		break;
	}
	case KEYUP_PIN:
	{
		if (HAL_GPIO_ReadPin(KEYUP_PORT, KEYUP_PIN) == KEYUP_Down)
			KEYUP_Function();
		break;
	}
	default:break;
	}
}
*/
/**********************************进入外部中断*/
/*
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	Key_Scan_Common(GPIO_Pin);
}
*/