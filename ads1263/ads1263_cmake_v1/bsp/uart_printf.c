#include "uart_printf.h"

// int fputc(int ch, FILE* f){
//   HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, 1000);
//   return ch;
// }

/**** STM32-printf重映射串口，需#include "stdio.h"	注意，使用printf处也需#include "stdio.h"  ****/
#ifdef __GNUC__  
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)  
#else  
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE* f)  
#endif /* __GNUC__ */  
   
#ifdef __cplusplus  
extern "C" {  
#endif //__cplusplus  
   
PUTCHAR_PROTOTYPE  
{  
HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);  //调用STM32的HAL库发送一个字节,此项目使用&huart1接口，根据实际调整
   
  return (ch);  
}  
   
#ifdef __cplusplus  
}  
#endif //__cplusplus  
/*****	 STM32-printf重映射串口	 ****/