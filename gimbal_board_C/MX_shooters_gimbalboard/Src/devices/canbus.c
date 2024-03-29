#include "main.h"

static CAN_TxHeaderTypeDef  CAN_tx;
static uint8_t              CAN_tx_message[8];

uint8_t CAN1_ready=0;
uint8_t CAN2_ready=0;

/*-------------------------------------
* 函数名：CAN初始化
* 描述  ：初始化CAN1/2
* 输入  ：无
* 输出  ：无
作者：LPGUAIA
日期：2021.9.20
-----------------------------------------*/ 
void can_filter_init(void)
{
    CAN_FilterTypeDef can_filter_st;
    can_filter_st.FilterActivation = ENABLE;
    can_filter_st.FilterMode = CAN_FILTERMODE_IDMASK;
    can_filter_st.FilterScale = CAN_FILTERSCALE_32BIT;
    can_filter_st.FilterIdHigh = 0x0000;
    can_filter_st.FilterIdLow = 0x0000;
    can_filter_st.FilterMaskIdHigh = 0x0000;
    can_filter_st.FilterMaskIdLow = 0x0000;
    can_filter_st.FilterBank = 0;
    can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO0;
    HAL_CAN_ConfigFilter(&hcan1, &can_filter_st);
    HAL_CAN_Start(&hcan1);
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);


    can_filter_st.SlaveStartFilterBank = 14;
    can_filter_st.FilterBank = 14;
    HAL_CAN_ConfigFilter(&hcan2, &can_filter_st);
    HAL_CAN_Start(&hcan2);
    HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
}

/*-------------------------------------
* 函数名：CAN发送
* 描述  ：发送协议信息
* 输入  ：地址，hcan1/2，传输内容的结构体
* 输出  ：无
作者：LPGUAIA
日期：2021.9.20
-----------------------------------------*/ 
void CAN_send(uint32_t address,\
							CAN_HandleTypeDef hcanx,\
							int16_t message[4]
							)
{
    uint32_t send_mail_box;
    CAN_tx.StdId = address;
    CAN_tx.IDE = CAN_ID_STD;
    CAN_tx.RTR = CAN_RTR_DATA;
    CAN_tx.DLC = 0x08;
    CAN_tx_message[0] = message[0] >> 8;
    CAN_tx_message[1] = message[0] ;
    CAN_tx_message[2] = message[1] >> 8;
    CAN_tx_message[3] = message[1];
    CAN_tx_message[4] = message[2] >> 8;
    CAN_tx_message[5] = message[2];
    CAN_tx_message[6] = message[3] >> 8;
    CAN_tx_message[7] = message[3];
		
		HAL_CAN_AddTxMessage(&hcanx, &CAN_tx, CAN_tx_message, &send_mail_box);
		//while(HAL_CAN_IsTxMessagePending(&hcanx,send_mail_box));
}


int16_t tm[4];
/*-------------------------------------
* 函数名：CAN接收
* 描述  ：接收中断，先判断是can1/2的数据，根据地址接收，然后解算成代码内使用的单位
* 输入  ：无
* 输出  ：无
作者：LPGUAIA
日期：2021.9.20
-----------------------------------------*/
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	CAN_RxHeaderTypeDef rx_header;
	uint8_t rx_data[8];

	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data);
	if(hcan->Instance==CAN1)
	{
		switch(rx_header.StdId)
		{
			
			
			#ifdef infa
			case 0x203:
			{
				canrxtomotinfo(&triginfo,rx_data);
			}break;
			
			#endif
			
			#ifdef hero
			case trigid:
			{
				canrxtomotinfo(&triginfo,rx_data);
			}break;
			
			case yawid:
			{
				canrxtomotinfo(&yawinfo,rx_data);
			}break;
			
			#endif
			
			case 0x234:
			{
				robocurinfo.zrelangle=((int16_t)(rx_data[0]<<8|rx_data[1]))/100.f;
			}break;
			
			case 0x200:
			{
				tm[0]=rx_data[0]<<8|rx_data[1];
				tm[1]=rx_data[2]<<8|rx_data[3];
				tm[2]=rx_data[4]<<8|rx_data[5];
			}break;
			
		}
		//HAL_IWDG_Refresh(&hiwdg);
		CAN1_ready=1;
	}
	else if (hcan->Instance==CAN2)
	{
		switch(rx_header.StdId)
		{
			
			case fric0id:
			{
					canrxtomotinfo(&fricinfo[0],rx_data);
			}break;
			
			case firc1id:
			{
					canrxtomotinfo(&fricinfo[1],rx_data);
			}break;
			
			#ifdef infa
			case 0x203:
			{
					canrxtomotinfo(&magainfo,rx_data);
			}break;
			
			case 0x206:
			{
				canrxtomotinfo(&pitinfo,rx_data);
			}break;
			
			#endif
			
			#ifdef hero
			case pitid:
			{
				canrxtomotinfo(&pitinfo,rx_data);
			}break;
			#endif
			
			case 0x188:
			{
				mpu_acc_reci(rx_data,&mpudata);
			}break;
			case 0x288:
			{
				mpu_spe_reci(rx_data,&mpudata);
			}break;
			case 0x388:
			{
				mpu_ang_reci(rx_data,&mpudata);
				//mpu_Quat_reci(rx_data,&mpudata);
				//mpu_angle_calc(&mpudata);
			}break;
			
			case 0x123:
			{
				//curmestochas_unpack(&chasinfo,rx_data);
			}break;
			case 0x321:
			{
				//ctrlmestochas_unpack(&chasinfo,rx_data);
			}break;

		}
	CAN2_ready=1;
	}
}
