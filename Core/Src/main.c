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
#include "fatfs.h"

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
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc3;

I2C_HandleTypeDef hi2c1;

SD_HandleTypeDef hsd;
DMA_HandleTypeDef hdma_sdio;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;

SRAM_HandleTypeDef hsram1;
SRAM_HandleTypeDef hsram2;

/* USER CODE BEGIN PV */
extern uint16_t xpos, ypos;
uint8_t touch_flag;

uint8_t joypad;

int p_x=0, p_y=0;
int p_prev_i, p_prev_j;
int p_curr_i, p_curr_j;
int p_d = 2;

int g1_x, g1_y;
int g1_prev_i, g1_prev_j;
int g1_curr_i, g1_curr_j;
int g1_d;
int g1_state;

int g2_x, g2_y;
int g2_prev_i, g2_prev_j;
int g2_curr_i, g2_curr_j;
int g2_d;
int g2_state;

int g3_x, g3_y;
int g3_prev_i, g3_prev_j;
int g3_curr_i, g3_curr_j;
int g3_d;
int g3_state;

int g4_x, g4_y;
int g4_prev_i, g4_prev_j;
int g4_curr_i, g4_curr_j;
int g4_d;
int g4_state;

// speed: To move 1 block, it needs speed cnt
int p_speed = 8;

int g1_speed = 64;
int g2_speed = 64;
int g3_speed = 64;
int g4_speed = 64;

// 0:main 1:name 2:play 3:gameover
int game_state = 2;

int score = 0;
int life = 3;
int level = 1;

int cnt = 0;
int level_start_cnt = 0;
// all food = 299
int food_cnt = 0;

