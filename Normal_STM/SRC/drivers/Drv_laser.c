/******************** (C) COPYRIGHT 2017 ANO Tech ********************************
 * 作者    ：匿名科创
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
 * 描述    ：激光模块读取
**********************************************************************************/
#include "Drv_laser.h"
#include "Ano_FcData.h"
#include "Drv_time.h"
#include "bsp_usart_dma.h"
u8 LASER_LINKOK = 0;	//0:无效，1：有效，2：测试中

u16 Laser_height_cm;
u8 Drv_Laser_Init(void)
{
	LASER_LINKOK = 2;
	for(u16 i=0; i<1000; i++)
	{
		if(LASER_LINKOK == 1)
			break;
		else
			Delay_ms(1);
	}
	if(LASER_LINKOK == 2)
		LASER_LINKOK = 0;
	sens_hd_check.tof_ok = LASER_LINKOK;
	return LASER_LINKOK;
}
 u8 tmp1[9];
void Drv_Laser_GetOneByte_1(u8 data)
{

	static u8 sta = 0;
	static u8 cnt = 0;
	
	if(sta == 0 && data == 0x59)
	{
		tmp1[0] = 0x59;
		sta = 1;
	}
	else if(sta == 1)
	{
		if(data == 0x59)
		{
			tmp1[1] = 0x59;
			sta = 2;
			cnt = 2;
		}
		else
			sta = 0;
	}
	else if(sta == 2)
	{
		tmp1[cnt++] = data;
		if(cnt >= 9)
		{
			u8 sum = 0;
			for(u8 i=0; i<8; i++)
				sum += tmp1[i];
			if(sum == tmp1[8])	//校验通过
			{
				if(LASER_LINKOK == 2)
					LASER_LINKOK = 1;
				camera_crt.distance_l = (tmp1[2] + ((u16)tmp1[3]<<8));
			}
			sta = 0;
			cnt = 0;
		}
	}
}
u8 tmp2[9];
void Drv_Laser_GetOneByte_2(u8 data)
{

//	static u8 sta = 0;
//	static u8 cnt = 0;
//	
//	if(sta == 0 && data == 0x59)
//	{
//		tmp2[0] = 0x59;
//		sta = 1;
//	}
//	else if(sta == 1)
//	{
//		if(data == 0x59)
//		{
//			tmp2[1] = 0x59;
//			sta = 2;
//			cnt = 2;
//		}
//		else
//			sta = 0;
//	}
//	else if(sta == 2)
//	{
//		tmp2[cnt++] = data;
//		if(cnt >= 9)
//		{
//			u8 sum = 0;
//			for(u8 i=0; i<8; i++)
//				sum += tmp2[i];
//			if(sum == tmp2[8])	//校验通过
//			{
//				if(LASER_LINKOK == 2)
//					LASER_LINKOK = 1;
//				camera_crt.distance_2 = (tmp2[2] + ((u16)tmp2[3]<<8));
//			}
//			sta = 0;
//			cnt = 0;
//		}
//	}

	static u8 sta = 0;
	static u8 cnt = 0;
	
	if(sta == 0 )
	{
		tmp2[0] = data;
		sta = 1;
	}
	else if(sta == 1)
	{

			tmp2[1] = data;
			sta = 2;
			cnt = 2;
		
	}
	else if(sta == 2)
	{
		tmp2[cnt++] = data;
		if(cnt >= 9)
		{
			u8 sum = 0;
			for(u8 i=0; i<8; i++)
				sum += tmp2[i];
			if(sum == tmp2[8])	//校验通过
			{
				if(LASER_LINKOK == 2)
					LASER_LINKOK = 1;
				camera_crt.distance_2 = (tmp2[2] + ((u16)tmp2[3]<<8));
			}
			sta = 0;
			cnt = 0;
		}
	}
}
 u8 tmp5[9];
void Drv_Laser_GetOneByte_5(u8 data)
{
{

	static u8 sta = 0;
	static u8 cnt = 0;
	
	if(sta == 0 && data == 0x59)
	{
		tmp5[0] = 0x59;
		sta = 1;
	}
	else if(sta == 1)
	{
		if(data == 0x59)
		{
			tmp5[1] = 0x59;
			sta = 2;
			cnt = 2;
		}
		else
			sta = 0;
	}
	else if(sta == 2)
	{
		tmp5[cnt++] = data;
		if(cnt >= 9)
		{
			u8 sum = 0;
			for(u8 i=0; i<8; i++)
				sum += tmp5[i];
			if(sum == tmp5[8])	//校验通过
			{
				if(LASER_LINKOK == 2)
					LASER_LINKOK = 1;
				camera_crt.distance_3 = (tmp5[2] + ((u16)tmp5[3]<<8));
			}
			sta = 0;
			cnt = 0;
		}
	}
}
}
