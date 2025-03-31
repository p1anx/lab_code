#include "oled.h"
#include "stdlib.h"
//#include "delay.h"
#include "spi.h"
#include "oledfont.h"
//���Ժ���
void OLED_ColorTurn(u8 i)
{
	if(i==0)
	{
		OLED_WR_Byte(0xA6,OLED_CMD);//������ʾ
	}
	if(i==1)
	{
		OLED_WR_Byte(0xA7,OLED_CMD);//��ɫ��ʾ
	}
}

//��Ļ��ת180��
void OLED_DisplayTurn(u8 i)
{
	if(i==0)
	{
		OLED_WR_Byte(0xC8,OLED_CMD);//������ʾ
		OLED_WR_Byte(0xA1,OLED_CMD);
	}
	if(i==1)
	{
		OLED_WR_Byte(0xC0,OLED_CMD);//��ת��ʾ
		OLED_WR_Byte(0xA0,OLED_CMD);
	}
}

//����OLED��ʾ 
void OLED_DisPlay_On(void)
{
	OLED_WR_Byte(0x8D,OLED_CMD);//��ɱ�ʹ��
	OLED_WR_Byte(0x14,OLED_CMD);//������ɱ�
	OLED_WR_Byte(0xAF,OLED_CMD);//������Ļ
}

//�ر�OLED��ʾ 
void OLED_DisPlay_Off(void)
{
	OLED_WR_Byte(0x8D,OLED_CMD);//��ɱ�ʹ��
	OLED_WR_Byte(0x10,OLED_CMD);//�رյ�ɱ�
	OLED_WR_Byte(0xAE,OLED_CMD);//�ر���Ļ
}


//��SSD1306д��һ���ֽڡ�
//mode:����/�����־ 0,��ʾ����;1,��ʾ����;
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

//��������
void OLED_Clear(void)
{
	u8 i,n;
	for(i=0;i<8;i++)
	{
	 	 OLED_WR_Byte(0xb0+i,OLED_CMD);//����ҳ��ַ
	   OLED_WR_Byte(0x10,OLED_CMD);  //�����е�ַ�ĸ�4λ
	   OLED_WR_Byte(0x00,OLED_CMD);  //�����е�ַ�ĵ�4λ
	   for(n=0;n<128;n++)
		 {
			 OLED_WR_Byte(0x00,OLED_DATA);//�����������
		 }
  }
}

//������ʼ��ַ
void OLED_address(u8 x,u8 y)
{
	OLED_WR_Byte(0xb0+y,OLED_CMD);              //����ҳ��ַ
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);  //�����е�ַ�ĸ�4λ
	OLED_WR_Byte((x&0x0f),OLED_CMD);            //�����е�ַ�ĵ�4λ
}
void OLED_SetPos(u8 page, u8 col){
	OLED_WR_Byte(0xb0 + page, OLED_CMD);
	OLED_WR_Byte(((col & 0xf0) >> 4) | 0x10, OLED_CMD);
	OLED_WR_Byte(col & 0x0f, OLED_CMD);

}

// extern const unsigned char asc2_1608[95][16];

void OLED_PutChar(int page, int col, char c){
	int i = 0;
	
	u8 *p = asc2_1608[c - ' '];
	OLED_SetPos(page, col);
	for(i = 0; i < 8; i++){
		OLED_WR_Byte(p[i], OLED_DATA);
	}
	OLED_SetPos(page + 1, col);
	for(i = 0; i < 8; i++){
		OLED_WR_Byte(p[i + 8], OLED_DATA);
	}

}

void OLED_Print(int col, int  page, char *str){
	int i = 0;
	while(str[i] != '\0'){
		OLED_PutChar(page, col, str[i]);
		col += 8;
		if(col > 127){
			col = 0;
			page += 2;
		}
		i++;
	}
}

//��ʾ128x64����ͼ��
void OLED_Display_128x64(u8 *dp)
{
	u8 i,j;
	for(i=0;i<8;i++)
	{
		OLED_address(0,i);
		for(j=0;j<128;j++)
		{
			OLED_WR_Byte(*dp,OLED_DATA); //д���ݵ�OLED,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1
			dp++;
    }
  }
}

//��ʾ16x16����ͼ�񡢺��֡���Ƨ�ֻ�16x16���������ͼ��
void OLED_Display_16x16(u8 x,u8 y,u8 *dp)
{
	u8 i,j;
	for(j=0;j<2;j++)
	{
		OLED_address(x,y);
		for(i=0;i<16;i++)
		{
			OLED_WR_Byte(*dp,OLED_DATA);  //д���ݵ�OLED,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1
			dp++;
    }
		y++;
  }
}