// 1:block  10:food
int map_init_state[31][28] = {
		{ 1, 1, 1, 1, 1,  1, 1, 1, 1, 1,  1, 1, 1, 1, 1,  1, 1, 1, 1, 1,  1, 1, 1, 1, 1,  1, 1, 1},
		{ 1,10,10,10,10, 10,10,10,10,10, 10,10,10, 1, 1, 10,10,10,10,10, 10,10,10,10,10, 10,10, 1},
		{ 1,10, 1, 1, 1,  1,10, 1, 1, 1,  1, 1,10, 1, 1, 10, 1, 1, 1, 1,  1,10, 1, 1, 1,  1,10, 1},
		{ 1,10, 1, 1, 1,  1,10, 1, 1, 1,  1, 1,10, 1, 1, 10, 1, 1, 1, 1,  1,10, 1, 1, 1,  1,10, 1},
		{ 1,10, 1, 1, 1,  1,10, 1, 1, 1,  1, 1,10, 1, 1, 10, 1, 1, 1, 1,  1,10, 1, 1, 1,  1,10, 1},

		{ 1,10,10,10,10, 10,10,10,10,10, 10,10,10,10,10, 10,10,10,10,10, 10,10,10,10,10, 10,10, 1},
		{ 1,10, 1, 1, 1,  1,10, 1, 1,10,  1, 1, 1, 1, 1,  1, 1, 1,10, 1,  1,10, 1, 1, 1,  1,10, 1},
		{ 1,10, 1, 1, 1,  1,10, 1, 1,10,  1, 1, 1, 1, 1,  1, 1, 1,10, 1,  1,10, 1, 1, 1,  1,10, 1},
		{ 1,10,10,10,10, 10,10, 1, 1,10, 10,10,10, 1, 1, 10,10,10,10, 1,  1,10,10,10,10, 10,10, 1},
		{ 1, 1, 1, 1, 1,  1,10, 1, 1, 1,  1, 1,10, 1, 1, 10, 1, 1, 1, 1,  1,10, 1, 1, 1,  1, 1, 1},

		{ 0, 0, 0, 0, 0,  1,10, 1, 1, 1,  1, 1,10, 1, 1, 10, 1, 1, 1, 1,  1,10, 1, 0, 0,  0, 0, 0},
		{ 0, 0, 0, 0, 0,  1,10, 1, 1,10, 10,10,10,10,10, 10,10,10,10, 1,  1,10, 1, 0, 0,  0, 0, 0},
		{ 0, 0, 0, 0, 0,  1,10, 1, 1,10,  1, 1, 1, 1, 1,  1, 1, 1,10, 1,  1,10, 1, 0, 0,  0, 0, 0},
		{ 1, 1, 1, 1, 1,  1,10, 1, 1,10,  1, 0, 0, 0, 0,  0, 0, 1,10, 1,  1,10, 1, 1, 1,  1, 1, 1},
		{10,10,10,10,10, 10,10,10,10,10,  1, 0, 0, 0, 0,  0, 0, 1,10,10, 10,10,10,10,10, 10,10,10},

		{ 1, 1, 1, 1, 1,  1,10, 1, 1,10,  1, 0, 0, 0, 0,  0, 0, 1,10, 1,  1,10, 1, 1, 1,  1, 1, 1},
		{ 0, 0, 0, 0, 0,  1,10, 1, 1,10,  1, 1, 1, 1, 1,  1, 1, 1,10, 1,  1,10, 1, 0, 0,  0, 0, 0},
		{ 0, 0, 0, 0, 0,  1,10, 1, 1,10, 10,10,10, 0,10, 10,10,10,10, 1,  1,10, 1, 0, 0,  0, 0, 0},
		{ 0, 0, 0, 0, 0,  1,10, 1, 1,10,  1, 1, 1, 1, 1,  1, 1, 1,10, 1,  1,10, 1, 0, 0,  0, 0, 0},
		{ 1, 1, 1, 1, 1,  1,10, 1, 1,10,  1, 1, 1, 1, 1,  1, 1, 1,10, 1,  1,10, 1, 1, 1,  1, 1, 1},

		{ 1,10,10,10,10, 10,10,10,10,10, 10,10,10, 1, 1, 10,10,10,10,10, 10,10,10,10,10, 10,10, 1},
		{ 1,10, 1, 1, 1,  1,10, 1, 1, 1,  1, 1,10, 1, 1, 10, 1, 1, 1, 1,  1,10, 1, 1, 1,  1,10, 1},
		{ 1,10, 1, 1, 1,  1,10, 1, 1, 1,  1, 1,10, 1, 1, 10, 1, 1, 1, 1,  1,10, 1, 1, 1,  1,10, 1},
		{ 1,10,10,10, 1,  1,10,10,10,10, 10,10,10,10,10, 10,10,10,10,10, 10,10, 1, 1,10, 10,10, 1},
		{ 1, 1, 1,10, 1,  1,10, 1, 1,10,  1, 1, 1, 1, 1,  1, 1, 1,10, 1,  1,10, 1, 1,10,  1, 1, 1},

		{ 1, 1, 1,10, 1,  1,10, 1, 1,10,  1, 1, 1, 1, 1,  1, 1, 1,10, 1,  1,10, 1, 1,10,  1, 1, 1},
		{ 1,10,10,10,10, 10,10, 1, 1,10, 10,10,10, 1, 1, 10,10,10,10, 1,  1,10,10,10,10, 10,10, 1},
		{ 1,10, 1, 1, 1,  1, 1, 1, 1, 1,  1, 1,10, 1, 1, 10, 1, 1, 1, 1,  1, 1, 1, 1, 1,  1,10, 1},
		{ 1,10, 1, 1, 1,  1, 1, 1, 1, 1,  1, 1,10, 1, 1, 10, 1, 1, 1, 1,  1, 1, 1, 1, 1,  1,10, 1},
		{ 1,10,10,10,10, 10,10,10,10,10, 10,10,10,10,10, 10,10,10,10,10, 10,10,10,10,10, 10,10, 1},

		{ 1, 1, 1, 1, 1,  1, 1, 1, 1, 1,  1, 1, 1, 1, 1,  1, 1, 1, 1, 1,  1, 1, 1, 1, 1,  1, 1, 1}

};

int map[31][28];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_ADC1_Init(void);
static void MX_ADC3_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM1_Init(void);
static void MX_SPI1_Init(void);
static void MX_FSMC_Init(void);
static void MX_SDIO_SD_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
void init_map(void);
int check_game_over(int p_temp_x, int p_temp_y, int g1_temp_x, int g1_temp_y, int g2_temp_x, int g2_temp_y, int g3_temp_x, int g3_temp_y, int g4_temp_x, int g4_temp_y);
int check_level_up(void);
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
  int i, j;
  int p_temp_x, p_temp_y;
  int g1_temp_x, g1_temp_y;
  int g2_temp_x, g2_temp_y;
  int g3_temp_x, g3_temp_y;
  int g4_temp_x, g4_temp_y;
  int temp_score = 0;

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
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  MX_ADC3_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_SPI1_Init();
  MX_FSMC_Init();
  MX_SDIO_SD_Init();
  MX_FATFS_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim1, 0);
  Codex_HW_Reset();
  LCD_BL_on();

  LCD_init();
  LCD_Clear(COLOR_BLACK);
