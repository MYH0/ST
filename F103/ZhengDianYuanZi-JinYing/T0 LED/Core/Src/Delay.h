#ifndef SRC_DELAY_H_
#define SRC_DELAY_H_

void Delay_us(uint nus)
{
	uint temp;
	SysTick->LOAD = 9 * nus;
	SysTick->VAL = 0X00;		//��ռ�ʱ��
	SysTick->CTRL = 0X01;		//ʹ�ܣ����������޶����������ⲿʱ��Դ
	do
	{
		temp = SysTick->CTRL;		//��ȡ��ǰ������ֵ
	} while ((temp & 0x01) && (!(temp & (1 << 16))));	//�ȴ�ʱ�䵽��
	SysTick->CTRL = 0x00;			//�رռ�����
	SysTick->VAL = 0X00;			//��ռ�����
}

void Delay_ms(uint nms)
{
	uint temp;
	SysTick->LOAD = 9000 * nms;
	SysTick->VAL = 0X00;			//��ռ�����
	SysTick->CTRL = 0X01;			//ʹ�ܣ����������޶����������ⲿʱ��Դ
	do
	{
		temp = SysTick->CTRL;		//��ȡ��ǰ������ֵ
	} while ((temp & 0x01) && (!(temp & (1 << 16))));	//�ȴ�ʱ�䵽��
	SysTick->CTRL = 0x00;			//�رռ�����
	SysTick->VAL = 0X00;			//��ռ�����
}

#endif /* SRC_DELAY_H_ */
