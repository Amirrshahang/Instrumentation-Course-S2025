/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gpio.h"
#include <stdio.h>
#include <string.h>
#include "stdio.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define RS_Pin GPIO_PIN_0
#define EN_Pin GPIO_PIN_1
#define D4_Pin GPIO_PIN_10
#define D5_Pin GPIO_PIN_11
#define D6_Pin GPIO_PIN_12
#define D7_Pin GPIO_PIN_13
#define LCD_Port GPIOB
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

void LCD_Delay(uint32_t time) {
  for (uint32_t i = 0; i < time * 10; i++) __NOP();
}

void LCD_EnablePulse(void) {
  HAL_GPIO_WritePin(LCD_Port, EN_Pin, GPIO_PIN_SET);
  LCD_Delay(2);
  HAL_GPIO_WritePin(LCD_Port, EN_Pin, GPIO_PIN_RESET);
  LCD_Delay(2);
}

void LCD_Send4Bits(uint8_t data) {
  HAL_GPIO_WritePin(LCD_Port, D4_Pin, (data >> 0) & 1);
  HAL_GPIO_WritePin(LCD_Port, D5_Pin, (data >> 1) & 1);
  HAL_GPIO_WritePin(LCD_Port, D6_Pin, (data >> 2) & 1);
  HAL_GPIO_WritePin(LCD_Port, D7_Pin, (data >> 3) & 1);
  LCD_EnablePulse();
}

void LCD_SendCommand(uint8_t cmd) {
  HAL_GPIO_WritePin(LCD_Port, RS_Pin, GPIO_PIN_RESET);
  LCD_Send4Bits(cmd >> 4);
  LCD_Send4Bits(cmd & 0x0F);
  LCD_Delay(5);
}

void LCD_SendData(uint8_t data) {
  HAL_GPIO_WritePin(LCD_Port, RS_Pin, GPIO_PIN_SET);
  LCD_Send4Bits(data >> 4);
  LCD_Send4Bits(data & 0x0F);
  LCD_Delay(5);
}

void LCD_SendString(char* str) {
  while (*str) LCD_SendData(*str++);
}

void LCD_SetCursor(uint8_t row, uint8_t col) {
  uint8_t pos = (row == 0) ? (0x80 + col) : (0xC0 + col);
  LCD_SendCommand(pos);
}

void LCD_Init(void) {
  LCD_Delay(500);
  LCD_Send4Bits(0x03); LCD_Delay(50);
  LCD_Send4Bits(0x03); LCD_Delay(50);
  LCD_Send4Bits(0x03); LCD_Delay(50);
  LCD_Send4Bits(0x02);

  LCD_SendCommand(0x28);
  LCD_SendCommand(0x0C);
  LCD_SendCommand(0x06);
  LCD_SendCommand(0x01);
}
void LCD_Clear(void) {
  LCD_SendCommand(0x01);
  LCD_Delay(2);
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
  MX_GPIO_Init();

  /* USER CODE BEGIN 2 */


    LCD_Init();
    LCD_SetCursor(0, 0);


    uint8_t button_pressed = 0;
    uint8_t last_button_state = 1;
    uint8_t current_button_state = 0;
    uint8_t lcd_state = 255;
  /* USER CODE END 2 */

  /* Infinite loop */

  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

	  current_button_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
	    	 	  if (current_button_state == 1 && last_button_state == 1)
	    	 	  	    		{
	    	 	  	    			button_pressed = 1;
	    	 	  	    		}
	    	 		last_button_state = current_button_state;
	    	 		if (button_pressed)
	    	 			    		{
	    	 			    			button_pressed = 0;
	    	 			    			if (lcd_state != 1) {
	    	 			    				LCD_Clear();
	    	 			    				LCD_SendString("Touched");
	    	 			    				lcd_state = 1;
	    	 			    			}

	    	 			    		}
	    	 		else {
	    	 			if (lcd_state != 0) {
	    	 							LCD_Clear();
	    	 						    LCD_SendString("Not Touched");
	    	 						   lcd_state = 0;
	    	 			}
	    	 		}
	    	 		HAL_Delay(10);

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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
