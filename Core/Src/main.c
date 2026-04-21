/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "tjc_usart_hmi.h"
#define FRAME_LENGTH 7
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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	initRingBuffer();		//��ʼ�����λ�����
	HAL_UART_Receive_IT(&TJC_UART, RxBuffer, 1);	//�򿪴��ڽ����ж�
	int a = 100;
	char str[100];
	uint32_t nowtime = HAL_GetTick();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
while (1)
	{
		if (HAL_GetTick() - nowtime >= 1000)
		{
			nowtime = HAL_GetTick();

			sprintf(str, "page1.cnt.val=%d", a);
			tjc_send_string(str);
			// sprintf(str, "t0.txt=\"%d\"\xff\xff\xff", a);
			// tjc_send_string(str);
			// sprintf(str, "click b0,1\xff\xff\xff");
			// tjc_send_string(str);
			// HAL_Delay(50);
			// sprintf(str, "click b0,0\xff\xff\xff");
			// tjc_send_string(str);

			a++;
		}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

		//stm32f103��GND�Ӵ������򴮿ڹ��ߵ�GND,����
		//stm32f103��TX2(PA2)�Ӵ������򴮿ڹ��ߵ�RX
		//stm32f103��RX2(PA3)�Ӵ������򴮿ڹ��ߵ�TX
		//stm32f103��5V�Ӵ�������5V,����Ǵ��ڹ���,���ý�5VҲ����
		//�������ݸ�ʽ��
		//��������֡���ȣ�7�ֽ�
		//֡ͷ     ����1    ����2   ����3       ֡β
		//0x55     1�ֽ�   1�ֽ�    1�ֽ�     0xffffff
		//��������01ʱ
		//֡ͷ     ����1    ����2   ����3       ֡β
		//0x55     01     led���  led״̬    0xffffff
		//����1����λ������  printh 55 01 01 00 ff ff ff  ���壺1��led�ر�
		//����2����λ������  printh 55 01 04 01 ff ff ff  ���壺4��led��
		//����3����λ������  printh 55 01 00 01 ff ff ff  ���壺0��led��
		//����4����λ������  printh 55 01 04 00 ff ff ff  ���壺4��led�ر�
		//��������02��03ʱ
		//֡ͷ     ����1    ����2   ����3       ֡β
		//0x55     02/03   ����ֵ    00    0xffffff
		//����1����λ������  printh 55 02 64 00 ff ff ff  ���壺h0.val=100
		//����2����λ������  printh 55 02 00 00 ff ff ff  ���壺h0.val=0
		//����3����λ������  printh 55 03 64 00 ff ff ff  ���壺h1.val=100
		//����4����λ������  printh 55 03 00 00 ff ff ff  ���壺h1.val=0
		// �����ڻ��������ڵ���һ֡�ĳ���ʱ
	// 	while (usize >= FRAME_LENGTH)
	// 	{
	// 		// У��֡ͷ֡β�Ƿ�ƥ��
	// 		if (usize >= FRAME_LENGTH && u(0) == 0x55 && u(4) == 0xff && u(5) == 0xff && u(6) == 0xff)
	// 		{
	// 			// ƥ�䣬���н���
	// 			if (u(1) == 0x01)
	// 			{
	// 				sprintf(str, "msg.txt=\"led %d is %s\"", u(2),
	// 						u(3) ? "on" : "off");
	// 				tjc_send_string(str);
	// 			} else if (u(1) == 0x02)
	// 			{
	// 				// �·�����h0����������Ϣ
	// 				sprintf(str, "msg.txt=\"h0.val is %d\"", u(2));
	// 				tjc_send_string(str);
	// 			} else if (u(1) == 0x03)
	// 			{
	// 				// �·�����h1����������Ϣ
	// 				sprintf(str, "msg.txt=\"h1.val is %d\"", u(2));
	// 				tjc_send_string(str);
	// 			}

	// 			udelete(7); // ɾ��������������
	// 		} else
	// 		{
	// 			// ��ƥ��ɾ��1�ֽ�
	// 			udelete(1);
	// 			break;
	// 		}
	// 	}

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
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
#ifdef USE_FULL_ASSERT
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