//��ʾ8x16����ͼ��ASCII, ��8x16����������ַ�������ͼ��
void OLED_Display_8x16(u8 x,u8 y,u8 *dp)
{
	u8 i,j;
	for(j=0;j<2;j++)
	{
		OLED_address(x,y);
		for(i=0;i<8;i++)
		{
			OLED_WR_Byte(*dp,OLED_DATA);   //д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1
			dp++;
    }
		y++;
  }
}



//OLED�ĳ�ʼ��
void OLED_Init(void)
{
//	GPIO_InitTypeDef  GPIO_InitStructure;
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��A�˿�ʱ��
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);	  //��ʼ��GPIOA
//	
// 	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4);
//	
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_8;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //��ʼ��GPIOA

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //��ʼ��GPIOA
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
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
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
unsigned char OLED_GRAM[128][8];  //128*64���صĵ���
void OLED_Refresh_Gram(void)
{
    unsigned char i,n;
    for(i=0;i<8;i++)
    {
        OLED_WR_Byte(0xb0+i,OLED_CMD);  //����ҳ��ַ��0~7��
        OLED_WR_Byte(0x00,OLED_CMD);    //������ʾλ�á��е͵�ַ
        OLED_WR_Byte(0x10,OLED_CMD);    //������ʾλ�á��иߵ�ַ  
         
        for(n=0;n<128;n++)  //дһPAGE��GDDRAM����
        {
            OLED_WR_Byte(OLED_GRAM[n][i],1);
        }
    }
}



void OLED_DrawDot(unsigned char x,unsigned char y,unsigned char t)
{
	unsigned char pos,bx,temp=0;
    
	// ��OLED�ķֱ���Ϊ128*64�����������127�����������63��������Ƿ�	
    
	if(x>127||y>63) return;
    
	// ��Ϊ��OLED�ǰ�ҳ��ʾ��ÿҳ8�����أ�����/8���ڼ������ʾ�ĵ�����ҳ��
	pos=(y)/8;
    
	// һ������8�����أ����Լ���һ�´���ʾ�ĵ㣬�ڵ�ǰ���еĵڼ�����
	bx=y%8;
    
	// ��λ����temp�ĵ�bxλΪ1
	temp=1<<(bx);
    
	if(t) 
		OLED_GRAM[x][pos]|=temp;		//��bxλ����1������λֵ����
	else 
		OLED_GRAM[x][pos]&=~temp;		//��bxλ����0������λֵ����
        
	// ˢ������Һ����
	OLED_Refresh_Gram();	
}

void OLED_Init0(void){
	OLED_Init();
	OLED_ColorTurn(0);//0正常显示；1 反色显示
    OLED_DisplayTurn(0);//0正常显示；1 翻转显示
	OLED_Clear();
}
int a[] = {32, 33, 35, 36, 38, 39, 41, 42, 44, 45, 47, 48, 49, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 60, 61, 62, 62, 63, 63, 63, 63, 63, 64, 63, 63, 63, 63, 63, 62, 62, 61, 60, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 49, 48, 47, 45, 44, 42, 41, 39, 38, 36, 35, 33, 32, 30, 28, 27, 25, 24, 22, 21, 19, 18, 16, 15, 14, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16, 18, 19, 21, 22, 24, 25, 27, 28, 30, };
void OLED_Display_Demo(void){
	uint8_t x[128] = {0};
	uint8_t y[128] = {1};
	for(int i = 0; i < 128; i++){
		x[i] = i;
	}
	// for(int j = 0; j < 128; j++){
	// 	y[j] = a[j];
	// }
	OLED_Init0();
	while(1){
		// OLED_Axis();
		// OLED_Clear();
		// OLED_Plot(x, a);
		// for(int i = 0; i < 128; i++){
		// 	OLED_DrawDot(i, a[i], 1);
		// }

		// HAL_Delay(1000);
		OLED_Print(10, 0, "101.11");
		// OLED_Print(10, 4, "World!");
		// HAL_Delay(1000);
	}

}

void OLED_Plot(int *x, int *y){
	for(int i = 0; i < 128; i++){
		OLED_DrawDot(*(x+i), *(y+i), 1);
	}
}

void OLED_Axis(void){
	for(int i = 0; i < 64; i++){
		OLED_DrawDot(0, i, 1);
	}
	for(int i = 0; i < 128; i++){
		OLED_DrawDot(i, 63, 1);
	}
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 4; j++){
			OLED_DrawDot(j, i*8, 1);
		}
	}
	for(int i = 0; i < 16; i++){
		for(int j = 0; j < 4; j++){
			OLED_DrawDot(i*8, 63-j, 1);
		}
	}
	for(int i = 0; i < 64; i++){
		for(int j = 0; j < 128; j++){
			OLED_DrawDot(j, i, 0);
		}
	}
}
