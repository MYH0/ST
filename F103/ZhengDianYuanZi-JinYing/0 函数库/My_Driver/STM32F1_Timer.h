#pragma once

/***********************************��ʱ��ʹ��*******************************/
void TIM2_Enable()
{
    HAL_TIM_Base_Start_IT(&htim2);
}

/***********************************���붨ʱ�ж�******************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
    if (htim == (&htim2))
        TIM2_INT_FUNC();
//    if (htim == (&htim3))
//        TIM3_INT_FUNC();
//    if (htim == (&htim4))
//        TIM4_INT_FUNC();
//    if (htim == (&htim5))
//        TIM5_INT_FUNC();

}
