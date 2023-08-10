#ifndef __KEY_H
#define __KEY_H	 
#include "stm32f4xx_hal.h"
//////////////////////////////////////////////////////////////////////////////////	 
 
//按键输入驱动代码	   
//STM32F4工程-库函数版本
//淘宝店铺：http://mcudev.taobao.com								  
////////////////////////////////////////////////////////////////////////////////// 	 

/*下面的方式是通过直接操作库函数方式读取IO*/
#define KEY0 		HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4) //PE4
#define KEY1 		HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_3)	//PE3 
#define KEY2 		HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_2) //PE2
#define WK_UP 	HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)	//PA0


/*下面方式是通过位带操作方式读取IO*/
/*
#define KEY0 		PEin(4)   	//PE4
#define KEY1 		PEin(3)		//PE3 
#define KEY2 		PEin(2)		//P32
#define WK_UP 	PAin(0)		//PA0
*/


#define KEY0_PRES 	1
#define KEY1_PRES	2
#define KEY2_PRES	3
#define WKUP_PRES   4

void KEY_Init(void);	//IO初始化
uint8_t KEY_Scan(uint8_t);  		//按键扫描函数	

#endif
