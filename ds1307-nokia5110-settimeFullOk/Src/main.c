/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"

/* USER CODE BEGIN Includes */

//Hung
#include "nokia_5110.h"
#include "hinh_anh.h"

#include "stdio.h" 			// Thu vien chua ham sprintf
#include "string.h"			// Thu vien chua ham strlen()

// doc ds1307
#include "ds1307.h"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
DMA_HandleTypeDef hdma_i2c1_rx;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

//Hung
char lcdBuff[64];
char hh, mm, ss;
char dd, DD, MM, YY; 
int doDaiChuoi;

//On/Off Time
int isOn=0;
uint8_t pump_time=0;
uint8_t on_hh, on_mm, on_ss;
uint8_t on_dd, on_DD, on_MM, on_YY;
uint8_t off_hh, off_mm, off_ss;
uint8_t off_dd, off_DD, off_MM, off_YY;

char tmp_hh, tmp_mm, tmp_ss;
char tmp_dd, tmp_DD, tmp_MM, tmp_YY; 

//char* MENU_LIST ="Lua chon muc de sua";
typedef enum
{
	DateType = 0x01,
	MonthType = 0x02,
	YearType = 0x03,
	
	HourType = 0x04,
	MinType	= 0x05,
	SecondType = 0x06,

} Menu;	

typedef struct
{
	uint8_t	Date ;
	uint8_t	Month;
	uint8_t Year;
	
	uint8_t Hour;
	uint8_t Minute;
	uint8_t Second;

} RTCValue;

typedef enum{
	KEY_NONE = 0x00,
	KEY_UP = 0x01,
	KEY_DOWN = 0x02,
	KEY_DONE = 0x03,
} KeyType;


KeyType _key;
Menu _menu;
RTCValue _rtc;

//For debugging Hung
int count = 0;
//uint8_t menu; 

//Setup MENU
uint8_t selected_menu=0;
uint8_t selected_up=0;
uint8_t selected_down=0;
uint8_t selected_done=0;



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_I2C1_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

//Hung
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);


