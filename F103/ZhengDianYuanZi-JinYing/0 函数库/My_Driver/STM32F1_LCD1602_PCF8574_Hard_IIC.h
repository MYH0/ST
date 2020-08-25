//https://controllerstech.com/i2c-lcd-in-stm32/
#pragma once
/*************************************宏定义*****************************************/
/**************************************宏变量**************/
#define Slave_Address_LCD1602_PCF8574 0x4E //看具体情况
/**************************************宏操作**************/
#define LCD1602_Clear LCD1602_Clear_Display()
/************************************全局变量****************************************/
int row = 0;	//行
int col = 0;	//列
/**************************************操作******************************************/
/**************************************写命令**************/
void LCD1602_W_Cmd(char cmd)
{
	char cmd_l = 0;
	char cmd_h = 0;
	uchar cmd_group[4];
	cmd_h = cmd & 0xf0;
	cmd_l = (cmd << 4) & 0xf0;
	cmd_group[0] = cmd_h | 0x0c;	// en = 1，rs = 0 
	cmd_group[1] = cmd_h | 0x08;	// en = 0，rs = 0 
	cmd_group[2] = cmd_l | 0x0c;	// en = 1，rs = 0 
	cmd_group[3] = cmd_l | 0x08;	// en = 0，rs = 0 
	HAL_I2C_Master_Transmit(&hi2c1, Slave_Address_LCD1602_PCF8574, (uint8_t*)cmd_group, 4, 100);
}
/**************************************写数据**************/
void LCD1602_W_Data(char data)
{
	char data_l = 0;
	char data_h = 0;
	uchar data_group[4];
	data_h = data & 0xf0;
	data_l = (data << 4) & 0xf0;
	data_group[0] = data_h | 0x0D;  //en=1, rs=1
	data_group[1] = data_h | 0x09;  //en=0, rs=1
	data_group[2] = data_l | 0x0D;  //en=1, rs=1
	data_group[3] = data_l | 0x09;  //en=0, rs=1
	HAL_I2C_Master_Transmit(&hi2c1, Slave_Address_LCD1602_PCF8574, (uint8_t*)data_group, 4, 100);
}
/**************************************写字符串*************/
void LCD1602_W_Str(char* str)
{
	while (*str)
		LCD1602_W_Data(*str++);
}
/**************************************移动光标*************/
void LCD1602_Move_Cur(int row, int col)
{
	if (row == 1)
		col |= 0xc0;
	else
		col |= 0x80;
	LCD1602_W_Cmd(col);
}
/**************************************清屏*****************/
void LCD1602_Clear_Display()
{
	LCD1602_W_Cmd(0x01);
}
/**************************************初始化**************/
void LCD1602_Init()
{
	LCD1602_W_Cmd(0x28);	//4位，2行，5*8显示
	Delay_ms(1);
	LCD1602_W_Cmd(0x08);	//关闭显示
	Delay_ms(1);
	LCD1602_Clear_Display();	//清屏
	Delay_ms(1);
	LCD1602_W_Cmd(0x06);	//Entry mode set (设置输入模式)
	Delay_ms(1);
	LCD1602_W_Cmd(0x0c);	//显示开关-开显示，关光标

}



