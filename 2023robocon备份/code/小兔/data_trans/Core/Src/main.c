/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t Rxbuffer[35];
uint8_t jiexi[35];
uint8_t  c1,c2,c3,c4,c5,c6,c7,c8,c9,c10;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
		int i=1;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
uint16_t ledrpwmval = 0;
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM3_Init();
  MX_TIM14_Init();
  MX_TIM2_Init();
  MX_TIM1_Init();
  MX_TIM5_Init();
  /* USER CODE BEGIN 2 */
HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_2);//PB10
HAL_TIM_PWM_Start(&htim14,TIM_CHANNEL_1); //PF9     ------> TIM14_CH1
HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2); //PF9  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		HAL_UART_Receive_IT(&huart2,(uint8_t*)Rxbuffer,35);
		jiexi[0]=Rxbuffer[1];   //对应右手横向摇杆0-3，4，5-7
    jiexi[1]=Rxbuffer[3];   //对应右手纵向摇杆0-3，4，5-7
		jiexi[2]=Rxbuffer[5];   //对应左手油门 0-3，4，5-7
		jiexi[3]=Rxbuffer[7];   //对应左手横向摇杆0-3，4，5-7
		jiexi[4]=Rxbuffer[9];   //对应左手旋钮0-7
		jiexi[5]=Rxbuffer[11];  //对应右手旋钮0-7
		jiexi[6]=Rxbuffer[13];  //左一两段开关0，7
		jiexi[7]=Rxbuffer[15];  //左二两段开关0，7
		jiexi[8]=Rxbuffer[17];  //右二三段开关0，4，7
		jiexi[9]=Rxbuffer[19];  //右一两段开关0，7
		HAL_UART_Transmit(&huart1,&jiexi[0],2,0xFFFF);
		if(jiexi[0] == 1 | jiexi[0]==7 | jiexi[1]==1 | jiexi[1] ==7 |jiexi[3]==1 | jiexi[3]==7){
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_SET);
		}
		else{
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_RESET);
		}
		if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_2)==GPIO_PIN_SET){
			i=1;
		}
		if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_2)==GPIO_PIN_RESET){
			i=0;
		}
    if(jiexi[0]>5){
			//HAL_UART_Transmit(&huart1,"11",2,0xFFFF);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_RESET);
		}
		if(jiexi[0]<6&&jiexi[0]>2){
			//HAL_UART_Transmit(&huart1,"22",2,0xFFFF);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_SET);
		}
		if(jiexi[0]<3){
			//HAL_UART_Transmit(&huart1,"33",2,0xFFFF);
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_RESET);
		}
		//left and right
		
		

		
		if(jiexi[1]>5){
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14,GPIO_PIN_RESET);
		}
		if(jiexi[1]<6&&jiexi[1]>2){
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14,GPIO_PIN_SET);
	  	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_RESET);
		}
		if(jiexi[1]<3){
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_SET);
		}//down or up
		

		
	if(jiexi[3]>5){
			HAL_GPIO_WritePin(GPIOG,GPIO_PIN_7,GPIO_PIN_RESET);//这里初始状态时拉高，所以我设置了拉低为启动
		
		}
		if(jiexi[3]<6&&jiexi[3]>2){
						HAL_GPIO_WritePin(GPIOG,GPIO_PIN_7,GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOG,GPIO_PIN_8,GPIO_PIN_SET);
		}
		if(jiexi[3]<3){
						HAL_GPIO_WritePin(GPIOG,GPIO_PIN_8,GPIO_PIN_RESET);

		}  //left translation or right translation  

		
if(jiexi[4]<2){
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET);
}
if(jiexi[4]>1 && jiexi[4]<6){
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET);
}
if(jiexi[4]>5){
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET);
}
if(jiexi[5]<2){
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
}
if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_2)==GPIO_PIN_SET){
if(jiexi[5]>1 && jiexi[5]<6){
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
}
if(jiexi[5]>5){
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET);
}
}
if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_2)==GPIO_PIN_RESET){
	if(jiexi[5]>3){
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
}
	
if(jiexi[5]<2){
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
}}

if(jiexi[9]==0)
{
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, 200);//PB9//PB0
}
if(jiexi[9]==7)
{
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, 0);
}
if(jiexi[2]==0 || jiexi[2]==1)//PB10
{
	__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_2, 1000);//PA1
}


if(jiexi[2]==2 || jiexi[2] ==3)//PB10
{
	__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_2, 1250);//PA1
}

if(jiexi[2]==4 || jiexi[2]==5)//PB10
{
	__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_2, 1370);//PA1
}



if(jiexi[2]==6)
{
	__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_2, 1600);

}
if(jiexi[2]==7){
	__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_2, 1700);
}
	
if(jiexi[7]==0){
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 500);
}
if(jiexi[7]==7){
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 1800);
}
if(jiexi[8]==0)//PG2 bujin  PB0 PWM
{
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,GPIO_PIN_SET);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
}
if(jiexi[8]==4)
{
	HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
}
if(jiexi[8]==7)
{
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,GPIO_PIN_RESET);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
}
	}
}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  
  /* USER CODE END 3 */

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
