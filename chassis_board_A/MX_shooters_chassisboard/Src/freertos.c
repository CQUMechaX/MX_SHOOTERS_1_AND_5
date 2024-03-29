/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for infotask */
osThreadId_t infotaskHandle;
const osThreadAttr_t infotask_attributes = {
  .name = "infotask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for chassistask */
osThreadId_t chassistaskHandle;
const osThreadAttr_t chassistask_attributes = {
  .name = "chassistask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for UIdrawer */
osThreadId_t UIdrawerHandle;
const osThreadAttr_t UIdrawer_attributes = {
  .name = "UIdrawer",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for refereetask */
osThreadId_t refereetaskHandle;
const osThreadAttr_t refereetask_attributes = {
  .name = "refereetask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for capstask */
osThreadId_t capstaskHandle;
const osThreadAttr_t capstask_attributes = {
  .name = "capstask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void infoproc(void *argument);
void chasctrl(void *argument);
void UIdraw(void *argument);
void refread(void *argument);
void capsctrl(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of infotask */
  infotaskHandle = osThreadNew(infoproc, NULL, &infotask_attributes);

  /* creation of chassistask */
  chassistaskHandle = osThreadNew(chasctrl, NULL, &chassistask_attributes);

  /* creation of UIdrawer */
  UIdrawerHandle = osThreadNew(UIdraw, NULL, &UIdrawer_attributes);

  /* creation of refereetask */
  refereetaskHandle = osThreadNew(refread, NULL, &refereetask_attributes);

  /* creation of capstask */
  capstaskHandle = osThreadNew(capsctrl, NULL, &capstask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_infoproc */
/**
  * @brief  Function implementing the infotask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_infoproc */
__weak void infoproc(void *argument)
{
  /* USER CODE BEGIN infoproc */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END infoproc */
}

/* USER CODE BEGIN Header_chasctrl */
/**
* @brief Function implementing the chassistask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_chasctrl */
__weak void chasctrl(void *argument)
{
  /* USER CODE BEGIN chasctrl */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END chasctrl */
}

/* USER CODE BEGIN Header_UIdraw */
/**
* @brief Function implementing the UIdrawer thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_UIdraw */
__weak void UIdraw(void *argument)
{
  /* USER CODE BEGIN UIdraw */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END UIdraw */
}

/* USER CODE BEGIN Header_refread */
/**
* @brief Function implementing the refereetask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_refread */
__weak void refread(void *argument)
{
  /* USER CODE BEGIN refread */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END refread */
}

/* USER CODE BEGIN Header_capsctrl */
/**
* @brief Function implementing the capstask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_capsctrl */
__weak void capsctrl(void *argument)
{
  /* USER CODE BEGIN capsctrl */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END capsctrl */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
