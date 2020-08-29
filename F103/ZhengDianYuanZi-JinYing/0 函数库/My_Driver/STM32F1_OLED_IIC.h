#pragma once
/*************************************ͷ�ļ�*****************************************/
#include "i2c.h"		//��CUBEMX����
#include "OLED_Dot.h"
/*************************************�궨��*****************************************/
/*************************************ȫ�ֱ���***************************************/

const uchar OLED_Init_Cmd_Group[28] =
{
	0xAE,		//����ʾ
	0xD5, 0x80,	//����ʱ��Ƶ�ʺͷ�Ƶ��Ĭ��Ƶ�ʲ���Ƶ
	0xA8, 0x3F,	//��������·����Ĭ��ֵ1/64
	0xD3, 0x00,	//������ʾƫ�ƣ�ƫ����Ϊ0
	0x40,		//������Ļ��ʼ��
	0x20, 0x02,	//�����ڴ��ַģʽ��Ĭ��ֵ��ҳ��ַģʽ
	0xB0,		//����ҳ��ʼ��ַ������һҳ��ʼ
	0x00, 0x10,	//ҳ��ַģʽ����������ʼ��ַ��λ������ʼ��ַ��λ
	0xA1,		//���ض�������,bit0:0,0->0;1,0->127
	0xC8,		//���������ɨ�跽��
	0xDA, 0x12,	//����COM Ӳ���������ã���ѡ������������, �����ɨ�跽���COM63��COM0(C8h), ��������/��ӳ��
	0x81, 0xef,	//��ʼ���öԱȶȣ�Ĭ��ֵ
	0xD9, 0xF1,	//��ʼ����Ԥ������ڣ�Ĭ��ֵ
	0xDB, 0x30,	//����VCOMH ��ѹ���ʣ�Ĭ��ֵ0.83*VCC
	0xA4,		//����RAM���
	0xA6,		//������ʾ����ת��Ļ
	0x8D, 0x14, //��ɱ�����,��---0x10Ϊ�ر�
	0xAF		//����ʾ---0xAEΪ�ر�
};
/**************************************����*******************************************/
/**************************************д������*******************/
void OLED_W_Cmd(uchar cmd)
{
	HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x00, I2C_MEMADD_SIZE_8BIT, &cmd, 1, 0x100);
}
/**************************************д������*******************/
void OLED_W_Data(uchar data)
{
	HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x40, I2C_MEMADD_SIZE_8BIT, &data, 1, 0x100);
}
/**************************************��ʼ��*********************/
void OLED_Init()
{
	HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x00, I2C_MEMADD_SIZE_8BIT, (uint8_t*)OLED_Init_Cmd_Group, 28, 0x100);
}
/**************************************����***********************/
void OLED_Clear()
{
	uchar page = 0, col = 0;
	for (page = 0; page < 8; page++)
	{
		OLED_W_Cmd(0xB0 + page);
		OLED_W_Cmd(0x00);
		OLED_W_Cmd(0x10);
		for (col = 0; col < 128; col++)
		{
			OLED_W_Data(0x00);
		}
	}
}
/**************************************����OLED��ʾ ****************/
void OLED_Display_On()
{
	OLED_W_Cmd(0x8D);
	OLED_W_Cmd(0x14);
	OLED_W_Cmd(0xAF);
}
/**************************************�ر�OLED��ʾ ****************/
void OLED_Display_Off()
{
	OLED_W_Cmd(0x8D);
	OLED_W_Cmd(0x10);
	OLED_W_Cmd(0xAE);
}
/**************************************OLED�������궨λ************/
void OLED_Set_Location(uchar col,uchar page)
{
	OLED_W_Cmd(0xB0 + page);
	OLED_W_Cmd(((col & 0xf0) >> 4) | 0x10);
	OLED_W_Cmd(col & 0x0f);
}
/**************************************OLED���������������*********/
/**************************************�ָ�Ϊ16*/
void OLED_Adjust_Location_High16(uchar col, uchar page)
{
	if (col > 127)
	{
		col = 0;
		page += 2;
	}
}
/**************************************��ʾ�ַ�********************/
void OLED_Show_Char_8x16(uchar col, uchar page, char ch)
{
	uchar ch_num = 0;
	uchar i = 0;
	ch_num = ch - ' ';//�õ�ƫ�ƺ��ֵ
	OLED_Adjust_Location_High16(col, page);

	OLED_Set_Location(col, page);
	for (i = 0; i < 8; i++)
	{
		OLED_W_Data(Char_8X16[ch_num][i]);
	}
	OLED_Set_Location(col, page + 1);
	for (i = 0; i < 8; i++)
	{
		OLED_W_Data(Char_8X16[ch_num][i + 8]);
	}
}
/**************************************��ʾ�ַ���********************/
void OLED_Show_String_8x16(uchar col, uchar page, uchar* str)
{
	uchar i = 0;
	OLED_Adjust_Location_High16(col, page);

	while (str[i] != '\0')
	{
		OLED_Show_Char_8x16(col, page, str[i]);
		col += 8;
		OLED_Adjust_Location_High16(col, page);
		i++;
	}
}
/**************************************��ʾ����**********************/
//lenΪ����λ��
void OLED_Show_Num_8x16(uchar col, uchar page, uint num, uchar len)
{
	uchar i = 0;
	uchar temp = 0;
	uchar first_bit = 0;
	OLED_Adjust_Location_High16(col, page);

	for (i = 0; i < len; i++)
	{
		temp = (num / low_pow(10, len - i - 1)) % 10;
		if (first_bit == 0 && i < (len - 1))		//�ж϶�λ���ֵ���λ�Ƿ�Ϊ0
		{
			if (temp == 0)
			{
				OLED_Show_Char_8x16(col, page, ' ');
				OLED_Set_Location(col + 8, page);
				continue;
			}
			else
				first_bit = 1;
		}
		OLED_Show_Char_8x16(col, page, temp + '0');
		col += 8;
	}
}
/**************************************��ʾ����**********************/
/***************************************16x16*/
void OLED_Show_Chinese_16x16(uchar col, uchar page, uchar hz_num)
{
	uchar i = 0;
	hz_num *= 2;
	OLED_Adjust_Location_High16(col, page);

	OLED_Set_Location(col, page);
	for (i = 0; i < 16; i++)
	{
		OLED_W_Data(Chinese_16x16[hz_num][i]);
	}
	OLED_Set_Location(col, page + 1);
	for (i = 0; i < 16; i++)
	{
		OLED_W_Data(Chinese_16x16[hz_num + 1][i]);
	}
}
/***************************************32x32*/
void OLED_Show_Chinese_32x32(uchar col, uchar page, uchar hz_num)
{
	uchar i = 0;
	hz_num *= 4;
	OLED_Adjust_Location_High16(col, page);

	OLED_Set_Location(col, page);
	for (i = 0; i < 32; i++)
	{
		OLED_W_Data(Chinese_32x32[hz_num][i]);
	}
	OLED_Set_Location(col, page + 1);
	for (i = 0; i < 32; i++)
	{
		OLED_W_Data(Chinese_32x32[hz_num + 1][i]);
	}
	OLED_Set_Location(col, page + 2);
	for (i = 0; i < 32; i++)
	{
		OLED_W_Data(Chinese_32x32[hz_num + 2][i]);
	}
	OLED_Set_Location(col, page + 3);
	for (i = 0; i < 32; i++)
	{
		OLED_W_Data(Chinese_32x32[hz_num + 3][i]);
	}
}
