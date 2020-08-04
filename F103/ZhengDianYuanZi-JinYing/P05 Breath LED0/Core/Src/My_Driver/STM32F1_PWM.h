#pragma once

#include "STM32F1_Timer.h"
/***********************************�궨��***********************************/
/*********************************ϵͳ�궨��******************/

/*********************************�����궨��******************/
/*******************************PWMͨ��ʹ�����*/
#define PWM_TIM3_CH2_Enable HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2)

/**********************************ȫ�ֱ���**********************************/
uint duty = 0;

/************************************����************************************/
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
