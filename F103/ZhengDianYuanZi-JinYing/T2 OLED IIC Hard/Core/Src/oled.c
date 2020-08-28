#include "oled.h"
#include "i2c.h"
#include "oledfont.h"          //ͷ�ļ�

//https://blog.csdn.net/notMine/article/details/79317782
//https://blog.csdn.net/qq_39542860/article/details/105907958?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.channel_param&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.channel_param

uint8_t CMD_Data[28] = {
	0xAE,		//����ʾ
	0xD5, 0x80,	//����ʱ��Ƶ�ʺͷ�Ƶ��Ĭ��Ƶ�ʲ���Ƶ
	0xA8, 0x3F,	//��������·����Ĭ��ֵ1/64
	0xD3, 0x00,	//������ʾƫ�ƣ�ƫ����Ϊ0
	0x40,		//������Ļ��ʼ��
	0x20, 0x02,	//�����ڴ��ַģʽ��Ĭ��ֵ��ҳ��ַģʽ
	0xB0,		//����ҳ��ʼ��ַ
	0x00, 0x10,	//ҳ��ַģʽ����������ʼ��ַ��λ������ʼ��ַ��λ
	0xA1,		//���ض�������,bit0:0,0->0;1,0->127
	0xC8,		//���������ɨ�跽��
	0xDA, 0x12,	//����COM Ӳ���������ã���ѡ������������, �����ɨ�跽���COM63��COM0(C8h), ��������/��ӳ��
	0x81, 0xef,	//��ʼ���öԱȶȣ�Ĭ��ֵ
	0xD9, 0xF1,	//��ʼ����Ԥ������ڣ�Ĭ��ֵ
	0xDB, 0x30,	//����VCOMH ��ѹ���ʣ�Ĭ��ֵ0.83*VCC
	0xA4,		//����RAM���
	0xA6,		//������ʾ����ת��Ļ
	0x8D, 0x14, //��ɱ�����,��
	0xAF		//����ʾ
};

void WriteCmd(void)
{
	uint8_t i = 0;
	for (i = 0; i < 28; i++)
	{
		HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x00, I2C_MEMADD_SIZE_8BIT, CMD_Data + i, 1, 0x100);
	}
}
//���豸д��������
void OLED_WR_CMD(uint8_t cmd)
{
	HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x00, I2C_MEMADD_SIZE_8BIT, &cmd, 1, 0x100);
}
//���豸д����
void OLED_WR_DATA(uint8_t data)
{
	HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x40, I2C_MEMADD_SIZE_8BIT, &data, 1, 0x100);
}
//��ʼ��oled��Ļ
void OLED_Init(void)
{
	HAL_Delay(200);

	WriteCmd();
}
//����
void OLED_Clear(void)
{
	uint8_t i, n;
	for (i = 0; i < 8; i++)
	{
		OLED_WR_CMD(0xb0 + i);
		OLED_WR_CMD(0x00);
		OLED_WR_CMD(0x10);
		for (n = 0; n < 128; n++)
			OLED_WR_DATA(0);
	}
}
//����OLED��ʾ    
void OLED_Display_On(void)
{
	OLED_WR_CMD(0X8D);  //SET DCDC����
	OLED_WR_CMD(0X14);  //DCDC ON
	OLED_WR_CMD(0XAF);  //DISPLAY ON
}
//�ر�OLED��ʾ     
void OLED_Display_Off(void)
{
	OLED_WR_CMD(0X8D);  //SET DCDC����
	OLED_WR_CMD(0X10);  //DCDC OFF
	OLED_WR_CMD(0XAE);  //DISPLAY OFF
}
void OLED_Set_Pos(uint8_t x, uint8_t y)		//X����  Y:ҳ
{
	OLED_WR_CMD(0xb0 + y);
	OLED_WR_CMD(((x & 0xf0) >> 4) | 0x10);
	OLED_WR_CMD(x & 0x0f);
}

void OLED_On(void)
{
	uint8_t i, n;
	for (i = 0; i < 8; i++)
	{
		OLED_WR_CMD(0xb0 + i);    //����ҳ��ַ��0~7��
		OLED_WR_CMD(0x00);      //������ʾλ�á��е͵�ַ
		OLED_WR_CMD(0x10);      //������ʾλ�á��иߵ�ַ   
		for (n = 0; n < 128; n++)
			OLED_WR_DATA(1);
	} //������ʾ
}
unsigned int oled_pow(uint8_t m, uint8_t n)
{
	unsigned int result = 1;
	while (n--)
		result *= m;
	return result;
}
//��ʾ2������
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//num:��ֵ(0~4294967295);	 		  
void OLED_ShowNum(uint8_t x, uint8_t y, unsigned int num, uint8_t len, uint8_t size)
{
	uint8_t t, temp;
	uint8_t enshow = 0;
	for (t = 0; t < len; t++)
	{
		temp = (num / oled_pow(10, len - t - 1)) % 10;
		if (enshow == 0 && t < (len - 1))	//�ж���λ�Ƿ�Ϊ0
		{
			if (temp == 0)
			{
				OLED_ShowChar(x + (size / 2) * t, y, ' ', size);
				continue;
			}
			else enshow = 1;

		}
		OLED_ShowChar(x + (size / 2) * t, y, temp + '0', size);
	}
}
//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//size:ѡ������ 16/12 
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t Char_Size)
{
	unsigned char c = 0, i = 0;
	c = chr - ' ';//�õ�ƫ�ƺ��ֵ			
	if (x > 127)
	{
		x = 0;
		y += 2;
	}
	if (Char_Size == 16)
	{
		OLED_Set_Pos(x, y);
		for (i = 0; i < 8; i++)
			OLED_WR_DATA(F8X16[c][i]);
		OLED_Set_Pos(x, y + 1);
		for (i = 0; i < 8; i++)
			OLED_WR_DATA(F8X16[c][i + 8]);
	}
	else {
		OLED_Set_Pos(x, y);
		for (i = 0; i < 6; i++)
			OLED_WR_DATA(F6x8[c][i]);

	}
}

//��ʾһ���ַ��Ŵ�
void OLED_ShowString(uint8_t x, uint8_t y, uint8_t* chr, uint8_t Char_Size)
{
	unsigned char j = 0;
	while (chr[j] != '\0')
	{
		OLED_ShowChar(x, y, chr[j], Char_Size);
		x += 8;
		if (x > 127)
		{
			x = 0;
			y += 2;
		}
		j++;
	}
}
//��ʾ����
//hzk ��ȡģ����ó�������
void OLED_ShowCHinese(uint8_t x, uint8_t y, uint8_t no)
{
	uint8_t t = 0;
	OLED_Set_Pos(x, y);
	for (t = 0; t < 16; t++)
	{
		OLED_WR_DATA(Hzk[no][t]);
	}
	OLED_Set_Pos(x, y + 1);
	for (t = 0; t < 16; t++)
	{
		OLED_WR_DATA(Hzk[no][t + 16]);
	}
}