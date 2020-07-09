#ifndef SRC_GPIO_H_
#define SRC_GPIO_H_

/*************************Define********************************/

//LED Operate

//LED0-Red
#define LED0_ON HAL_GPIO_WritePin(PB,BIT5,0)
#define LED0_OFF HAL_GPIO_WritePin(PB,BIT5,1)
#define LED0_Toggle HAL_GPIO_TogglePin(PB, BIT5)

#endif /* SRC_GPIO_H_ */
