#pragma once
/*************************************头文件*****************************************/
#include "i2c.h"		//由CUBEMX生成
#include "OLED_Dot.h"
/*************************************宏定义*****************************************/
/*************************************全局变量***************************************/

const uchar OLED_Init_Cmd_Group[28] =
{
	0xAE,		//关显示
	0xD5, 0x80,	//设置时钟频率和分频，默认频率不分频
	0xA8, 0x3F,	//设置驱动路数，默认值1/64
	0xD3, 0x00,	//设置显示偏移，偏移量为0
	0x40,		//设置屏幕起始行
	0x20, 0x02,	//设置内存地址模式，默认值：页地址模式
	0xB0,		//设置页起始地址，从哪一页开始
	0x00, 0x10,	//页地址模式下设置列起始地址低位，列起始地址高位
	0xA1,		//段重定义设置,bit0:0,0->0;1,0->127
	0xC8,		//设置列输出扫描方向
	0xDA, 0x12,	//设置COM 硬件引脚配置，备选的列引脚配置, 列输出扫描方向从COM63到COM0(C8h), 禁用列左/右映射
	0x81, 0xef,	//开始设置对比度，默认值
	0xD9, 0xF1,	//开始设置预充电周期，默认值
	0xDB, 0x30,	//设置VCOMH 电压倍率，默认值0.83*VCC
	0xA4,		//依照RAM输出
	0xA6,		//正常显示不反转屏幕
	0x8D, 0x14, //电荷泵设置,打开---0x10为关闭
	0xAF		//开显示---0xAE为关闭
};
/**************************************操作*******************************************/
/**************************************写入命令*******************/
void OLED_W_Cmd(uchar cmd)
{
	HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x00, I2C_MEMADD_SIZE_8BIT, &cmd, 1, 0x100);
}
/**************************************写入数据*******************/
void OLED_W_Data(uchar data)
{
	HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x40, I2C_MEMADD_SIZE_8BIT, &data, 1, 0x100);
}
/**************************************初始化*********************/
void OLED_Init()
{
	HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x00, I2C_MEMADD_SIZE_8BIT, (uint8_t*)OLED_Init_Cmd_Group, 28, 0x100);
}
/**************************************清屏***********************/
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
/**************************************开启OLED显示 ****************/
void OLED_Display_On()
{
	OLED_W_Cmd(0x8D);
	OLED_W_Cmd(0x14);
	OLED_W_Cmd(0xAF);
}
/**************************************关闭OLED显示 ****************/
void OLED_Display_Off()
{
	OLED_W_Cmd(0x8D);
	OLED_W_Cmd(0x10);
	OLED_W_Cmd(0xAE);
}
/**************************************OLED像素坐标定位************/
void OLED_Set_Location(uchar col,uchar page)
{
	OLED_W_Cmd(0xB0 + page);
	OLED_W_Cmd(((col & 0xf0) >> 4) | 0x10);
	OLED_W_Cmd(col & 0x0f);
}
/**************************************OLED像素坐标矫正坐标*********/
/**************************************字高为16*/
void OLED_Adjust_Location_High16(uchar col, uchar page)
{
	if (col > 127)
	{
		col = 0;
		page += 2;
	}
}
/**************************************显示字符********************/
void OLED_Show_Char_8x16(uchar col, uchar page, char ch)
{
	uchar ch_num = 0;
	uchar i = 0;
	ch_num = ch - ' ';//得到偏移后的值
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
/**************************************显示字符串********************/
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
/**************************************显示数字**********************/
//len为数字位数
void OLED_Show_Num_8x16(uchar col, uchar page, uint num, uchar len)
{
	uchar i = 0;
	uchar temp = 0;
	uchar first_bit = 0;
	OLED_Adjust_Location_High16(col, page);

	for (i = 0; i < len; i++)
	{
		temp = (num / low_pow(10, len - i - 1)) % 10;
		if (first_bit == 0 && i < (len - 1))		//判断多位数字的首位是否为0
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
/**************************************显示汉字**********************/
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
