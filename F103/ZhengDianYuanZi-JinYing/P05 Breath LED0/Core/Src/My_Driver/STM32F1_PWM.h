#pragma once

#include "STM32F1_Timer.h"
/***********************************宏定义***********************************/
/*********************************系统宏定义******************/

/*********************************动作宏定义******************/
/*******************************PWM通道使能输出*/
#define PWM_TIM3_CH2_Enable HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2)

/**********************************全局变量**********************************/
uint duty = 0;

/************************************操作************************************/
void PWM_Breath()
{
	while (duty < 500)
	{
		duty++;
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, duty);
		Delay_ms(1);
	}
	while (duty)
	{
		duty--;
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, duty);
		Delay_ms(1);

	}
	Delay_ms(200);

}
