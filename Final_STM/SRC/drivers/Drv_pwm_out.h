#ifndef _PWM_OUT_H_
#define _PWM_OUT_H_

#include "stm32f4xx.h"

u8 PWM_Out_Init(void);
void SetPwm(int16_t pwm[]);
void SetPwm_Crt_A(int16_t pwm);
void SetPwm_Crt_B(int16_t pwm);
void SetPwm_Crt_C(int16_t pwm);


#endif

