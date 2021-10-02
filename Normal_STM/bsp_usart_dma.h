#ifndef __USARTDMA_H

#define __USARTDMA_H



#include "stm32f4xx.h"


#include <stdio.h>

#define DMASIZE 4
typedef struct
{
	u16  val;//≥ﬂ∂»
	u16  spd;//æ‡¿Î
	int16_t camera[8];
	u16  HIGH;
	u16 crt;//øÿ÷∆√¸¡Ó
	float yaw;//yaw	
	u16   distance_l;
	u16    distance_2;
	u16    distance_3;	
	u16  duoji_A;
	u16  duoji_B;
	u16  duoji_C;
	char RC_B;
	char RC_C;	
	char RC_D;
}Camera_crt;
extern Camera_crt camera_crt;
void usart_dma_init(void);


#endif 