/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_DMA_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
//Hung
	LCDInit(0x30, 0, 2); //(contrast, coefficent, bias)
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);//Chan B15 noi voi BackLight cua LCD Nokia 5110 bi thieu dien nen phai set
	LCDClear();
	//Ds1307
	// Initialize DS1307
  //rtcWriteTime(9,01, 50); //Thiet lap thoi gian
	//rtcWriteDate(1, 26, 2, 18); //Thiet lap ngay thang
	
	
	 selected_menu=0;
	  selected_up=0;
	  selected_down=0;
	  selected_done=0;
		
		//Init On Time
		on_ss=0;
		on_mm=0;
		on_hh=0;
		on_dd=0;
		on_DD=0;
		on_MM=0;
		on_YY=0;
		isOn=0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
 while (1)
  {

  /* USER CODE END WHILE */
		
		 gotoXY(0,0);
//		sprintf(lcdBuff, "Chao Hung");
//		doDaiChuoi = strlen(lcdBuff);   // Lay do dai cua choi trong mang buffer
//		LCDString(lcdBuff); 
		
//		//Doc DS1307
		rtcReadTime(&hh, &mm, &ss);
//		sprintf(&lcdBuff[0], "%0.2d:%0.2d:%0.2d", hh, mm, ss);
//		gotoXY(0,1);
//		LCDString(&lcdBuff[0]);
//		
		rtcReadDate(&dd, &DD, &MM, &YY);
//		sprintf(&lcdBuff[0], "%0.2d-%0.2d/%0.2d/20%0.2d", dd, DD, MM, YY);
//		gotoXY(0,2);
//		LCDString(&lcdBuff[0]);
		
		gotoXY(0, 0);
		sprintf(&lcdBuff[0], (hh <= 9) ? "0%d" : "%d", hh);
		LCDString(&lcdBuff[0]);
		LCDString(":");
		sprintf(&lcdBuff[0], (mm <= 9) ? "0%d" : "%d", mm);
		LCDString(&lcdBuff[0]);
		LCDString(":");
		sprintf(&lcdBuff[0], (ss <= 9) ? "0%d" : "%d", ss);
		LCDString(&lcdBuff[0]);
		
		gotoXY(0, 1);
		sprintf(&lcdBuff[0], (DD <= 9) ? "0%d" : "%d", DD);
		LCDString(&lcdBuff[0]);
		LCDString("/");
		sprintf(&lcdBuff[0], (MM <= 9) ? "0%d" : "%d", MM);
		LCDString(&lcdBuff[0]);
		LCDString("/");
		sprintf(&lcdBuff[0], "20%d", YY);
		LCDString(&lcdBuff[0]);
		
		
		
		HAL_Delay(400);
		
		
		
		
//			HAL_Delay(10000);
			
		//Turn On Pump on Scheduled
		if(isOn==1){
			pump_time++;
			
			rtcReadTime(&tmp_hh, &tmp_mm, &tmp_ss);
      rtcReadDate(&tmp_dd, &tmp_DD, &tmp_MM, &tmp_YY);
			
			on_hh = (uint8_t) tmp_hh;
			on_mm = (uint8_t) tmp_mm;
			on_ss = (uint8_t) tmp_ss;
			
//			sprintf(&on_hh, (tmp_hh <= 9) ? "0%d" : "%d", tmp_hh);
//			sprintf(&on_mm, (tmp_mm <= 9) ? "0%d" : "%d", tmp_mm);
//			sprintf(&on_ss, (tmp_ss <= 9) ? "0%d" : "%d", tmp_ss);
			
			gotoXY(0, 5);
			sprintf(&lcdBuff[0], (hh <= 9) ? "0%d" : "%d", hh);
			LCDString(&lcdBuff[0]);
			LCDString(":");
			sprintf(&lcdBuff[0], (mm <= 9) ? "0%d" : "%d", mm);
			LCDString(&lcdBuff[0]);
			LCDString(":");
			sprintf(&lcdBuff[0], (ss <= 9) ? "0%d" : "%d", ss);
			LCDString(&lcdBuff[0]);

			HAL_GPIO_WritePin(RELAY1_GPIO_Port, RELAY1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(RELAY2_GPIO_Port, RELAY2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(RELAY3_GPIO_Port, RELAY3_Pin, GPIO_PIN_SET);
			if(pump_time>50){
				gotoXY(0, 5);
				LCDString("TURN OFF PUMP");
				HAL_GPIO_WritePin(RELAY1_GPIO_Port, RELAY1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(RELAY2_GPIO_Port, RELAY2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(RELAY3_GPIO_Port, RELAY3_Pin, GPIO_PIN_RESET);
				isOn=0;
			}
			
//			if(mm==on_mm && hh==on_hh && DD==on_DD && MM==on_MM && YY==on_YY){
//				HAL_GPIO_WritePin(RELAY1_GPIO_Port, RELAY1_Pin, GPIO_PIN_SET);
//				HAL_Delay(10000);
//				HAL_GPIO_WritePin(RELAY1_GPIO_Port, RELAY1_Pin, GPIO_PIN_RESET);
//			}else{
//				on_ss=0;
//				on_mm=0;
//				on_hh=0;
//				on_dd=0;
//				on_DD=0;
//				on_MM=0;
//				on_YY=0;
//			}
			
			
		}else{
			on_ss=0;
			on_mm=0;
			on_hh=0;
			on_dd=0;
			on_DD=0;
			on_MM=0;
			on_YY=0;
			isOn=0;
		}
		
		

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}


//Hung
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	 
	
		//menu = HAL_GPIO_ReadPin(GPIOA,GPIO_Pin);
//		if(HAL_GPIO_ReadPin(GPIOA,GPIO_Pin)==GPIO_PIN_RESET)
//		{
			if(GPIO_Pin==MENU){
				selected_menu++;
				count++;
				//LCDClear();
				gotoXY(0,2);
				LCDString("Chon MENU:");
				gotoXY(0,3);
				LCDString("1.Set Clock Time");
				gotoXY(0,4);
				LCDString("2.Pump On/Off");
				gotoXY(0,5);
				LCDString("3.Pump Length");
				if(selected_menu>2){
					selected_down = 0;
					selected_up = 0;
					selected_done = 0;
					//selected_menu = 1;
				}
			}
			
			if(GPIO_Pin==DOWN){
				count++;
				//LCDClear();
				
				 // LCDString("                ");
				selected_down++;
				
				if(selected_menu){
					
					if(selected_down==1){
						gotoXY(0,3);
						LCDString("<Back MENU");
						gotoXY(0,4);
						LCDString("1.Set Clock");
						gotoXY(0,5);
						LCDString("             ");
					} else if(selected_down==2){
						gotoXY(0,3);
						LCDString("2.Pump On/Off");
						gotoXY(0,4);
						LCDString("             ");
						gotoXY(0,5);
						LCDString("             ");
					} else if(selected_down==3){
						gotoXY(0,3);
						LCDString("3.Pump Length");
						gotoXY(0,4);
						LCDString("<Back           ");
						gotoXY(0,5);
						LCDString("             ");
						
					} else if(selected_down==4){
						gotoXY(0,2);
						LCDString("Chon MENU:");
						gotoXY(0,3);
						LCDString("1.Set Clock Time");
						gotoXY(0,4);
						LCDString("2.Pump On/Off");
						gotoXY(0,5);
						LCDString("3.Pump Length");
						selected_down=0;
					}
					
					
				}else{
					gotoXY(0,3);
					LCDString("DOWN");
				}
				
			}
			
			
			if(GPIO_Pin==UP){
				count++;
				//LCDClear();
				
				selected_up++;
				
				if(selected_menu){
					//LCDClear();
					if(selected_down==1){
						
						
						if(selected_up>=1){
							
							gotoXY(0,2);
							LCDString("Chon MENU:");
							gotoXY(0,3);
							LCDString("1.Set Clock Time");
							gotoXY(0,4);
							LCDString("2.Pump On/Off");
							gotoXY(0,5);
							LCDString("3.Pump Length");
							
							selected_up = 0;//reset lai bien selected_up trong truong hop press nhieu lan
							
						}
						
						
						
					} else if(selected_down==2){
						
						
						
						if(selected_up==1){
							
							gotoXY(0,3);
							LCDString("<Back MENU    ");
							gotoXY(0,4);
							LCDString("1.Set Clock");
							gotoXY(0,5);
							LCDString("             ");
							
							
							
						}
						else if(selected_up>=2){
						
							
							gotoXY(0,2);
							LCDString("Chon MENU:");
							gotoXY(0,3);
							LCDString("1.Set Clock Time");
							gotoXY(0,4);
							LCDString("2.Pump On/Off");
							gotoXY(0,5);
							LCDString("3.Pump Length");
							selected_up = 0;//reset lai bien selected_up trong truong hop press nhieu lan
							
							
						}
						
						
						
						
							
						
					} else if(selected_down==3){
						
						if(selected_up==1){
							
							gotoXY(0,3);
							LCDString("              ");
							gotoXY(0,4);
							LCDString("2.Pump On/Off");
							gotoXY(0,5);
							LCDString("             ");
							
							
							
						}
						else if(selected_up==2){
						
							
							gotoXY(0,3);
							LCDString("<Back MENU");
							gotoXY(0,4);
							LCDString("1.Set Clock Time");
							gotoXY(0,5);
							LCDString("              ");
							
							
							
						}else if(selected_up>=3){
						
							
							
							gotoXY(0,2);
							LCDString("Chon MENU:");
							gotoXY(0,3);
							LCDString("1.Set Clock Time");
							gotoXY(0,4);
							LCDString("2.Pump On/Off");
							gotoXY(0,5);
							LCDString("3.Pump Length");
							//selected_up = 0;//reset lai bien selected_up trong truong hop press nhieu lan
							
							
							
						}
						
						
						
					} else if(selected_down==4){
						if(selected_up==1){
							
							gotoXY(0,3);
							LCDString("              ");
							gotoXY(0,4);
							LCDString("3.Pump Length");
							gotoXY(0,5);
							LCDString("             ");
							
							
							
						}
						else if(selected_up==2){
						
							
							
							gotoXY(0,3);
							LCDString("2.Pump On/Off");
							gotoXY(0,4);
							LCDString("              ");
							gotoXY(0,5);
							LCDString("              ");
							
							
							
						}else if(selected_up==3){
						
							
							
							
							gotoXY(0,3);
							LCDString("<Back MENU");
							gotoXY(0,4);
							LCDString("1.Set Clock Time");
							gotoXY(0,5);
							LCDString("                 ");
							//selected_up = 0;//reset lai bien selected_up trong truong hop press nhieu lan
							
							
							
						}else if(selected_up>3){
						
							
							
							gotoXY(0,2);
							LCDString("Chon MENU:");
							gotoXY(0,3);
							LCDString("1.Set Clock Time");
							gotoXY(0,4);
							LCDString("2.Pump On/Off");
							gotoXY(0,5);
							LCDString("3.Pump Length");
							selected_up = 0;//reset lai bien selected_up trong truong hop press nhieu lan
							
							
							
						}
						
						
					}
					
					
				} else{ //selected_menu = 0
					gotoXY(0,3);
					LCDString("UP");
				}
			}//Up Key 
			
			if(GPIO_Pin==DONE){//TODO
				count++;
				selected_done++;
				if(selected_menu==1){
					if(selected_down==2){
						if(selected_done==1){
							isOn=1;
							
//							rtcReadTime(&tmp_hh, &tmp_mm, &tmp_ss);
//							rtcReadDate(&tmp_dd, &tmp_DD, &tmp_MM, &tmp_YY);
//							
							gotoXY(0, 4);
							LCDString("Pump on at:");
//							
//						sprintf(&on_hh, (tmp_hh <= 9) ? "0%d" : "%d", tmp_hh);
//						sprintf(&on_mm, (tmp_mm <= 9) ? "0%d" : "%d", tmp_mm+1);
//						sprintf(&on_ss, (tmp_ss <= 9) ? "0%d" : "%d", tmp_ss);
//						
////							on_mm = mm+1;
////							on_hh=hh;
////							if(on_mm>59) {
////								on_hh=hh+1;
////								if(on_hh>24){
////									on_hh=1;
////									on_mm=1;
////								}
////								on_mm=1;
////							}
//							gotoXY(0, 5);
//							sprintf(&lcdBuff[0], (hh <= 9) ? "0%d" : "%d", hh);
//							LCDString(&lcdBuff[0]);
//							LCDString(":");
//							sprintf(&lcdBuff[0], (on_mm <= 9) ? "0%d" : "%d", on_mm);
//							LCDString(&lcdBuff[0]);
//							LCDString(":");
//							sprintf(&lcdBuff[0], (ss <= 9) ? "0%d" : "%d", ss);
//							LCDString(&lcdBuff[0]);
//							//on_mm=mm;
//							//on_hh=hh;
//							on_ss=ss;
//							on_dd=dd;
//							on_DD=DD;
//							on_MM=MM;
//							on_YY=YY;
							selected_done=0;//reset
							
							
						}
					}
				}else{
					LCDClear();
					gotoXY(0,3);
					LCDString("DONE!");
				}
				
				
			}
			
			
		//}
	
}
//End Hung

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* I2C1 init function */
static void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel7_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, RELAY1_Pin|RELAY2_Pin|RELAY3_Pin|GPIO_PIN_10 
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
                          |GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : DONE_Pin DOWN_Pin MENU_Pin UP_Pin */
  GPIO_InitStruct.Pin = DONE_Pin|DOWN_Pin|MENU_Pin|UP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : RELAY1_Pin RELAY2_Pin RELAY3_Pin PB10 
                           PB11 PB12 PB13 PB14 
                           PB15 */
  GPIO_InitStruct.Pin = RELAY1_Pin|RELAY2_Pin|RELAY3_Pin|GPIO_PIN_10 
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
                          |GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
