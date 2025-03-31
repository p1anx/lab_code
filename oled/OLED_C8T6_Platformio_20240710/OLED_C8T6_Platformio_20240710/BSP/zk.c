#include "oled.h"
#include "spi.h"

//送指令到晶联讯字库IC
void Send_Command_to_ROM(u8 dat)
{
//	u8 i;
//	for(i=0;i<8;i++)
//	{
//		ZK_SCLK_Clr();
//		if(dat&0x80)
//		{
//			ZK_MOSI_Set();
//    }
//		else
//		{
//			ZK_MOSI_Clr();
//    }
//		dat<<=1;
//		ZK_SCLK_Set();
//  }
    HAL_SPI_Transmit(&hspi1, &dat, 1, 0X100);
    
}

//从晶联讯字库IC中取汉字或字符数据（1个字节）
u8 Get_data_from_ROM(void)
{
	u8 read=0;
//	for(i=0;i<8;i++)
//	{
//		ZK_SCLK_Clr();
//		read<<=1;
//		if(ZK_MISO())
//		{
//			read++;
//    }
//		ZK_SCLK_Set();
//  }
    
    HAL_SPI_Receive(&hspi1, &read, 1, 0X100);
	return read;
}


//从相关地址（addrHigh：地址高字节,addrMid：地址中字节,addrLow：地址低字节）中连续读出DataLen个字节的数据到 pbuff的地址
//连续读取
void OLED_get_data_from_ROM(u8 addrHigh,u8 addrMid,u8 addrLow,u8 *pbuff,u8 DataLen)
{
	u8 i;
	ZK_CS_Clr();
	Send_Command_to_ROM(0x03);
	Send_Command_to_ROM(addrHigh);
	Send_Command_to_ROM(addrMid);
	Send_Command_to_ROM(addrLow);
	for(i=0;i<DataLen;i++)
	{
		*(pbuff+i)=Get_data_from_ROM();
  }
	ZK_CS_Set();
}


u32 fontaddr=0;
void OLED_Display_GB2312_string(u8 x,u8 y,u8 *text)
{
	u8 i=0;
	u8 addrHigh,addrMid,addrLow;
	u8 fontbuf[32];
	while(text[i]>0x00)
	{
		if((text[i]>=0xb0)&&(text[i]<=0xf7)&&(text[i+1]>=0xa1))
		{
			//国标简体（GB2312）汉字在晶联讯字库IC中的地址由以下公式来计算：
			//Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+ 846)*32+ BaseAdd;BaseAdd=0
			//由于担心8位单片机有乘法溢出问题，所以分三部取地址
			fontaddr=(text[i]-0xb0)*94;
			fontaddr+=(text[i+1]-0xa1)+846;
			fontaddr=fontaddr*32;
			
			addrHigh=(fontaddr&0xff0000)>>16;   //地址的高8位,共24位
			addrMid=(fontaddr&0xff00)>>8;       //地址的中8位,共24位
			addrLow=(fontaddr&0xff);            //地址的低8位,共24位
			
			OLED_get_data_from_ROM(addrHigh,addrMid,addrLow,fontbuf,32);
			//取32个字节的数据，存到"fontbuf[32]"
			OLED_Display_16x16(x,y,fontbuf);
			//显示汉字到LCD上，y为页地址，x为列地址，fontbuf[]为数据
			x+=16;
			i+=2;
    }
		else if((text[i]>=0xa1)&&(text[i]<=0xa3)&&(text[i+1]>=0xa1))
		{
			
			fontaddr=(text[i]-0xa1)*94;
			fontaddr+=(text[i+1]-0xa1);
			fontaddr=fontaddr*32;
			
			addrHigh=(fontaddr&0xff0000)>>16;
			addrMid=(fontaddr&0xff00)>>8;
			addrLow=(fontaddr&0xff);
			
			OLED_get_data_from_ROM(addrHigh,addrMid,addrLow,fontbuf,32);
			ZK_Display_16x16(x,y,fontbuf);
			x+=16;
			i+=2;
    }
		else if((text[i]>=0x20)&&(text[i]<=0x7e))
		{
			unsigned char fontbuf[16];
			fontaddr=(text[i]-0x20);
			fontaddr=(unsigned long)(fontaddr*16);
			fontaddr=(unsigned long)(fontaddr+0x3cf80);
			
			addrHigh=(fontaddr&0xff0000)>>16;
			addrMid=(fontaddr&0xff00)>>8;
			addrLow=fontaddr&0xff;
			
			OLED_get_data_from_ROM(addrHigh,addrMid,addrLow,fontbuf,16);
			ZK_Display_8x16(x,y,fontbuf);
			x+=8;
			i+=1;
    }
		else 
			i++;
  }
}

//显示16X16字库汉字
void ZK_Display_16x16(u8 x,u8 y,u8 *dp)
{
	u8 i,j;
	for(j=0;j<2;j++)
	{
		OLED_address(x,y);
		for(i=0;i<16;i++)
		{
			OLED_WR_Byte(*dp,OLED_DATA);  //写数据到OLED,每写完一个8位的数据后列地址自动加1
			dp++;
    }
		y++;
  }
}

//显示8x16字库字符
void ZK_Display_8x16(u8 x,u8 y,u8 *dp)
{
	u8 i,j;
	for(j=0;j<2;j++)
	{
		OLED_address(x,y);
		for(i=0;i<8;i++)
		{
			OLED_WR_Byte(*dp,OLED_DATA);   //写数据到LCD,每写完一个8位的数据后列地址自动加1
			dp++;
    }
		y++;
  }
}

void OLED_Display_string_5x7(u8 x,u8 y,u8 *text)
{
	u8 i=0;
	u8 addrHigh,addrMid,addrLow;
	while(text[i]>0x00)
	{
		if((text[i]>=0x20)&&(text[i]<=0x7e))
		{
			u8 fontbuf[8];
			fontaddr=(text[i]-0x20);
			fontaddr=(unsigned long)(fontaddr*8);
			fontaddr=(unsigned long)(fontaddr+0x3bfc0);
			
			addrHigh=(fontaddr&0xff0000)>>16;
			addrMid=(fontaddr&0xff00)>>8;
			addrLow=fontaddr&0xff;
			
			OLED_get_data_from_ROM(addrHigh,addrMid,addrLow,fontbuf,8);
			ZK_Display_5x7(x,y,fontbuf);
			x+=6;
			i+=1;
    }
		else 
			i++;
  }
}

//显示5*7字库字符
void ZK_Display_5x7(u8 x,u8 y,u8 *dp)
{
	u8 i;
    OLED_address(x,y);
	for(i=0;i<6;i++)
	{
		OLED_WR_Byte(*dp,OLED_DATA);
		dp++;
  }
}


























