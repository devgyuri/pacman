/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
int temp_i, temp_j;
int d[5][2] = {{0, 0}, {-1, 0}, {0, -1}, {1, 0}, {0, 1}}; //0: not move
int ready_time[5] = {0, 0, 20, 60, 100};
int test_valid = 0;
int test_k = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_sdio;
extern SD_HandleTypeDef hsd;
extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart1;
/* USER CODE BEGIN EV */
extern TIM_HandleTypeDef htim1;
extern uint8_t touch_flag;

extern int p_x, p_y;
extern int p_prev_i, p_prev_j;
extern int p_curr_i, p_curr_j;
extern int p_d;

extern int g1_x, g1_y;
extern int g1_prev_i, g1_prev_j;
extern int g1_curr_i, g1_curr_j;
extern int g1_d;
extern int g1_state;

extern int g2_x, g2_y;
extern int g2_prev_i, g2_prev_j;
extern int g2_curr_i, g2_curr_j;
extern int g2_d;
extern int g2_state;

extern int g3_x, g3_y;
extern int g3_prev_i, g3_prev_j;
extern int g3_curr_i, g3_curr_j;
extern int g3_d;
extern int g3_state;

extern int g4_x, g4_y;
extern int g4_prev_i, g4_prev_j;
extern int g4_curr_i, g4_curr_j;
extern int g4_d;
extern int g4_state;

extern int p_speed;
extern int g1_speed;
extern int g2_speed;
extern int g3_speed;
extern int g4_speed;

extern int score;
extern int level;

extern int cnt;
extern int level_start_cnt;
extern int food_cnt;

extern int map[31][28];
extern uint8_t joypad;


/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line2 interrupt.
  */
void EXTI2_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI2_IRQn 0 */

  /* USER CODE END EXTI2_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(KEY2_Pin);
  /* USER CODE BEGIN EXTI2_IRQn 1 */

  /* USER CODE END EXTI2_IRQn 1 */
}

/**
  * @brief This function handles EXTI line3 interrupt.
  */
void EXTI3_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI3_IRQn 0 */

  /* USER CODE END EXTI3_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(KEY1_Pin);
  /* USER CODE BEGIN EXTI3_IRQn 1 */

  /* USER CODE END EXTI3_IRQn 1 */
}

/**
  * @brief This function handles EXTI line4 interrupt.
  */
void EXTI4_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_IRQn 0 */

  /* USER CODE END EXTI4_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(KEY0_Pin);
  /* USER CODE BEGIN EXTI4_IRQn 1 */

  /* USER CODE END EXTI4_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */

	//////////////////////////////////////////////////////////

  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(REMOTE_IN_Pin);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */
  g1_state = calc_ghost_state(g1_state, g1_speed, 1);
  g2_state = calc_ghost_state(g2_state, g2_speed, 2);
  g3_state = calc_ghost_state(g3_state, g3_speed, 3);
  g4_state = calc_ghost_state(g4_state, g4_speed, 4);
  move_pacman();
  move_ghost1(g1_state);
  move_ghost2(g2_state);
  move_ghost3(g3_state);
  move_ghost4(g4_state);
  cnt++;


  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */
 // HAL_UART_Receive_IT(&huart1, &str_r, 1);
  //HAL_UART_Transmit(&huart1, &str_r, 1, 100);

/*
  switch(str_r)
  {
  case 'q':
	  HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET); // LED0 ON
	  HAL_UART_Transmit(&huart1, "LED0 ON\n", 8, 100);
	  break;
  case 'w':
	  HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET); // LED0 OFF
	  HAL_UART_Transmit(&huart1, "LED0 OFF\n", 9, 100);
	  break;
  case 'e':
	  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET); // LED1 ON
	  HAL_UART_Transmit(&huart1, "LED1 ON\n", 8, 100);
	  break;
  case 'r':
	  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET); // LED1 OFF
	  HAL_UART_Transmit(&huart1, "LED1 OFF\n", 9, 100);
	  break;
  }
*/

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(PEN_Pin);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */
  touch_flag = 1;
  /* USER CODE END EXTI15_10_IRQn 1 */
}

/**
  * @brief This function handles SDIO global interrupt.
  */
