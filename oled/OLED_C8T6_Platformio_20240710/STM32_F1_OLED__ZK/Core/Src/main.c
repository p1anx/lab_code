/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
 #include "oled.h"
 #include "bmp.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
    OLED_Init();
	OLED_ColorTurn(0);//0正常显示，1 反色显示
    OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
	OLED_Clear();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    
    for(int i=0;i<128;i++)
    {
      OLED_DrawDot(i,0,1);
      OLED_DrawDot(i,63,1);
    }
    //     OLED_Display_128x64(bmp1);
		// HAL_Delay(5000);
      
      
		// OLED_Display_GB2312_string(0,0,"12864,带中文字库");	/*在第1页，第1列，显示一串16x16点阵汉字或8x16的ASCII字*/
		// OLED_Display_GB2312_string(0,2,"16X16简体汉字库,");  /*显示一串16x16点阵汉字或8x16的ASCII字.以下雷同*/
		// OLED_Display_GB2312_string(0,4,"或8X16点阵ASCII,");
		// OLED_Display_GB2312_string(0,6,"或5X7点阵ASCII码");
		// HAL_Delay(5000);
		// OLED_Clear();
		// OLED_Display_GB2312_string(24,0,"中景园电子");	
		// OLED_Display_GB2312_string(0,2,"主要生产OLED模块");
		// OLED_Display_GB2312_string(0,4,"顾客至上真诚服务");
		// OLED_Display_GB2312_string(0,6,"诚信与质量第一！");
		// HAL_Delay(500);
		// OLED_Clear();		
		// OLED_Display_GB2312_string(0,0,"GB2312简体字库及");	
		// OLED_Display_GB2312_string(0,2,"有图型功能，可自");	
		// OLED_Display_GB2312_string(0,4,"编大字或图像或生");
		// OLED_Display_GB2312_string(0,6,"僻字，例如：");
		// OLED_Display_16x16(97,6,jiong1);					/*在第7页，第81列显示单个自编生僻汉字“囧”*/
    // OLED_Display_16x16(113,6,lei1);
		// HAL_Delay(500);
		// OLED_Clear();
		// OLED_Display_GB2312_string(0,0,"<!@#$%^&*()_-+]/");	/*在第1页，第1列，显示一串16x16点阵汉字或8*16的ASCII字*/
		// OLED_Display_string_5x7(0,2,"<!@#$%^&*()_-+]/;.,?[");/*在第3页，第1列，显示一串5x7点阵的ASCII字*/
		// OLED_Display_string_5x7(0,3,"XY electronics Co., ");/*显示一串5x7点阵的ASCII字*/
		// OLED_Display_string_5x7(0,4,"Ltd. established at  ");/*显示一串5x7点阵的ASCII字*/	
		// OLED_Display_string_5x7(0,5,"year 2010.Focus OLED ");/*显示一串5x7点阵的ASCII字*/
		// OLED_Display_string_5x7(0,6,"Mobile:13265585975");/*显示一串5x7点阵的ASCII字*/
		// OLED_Display_string_5x7(0,7,"Tel:0755-32910715");/*显示一串5x7点阵的ASCII字*/
		// HAL_Delay(500);
		// OLED_Clear();	
		// OLED_Display_GB2312_string(0,0,"啊阿埃挨哎唉哀皑");	/*在第1页，第1列，显示一串16x16点阵汉字或8x16的ASCII字*/
		// OLED_Display_GB2312_string(0,2,"癌蔼矮艾碍爱隘鞍");  /*显示一串16x16点阵汉字或8x16的ASCII字.以下雷同*/
		// OLED_Display_GB2312_string(0,4,"氨安俺按暗岸胺案");
		// OLED_Display_GB2312_string(0,6,"肮昂盎凹敖熬翱袄");		        
		// HAL_Delay(500);
		// OLED_Clear();	
		// OLED_Display_GB2312_string(0,0,"鬟鬣麽麾縻麂麇麈");
		// OLED_Display_GB2312_string(0,2,"麋麒鏖麝麟黛黜黝");
		// OLED_Display_GB2312_string(0,4,"黠黟黢黩黧黥黪黯");
		// OLED_Display_GB2312_string(0,6,"齄鼬鼹鼷鼽鼾鼢鼯");
		// HAL_Delay(500);
		// OLED_Clear();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
