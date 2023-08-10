/* 
  pid
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __pid_H
#define __pid_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */
 

/* USER CODE BEGIN Private defines */
typedef struct PID_tag{
		double uk_1;//
		double SetValue; //   Desired Value
		double Kp ; //  Proportional Const
		double Ki; //   Integral Const
		double Kd; //  Derivative Const
		double ek_1; // Error[-1]
		double ek_2; // Error[-2]
		double max_limit; // value<=Max_limit
	  double min_limit; // value>=min_limit
} PID;
/* USER CODE END Private defines */

 

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ pid_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
