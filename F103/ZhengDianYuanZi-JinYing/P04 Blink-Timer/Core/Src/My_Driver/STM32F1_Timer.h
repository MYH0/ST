#pragma once

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
