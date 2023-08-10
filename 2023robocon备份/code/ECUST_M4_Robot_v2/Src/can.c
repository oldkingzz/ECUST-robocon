#include "can.h"
  
uint8_t can1_tx_data[8];
uint8_t can2_tx_data[8];
int16_t motor_i=1000;
int16_t motor_speed_current[8];
extern int16_t motor_out[8];
void  send_can_data()
{
    can1_tx_data[0]=motor_out[0]>>8;
		can1_tx_data[1]=(motor_out[0] & 0xff);
		can1_tx_data[2]=motor_out[1]>>8;//0;
		can1_tx_data[3]=(motor_out[1] & 0xff);//0;
		can1_tx_data[4]=motor_out[2]>>8;//0;
		can1_tx_data[5]=(motor_out[2] & 0xff);//0;
		can1_tx_data[6]=motor_out[3]>>8;//0;
		can1_tx_data[7]=(motor_out[3] & 0xff);//0;
		CAN_Send_Msg(&hcan1,can1_tx_data, 8);
	
//	  can1_tx_data[0]=motor_out[4]>>8;
//		can1_tx_data[1]=(motor_out[4] & 0xff);
//		can1_tx_data[2]=motor_out[5]>>8;//0;
//		can1_tx_data[3]=(motor_out[5] & 0xff);//0;
//		can1_tx_data[4]=motor_out[6]>>8;//0;
//		can1_tx_data[5]=(motor_out[6] & 0xff);//0;
//		can1_tx_data[6]=motor_out[7]>>8;//0;
//		can1_tx_data[7]=(motor_out[7] & 0xff);//0;
//		CAN_Send_Msg1(&hcan1,can1_tx_data, 8);
	
}
//can filter must be initialized before use
void CanFilter_Init(CAN_HandleTypeDef* hcan)
{
  
	
	CAN_FilterConfTypeDef canfilter;
  
  //create memory to save the message, if not will raise error
  static CanTxMsgTypeDef  Tx1Message;
  static CanRxMsgTypeDef  Rx1Message;
  static CanTxMsgTypeDef  Tx2Message;
  static CanRxMsgTypeDef  Rx2Message;
  
  canfilter.FilterMode = CAN_FILTERMODE_IDMASK;
  canfilter.FilterScale = CAN_FILTERSCALE_32BIT;
  
  //filtrate any ID you want here
  canfilter.FilterIdHigh = 0x0000;
  canfilter.FilterIdLow = 0x0000;
  canfilter.FilterMaskIdHigh = 0x0000;
  canfilter.FilterMaskIdLow = 0x0000;
  
  canfilter.FilterFIFOAssignment = CAN_FilterFIFO0;
  canfilter.FilterActivation = ENABLE;
  canfilter.BankNumber = 14;
  
  //use different filter for can1&can2
  if(hcan == &hcan1)
  {
    canfilter.FilterNumber = 0;
    hcan->pTxMsg = &Tx1Message;
    hcan->pRxMsg = &Rx1Message;
  }
  if(hcan == &hcan2)
  {
    canfilter.FilterNumber = 14;
    hcan->pTxMsg = &Tx2Message;
    hcan->pRxMsg = &Rx2Message;
  }
  
  HAL_CAN_ConfigFilter(hcan, &canfilter);
  
}
//CAN send message test
//HAL_StatusTypeDef HAL_CAN_AddTxMessage(CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *pHeader, uint8_t aData[], uint32_t *pTxMailbox)
void CAN_Send_Msg(CAN_HandleTypeDef* hcan, uint8_t aData[], uint8_t len)
{
	HAL_StatusTypeDef temp;
 
  hcan->pTxMsg->StdId = TX_CAN_ID;
	hcan->pTxMsg->ExtId= TX_CAN_ID;
  hcan->pTxMsg->IDE = CAN_ID_STD;
  hcan->pTxMsg->RTR = CAN_RTR_DATA;
  hcan->pTxMsg->DLC = len;
  for(uint8_t i = 0 ; i < 8 ; ++i)
        hcan->pTxMsg->Data[i] = aData[i];   //发送第1到4号电机控制电流值
	HAL_CAN_Transmit(&hcan1, 10) ; 
	
}
void CAN_Send_Msg1(CAN_HandleTypeDef* hcan, uint8_t aData[], uint8_t len)
{
   
	HAL_StatusTypeDef temp;
 
  hcan->pTxMsg->StdId = TX_CAN_ID1;
	hcan->pTxMsg->ExtId= TX_CAN_ID;
  hcan->pTxMsg->IDE = CAN_ID_STD;
  hcan->pTxMsg->RTR = CAN_RTR_DATA;
  hcan->pTxMsg->DLC = len;
  for(uint8_t i = 0 ; i < 8 ; ++i)
        hcan->pTxMsg->Data[i] = aData[i];   //发送第5到8号电机控制电流值
	HAL_CAN_Transmit(&hcan2, 10) ; 
	
}
/**
  * @brief  Transmission  complete callback in non blocking mode 
  * @param  hcan pointer to a CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @retval None
  */
void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan){
    
 
    motor_speed_current[hcan1.pRxMsg->StdId-0x201] = (hcan1.pRxMsg->Data[2]<<8)+hcan->pRxMsg->Data[3];//0,1 angle;2,3 speed rpm;4,5 current       //printf("ID= 0x%x\t Speed= %d\t Angle= %d\t Current= %d\t Temperature= %d\r\n",TempID,MotorAngle[TempID-0x201],MotorSpeed[TempID-0x201],MotorTrueCurrent[TempID-0x201],MotorTemperature[TempID-0x201]);
    
    HAL_CAN_Receive_IT(&hcan1,CAN_FIFO0);              //need here!
}



