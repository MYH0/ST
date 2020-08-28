#include "oled.h"
#include "i2c.h"
#include "oledfont.h"          //头文件

//https://blog.csdn.net/notMine/article/details/79317782
//https://blog.csdn.net/qq_39542860/article/details/105907958?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.channel_param&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.channel_param

uint8_t CMD_Data[28] = {
	0xAE,		//关显示
	0xD5, 0x80,	//设置时钟频率和分频，默认频率不分频
	0xA8, 0x3F,	//设置驱动路数，默认值1/64
	0xD3, 0x00,	//设置显示偏移，偏移量为0
	0x40,		//设置屏幕起始行
	0x20, 0x02,	//设置内存地址模式，默认值：页地址模式
	0xB0,		//设置页起始地址
	0x00, 0x10,	//页地址模式下设置列起始地址低位，列起始地址高位
	0xA1,		//段重定义设置,bit0:0,0->0;1,0->127
	0xC8,		//设置列输出扫描方向
	0xDA, 0x12,	//设置COM 硬件引脚配置，备选的列引脚配置, 列输出扫描方向从COM63到COM0(C8h), 禁用列左/右映射
	0x81, 0xef,	//开始设置对比度，默认值
	0xD9, 0xF1,	//开始设置预充电周期，默认值
	0xDB, 0x30,	//设置VCOMH 电压倍率，默认值0.83*VCC
	0xA4,		//依照RAM输出
	0xA6,		//正常显示不反转屏幕
	0x8D, 0x14, //电荷泵设置,打开
	0xAF		//开显示
};

void WriteCmd(void)
{
	uint8_t i = 0;
	for (i = 0; i < 28; i++)
	{
		HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x00, I2C_MEMADD_SIZE_8BIT, CMD_Data + i, 1, 0x100);
	}
}
//向设备写控制命令
void OLED_WR_CMD(uint8_t cmd)
{
	HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x00, I2C_MEMADD_SIZE_8BIT, &cmd, 1, 0x100);
}
//向设备写数据
void OLED_WR_DATA(uint8_t data)
{
	HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x40, I2C_MEMADD_SIZE_8BIT, &data, 1, 0x100);
}
//初始化oled屏幕
void OLED_Init(void)
{
	HAL_Delay(200);

	WriteCmd();
}
//清屏
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
//开启OLED显示    
void OLED_Display_On(void)
{
	OLED_WR_CMD(0X8D);  //SET DCDC命令
	OLED_WR_CMD(0X14);  //DCDC ON
	OLED_WR_CMD(0XAF);  //DISPLAY ON
}
//关闭OLED显示     
void OLED_Display_Off(void)
{
	OLED_WR_CMD(0X8D);  //SET DCDC命令
	OLED_WR_CMD(0X10);  //DCDC OFF
	OLED_WR_CMD(0XAE);  //DISPLAY OFF
}
void OLED_Set_Pos(uint8_t x, uint8_t y)		//X：列  Y:页
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
		OLED_WR_CMD(0xb0 + i);    //设置页地址（0~7）
		OLED_WR_CMD(0x00);      //设置显示位置—列低地址
		OLED_WR_CMD(0x10);      //设置显示位置—列高地址   
		for (n = 0; n < 128; n++)
			OLED_WR_DATA(1);
	} //更新显示
}
unsigned int oled_pow(uint8_t m, uint8_t n)
{
	unsigned int result = 1;
	while (n--)
		result *= m;
	return result;
}
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//num:数值(0~4294967295);	 		  
void OLED_ShowNum(uint8_t x, uint8_t y, unsigned int num, uint8_t len, uint8_t size)
{
	uint8_t t, temp;
	uint8_t enshow = 0;
	for (t = 0; t < len; t++)
	{
		temp = (num / oled_pow(10, len - t - 1)) % 10;
		if (enshow == 0 && t < (len - 1))	//判断首位是否为0
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
//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//size:选择字体 16/12 
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t Char_Size)
{
	unsigned char c = 0, i = 0;
	c = chr - ' ';//得到偏移后的值			
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

//显示一个字符号串
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
//显示汉字
//hzk 用取模软件得出的数组
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