void SDIO_IRQHandler(void)
{
  /* USER CODE BEGIN SDIO_IRQn 0 */

  /* USER CODE END SDIO_IRQn 0 */
  HAL_SD_IRQHandler(&hsd);
  /* USER CODE BEGIN SDIO_IRQn 1 */

  /* USER CODE END SDIO_IRQn 1 */
}

/**
  * @brief This function handles DMA2 channel4 and channel5 global interrupts.
  */
void DMA2_Channel4_5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Channel4_5_IRQn 0 */

  /* USER CODE END DMA2_Channel4_5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_sdio);
  /* USER CODE BEGIN DMA2_Channel4_5_IRQn 1 */

  /* USER CODE END DMA2_Channel4_5_IRQn 1 */
}

/* USER CODE BEGIN 1 */
int calc_ghost_state(int prev_state, int speed, int number) {
	if(prev_state == 0) {
		if((cnt - level_start_cnt) == ready_time[number]*speed) {
			switch(number) {
			case 1:
				g1_prev_i=11, g1_prev_j=14;
				g1_curr_i=11, g1_curr_j=14; break;
			case 2:
				g2_prev_i=11, g2_prev_j=14;
				g2_curr_i=11, g2_curr_j=14; break;
			case 3:
				g3_prev_i=11, g3_prev_j=16;
				g3_curr_i=11, g3_curr_j=16; break;
			case 4:
				g4_prev_i=11, g4_prev_j=12;
				g4_curr_i=11, g4_curr_j=12; break;
			}
		}
		if((cnt - level_start_cnt) >= ready_time[number]*speed) {
			return 1;
		}
	} else if(prev_state == 1 || prev_state == 2) {
		if(cnt%(100*speed) <= 75*speed) {
			return 1;
	 	} else {
	 		return 2;
	 	}
	}
	return 0;
}

int valid_direction(int di, int curr_i, int curr_j) {
	if(di == 1) {
		if((curr_i-1 >= 0) && (map[curr_i-1][curr_j] != 1)) {
			return 1;
		} else {
			return 0;
		}
	} else if(di==2) {
		if((curr_j-1 >= 0) && (map[curr_i][curr_j-1] != 1)) {
			return 1;
		} else if(curr_i == 14 && curr_j == 0) {
			return 1;
		} else {
			return 0;
		}
	} else if(di==3) {
		if((curr_i+1 <= 30) && (map[curr_i+1][curr_j] != 1)) {
			return 1;
		} else {
			return 0;
		}
	} else if(di==4) {
		if((curr_j+1 <= 27) && (map[curr_i][curr_j+1] != 1)) {
			return 1;
		} else if(curr_i == 14 && curr_j == 27) {
			return 1;
		} else {
			return 0;
		}
	}
	return 0;
}

void move_pacman() {
	p_x= 12 + (p_prev_j * 8) + ((p_curr_j-p_prev_j)*(cnt%p_speed)*8/p_speed);
    p_y = 40 + (p_prev_i * 8) + ((p_curr_i-p_prev_i)*(cnt%p_speed)*8/p_speed);

    if((cnt%p_speed) == p_speed-1) {
	    if((joypad & 0x01) == 0x01) { // move right
		    if(valid_direction(2, p_curr_i, p_curr_j)) {
			    p_d = 2;
		    }
	    } else if((joypad & 0x02) == 0x02) { // move left
		    if(valid_direction(4, p_curr_i, p_curr_j)) {
			    p_d = 4;
		    }
	    } else if((joypad & 0x04) == 0x04) { // move down
		    if(valid_direction(3, p_curr_i, p_curr_j)) {
			    p_d = 3;
		    }
	    } else if((joypad & 0x08) == 0x08) { // move up
		    if(valid_direction(1, p_curr_i, p_curr_j)) {
			    p_d = 1;
		    }
	    }

	    p_prev_i = p_curr_i;
	    p_prev_j = p_curr_j;
	    if(valid_direction(p_d, p_curr_i, p_curr_j)) {
	    	p_curr_i += d[p_d][0];
	    	p_curr_j += d[p_d][1];
	    	if(p_curr_j > 27) {
	    		p_curr_j = 0;
	    		p_prev_j = 0;
	    	} else if(p_curr_j < 0) {
	    		p_curr_j = 27;
				p_prev_j = 27;
	    	}
	    } else {
	    	p_d = 0;
	    }
  }
  check_eat(p_curr_i, p_curr_j);
}