//  Codex_Speaker_on();

  HAL_Delay(100);

  HAL_TIM_Base_Start_IT(&htim2);

  init_map();
  temp_score = score;
  LCD_Draw_Score(temp_score, 1);
  LCD_Draw_Score(temp_score, 0);
  LCD_Draw_Level(level);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	if(game_state == 2) {
		temp_score = score;
		p_temp_x = p_x, p_temp_y = p_y;
		g1_temp_x = g1_x, g1_temp_y = g1_y;
		g2_temp_x = g2_x, g2_temp_y = g2_y;
		g3_temp_x = g3_x, g3_temp_y = g3_y;
		g4_temp_x = g4_x, g4_temp_y = g4_y;

		if(map[g1_prev_i][g1_prev_j] != 0) {
			LCD_Draw_Food(8*g1_prev_j+8, 8*g1_prev_i+36);
		}
		LCD_Draw_Ghost(g1_temp_x, g1_temp_y, 1, 1);

		if(map[g2_prev_i][g2_prev_j] != 0) {
			LCD_Draw_Food(8*g2_prev_j+8, 8*g2_prev_i+36);
		}
		LCD_Draw_Ghost(g2_temp_x, g2_temp_y, 2, 1);

		if(map[g3_prev_i][g3_prev_j] != 0) {
			LCD_Draw_Food(8*g3_prev_j+8, 8*g3_prev_i+36);
		}
		LCD_Draw_Ghost(g3_temp_x, g3_temp_y, 3, 1);

		if(map[g4_prev_i][g4_prev_j] != 0) {
			LCD_Draw_Food(8*g4_prev_j+8, 8*g4_prev_i+36);
		}
		LCD_Draw_Ghost(g4_temp_x, g4_temp_y, 4, 1);

		LCD_Draw_Score(temp_score, 1);
		LCD_Draw_Pacman(p_temp_x, p_temp_y, 1);
		HAL_Delay(10);

		LCD_Draw_Score(temp_score, 0);
		LCD_Draw_Pacman(p_temp_x, p_temp_y, 0);

		LCD_Draw_Ghost(g1_temp_x, g1_temp_y, 1, 0);
		LCD_Draw_Ghost(g2_temp_x, g2_temp_y, 2, 0);
		LCD_Draw_Ghost(g3_temp_x, g3_temp_y, 3, 0);
		LCD_Draw_Ghost(g4_temp_x, g4_temp_y, 4, 0);


		if(check_game_over(p_temp_x, p_temp_y, g1_temp_x, g1_temp_y, g2_temp_x, g2_temp_y, g3_temp_x, g3_temp_y, g4_temp_x, g4_temp_y)) {
			if(life > 1) {
				life--;
				init_map();
			} else {
				game_state = 3;
			}
		}
		if(food_cnt > 296) {
			if(check_level_up()) {
				init_map();
				level++;
				g1_speed -= 8;
				g2_speed -= 8;
				g3_speed -= 8;
				g4_speed -= 8;
				LCD_Draw_Level(level);
			}
		}
		joypad = Joypad_read();
	} else if(game_state == 3) { // game over
		LCD_Clear(COLOR_BLACK);
		break;
	}


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  LCD_Draw_Str(196, 120, "Your final score is", COLOR_WHITE, 1);
  LCD_Draw_Final_Score(score);
  while(1) {}
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief ADC3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC3_Init(void)
{

  /* USER CODE BEGIN ADC3_Init 0 */

  /* USER CODE END ADC3_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC3_Init 1 */

  /* USER CODE END ADC3_Init 1 */

  /** Common config
  */
  hadc3.Instance = ADC3;
  hadc3.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc3.Init.ContinuousConvMode = ENABLE;
  hadc3.Init.DiscontinuousConvMode = DISABLE;
  hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc3.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_6;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC3_Init 2 */

  /* USER CODE END ADC3_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
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
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SDIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_SDIO_SD_Init(void)
{

  /* USER CODE BEGIN SDIO_Init 0 */

  /* USER CODE END SDIO_Init 0 */

  /* USER CODE BEGIN SDIO_Init 1 */

  /* USER CODE END SDIO_Init 1 */
  hsd.Instance = SDIO;
  hsd.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;
  hsd.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;
  hsd.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;
  hsd.Init.BusWide = SDIO_BUS_WIDE_1B;
  hsd.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
  hsd.Init.ClockDiv = 10;
  /* USER CODE BEGIN SDIO_Init 2 */
  HAL_SD_Init(&hsd);
  HAL_SD_InitCard(&hsd);
  /* USER CODE END SDIO_Init 2 */

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
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
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
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 1000;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_ENABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

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
  htim2.Init.Prescaler = 71;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9999;
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
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Channel4_5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Channel4_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Channel4_5_IRQn);

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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5|VS_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, VS_XDCS_Pin|T_MOSI_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, VS_XCS_Pin|T_CS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LCD_BL_Pin|T_SCL_Pin|JOYPAD_LAT_Pin|BEEP_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(JOYPAD_CLK_GPIO_Port, JOYPAD_CLK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : KEY2_Pin KEY1_Pin KEY0_Pin */
  GPIO_InitStruct.Pin = KEY2_Pin|KEY1_Pin|KEY0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PE5 VS_RST_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_5|VS_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : VS_DERQ_Pin */
  GPIO_InitStruct.Pin = VS_DERQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(VS_DERQ_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : VS_XDCS_Pin VS_XCS_Pin T_MOSI_Pin T_CS_Pin */
  GPIO_InitStruct.Pin = VS_XDCS_Pin|VS_XCS_Pin|T_MOSI_Pin|T_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : PEN_Pin */
  GPIO_InitStruct.Pin = PEN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(PEN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_BL_Pin T_SCL_Pin JOYPAD_LAT_Pin LED0_Pin
                           BEEP_Pin */
  GPIO_InitStruct.Pin = LCD_BL_Pin|T_SCL_Pin|JOYPAD_LAT_Pin|LED0_Pin
                          |BEEP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : T_MISO_Pin JOYPAD_DAT_Pin */
  GPIO_InitStruct.Pin = T_MISO_Pin|JOYPAD_DAT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : JOYPAD_CLK_Pin */
  GPIO_InitStruct.Pin = JOYPAD_CLK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(JOYPAD_CLK_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : REMOTE_IN_Pin */
  GPIO_InitStruct.Pin = REMOTE_IN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(REMOTE_IN_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI2_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* FSMC initialization function */
static void MX_FSMC_Init(void)
{

  /* USER CODE BEGIN FSMC_Init 0 */

  /* USER CODE END FSMC_Init 0 */

  FSMC_NORSRAM_TimingTypeDef Timing = {0};

  /* USER CODE BEGIN FSMC_Init 1 */

  /* USER CODE END FSMC_Init 1 */

  /** Perform the SRAM1 memory initialization sequence
  */
  hsram1.Instance = FSMC_NORSRAM_DEVICE;
  hsram1.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
  /* hsram1.Init */
  hsram1.Init.NSBank = FSMC_NORSRAM_BANK4;
  hsram1.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
  hsram1.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
  hsram1.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
  hsram1.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
  hsram1.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
  hsram1.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
  hsram1.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
  hsram1.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
  hsram1.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
  hsram1.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
  hsram1.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
  hsram1.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
  /* Timing */
  Timing.AddressSetupTime = 6;
  Timing.AddressHoldTime = 15;
  Timing.DataSetupTime = 26;
  Timing.BusTurnAroundDuration = 0;
  Timing.CLKDivision = 16;
  Timing.DataLatency = 17;
  Timing.AccessMode = FSMC_ACCESS_MODE_A;
  /* ExtTiming */

  if (HAL_SRAM_Init(&hsram1, &Timing, NULL) != HAL_OK)
  {
    Error_Handler( );
  }

  /** Perform the SRAM2 memory initialization sequence
  */
  hsram2.Instance = FSMC_NORSRAM_DEVICE;
  hsram2.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
  /* hsram2.Init */
  hsram2.Init.NSBank = FSMC_NORSRAM_BANK3;
  hsram2.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
  hsram2.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
  hsram2.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
  hsram2.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
  hsram2.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
  hsram2.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
  hsram2.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
  hsram2.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
  hsram2.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
  hsram2.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
  hsram2.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
  hsram2.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
  /* Timing */
  Timing.AddressSetupTime = 4;
  Timing.AddressHoldTime = 15;
  Timing.DataSetupTime = 4;
  Timing.BusTurnAroundDuration = 0;
  Timing.CLKDivision = 16;
  Timing.DataLatency = 17;
  Timing.AccessMode = FSMC_ACCESS_MODE_A;
  /* ExtTiming */

  if (HAL_SRAM_Init(&hsram2, &Timing, NULL) != HAL_OK)
  {
    Error_Handler( );
  }

  /** Disconnect NADV
  */

  __HAL_AFIO_FSMCNADV_DISCONNECTED();

  /* USER CODE BEGIN FSMC_Init 2 */

  /* USER CODE END FSMC_Init 2 */
}

/* USER CODE BEGIN 4 */

void init_map() {
	int i, j;
	food_cnt = 0;
	level_start_cnt = cnt;
	p_prev_i=17, p_prev_j=13;
	p_curr_i=17, p_curr_j=13;
	p_d = 2;
	p_x = 12 + (p_prev_j * 8);
	p_y = 40 + (p_prev_i * 8);

	g1_prev_i=11, g1_prev_j=14;
	g1_curr_i=11, g1_curr_j=14;
	g1_d = 0;
	g1_x = 12 + (g1_prev_j * 8);
	g1_y = 40 + (g1_prev_i * 8);
	g1_state = 1;

	g2_prev_i=13, g2_prev_j=14;
	g2_curr_i=13, g2_curr_j=14;
	g2_d = 3;
	g2_x = 12 + (g2_prev_j * 8);
	g2_y = 40 + (g2_prev_i * 8);
	g2_state = 0;

	g3_prev_i=15, g3_prev_j=16;
	g3_curr_i=15, g3_curr_j=16;
	g3_d = 1;
	g3_x = 12 + (g3_prev_j * 8);
	g3_y = 40 + (g3_prev_i * 8);
	g3_state = 0;

	g4_prev_i=15, g4_prev_j=12;
	g4_curr_i=15, g4_curr_j=12;
	g4_d = 1;
	g4_x = 12 + (g4_prev_j * 8);
	g4_y = 40 + (g4_prev_i * 8);
	g4_state = 0;

	for(i=0; i<31; i++) {
		for(j=0; j<28; j++) {
			map[i][j] = map_init_state[i][j];
			if(map_init_state[i][j] == 1) {
				LCD_Draw_Block(8*j+8, 8*i+36);
			} else if(map_init_state[i][j] == 10) {
				LCD_Draw_Food(8*j+8, 8*i+36);
			}
		}
	}
	LCD_Draw_Life(life+1, 0);
	LCD_Draw_Life(life, 1);
}

int check_game_over(int p_temp_x, int p_temp_y, int g1_temp_x, int g1_temp_y, int g2_temp_x, int g2_temp_y, int g3_temp_x, int g3_temp_y, int g4_temp_x, int g4_temp_y) {
	if((g1_temp_x + 8 > p_temp_x) && (g1_temp_x - 8 < p_temp_x) && (g1_temp_y + 8 > p_temp_y) && (g1_temp_y - 8 < p_temp_y)) {
		return 1;
	}
	if((g2_temp_x + 8 > p_temp_x) && (g2_temp_x - 8 < p_temp_x) && (g2_temp_y + 8 > p_temp_y) && (g2_temp_y - 8 < p_temp_y)) {
		return 1;
	}
	if((g3_temp_x + 8 > p_temp_x) && (g3_temp_x - 8 < p_temp_x) && (g3_temp_y + 8 > p_temp_y) && (g3_temp_y - 8 < p_temp_y)) {
		return 1;
	}
	if((g4_temp_x + 8 > p_temp_x) && (g4_temp_x - 8 < p_temp_x) && (g4_temp_y + 8 > p_temp_y) && (g4_temp_y - 8 < p_temp_y)) {
		return 1;
	}
	return 0;
}

int check_level_up() {
	int i, j;
	for(i=0; i<31; i++) {
		for(j=0; j<28; j++) {
			if(map[i][j] == 10 || map[i][j] == 50) {
				return 0;
			}
		}
	}
	return 1;
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
