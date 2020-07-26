#pragma once

#include "S32F1_GPIO.H"

/**********************************宏定义*************************************/
/********************************接口宏定义***************/
//KEY0-PE4
#define KEY0_PORT PE
#define KEY0_PIN B4			
//KEY1-PE3
#define KEY1_PORT PE
#define KEY1_PIN B3			
//KEY_UP-PA0
#define KEYUP_PORT PA
#define KEYUP_PIN B0	

/********************************常数宏定义***************/
//按键状态
#define KEY0_UP 1
#define KEY1_UP 1
#define KEYUP_UP 0

#define KEY0_Down 0
#define KEY1_Down 0
#define KEYUP_Down 1

/********************************提前声明**************************************/
/********************************全局变量******************/

/********************************函数******************/
void KEY0_Function();
void KEY1_Function();
void KEYUP_Function();
void Key_Scan_EXTI(uint);
void HAL_GPIO_EXTI_Callback(uint16_t);
/**********************************动作****************************************/
/********************************按键功能******************/
//KEY0
void KEY0_Function()
{
	LED0_Toggle;
}

//KEY1
void KEY1_Function()
{
	LED1_Toggle;
}

//KEYUP
void KEYUP_Function()
{
	BEEP_Toggle;
}

/******************************外部中断按键检测**************/
void Key_Scan_EXTI(uint GPIO_Interrupt_PIN)
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

/**********************************进入外部中断*****************/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	Key_Scan_EXTI(GPIO_Pin);
}

