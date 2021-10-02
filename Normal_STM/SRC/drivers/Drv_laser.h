#ifndef _LASER_H_
#define _LASER_H_
#include "stm32f4xx.h"

extern u8 LASER_LINKOK;
extern u16 Laser_height_cm;

u8 		Drv_Laser_Init(void);
void 	Drv_Laser_GetOneByte_1(u8 data);
void Drv_Laser_GetOneByte_5(u8 data);
void Drv_Laser_GetOneByte_2(u8 data);
#endif
