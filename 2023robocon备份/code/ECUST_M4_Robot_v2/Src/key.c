#include "key.h"
 
//////////////////////////////////////////////////////////////////////////////////	 
// 
//按键输入驱动代码	   
//key
//
////////////////////////////////////////////////////////////////////////////////// 	 
void delay_ms(uint16_t nms)//about 1ms!
{	 	 
	uint32_t temp; 
	while(nms)
	{
		nms--;
		temp=10000;
		while(temp)
		{
			temp--;
		}
	} 	
} 
//按键初始化函数
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  __HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();//使能GPIOA,GPIOE时钟
 
  GPIO_InitStructure.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure.Mode = GPIO_MODE_INPUT;//普通输入模式
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;//100M
  GPIO_InitStructure.Pull = GPIO_PULLUP;//上拉
  HAL_GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE2,3,4
	
	 
  GPIO_InitStructure.Pin = GPIO_PIN_0;//WK_UP对应引脚PA0
  GPIO_InitStructure.Pull = GPIO_PULLDOWN ;//下拉
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA0
 
} 
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，WKUP按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>WK_UP!!
uint8_t KEY_Scan(uint8_t mode)
{	 
	static uint8_t key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||WK_UP==1))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)return 1;
		else if(KEY1==0)return 2;//down
		else if(KEY2==0)return 3;//left
		else if(WK_UP==1)return 4;//right
	/*;  //left translation
		//right translation   */
	}else if(KEY0==1&&KEY1==1&&KEY2==1&&WK_UP==0)key_up=1;
 	
 	return 0;// 无按键按下
}




















