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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "software_timer.h"
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
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_TIM2_Init(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
const uint8_t segDigits[10] = {
    0b01000000, // 0: Seg0, Seg1, Seg2, Seg3, Seg4, Seg5
    0b01111001, // 1: Seg1, Seg2
    0b00100100, // 2: Seg0, Seg1, Seg3, Seg4, Seg6
    0b00110000, // 3: Seg0, Seg1, Seg2, Seg3, Seg6
    0b00011001, // 4: Seg1, Seg2, Seg5, Seg6
    0b00010010, // 5: Seg0, Seg2, Seg3, Seg5, Seg6
    0b00000010, // 6: Seg0, Seg2, Seg3, Seg4, Seg5, Seg6
    0b01111000, // 7: Seg0, Seg1, Seg2
    0b00000000, // 8: Seg0, Seg1, Seg2, Seg3, Seg4, Seg5, Seg6
    0b00010000  // 9: Seg0, Seg1, Seg2, Seg3, Seg5, Seg6
};

// ham thuc hien led 7 doan
void displayDigit(uint8_t digit) {
    HAL_GPIO_WritePin(Seg0_GPIO_Port, Seg0_Pin, (segDigits[digit] & 0x01) ? 1 : 0);
    HAL_GPIO_WritePin(Seg1_GPIO_Port, Seg1_Pin, (segDigits[digit] & 0x02) ? 1 : 0);
    HAL_GPIO_WritePin(Seg2_GPIO_Port, Seg2_Pin, (segDigits[digit] & 0x04) ? 1 : 0);
    HAL_GPIO_WritePin(Seg3_GPIO_Port, Seg3_Pin, (segDigits[digit] & 0x08) ? 1 : 0);
    HAL_GPIO_WritePin(Seg4_GPIO_Port, Seg4_Pin, (segDigits[digit] & 0x10) ? 1 : 0);
    HAL_GPIO_WritePin(Seg5_GPIO_Port, Seg5_Pin, (segDigits[digit] & 0x20) ? 1 : 0);
    HAL_GPIO_WritePin(Seg6_GPIO_Port, Seg6_Pin, (segDigits[digit] & 0x40) ? 1 : 0);
}
const int MAX_LED = 4;
int index_led = 0;
int led_buffer[4] = {1, 2, 3, 4};
void update7SEG(int index) {
	HAL_GPIO_WritePin(GPIOA, EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin, 1);
	switch (index) {
		case 0:
			//Display the first 7SEG with led_buffer [0]
			HAL_GPIO_WritePin(GPIOA, EN0_Pin, 0);
			displayDigit(led_buffer[0]);
			break;
		case 1:
			//Display the second 7SEG with led_buffer [1]
			HAL_GPIO_WritePin(GPIOA, EN1_Pin, 0);
			displayDigit(led_buffer[1]);
			break;
		case 2:
			//Display the third 7SEG with led_buffer [2]
			HAL_GPIO_WritePin(GPIOA, EN2_Pin, 0);
			displayDigit(led_buffer[2]);
			break;
		case 3:
			//Display the forth 7SEG with led_buffer [3]
			HAL_GPIO_WritePin(GPIOA, EN3_Pin, 0);
			displayDigit(led_buffer[3]);
			break;
		default:
			break;
	}

	index_led++;
	if(index_led >= MAX_LED){
		index_led = 0;
	}
}
int h = 15, min = 59, sec = 50;
void updateClockBuffer(){
	if(h < 10){
		led_buffer[0] = 0;
		led_buffer[1] = h;
	}
	else{
		led_buffer[0] = h/10;
		led_buffer[1] = h%10;
	}
	if(min < 10){
		led_buffer[2] = 0;
		led_buffer[3] = min;
	}
	else{
		led_buffer[2] = min/10;
		led_buffer[3] = min%10;
	}
}
void digitalClock(){
	sec++;
	if(sec >= 60){
		min++;
		sec = 0;
	}
	if(min >= 60){
		h++;
		min = 0;
	}
	if(h >= 24){
		h = 0;
	}
}
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
  MX_TIM2_Init();
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT (& htim2 );
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
/*
 * tai sao sai so cua software_timer la 1 tich
 * vong lap while(1) khong xac dinh thoi gian
 * setTimer nam o bat ki thoi gian nao
 * mat di 1 counter 1 tick ngay dau tien, tu thu hai luon dung
 * */
  setTimer(0, 100);
  setTimer(1, 150);
  setTimer(2, 200);
  while (1)
  {
	  if(isTimerExpired(0) == 1){
		  //LED_RED
		  setTimer(0, 1000);
		  HAL_GPIO_TogglePin(Led_red_GPIO_Port, Led_red_Pin);
	  }
	  if(isTimerExpired(1) == 1){
		  //DOT
		  setTimer(1, 1000);
		  HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
	  }
	  if(isTimerExpired(2) == 1){
		  //7led
		  setTimer(2, 250);
		  updateClockBuffer();
		  update7SEG(index_led);
		  digitalClock();
	  }
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
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

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
  HAL_GPIO_WritePin(GPIOA, DOT_Pin|Led_red_Pin|EN0_Pin|EN1_Pin
                          |EN2_Pin|EN3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Seg0_Pin|Seg1_Pin|Seg2_Pin|Seg3_Pin
                          |Seg4_Pin|Seg5_Pin|Seg6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : DOT_Pin Led_red_Pin EN0_Pin EN1_Pin
                           EN2_Pin EN3_Pin */
  GPIO_InitStruct.Pin = DOT_Pin|Led_red_Pin|EN0_Pin|EN1_Pin
                          |EN2_Pin|EN3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : Seg0_Pin Seg1_Pin Seg2_Pin Seg3_Pin
                           Seg4_Pin Seg5_Pin Seg6_Pin */
  GPIO_InitStruct.Pin = Seg0_Pin|Seg1_Pin|Seg2_Pin|Seg3_Pin
                          |Seg4_Pin|Seg5_Pin|Seg6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim )
{
	timerRun();
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
