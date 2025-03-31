#include "oled.h"
#include "stdlib.h"
//#include "delay.h"
#include "spi.h"
//反显函数
void OLED_ColorTurn(u8 i)
{
	if(i==0)
	{
		OLED_WR_Byte(0xA6,OLED_CMD);//正常显示
	}
	if(i==1)
	{
		OLED_WR_Byte(0xA7,OLED_CMD);//反色显示
	}
}

//屏幕旋转180度
void OLED_DisplayTurn(u8 i)
{
	if(i==0)
	{
		OLED_WR_Byte(0xC8,OLED_CMD);//正常显示
		OLED_WR_Byte(0xA1,OLED_CMD);
	}
	if(i==1)
	{
		OLED_WR_Byte(0xC0,OLED_CMD);//反转显示
		OLED_WR_Byte(0xA0,OLED_CMD);
	}
}

//开启OLED显示 
void OLED_DisPlay_On(void)
{
	OLED_WR_Byte(0x8D,OLED_CMD);//电荷泵使能
	OLED_WR_Byte(0x14,OLED_CMD);//开启电荷泵
	OLED_WR_Byte(0xAF,OLED_CMD);//点亮屏幕
}

//关闭OLED显示 
void OLED_DisPlay_Off(void)
{
	OLED_WR_Byte(0x8D,OLED_CMD);//电荷泵使能
	OLED_WR_Byte(0x10,OLED_CMD);//关闭电荷泵
	OLED_WR_Byte(0xAE,OLED_CMD);//关闭屏幕
}


//向SSD1306写入一个字节。
//mode:数据/命令标志 0,表示命令;1,表示数据;
void OLED_WR_Byte(u8 dat,u8 cmd)
{	
//	u8 i;			  
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		  
	OLED_CS_Clr();
//	for(i=0;i<8;i++)
//	{			  
//		OLED_SCLK_Clr();
//		if(dat&0x80)
//		   OLED_MOSI_Set();
//		else 
//		   OLED_MOSI_Clr();
//		OLED_SCLK_Set();
//		dat<<=1;   
//	}				 		  
    HAL_SPI_Transmit(&hspi1, &dat, 1, 0X100);
	OLED_CS_Set();
	OLED_DC_Set();   	  
}

//清屏函数
void OLED_Clear(void)
{
	u8 i,n;
	for(i=0;i<8;i++)
	{
	 	 OLED_WR_Byte(0xb0+i,OLED_CMD);//设置页地址
	   OLED_WR_Byte(0x10,OLED_CMD);  //设置列地址的高4位
	   OLED_WR_Byte(0x00,OLED_CMD);  //设置列地址的低4位
	   for(n=0;n<128;n++)
		 {
			 OLED_WR_Byte(0x00,OLED_DATA);//清除所有数据
		 }
  }
}

//设置起始地址
void OLED_address(u8 x,u8 y)
{
	OLED_WR_Byte(0xb0+y,OLED_CMD);              //设置页地址
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);  //设置列地址的高4位
	OLED_WR_Byte((x&0x0f),OLED_CMD);            //设置列地址的低4位
}

//显示128x64点阵图像
void OLED_Display_128x64(u8 *dp)
{
	u8 i,j;
	for(i=0;i<8;i++)
	{
		OLED_address(0,i);
		for(j=0;j<128;j++)
		{
			OLED_WR_Byte(*dp,OLED_DATA); //写数据到OLED,每写完一个8位的数据后列地址自动加1
			dp++;
    }
  }
}

//显示16x16点阵图像、汉字、生僻字或16x16点阵的其他图标
void OLED_Display_16x16(u8 x,u8 y,u8 *dp)
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

//显示8x16点阵图像、ASCII, 或8x16点阵的自造字符、其他图标
void OLED_Display_8x16(u8 x,u8 y,u8 *dp)
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



//OLED的初始化
void OLED_Init(void)
{
//	GPIO_InitTypeDef  GPIO_InitStructure;
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);	 //使能A端口时钟
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);	  //初始化GPIOA
//	
// 	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4);
//	
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_8;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //初始化GPIOA

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //初始化GPIOA
//	
//	GPIO_SetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);
	
	OLED_RES_Clr();
	HAL_Delay(10);
	OLED_RES_Set();
	
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xFF,OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_Clear();
	OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
}
unsigned char OLED_GRAM[128][8];  //128*64像素的点阵
void OLED_Refresh_Gram(void)
{
    unsigned char i,n;
    for(i=0;i<8;i++)
    {
        OLED_WR_Byte(0xb0+i,OLED_CMD);  //设置页地址（0~7）
        OLED_WR_Byte(0x00,OLED_CMD);    //设置显示位置—列低地址
        OLED_WR_Byte(0x10,OLED_CMD);    //设置显示位置—列高地址  
         
        for(n=0;n<128;n++)  //写一PAGE的GDDRAM数据
        {
            OLED_WR_Byte(OLED_GRAM[n][i],1);
        }
    }
}



void OLED_DrawDot(unsigned char x,unsigned char y,unsigned char t)
{
	unsigned char pos,bx,temp=0;
    
	// 此OLED的分辨率为128*64，横坐标大于127，纵坐标大于63，则参数非法	
    
	if(x>127||y>63) return;
    
	// 因为此OLED是按页显示，每页8个像素，所以/8用于计算待显示的点在哪页中
	pos=(y)/8;
    
	// 一列中有8个像素，所以计算一下待显示的点，在当前列中的第几个点
	bx=y%8;
    
	// 移位，让temp的第bx位为1
	temp=1<<(bx);
    
	if(t) 
		OLED_GRAM[x][pos]|=temp;		//第bx位，置1，其他位值不变
	else 
		OLED_GRAM[x][pos]&=~temp;		//第bx位，置0，其他位值不变
        
	// 刷新整个液晶屏
	OLED_Refresh_Gram();	
}
