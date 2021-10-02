#include "bsp_usart_dma.h"
#include "string.h"

u8 RxBuffer1[DMASIZE] = {0x00}; //串口1接收后存放到此数组

u8 TxBuffer1[DMASIZE] = {0x00}; //串口1发送此数组的数据

u16 RxBufferSize = 0;

void usart_dma_init(void)

{

   USART_InitTypeDef USART_InitStructure;
   DMA_InitTypeDef DMA_InitStructure; 
   GPIO_InitTypeDef GPIO_InitStructure;
	
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); 
    //TX
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//复用推挽输出
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
   //RX
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; 
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
   
   GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
   GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);
	 
	 
	 
	 USART_OverSampling8Cmd(USART3, ENABLE);  
   USART_InitStructure.USART_BaudRate = 115200;
   USART_InitStructure.USART_WordLength = USART_WordLength_8b;
   USART_InitStructure.USART_StopBits = USART_StopBits_1;
   USART_InitStructure.USART_Parity = USART_Parity_No;
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
   USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;   USART_Init(USART3, &USART_InitStructure);

	 USART_Init(USART3, &USART_InitStructure);
   USART_Cmd(USART3,ENABLE); 
	 USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); //开启空闲中断 
 	/*USART3中断 */

  NVIC_InitTypeDef  NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel 					 = USART3_IRQn;      //IRQ通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;          		 //主优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		 = 1;                //从优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd				 = ENABLE;           //使能通道
	NVIC_Init(&NVIC_InitStructure);
   USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE); //允许DMA接收

   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);
	 
   DMA_DeInit(DMA1_Stream1);
   while (DMA_GetCmdStatus(DMA1_Stream1) != DISABLE);//等待DMA可配置
   DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
   DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART3->DR;
   DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)RxBuffer1;
   DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
   DMA_InitStructure.DMA_BufferSize = DMASIZE;
   DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
   DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
   DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
   DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
   DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
   DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
   DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
   DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
   DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
   DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	 
   DMA_Init(DMA1_Stream1, &DMA_InitStructure);
   DMA_Cmd(DMA1_Stream1, ENABLE);


}



uint8_t buf[9];


void decode(void)
{ //解析接收到的数据，然后发送

		if(RxBuffer1[0]==0x63)
		{

		buf[0]=RxBuffer1[0];
		buf[1]=RxBuffer1[1];

		}



}

u16 RecvLen;


Camera_crt camera_crt;



void USART3_IRQHandler(void)
{

		RecvLen++;

if(RxBuffer1[0]==0x63)
{
	  camera_crt.crt=*(int8_t*)&RxBuffer1[1];//起飞
	  camera_crt .camera [1]=*(int8_t*)&RxBuffer1[2];//有目标

}
}
//char cnt_1;

//void USART1_IRQHandler(void)  
//{  
//	unsigned char RX_dat;  

//	if ( USART1->SR & USART_SR_ORE ) //ORE??
//    {
//        RX_dat = USART1->DR;
//    }
//	
//	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)//USART_IT_RXNE:????  
//	{   
//		USART_ClearITPendingBit(USART1,USART_IT_RXNE);  
//		RX_dat=USART_ReceiveData(USART1); 
//		if (cnt_1 == 0)
//		{
//			if (RX_dat == 0xB5)									//帧头1
//			{
//				GPS_data_buff[cnt_1] = RX_dat;
//				GPS_get_cnt = 1;
//			}
//		}
//		else if (GPS_get_cnt == 1)
//		{
//			if (RX_dat == 0x62)									//帧头2
//			{
//				GPS_data_buff[GPS_get_cnt] = RX_dat;
//				GPS_get_cnt = 2;
//			}
//			else
//			{
//				GPS_get_cnt = 0;
//			}
//		}
//		else
//		{
//			GPS_data_buff[GPS_get_cnt] = RX_dat;
//			GPS_get_cnt++;
//			if (GPS_get_cnt >= 100)
//			{
//				GPS_get_cnt = 0;
//				
//				if (GPS_ubx_check_sum(GPS_data_buff))			//GPS数据校验
//				{
//					GPS_data_analysis();						//GPS数据解析
//				}
//			}
//		}			
//	}	
//} 










