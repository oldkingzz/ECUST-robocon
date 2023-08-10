#include "stm32f4xx_hal.h"
#include "pid.h"
#define speed_const 2300
#define speed_const2 1000
//ด๓ฯ๓1200
//ะกอร1000

#define speed_man 200
extern uint8_t KEY_Scan(uint8_t mode);
extern	PID motor_speed_pid[8];

void key_process()
{
	uint8_t KEY_Value;
	KEY_Value= KEY_Scan(1);
	if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2) == SET){
	if(HAL_GPIO_ReadPin( GPIOG,  GPIO_PIN_7)==RESET|HAL_GPIO_ReadPin( GPIOG, GPIO_PIN_8)==RESET)
	{
		
		
		if(HAL_GPIO_ReadPin( GPIOG,  GPIO_PIN_7)==RESET)//left translation
	{
		motor_speed_pid[0].SetValue=speed_const2;
		motor_speed_pid[1].SetValue=speed_const2;
		motor_speed_pid[2].SetValue=-speed_const2;
		motor_speed_pid[3].SetValue=-speed_const2;
	}
	else if(HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_8)==RESET)//right translation
	{
		motor_speed_pid[0].SetValue=-speed_const2;
		motor_speed_pid[1].SetValue=-speed_const2;
		motor_speed_pid[2].SetValue=speed_const2;
		motor_speed_pid[3].SetValue=speed_const2;
	}
}
	
	else{	if(KEY_Value==1)//up
		{
			motor_speed_pid[0].SetValue=speed_const;
			motor_speed_pid[1].SetValue=speed_const;
			motor_speed_pid[2].SetValue=speed_const;
			motor_speed_pid[3].SetValue=speed_const;
		}
		else if(KEY_Value==2)//down
		{
			motor_speed_pid[0].SetValue=-speed_const;
			motor_speed_pid[1].SetValue=-speed_const;
			motor_speed_pid[2].SetValue=-speed_const;
			motor_speed_pid[3].SetValue=-speed_const;
		}
		else if(KEY_Value==3)//left
		{
			motor_speed_pid[0].SetValue=speed_const;
			motor_speed_pid[1].SetValue=-speed_const;
			motor_speed_pid[2].SetValue=speed_const;
			motor_speed_pid[3].SetValue=-speed_const;
		}
		else if(KEY_Value==4)//right
		{
			motor_speed_pid[0].SetValue=-speed_const;
			motor_speed_pid[1].SetValue=speed_const;
			motor_speed_pid[2].SetValue=-speed_const;
			motor_speed_pid[3].SetValue=speed_const;
		}
		else
		{
			motor_speed_pid[0].SetValue=0;
			motor_speed_pid[1].SetValue=0;
			motor_speed_pid[2].SetValue=0;
			motor_speed_pid[3].SetValue=0;
			for(uint8_t i=0;i<8;i++)
			{
				motor_speed_pid[i].uk_1=0.0;
			}
		}
	}
}
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2) == RESET){
if(HAL_GPIO_ReadPin( GPIOG,  GPIO_PIN_7)==RESET|HAL_GPIO_ReadPin( GPIOG, GPIO_PIN_8)==RESET)
	{
		
		
		if(HAL_GPIO_ReadPin( GPIOG,  GPIO_PIN_7)==RESET)//left translation
	{
		motor_speed_pid[0].SetValue=speed_man;
		motor_speed_pid[1].SetValue=speed_man;
		motor_speed_pid[2].SetValue=-speed_man;
		motor_speed_pid[3].SetValue=-speed_man;
	}
	else if(HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_8)==RESET)//right translation
	{
		motor_speed_pid[0].SetValue=-speed_man;
		motor_speed_pid[1].SetValue=-speed_man;
		motor_speed_pid[2].SetValue=speed_man;
		motor_speed_pid[3].SetValue=speed_man;
	}
}
	
	else{	if(KEY_Value==1)//up
		{
			motor_speed_pid[0].SetValue=speed_man;
			motor_speed_pid[1].SetValue=speed_man;
			motor_speed_pid[2].SetValue=speed_man;
			motor_speed_pid[3].SetValue=speed_man;
		}
		else if(KEY_Value==2)//down
		{
			motor_speed_pid[0].SetValue=-speed_man;
			motor_speed_pid[1].SetValue=-speed_man;
			motor_speed_pid[2].SetValue=-speed_man;
			motor_speed_pid[3].SetValue=-speed_man;
		}
		else if(KEY_Value==3)//left
		{
			motor_speed_pid[0].SetValue=speed_man;
			motor_speed_pid[1].SetValue=-speed_man;
			motor_speed_pid[2].SetValue=speed_man;
			motor_speed_pid[3].SetValue=-speed_man;
		}
		else if(KEY_Value==4)//right
		{
			motor_speed_pid[0].SetValue=-speed_man;
			motor_speed_pid[1].SetValue=speed_man;
			motor_speed_pid[2].SetValue=-speed_man;
			motor_speed_pid[3].SetValue=speed_man;
		}
		else
		{
			motor_speed_pid[0].SetValue=0;
			motor_speed_pid[1].SetValue=0;
			motor_speed_pid[2].SetValue=0;
			motor_speed_pid[3].SetValue=0;
			for(uint8_t i=0;i<8;i++)
			{
				motor_speed_pid[i].uk_1=0.0;
			}
		}
	}



}
}
