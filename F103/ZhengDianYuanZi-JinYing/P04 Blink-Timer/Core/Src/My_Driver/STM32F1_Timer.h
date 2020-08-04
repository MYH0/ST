#pragma once

/***********************************定时器使能*******************************/
void TIM2_Enable()
{
    HAL_TIM_Base_Start_IT(&htim2);
}

//void TIM3_Enable()
//{
//    HAL_TIM_Base_Start_IT(&htim3);
//}
//
//void TIM4_Enable()
//{
//    HAL_TIM_Base_Start_IT(&htim4);
//}
//
//void TIM5_Enable()
//{
//    HAL_TIM_Base_Start_IT(&htim5);
//}


/***********************************进入定时中断******************************/
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