// state 0:in-box 1:chase 2:scatter 3:flee 4:go-back
void move_ghost1(uint8_t state) {
	g1_x = 12 + (g1_prev_j * 8) + ((g1_curr_j-g1_prev_j)*(cnt%g1_speed)*8/g1_speed);
	g1_y = 40 + (g1_prev_i * 8) + ((g1_curr_i-g1_prev_i)*(cnt%g1_speed)*8/g1_speed);

	if(cnt%g1_speed == g1_speed-1) {
		if(state == 0) {
			if(!valid_direction(g1_d, g1_curr_i, g1_curr_j)) {
				g1_d = ((g1_d+1) % 4) + 1;
			}
		} else if(state == 1) {
			g1_d = move_to_goal(p_curr_i, p_curr_j, g1_prev_i, g1_prev_j, g1_curr_i, g1_curr_j, g1_d, 1);
		} else if(state == 2) {
			g1_d = move_to_goal(0, 0, g1_prev_i, g1_prev_j, g1_curr_i, g1_curr_j, g1_d, 1);
		}


		g1_prev_i = g1_curr_i;
		g1_prev_j = g1_curr_j;
		g1_curr_i += d[g1_d][0];
		g1_curr_j += d[g1_d][1];
		if(g1_curr_j > 27) {
			g1_curr_j = 0;
			g1_prev_j = 0;
		} else if(g1_curr_j < 0) {
			g1_curr_j = 27;
			g1_prev_j = 27;
		}
	}
}

void move_ghost2(uint8_t state) {
	g2_x = 12 + (g2_prev_j * 8) + ((g2_curr_j-g2_prev_j)*(cnt%g2_speed)*8/g2_speed);
	g2_y = 40 + (g2_prev_i * 8) + ((g2_curr_i-g2_prev_i)*(cnt%g2_speed)*8/g2_speed);

	if(cnt%g2_speed == g2_speed-1) {
		if(state == 0) {
			if(!valid_direction(g2_d, g2_curr_i, g2_curr_j)) {
				g2_d = ((g2_d+1) % 4) + 1;
			}
		} else if(state == 1) {
			g2_d = move_to_goal(p_curr_i+(d[p_d][0]*4), p_curr_j+(d[p_d][1]*4), g2_prev_i, g2_prev_j, g2_curr_i, g2_curr_j, g2_d, 1);
		} else if(state == 2) {
			g2_d = move_to_goal(0, 27, g2_prev_i, g2_prev_j, g2_curr_i, g2_curr_j, g2_d, 1);
		}


		g2_prev_i = g2_curr_i;
		g2_prev_j = g2_curr_j;
		g2_curr_i += d[g2_d][0];
		g2_curr_j += d[g2_d][1];
		if(g2_curr_j > 27) {
			g2_curr_j = 0;
			g2_prev_j = 0;
		} else if(g2_curr_j < 0) {
			g2_curr_j = 27;
			g2_prev_j = 27;
		}
	}
}

void move_ghost3(uint8_t state) {
	int goal_i, goal_j;
	g3_x = 12 + (g3_prev_j * 8) + ((g3_curr_j-g3_prev_j)*(cnt%g3_speed)*8/g3_speed);
	g3_y = 40 + (g3_prev_i * 8) + ((g3_curr_i-g3_prev_i)*(cnt%g3_speed)*8/g3_speed);

	if(cnt%g3_speed == g3_speed-1) {
		if(state == 0) {
			if(!valid_direction(g3_d, g3_curr_i, g3_curr_j)) {
				g3_d = ((g3_d+1) % 4) + 1;
			}
		} else if(state == 1) {
			goal_i = p_curr_i - (g1_curr_i - p_curr_i);
			goal_j = p_curr_j - (g1_curr_j - p_curr_j);
			g3_d = move_to_goal(goal_i, goal_j, g3_prev_i, g3_prev_j, g3_curr_i, g3_curr_j, g3_d, 1);
		} else if(state == 2) {
			g3_d = move_to_goal(30, 27, g3_prev_i, g3_prev_j, g3_curr_i, g3_curr_j, g3_d, 1);
		}

		g3_prev_i = g3_curr_i;
		g3_prev_j = g3_curr_j;
		g3_curr_i += d[g3_d][0];
		g3_curr_j += d[g3_d][1];
		if(g3_curr_j > 27) {
			g3_curr_j = 0;
			g3_prev_j = 0;
		} else if(g3_curr_j < 0) {
			g3_curr_j = 27;
			g3_prev_j = 27;
		}
	}
}

