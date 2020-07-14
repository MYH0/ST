#ifndef SRC_GPIO_H_
#define SRC_GPIO_H_

/*************************Define********************************/

//LED Operate

//LED0-Red
#define LED0_ON HAL_GPIO_WritePin(PB,B5,0)
#define LED0_OFF HAL_GPIO_WritePin(PB,B5,1)
#define LED0_Toggle HAL_GPIO_TogglePin(PB, B5)

//LED-Green
#define LED1_ON HAL_GPIO_WritePin(PE,B5,0)
#define LED1_OFF HAL_GPIO_WritePin(PE,B5,1)
#define LED1_Toggle HAL_GPIO_TogglePin(PE, B5)


#endif /* SRC_GPIO_H_ */
