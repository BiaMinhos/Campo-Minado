/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
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
#include "ST7789\st7789.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BTNUP  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) == GPIO_PIN_RESET
#define BTNDOWN  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) == GPIO_PIN_RESET
#define BTNLEFT  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) == GPIO_PIN_RESET
#define BTNRIGHT  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == GPIO_PIN_RESET
#define LED6_ON  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3,1)
#define LED6_OFF HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3, 0)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
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
  ST7789_Init();
  MainMenu();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//	  MainMenu();
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ST7789_CS_GPIO_Port, ST7789_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ST7789_DC_Pin|ST7789_RST_Pin|LED1_Pin|LED2_Pin
                          |LED3_Pin|LED4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : ST7789_CS_Pin */
  GPIO_InitStruct.Pin = ST7789_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ST7789_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ST7789_DC_Pin ST7789_RST_Pin LED1_Pin LED2_Pin
                           LED3_Pin LED4_Pin */
  GPIO_InitStruct.Pin = ST7789_DC_Pin|ST7789_RST_Pin|LED1_Pin|LED2_Pin
                          |LED3_Pin|LED4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : BTNLEFT_Pin BTNDOWN_Pin BTNRIGHT_Pin BTNUP_Pin */
  GPIO_InitStruct.Pin = BTNLEFT_Pin|BTNDOWN_Pin|BTNRIGHT_Pin|BTNUP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
int choice_menu = 0;
int confirm_choice = 0;
int choice_bomb = 0;
int confirm_bomb = 0;
void MainMenu (void)
{
	ST7789_Fill_Color(BLACK);
	ST7789_WriteString(45,20,"Mine Field", Font_16x26,CYAN, BLACK);
	ST7789_WriteString(65,100," Play (UP) ", Font_11x18,CYAN, BLACK);
	ST7789_WriteString(20,140," Difficulty (DOWN) ", Font_11x18,CYAN, BLACK);
	ST7789_WriteString(35,180," Confirm (RIGHT) ", Font_11x18,CYAN, BLACK);

		if(BTNUP == 1)
			{
				choice_menu = 1;
			}
			else if(BTNDOWN == 1)
			{
				choice_menu = 2;
			}

			switch(choice_menu)
			{
				case 1:
					ST7789_WriteString(65,100," Play (UP) ", Font_11x18, BLACK, CYAN);
				break;

				case 2:
					ST7789_WriteString(20,140," Difficulty (DOWN) ", Font_11x18, BLACK, CYAN);
				break;
			}

			if(BTNRIGHT == 1)
			{
				confirm_choice = 1;
			}

			if(choice_menu == 1 && confirm_choice == 1)
			{
				confirm_choice = 0;
				ST7789_Fill_Color(BLACK);
			}
			else if (choice_menu == 2 && confirm_choice == 1)
			{
				confirm_choice = 0;
				ST7789_Fill_Color(BLACK);
			}
			ST7789_Fill_Color(BLACK);
			DifficultyBomb();
}

void DifficultyBomb (void)
{
	while (confirm_bomb == 0)
		{
			ST7789_WriteString(25,20," Mine Field ", Font_16x26, BLACK, CYAN);
			ST7789_WriteString(40,75," Easy - 4 bombs ", Font_11x18, WHITE, BLACK);
			ST7789_WriteString(90,95," (UP) ", Font_11x18, WHITE, BLACK);
			ST7789_WriteString(30,120," Medium - 8 bombs ", Font_11x18, WHITE, BLACK);
			ST7789_WriteString(80,145," (LEFT) ", Font_11x18, WHITE, BLACK);
			ST7789_WriteString(40,165," Hard - 12 bombs ", Font_11x18, WHITE, BLACK);
			ST7789_WriteString(80,185," (DOWN) ", Font_11x18, WHITE, BLACK);
			ST7789_WriteString(60,220," Confirm (RIGHT) ", Font_7x10, WHITE, BLACK);

			if(BTNUP == 1)
			{
				choice_bomb = 1;
			}
			else if(BTNLEFT == 1)
			{
				choice_bomb = 2;
			}
			else if(BTNDOWN == 1)
			{
				choice_bomb = 3;
			}

			switch(choice_bomb)
			{
				case 1:
					ST7789_WriteString(40,75," Easy - 4 bombs ", Font_11x18, BLACK, CYAN);
				break;

				case 2:
					ST7789_WriteString(30,120," Medium - 8 bombs ", Font_11x18, BLACK, CYAN);
				break;

				case 3:
					ST7789_WriteString(40,165," Hard - 12 bombs ", Font_11x18, BLACK, CYAN);
				break;
			}

			if(BTNRIGHT == 1)
			{
				confirm_bomb = 1;
			}
		}
		if(choice_bomb == 1 && confirm_bomb == 1)
		{
			confirm_bomb = 0;
			ST7789_Fill_Color(BLACK);
			MainMenu();
		}
		else if (choice_bomb == 2 && confirm_bomb == 1)
		{
			confirm_bomb = 0;
			ST7789_Fill_Color(BLACK);
			MainMenu();

		}
		else if (choice_bomb == 3 && confirm_bomb == 1)
		{
			confirm_bomb = 0;
			ST7789_Fill_Color(BLACK);
			MainMenu();
		}
}
void MineField (void)
{

}
void BombMark (void)
{

}
void Win (void)
{

}
void Lose (void)
{

}

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