void move_ghost4(uint8_t state) {
	int curr_dist;
	g4_x = 12 + (g4_prev_j * 8) + ((g4_curr_j-g4_prev_j)*(cnt%g4_speed)*8/g4_speed);
	g4_y = 40 + (g4_prev_i * 8) + ((g4_curr_i-g4_prev_i)*(cnt%g4_speed)*8/g4_speed);

	if(cnt%g4_speed == g4_speed-1) {
		if(state == 0) {
			if(!valid_direction(g4_d, g4_curr_i, g4_curr_j)) {
				g4_d = ((g4_d+1) % 4) + 1;
			}
		} else if(state == 1) {
			curr_dist = (g4_curr_i-p_curr_i)*(g4_curr_i-p_curr_i) + (g4_curr_j-p_curr_j)*(g4_curr_j-p_curr_j);
			if(curr_dist <= 64) {
				g4_d = move_to_goal(p_curr_i, p_curr_j, g4_prev_i, g4_prev_j, g4_curr_i, g4_curr_j, g4_d, 0);
			} else {
				g4_d = move_to_goal(p_curr_i, p_curr_j, g4_prev_i, g4_prev_j, g4_curr_i, g4_curr_j, g4_d, 1);
			}
		} else if(state == 2) {
			g4_d = move_to_goal(30, 0, g4_prev_i, g4_prev_j, g4_curr_i, g4_curr_j, g4_d, 1);
		}

		g4_prev_i = g4_curr_i;
		g4_prev_j = g4_curr_j;
		g4_curr_i += d[g4_d][0];
		g4_curr_j += d[g4_d][1];
		if(g4_curr_j > 27) {
			g4_curr_j = 0;
			g4_prev_j = 0;
		} else if(g4_curr_j < 0) {
			g4_curr_j = 27;
			g4_prev_j = 27;
		}
	}
}



// flag 0:backward 1:toward
int move_to_goal(int goal_i, int goal_j, int prev_i, int prev_j, int curr_i, int curr_j, int prev_d, uint8_t flag) {
	int k;
	int min_dist = 2000;
	int max_dist = 0;
	int curr_d = 0;
	int tmp_dist;
	for(k=1; k<=4; k++) {
		if(((k+1) % 4) + 1 == prev_d) { // 1-3, 2-4, prevent 180 rotation
			continue;
		}
		if(!valid_direction(k, curr_i, curr_j)) {
			continue;
		}
		if((curr_i+d[k][0] == prev_i) && (curr_j+d[k][1] == prev_j)) { // previous position
			continue;
		}
		tmp_dist = (curr_i+d[k][0]-goal_i)*(curr_i+d[k][0]-goal_i) + (curr_j+d[k][1]-goal_j)*(curr_j+d[k][1]-goal_j);
		if(flag == 1) {
			if(min_dist > tmp_dist) {
				min_dist = tmp_dist;
				curr_d = k;
			}
		} else if(flag == 0) {
			if(max_dist < tmp_dist) {
				max_dist = tmp_dist;
				curr_d = k;
			}
		}
	}
	return curr_d;
}

void check_eat(int curr_i, int curr_j) {
	if(map[curr_i][curr_j] == 10) {
		food_cnt++;
		score += map[curr_i][curr_j] * level;
		map[curr_i][curr_j] = 0;
	} else if(map[curr_i][curr_j] == 50) {
		food_cnt++;
		score += map[curr_i][curr_j];
		map[curr_i][curr_j] = 0;
	}
}
/* USER CODE END 1 */
