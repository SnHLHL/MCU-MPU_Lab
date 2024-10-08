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
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void display7SEG();
void updateClockBuffer();
void update7SEG();
int timer0_counter = 0;
int timer0_flag = 0;
int timer1_counter = 0;
int timer1_flag = 0;
int timer2_counter = 0;
int timer2_flag = 0;
int timer3_counter = 0;
int timer3_flag = 0;
int TIMER_CYCLE = 10;

//-- setTimer0 is used for the blinking Red LED --//
void setTimer0 (int duration)
{
	timer0_counter = duration / TIMER_CYCLE;
	timer0_flag = 0;
}

//-- setTimer1 is used for the Blinking DOT and Time Value Updating --//
void setTimer1 (int duration)
{
	timer1_counter = duration / TIMER_CYCLE;
	timer1_flag = 0;
}

//-- setTimer2 is used for updating the 7SEG --//
void setTimer2 (int duration)
{
	timer2_counter = duration / TIMER_CYCLE;
	timer2_flag = 0;
}

//-- setTimer3 is used for updating the 8x8 matrix LED --//
void setTimer3 (int duration)
{
	timer3_counter = duration / TIMER_CYCLE;
	timer3_flag = 0;
}

void timer_run()
{
	if (timer0_counter > 0)
	{
		timer0_counter--;
		if (timer0_counter <= 0)
		{
			timer0_flag = 1;
		}
	}
	if (timer1_counter > 0)
	{
		timer1_counter--;
		if (timer1_counter <= 0)
		{
			timer1_flag = 1;
		}
	}
	if (timer2_counter > 0)
	{
		timer2_counter--;
		if (timer2_counter <= 0)
		{
			timer2_flag = 1;
		}
	}
	if (timer3_counter > 0)
	{
		timer3_counter--;
		if (timer3_counter <= 0)
		{
			timer3_flag = 1;
		}
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
//	const int MAX_LED_MATRIX = 8;
	int index_led_matrix = 0;
	uint8_t matrix_buffer[8] = {0x00, 0xFC, 0xFE, 0x33, 0x33, 0xFE, 0xFC, 0x00};
	void updateLEDMatrix(int index)
	{
		switch(index)
		{
		case 0:
			HAL_GPIO_WritePin(ENM_0_GPIO_Port, ENM_0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, ENM_1_Pin|ENM_2_Pin|ENM_3_Pin|ENM_4_Pin|ENM_5_Pin|ENM_6_Pin|ENM_7_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, 0xff<<8, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, matrix_buffer[index]<<8, GPIO_PIN_RESET);
			break;
		case 1:
			HAL_GPIO_WritePin(ENM_1_GPIO_Port, ENM_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, ENM_0_Pin|ENM_2_Pin|ENM_3_Pin|ENM_4_Pin|ENM_5_Pin|ENM_6_Pin|ENM_7_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, 0xff<<8, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, matrix_buffer[index]<<8, GPIO_PIN_RESET);
			break;
		case 2:
			HAL_GPIO_WritePin(ENM_2_GPIO_Port, ENM_2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, ENM_0_Pin|ENM_1_Pin|ENM_3_Pin|ENM_4_Pin|ENM_5_Pin|ENM_6_Pin|ENM_7_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, 0xff<<8, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, matrix_buffer[index]<<8, GPIO_PIN_RESET);
			break;
		case 3:
			HAL_GPIO_WritePin(ENM_3_GPIO_Port, ENM_3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, ENM_0_Pin|ENM_1_Pin|ENM_2_Pin|ENM_4_Pin|ENM_5_Pin|ENM_6_Pin|ENM_7_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, 0xff<<8, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, matrix_buffer[index]<<8, GPIO_PIN_RESET);
			break;
		case 4:
			HAL_GPIO_WritePin(ENM_4_GPIO_Port, ENM_4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, ENM_0_Pin|ENM_1_Pin|ENM_2_Pin|ENM_3_Pin|ENM_5_Pin|ENM_6_Pin|ENM_7_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, 0xff<<8, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, matrix_buffer[index]<<8, GPIO_PIN_RESET);
			break;
		case 5:
			HAL_GPIO_WritePin(ENM_5_GPIO_Port, ENM_5_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, ENM_0_Pin|ENM_1_Pin|ENM_2_Pin|ENM_3_Pin|ENM_4_Pin|ENM_6_Pin|ENM_7_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, 0xff<<8, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, matrix_buffer[index]<<8, GPIO_PIN_RESET);
			break;
		case 6:
			HAL_GPIO_WritePin(ENM_6_GPIO_Port, ENM_6_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, ENM_0_Pin|ENM_1_Pin|ENM_2_Pin|ENM_3_Pin|ENM_4_Pin|ENM_5_Pin|ENM_7_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, 0xff<<8, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, matrix_buffer[index]<<8, GPIO_PIN_RESET);
			break;
		case 7:
			HAL_GPIO_WritePin(ENM_7_GPIO_Port, ENM_7_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, ENM_0_Pin|ENM_1_Pin|ENM_2_Pin|ENM_3_Pin|ENM_4_Pin|ENM_5_Pin|ENM_6_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, 0xff<<8, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, matrix_buffer[index]<<8, GPIO_PIN_RESET);
			break;
		default:
			break;
		}
	}

	// Create function to shift every array to the left by 1 column
	void shift_matrix_buffer()
	{
		uint8_t tmp;  // Create 8-bit tmp to store the array
		uint8_t i;	// Create 8-bit i to store the arry
		for(i = 0; i < 8; i++)
		{
			tmp = matrix_buffer[i];	// Store the value of array i to tmp
			matrix_buffer[i] = matrix_buffer[i + 1];	// Assign the value of array i+1 to i
			matrix_buffer[i + 1] = tmp;	// Assign the value of tmp to array i+1
		}
	}

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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int hour = 15, minute = 45, second = 30;

  setTimer0(2000);
  setTimer1(1000);
  setTimer2(250);
  setTimer3(100);

  int index_led = 0;
  while (1)
  {
	  if(timer0_flag == 1)
	  {
		  setTimer0(2000);
		  HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
	  }
	  if(timer1_flag == 1)
	  {
		  setTimer1(1000);
		  second++;
		  if(second >= 60)
		  {
			  minute++;
			  second = 0;
		  }
		  if(minute >= 60)
		  {
			  hour++;
			  minute = 0;
		  }
		  if(hour >= 24)
		  {
			  hour = 0;
		  }
		  HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
		  updateClockBuffer(hour, minute);
	  }
	  if(timer2_flag == 1)
	  {
		  setTimer2(250);
		  update7SEG(index_led++);
		  if(index_led > 3)
		  {
			  index_led = 0;
		  }
	  }
	  if(timer3_flag == 1)
	  {
		  setTimer3(100);
		  updateLEDMatrix(index_led_matrix++);
		  if(index_led_matrix > 8)
		  {
			  index_led_matrix = 0;
			  shift_matrix_buffer();	// Shift the array once the letter A has been fully shown up
		  }
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
  HAL_GPIO_WritePin(GPIOA, ENM_0_Pin|ENM_1_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM_2_Pin|ENM_3_Pin|ENM_4_Pin|ENM_5_Pin
                          |ENM_6_Pin|ENM_7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG_0_Pin|SEG_1_Pin|SEG_2_Pin|ROW_2_Pin
                          |ROW_3_Pin|ROW_4_Pin|ROW_5_Pin|ROW_6_Pin
                          |ROW_7_Pin|SEG_3_Pin|SEG_4_Pin|SEG_5_Pin
                          |SEG_6_Pin|ROW_0_Pin|ROW_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ENM_0_Pin ENM_1_Pin DOT_Pin LED_RED_Pin
                           EN0_Pin EN1_Pin EN2_Pin EN3_Pin
                           ENM_2_Pin ENM_3_Pin ENM_4_Pin ENM_5_Pin
                           ENM_6_Pin ENM_7_Pin */
  GPIO_InitStruct.Pin = ENM_0_Pin|ENM_1_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM_2_Pin|ENM_3_Pin|ENM_4_Pin|ENM_5_Pin
                          |ENM_6_Pin|ENM_7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG_0_Pin SEG_1_Pin SEG_2_Pin ROW_2_Pin
                           ROW_3_Pin ROW_4_Pin ROW_5_Pin ROW_6_Pin
                           ROW_7_Pin SEG_3_Pin SEG_4_Pin SEG_5_Pin
                           SEG_6_Pin ROW_0_Pin ROW_1_Pin */
  GPIO_InitStruct.Pin = SEG_0_Pin|SEG_1_Pin|SEG_2_Pin|ROW_2_Pin
                          |ROW_3_Pin|ROW_4_Pin|ROW_5_Pin|ROW_6_Pin
                          |ROW_7_Pin|SEG_3_Pin|SEG_4_Pin|SEG_5_Pin
                          |SEG_6_Pin|ROW_0_Pin|ROW_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void display7SEG(int num)
  {
	  if (num == 0)
	  {
		  HAL_GPIO_WritePin(SEG_0_GPIO_Port, SEG_0_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_1_GPIO_Port, SEG_1_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_2_GPIO_Port, SEG_2_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_3_GPIO_Port, SEG_3_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_4_GPIO_Port, SEG_4_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_5_GPIO_Port, SEG_5_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_6_GPIO_Port, SEG_6_Pin, GPIO_PIN_SET);
	  }
	  else if (num == 1)
	  {
		  HAL_GPIO_WritePin(SEG_0_GPIO_Port, SEG_0_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(SEG_1_GPIO_Port, SEG_1_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_2_GPIO_Port, SEG_2_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_3_GPIO_Port, SEG_3_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(SEG_4_GPIO_Port, SEG_4_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(SEG_5_GPIO_Port, SEG_5_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(SEG_6_GPIO_Port, SEG_6_Pin, GPIO_PIN_SET);
	  }
	  else if (num == 2)
	  {
		  HAL_GPIO_WritePin(SEG_0_GPIO_Port, SEG_0_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_1_GPIO_Port, SEG_1_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_2_GPIO_Port, SEG_2_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(SEG_3_GPIO_Port, SEG_3_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_4_GPIO_Port, SEG_4_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_5_GPIO_Port, SEG_5_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(SEG_6_GPIO_Port, SEG_6_Pin, GPIO_PIN_RESET);
	  }
	  else if (num == 3)
	  {
		  HAL_GPIO_WritePin(SEG_0_GPIO_Port, SEG_0_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_1_GPIO_Port, SEG_1_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_2_GPIO_Port, SEG_2_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_3_GPIO_Port, SEG_3_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_4_GPIO_Port, SEG_4_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(SEG_5_GPIO_Port, SEG_5_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(SEG_6_GPIO_Port, SEG_6_Pin, GPIO_PIN_RESET);
	  }
	  else if (num == 4)
	  {
		  HAL_GPIO_WritePin(SEG_0_GPIO_Port, SEG_0_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(SEG_1_GPIO_Port, SEG_1_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_2_GPIO_Port, SEG_2_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_3_GPIO_Port, SEG_3_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(SEG_4_GPIO_Port, SEG_4_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(SEG_5_GPIO_Port, SEG_5_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_6_GPIO_Port, SEG_6_Pin, GPIO_PIN_RESET);
	  }
	  else if (num == 5)
	  {
		  HAL_GPIO_WritePin(SEG_0_GPIO_Port, SEG_0_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_1_GPIO_Port, SEG_1_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(SEG_2_GPIO_Port, SEG_2_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_3_GPIO_Port, SEG_3_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_4_GPIO_Port, SEG_4_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(SEG_5_GPIO_Port, SEG_5_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_6_GPIO_Port, SEG_6_Pin, GPIO_PIN_RESET);
	  }
	  else if (num == 6)
	  {
		  HAL_GPIO_WritePin(SEG_0_GPIO_Port, SEG_0_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_1_GPIO_Port, SEG_1_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(SEG_2_GPIO_Port, SEG_2_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_3_GPIO_Port, SEG_3_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_4_GPIO_Port, SEG_4_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_5_GPIO_Port, SEG_5_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_6_GPIO_Port, SEG_6_Pin, GPIO_PIN_RESET);
	  }
	  else if (num == 7)
	  {
		  HAL_GPIO_WritePin(SEG_0_GPIO_Port, SEG_0_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_1_GPIO_Port, SEG_1_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_2_GPIO_Port, SEG_2_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_3_GPIO_Port, SEG_3_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(SEG_4_GPIO_Port, SEG_4_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(SEG_5_GPIO_Port, SEG_5_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(SEG_6_GPIO_Port, SEG_6_Pin, GPIO_PIN_SET);
	  }
	  else if (num == 8)
	  {
		  HAL_GPIO_WritePin(SEG_0_GPIO_Port, SEG_0_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_1_GPIO_Port, SEG_1_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_2_GPIO_Port, SEG_2_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_3_GPIO_Port, SEG_3_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_4_GPIO_Port, SEG_4_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_5_GPIO_Port, SEG_5_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_6_GPIO_Port, SEG_6_Pin, GPIO_PIN_RESET);
	  }
	  else if (num == 9)
	  {
		  HAL_GPIO_WritePin(SEG_0_GPIO_Port, SEG_0_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_1_GPIO_Port, SEG_1_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_2_GPIO_Port, SEG_2_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_3_GPIO_Port, SEG_3_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_4_GPIO_Port, SEG_4_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(SEG_5_GPIO_Port, SEG_5_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SEG_6_GPIO_Port, SEG_6_Pin, GPIO_PIN_RESET);
	  }
  }

int led_buffer[4] = {0, 0, 0, 0};
void updateClockBuffer(int hour, int minute)
{
	if (minute <= 9)
	{
		led_buffer[2] = 0;
		led_buffer[3] = minute;
	}
	if (minute >= 10)
	{
		led_buffer[2] = minute / 10;
		led_buffer[3] = minute % 10;
	}
	if (hour <= 9)
	{
		led_buffer[0] = 0;
		led_buffer[1] = hour;
	}
	if (hour >= 10)
	{
		led_buffer[0] = hour / 10;
		led_buffer[1] = hour % 10;
	}
}

const int MAX_LED = 4;
int index_led = 0;
void update7SEG(int index)
{
	switch (index)
	{
	case 0:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
		display7SEG(led_buffer[0]);
		break;
	case 1:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
		display7SEG(led_buffer[1]);
		break;
	case 2:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
		display7SEG(led_buffer[2]);
		break;
	case 3:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_RESET);
		display7SEG(led_buffer[3]);
		break;
	default:
		break;
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	timer_run();
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
