/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.h
  * @brief   This file contains the headers of the interrupt handlers.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F1xx_IT_H
#define __STM32F1xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void TIM2_IRQHandler(void);
void USART1_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
void SDIO_IRQHandler(void);
void DMA2_Channel4_5_IRQHandler(void);
/* USER CODE BEGIN EFP */
int valid_direction(int d, int curr_i, int curr_j);
int calc_ghost_state(int prev_state, int speed, int number);
void move_pacman(void);
void move_ghost1(uint8_t state);
void move_ghost2(uint8_t state);
void move_ghost3(uint8_t state);
void move_ghost4(uint8_t state);
int move_to_goal(int goal_i, int goal_j, int prev_i, int prev_j, int curr_i, int curr_j, int prev_d, uint8_t flag);
void check_eat(int curr_i, int curr_j);
/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F1xx_IT_H */
