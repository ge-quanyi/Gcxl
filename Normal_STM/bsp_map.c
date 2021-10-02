#include "bsp_map.h"
#include "Ano_FlyCtrl.h"
#include "bsp_usart_dma.h"
#include "Drv_pwm_out.h"
#include "Ano_FlightCtrl.h"
#include "ANO_IMU.h"
char flag_a;
char high_flag;//控制高度的标志位
char yaw_l_flag;//控制自旋方向
char yaw_r_flag;//控制自旋方向
char flag_crt_go;
char flag_crt_go_1;
char flag_crt_T;

char flag_down;
#define  low_H 4
#define  duoji 5000
#define  jiangluo 20
#define  H_CRT 130
#define  H_CRT1 135
//相机控制逻辑
void Spd_set(void)
{
	switch (program_ctrl.cmd_state[0])
{
		case (0x01)://起飞
		{
			camera_crt.val=0;
			camera_crt.spd=0;
		}
		break;
		case (0x02):	//降落
		{
		  camera_crt.val=0;
			camera_crt.spd=0;
		}
		break;
		case (0xA0):	//紧急停机
		{
			camera_crt.val=0;
			camera_crt.spd=0;		
			
		}
		break;
		case (0x03):	//上升
		{	
			camera_crt.val=90;
			camera_crt.spd=120;
			if(high_flag)
			{
			camera_crt.val=50;
			camera_crt.spd=50;	
			}
		}
		break;
		case (0x04):	//下降
		{
			camera_crt.val=60;
			camera_crt.spd=60;
//			if(flag_down)
//			{
//			camera_crt.val=30;
//			camera_crt.spd=30;	
//			}			
			if(high_flag)
			{
			camera_crt.val=50;
			camera_crt.spd=50;	
			}
		}
		break;
		case (0x05):	//前进
		{
			camera_crt.val=30;
			camera_crt.spd=30;
			if(camera_crt .camera [1]==1)	
			{
				camera_crt.val=3;//尺度赋值
				camera_crt.spd=3;//速度赋值
			}	
			if((camera_crt .camera [1]==1)&&(flag_a))	
			{
				camera_crt.val=3;//尺度赋值
				camera_crt.spd=3;//速度赋值
			}	
     if(flag_crt_go)
		 {
		 	camera_crt.val=240;//尺度赋值
		  camera_crt.spd=90;//速度赋值
		 }
     if(flag_crt_go_1)
		 {
		 	camera_crt.val=170;//尺度赋值
		  camera_crt.spd=80;//速度赋值
		 }
			if(flag_crt_T==1)
			{
				camera_crt.val=20;//尺度赋值
				camera_crt.spd=20;//速度赋值
			}			 
		}
		break;
		case (0x06):	//后退
		{
			camera_crt.val=3;
			camera_crt.spd=3;		
		}
		break;
		case (0x07):	//向左
		{
			camera_crt.val=3;
			camera_crt.spd=3;	
			if((camera_crt .camera [1]==1)&&(flag_a))
			{
				camera_crt.val=3;//尺度赋值
				camera_crt.spd=3;//速度赋值
			}
			if(flag_crt_T==1)
			{
				camera_crt.val=30;//尺度赋值
				camera_crt.spd=30;//速度赋值
			}	
		}
		break;
		case (0x08):	//向右
		{
			camera_crt.val=3;
			camera_crt.spd=3;	
			if((camera_crt .camera [1]==1)&&(flag_a))
			{
				camera_crt.val=3;//尺度赋值
				camera_crt.spd=3;//速度赋值
			}
			if(flag_crt_T==1)
			{
				camera_crt.val=30;//尺度赋值
				camera_crt.spd=30;//速度赋值
			}			
			
		}
		break;
		case (0x09):	//左转
		{
			camera_crt.val=50;//时间
			camera_crt.spd=50;	
		}
		break;
		case (0x0A):	//右转
		{
			camera_crt.val=50;
			camera_crt.spd=50;
//			if(yaw_r_flag)
//			{
//			camera_crt.val=10;
//			camera_crt.spd=10;	
//			}			
		}
		break;
		case (0x0B):	//左后
		{
			camera_crt.val=3;
			camera_crt.spd=3;
			if((camera_crt .camera [1]==1)&&(flag_a))	
			{
				camera_crt.val=3;//尺度赋值
				camera_crt.spd=3;//速度赋值
			}				
		}
				case (0x0C):	//左前
		{
			camera_crt.val=3;
			camera_crt.spd=3;	
			if((camera_crt .camera [1]==1)&&(flag_a))	
			{
				camera_crt.val=3;//尺度赋值
				camera_crt.spd=3;//速度赋值
			}			
		}
		break;
				case (0x0D):	//右右后
		{
			camera_crt.val=3;
			camera_crt.spd=3;	
			if((camera_crt .camera [1]==1)&&(flag_a))	
			{
				camera_crt.val=3;//尺度赋值
				camera_crt.spd=3;//速度赋值
			}			
		}
		break;
				case (0x0E):	//右前
		{
			camera_crt.val=3;
			camera_crt.spd=3;
			if((camera_crt .camera [1]==1)&&(flag_a))	
			{
				camera_crt.val=3;//尺度赋值
				camera_crt.spd=3;//速度赋值
			}			
		}
		break;

		default:
		{
		
		}
		break;
	}



}
//void High_crt_h1(void)
//{

// static char flagh1_crt_up;
// static char flagh1_up_ok;
// if((camera_crt.HIGH>100)&&(flag_crt_go_1==0))
// {
//	 program_ctrl.cmd_state[0]=4;//下降
//	 high_flag=1;
// }
// else
// {
// 	high_flag=0;
// }
//   if((flag_crt_go_1==0)&&(flagh1_crt_up==0)&&(camera_crt.crt==5))
// {
//   flagh1_crt_up=1;
// }
//// if((((camera_crt.distance_2<70)&&(camera_crt.distance_2!=0))||((camera_crt.distance_l<70)&&(camera_crt.distance_l!=0))||((camera_crt.distance_3<70)&&(camera_crt.distance_3!=0)))&&(flag_crt_go==0)&&(flagh_crt_up==0)&&(camera_crt.crt==5))
//// {
////   flagh_crt_up=1;
//// }
// if((camera_crt.HIGH<100)&&(flagh1_crt_up==1)&&(flagh1_up_ok==0))
// {
//	 program_ctrl.cmd_state[0]=3;//上升
//	 high_flag=1;	 
// }
// if((camera_crt.HIGH>H_CRT)&&(flagh1_up_ok==0))
// {
// flagh1_up_ok=1;
// flag_crt_go=1;
// program_ctrl.cmd_state[0]=0;
// high_flag=0;
// } 
// if(flag_crt_go)
// {
//  program_ctrl.cmd_state[0]=5;

// }

//}
void High_crt_h(void)
{
 static char flagh_crt_down;
 static char flagh_crt_up;
 static char flagh_up_ok;
 if((camera_crt.HIGH>100)&&(flag_crt_go_1==0))
 {
	 program_ctrl.cmd_state[0]=4;//下降
	 high_flag=1;
 }
 else
 {
 	high_flag=0;
 }
   if((flag_crt_go==0)&&(flagh_crt_up==0))
 {
   flagh_crt_up=1;
 }
// if((((camera_crt.distance_2<70)&&(camera_crt.distance_2!=0))||((camera_crt.distance_l<70)&&(camera_crt.distance_l!=0))||((camera_crt.distance_3<70)&&(camera_crt.distance_3!=0)))&&(flag_crt_go==0)&&(flagh_crt_up==0)&&(camera_crt.crt==5))
// {
//   flagh_crt_up=1;
// }
 if((camera_crt.HIGH<H_CRT1)&&(flagh_crt_up==1)&&(flagh_up_ok==0))
 {
	 program_ctrl.cmd_state[0]=3;//上升
	 high_flag=1;	 
 }
 if((camera_crt.HIGH>H_CRT)&&(flagh_up_ok==0))
 {
 flagh_up_ok=1;
 flag_crt_go_1=1;
 program_ctrl.cmd_state[0]=0;
 high_flag=0;
 } 
 if(flag_crt_go_1)
 {
  program_ctrl.cmd_state[0]=5;
	 flagh_crt_down=1;
 }

}
void High_crt_c(void)
{
 static char flagc_crt_down;
static char flagc_crt_up;
static char flagc_up_ok;
 if((camera_crt.HIGH>120)&&(flag_crt_go_1==0))
 {
	 program_ctrl.cmd_state[0]=4;//下降
	 high_flag=1;
 }
 else
 {
 	high_flag=0;
 }
 if((flag_crt_go_1==0)&&(flagc_crt_up==0))
 {
   flagc_crt_up=1;
 }
 if((camera_crt.HIGH<H_CRT1)&&(flagc_crt_up==1)&&(flagc_up_ok==0))
 {
	 program_ctrl.cmd_state[0]=3;//上升
	 high_flag=1;	 
 }
 if((camera_crt.HIGH>H_CRT)&&(flagc_up_ok==0))
 {
 flagc_up_ok=1;
 flag_crt_go_1=1;
 program_ctrl.cmd_state[0]=0;
 high_flag=0;
 } 
 if(flag_crt_go_1)
 {
  program_ctrl.cmd_state[0]=5;
	 flagc_crt_down=1;
 }
  if((flagc_crt_down==1)&&(flag_crt_go_1==0))
 {
	 if(camera_crt.HIGH>low_H)
	 {
		 program_ctrl.cmd_state[0]=4;//下降
		 high_flag=1;
	 }
 }
}
//void High_crt_b1(void)
//{
// static char flagb1_crt_down;
// static char flagb1_crt_up;
// static char flagb1_up_ok;
// if((camera_crt.HIGH>100)&&(flag_crt_go_1==0))
// {
//	 program_ctrl.cmd_state[0]=4;//下降
//	 high_flag=1;
// }
// else
// {
// 	high_flag=0;
// }
//  if((flag_crt_go==0)&&(flagb1_crt_up==0)&&(camera_crt.crt==5))
// {
//   flagb1_crt_up=1;
// }
//// if((((camera_crt.distance_2<70)&&(camera_crt.distance_2!=0))||((camera_crt.distance_l<70)&&(camera_crt.distance_l!=0))||((camera_crt.distance_3<80)&&(camera_crt.distance_3!=0)))&&(flag_crt_go==0)&&(flagb_crt_up==0)&&(camera_crt.crt==5))
//// {
////   flagb_crt_up=1;
//// }
// if((camera_crt.HIGH<H_CRT1)&&(flagb1_crt_up==1)&&(flagb1_up_ok==0))
// {
//	 program_ctrl.cmd_state[0]=3;//上升
//	 high_flag=1;	 
// }
// if((camera_crt.HIGH>H_CRT)&&(flagb1_up_ok==0))
// {
// flagb1_up_ok=1;
// flag_crt_go_1=1;
// program_ctrl.cmd_state[0]=0;
// high_flag=0;
// } 
// if(flag_crt_go)
// {
//  program_ctrl.cmd_state[0]=5;
//	flagb1_crt_down=1;
// }
// if((flagb1_crt_down==1)&&(flag_crt_go_1==0))
// {
//	 if((camera_crt.HIGH>low_H)&&(flag_crt_go_1==0))
//	 {
//		 program_ctrl.cmd_state[0]=4;//下降
//		 high_flag=1;
//	 }
// }
//}
void High_crt_b(void)
{
 static char flagb_crt_down;
 static char flagb_crt_up;
 static char flagb_up_ok;
 if((camera_crt.HIGH>100)&&(flag_crt_go==0))
 {
	 program_ctrl.cmd_state[0]=4;//下降
	 high_flag=1;
 }
 else
 {
 	high_flag=0;
 }
  if((flag_crt_go_1==0)&&(flagb_crt_up==0))
 {
   flagb_crt_up=1;
 }
// if((((camera_crt.distance_2<70)&&(camera_crt.distance_2!=0))||((camera_crt.distance_l<70)&&(camera_crt.distance_l!=0))||((camera_crt.distance_3<80)&&(camera_crt.distance_3!=0)))&&(flag_crt_go==0)&&(flagb_crt_up==0)&&(camera_crt.crt==5))
// {
//   flagb_crt_up=1;
// }
 if((camera_crt.HIGH<H_CRT1)&&(flagb_crt_up==1)&&(flagb_up_ok==0))
 {
	 program_ctrl.cmd_state[0]=3;//上升
	 high_flag=1;	 
 }
 if((camera_crt.HIGH>H_CRT)&&(flagb_up_ok==0))
 {
 flagb_up_ok=1;
 flag_crt_go=1;
 program_ctrl.cmd_state[0]=0;
 high_flag=0;
 } 
 if(flag_crt_go)
 {
  program_ctrl.cmd_state[0]=5;
	flagb_crt_down=1;
 }
 if((flagb_crt_down==1)&&(flag_crt_go==0))
 {
	 if((camera_crt.HIGH>low_H)&&(flag_crt_go==0))
	 {
		 program_ctrl.cmd_state[0]=4;//下降
		 high_flag=1;
	 }
 }
}
void High_crt_a(void)
{
static char flag_crt_up_a;
 if((camera_crt.HIGH>100)&&(flag_crt_go==0)&&(flag_crt_up_a==0))
 {
	 program_ctrl.cmd_state[0]=4;//下降
	 high_flag=1;
 }
 else
 {
 	high_flag=0;
 } 
}

#define H   70
#define DOWN 4

////////////第一次起飞的所有标志位
char Fly_flag;//起飞
char Go_flag;//树莓派控制
char down_flag;//第一次下降
////////////第二次起飞的所有标志位
char turn_L_flag1;//左转弯90度
int turn_R_flag1;//右转弯90度
char down_flag1;//第一次下降
u16 Fly_flag1;//第二次起飞
char Go_flag1;//树莓派控制

////////////第三次起飞的所有标志位
char turn_L_fla2;//左转弯90度
char turn_R_flag2;//右转弯90度
char down_flag2;//下降
char Fly_flag2;//起飞
char Go_flag2;//树莓派控制
////////////第四次起飞的所有标志位
u16 turn_L_flag3;//左转弯90度
u16 turn_R_flag3;//右转弯90度
char down_flag3;//下降
u16 Fly_flag3;//起飞
char Go_flag3;//树莓派控制
////////////第五次起飞的所有标志位
char turn_L_fla4;//左转弯90度
u16 turn_R_flag4;//右转弯90度
char down_flag4;//下降
u16 Fly_flag4;//起飞
char Go_flag4;//树莓派控制
void camera_crt_A_45BC(void)
{

//计划ACB//
//第二点C起飞+右转45+前进＋识别H点+识别C下降	
if((down_flag3==2)&&(down_flag4<2))
{
		if(turn_R_flag4==131)
	{
    turn_R_flag4++;
		
		USART_SendData(USART3,'h');//开启树莓派控制
		USART_SendData(USART3,'h');//开启树莓派控制
	}
	if(turn_R_flag4==132)
	{
			program_ctrl.cmd_state[0]=camera_crt.crt;//指令赋值
			High_crt_h();
			if(camera_crt.crt=='h')
			{
				down_flag4=1;//终点
			}
			if((down_flag4)&&(camera_crt.HIGH>8))
			{
			 program_ctrl.cmd_state[0]=DOWN;
			}
			if((down_flag4==1)&&(camera_crt.HIGH<jiangluo))
			{
			 program_ctrl.cmd_state[0]=DOWN;//下降
			 flag_down=1;	
			}
			if((down_flag4)&&(camera_crt.HIGH<low_H))
			{
			 program_ctrl.cmd_state[0]=2;
			 down_flag4=2;//结束降落
			}
	}
	if((turn_R_flag4<131)&&(Go_flag4==1))//右转270
	{
		program_ctrl.cmd_state[0]=0x09;//
		turn_R_flag4++;
	}
			//上升
	if((Fly_flag4 ==250)&&(Go_flag4==0))
	{
		program_ctrl.cmd_state[0]=0x03;//上升
		if((camera_crt.HIGH>H)&&(camera_crt.HIGH<3000))
		{
		Go_flag4=1;
		program_ctrl.cmd_state[0]=0;
		}
	}		
		//投放时间
	if(Fly_flag4<250)//遥控最左边的拨杆
	{
		if(Fly_flag4>150)
		{
		SetPwm_Crt_C(duoji);	//下降稳定后投放				
		}
		program_ctrl.cmd_state[0]=0;
		Fly_flag4++;
	}

}
////计划ACB//
////第二点C起飞+右转45+前进＋识别H点+识别C下降	
//if((down_flag3==2)&&(down_flag4<2))
//{
//		if(turn_R_flag4==131)
//	{
//    turn_R_flag4++;
//		USART_SendData(USART3,'h');//开启树莓派控制
//		USART_SendData(USART3,'h');//开启树莓派控制
//		USART_SendData(USART3,'h');//开启树莓派控制
//	}
//	if(turn_R_flag4==132)
//	{
//			program_ctrl.cmd_state[0]=camera_crt.crt;//指令赋值
//			High_crt_h();
//			if(camera_crt.crt=='h')
//			{
//				down_flag4=1;//终点
//			}
//			if((down_flag4)&&(camera_crt.HIGH>8))
//			{
//			 program_ctrl.cmd_state[0]=DOWN;
//			}
//			if((down_flag4==1)&&(camera_crt.HIGH<jiangluo))
//			{
//			 program_ctrl.cmd_state[0]=DOWN;//下降
//			 flag_down=1;	
//			}
//			if((down_flag4)&&(camera_crt.HIGH<low_H))
//			{
//			 program_ctrl.cmd_state[0]=2;
//			 down_flag4=2;//结束降落
//			}
//	}
//	if((turn_R_flag4<131)&&(Go_flag4==1))//右转270
//	{
//		program_ctrl.cmd_state[0]=0x09;//
//		turn_R_flag4++;
//	}
//			//上升
//	if((Fly_flag4 ==250)&&(Go_flag4==0))
//	{
//		program_ctrl.cmd_state[0]=0x03;//上升
//		if(camera_crt.HIGH>H)
//		{
//		Go_flag4=1;
//		program_ctrl.cmd_state[0]=0;
//		}
//	}		
//		//投放时间
//	if((Fly_flag4<250)&&(camera_crt.HIGH<low_H))//遥控最左边的拨杆
//	{
//		if(Fly_flag4>150)
//		{
//		SetPwm_Crt_C(duoji);	//下降稳定后投放				
//		}
//		program_ctrl.cmd_state[0]=0;
//		Fly_flag4++;
//	}

//}	
//计划ACB//
//第三点B起飞+右转45+前进＋识别第二点+识别C下降	
if((down_flag1==2)&&(down_flag3<2))
{
		if(turn_L_flag3==132)
	{
    turn_L_flag3++;
		USART_SendData(USART3,'y');//开启树莓派控制
	}
	if(turn_L_flag3==133)
	{
			program_ctrl.cmd_state[0]=camera_crt.crt;//指令赋值
			High_crt_c();//控制高度
//			if(camera_crt.crt=='c')
//			{
//				down_flag3=1;//第三次降落
//			}
//			if((down_flag3)&&(camera_crt.HIGH>4))
//			{
//			 program_ctrl.cmd_state[0]=DOWN;
//			}
//			if((down_flag3==1)&&(camera_crt.HIGH<jiangluo))
//			{
//				program_ctrl.cmd_state[0]=DOWN;//下降
//				flag_down=1;	
//			}
			if(camera_crt.HIGH<low_H)
			{
				program_ctrl.cmd_state[0]=DOWN;//下降
			 down_flag3=2;//结束降落
				flag_down=0;
			}
	}

	if((turn_L_flag3<133)&&(flag_crt_T==0)&&(Go_flag3==1))//左转135
	{
		program_ctrl.cmd_state[0]=0x09;//左转
		turn_L_flag3++;
	}
	if(flag_crt_T==1)
	{
		program_ctrl.cmd_state[0]=0x08;//右移动20
	}
			//上升
	if((Fly_flag3 ==250)&&(Go_flag3==0))
	{
		program_ctrl.cmd_state[0]=0x03;//上升
		if((camera_crt.HIGH>H)&&(camera_crt.HIGH<3000))
		{
			SetPwm_Crt_B(100);
			Go_flag3=1;
			flag_crt_T=1;
			program_ctrl.cmd_state[0]=0;
		}
	}		
		//投放时间
	if(Fly_flag3<250)//遥控最左边的拨杆
	{
		if(Fly_flag3>150)
		{
		SetPwm_Crt_B(duoji);	//下降稳定后投放				
		}
		program_ctrl.cmd_state[0]=0;
		Fly_flag3++;
	}

}		
///////////////////////////////////////////////
/////////////第二点处理/
//A区起飞+A区右转90+飞到第二个区域
//down_flag1=3为C计划ACB//
//down_flag1=1\2为B计划ABC///////////////
if((down_flag==2)&&(down_flag1<2))
	{
	if(turn_R_flag1==134)//开启树莓派控制
		{
			USART_SendData(USART3,'y');//开启树莓派控制
//			USART_SendData(USART3,'y');//开启树莓派控制
			turn_R_flag1++;
		}
	if(turn_R_flag1==135)//开启树莓派控制
	{
		program_ctrl.cmd_state[0]=camera_crt.crt;//指令赋值
		High_crt_b();//控制高度

		if(camera_crt.HIGH<low_H)
		{
		program_ctrl.cmd_state[0]=DOWN;
		down_flag1=2;
		flag_down=0;
		}
	}	

	if((Go_flag1)&&(turn_R_flag1<134))//A区右转135
	{
		program_ctrl.cmd_state[0]=0x0A;//右转
		turn_R_flag1++;
	}
	if((Fly_flag1 ==251)&&(Go_flag1==0))//A区上升
	{
		program_ctrl.cmd_state[0]=0x03;//上升
		if((camera_crt.HIGH>H)&&(camera_crt.HIGH<3000))
		{
		SetPwm_Crt_A(100);	//下降稳定后投放		
		Go_flag1=1;
		program_ctrl.cmd_state[0]=0;
		}
	}	

	if(Fly_flag1<250)//A区投放时间
	{
		if(Fly_flag1>150)
		{
		SetPwm_Crt_A(duoji);	//下降稳定后投放				
		}
		program_ctrl.cmd_state[0]=0;
		Fly_flag1++;
	}

}

	//////////*A区*//H起飞+前进到A+A下降////////////////////
	if(down_flag<2)	
{
	if(Go_flag==1)//开启树莓派控制
	{
			if(down_flag==0)//
		{
			//USART_SendData(USART3,'y');//开启树莓派控制
			program_ctrl.cmd_state[0]=camera_crt.crt;//指令赋值
			High_crt_a();//控制高度
		}


		if(camera_crt.crt==97)////A区第一次降落
		{
			program_ctrl.cmd_state[0]=DOWN;//下降
			down_flag=1;
		}
		if((down_flag==1)&&(camera_crt.HIGH>5))
		{
			program_ctrl.cmd_state[0]=DOWN;//下降
		}
		if((down_flag==1)&&(camera_crt.HIGH<jiangluo))
		{
			program_ctrl.cmd_state[0]=DOWN;//下降
		  flag_down=1;//降低下降速度的标志位	
		}
		if((down_flag==1)&&(camera_crt.HIGH<low_H))
		{
			program_ctrl.cmd_state[0]=DOWN;
			flag_down=0;//清零标志位
			down_flag=2;//a点投放结束
			flag_a=1;
		}	
	}	

		//上升
	if((Fly_flag ==5)&&(Go_flag==0))
	{
		program_ctrl.cmd_state[0]=0x03;//上升
		
		if(camera_crt.HIGH>20)
		{

			Go_flag=1;
			program_ctrl.cmd_state[0]=0;
			USART_SendData(USART3,'y');//开启树莓派控制
		}
	}
	//遥控开启一键起飞
	if((flag.flight_mode == LOC_HOLD)&&(Fly_flag<5))//遥控最左边的拨杆
	{
		program_ctrl.cmd_state[0]=0x01;//起飞
		Fly_flag++;
	}
}
///////////////////////////////////////////////


///////////命令与速度处理////////////////////////
	Spd_set();

}


















//abc
//void camera_crt_ABC(void)
//{
//计划ACB//
//第二点C起飞+右转45+前进＋识别H点+识别C下降	
//if((down_flag3==2)&&(down_flag4<2))
//{
//		if(turn_R_flag4==90)
//	{
//    turn_R_flag4++;
//		USART_SendData(USART3,'h');//开启树莓派控制
//		USART_SendData(USART3,'h');//开启树莓派控制
//		USART_SendData(USART3,'h');//开启树莓派控制
//	}
//	if(turn_R_flag4==91)
//	{
//			program_ctrl.cmd_state[0]=camera_crt.crt;//指令赋值
//			High_crt_h1();
//			if(camera_crt.crt=='h')
//			{
//				down_flag4=1;//终点
//			}
//			if((down_flag4)&&(camera_crt.HIGH>8))
//			{
//			 program_ctrl.cmd_state[0]=DOWN;
//			}
//			if((down_flag4==1)&&(camera_crt.HIGH<jiangluo))
//			{
//			 program_ctrl.cmd_state[0]=DOWN;//下降
//			 flag_down=1;	
//			}
//			if((down_flag4)&&(camera_crt.HIGH<5))
//			{
//			 program_ctrl.cmd_state[0]=2;
//			 down_flag4=2;//结束降落
//			}
//	}
//	if((turn_R_flag4<90)&&(Go_flag4==1))//右转270
//	{
//		program_ctrl.cmd_state[0]=0x0A;//
//		turn_R_flag4++;
//	}
//			//上升
//	if((Fly_flag4 ==250)&&(Go_flag4==0))
//	{
//		program_ctrl.cmd_state[0]=0x03;//上升
//		if(camera_crt.HIGH>H)
//		{
//		Go_flag4=1;
//			SetPwm_Crt_C(100);
//		program_ctrl.cmd_state[0]=0;
//		}
//	}		
//		//投放时间
//	if((Fly_flag4<250)&&(camera_crt.HIGH<8))//遥控最左边的拨杆
//	{
//		if(Fly_flag4>150)
//		{
//		SetPwm_Crt_C(duoji);	//下降稳定后投放				
//		}
//		program_ctrl.cmd_state[0]=0;
//		Fly_flag4++;
//	}

//}	
//计划ACB//
//第三点B起飞+右转45+前进＋识别第二点+识别C下降	
//if((down_flag1==2)&&(down_flag3<2))
//{
//		if(turn_L_flag3==91)
//	{
//    turn_L_flag3++;
//		USART_SendData(USART3,'y');//开启树莓派控制
//	}
//	if(turn_L_flag3==92)
//	{
//			program_ctrl.cmd_state[0]=camera_crt.crt;//指令赋值
//			High_crt_c();//控制高度
//			if(camera_crt.crt=='c')
//			{
//				down_flag3=1;//第三次降落
//			}
//			if((down_flag3)&&(camera_crt.HIGH>low_H))
//			{
//			 program_ctrl.cmd_state[0]=DOWN;
//			}
//			if((down_flag3==1)&&(camera_crt.HIGH<jiangluo))
//			{
//				program_ctrl.cmd_state[0]=DOWN;//下降
//				flag_down=1;	
//			}
//			if(camera_crt.HIGH<low_H)
//			{
//			program_ctrl.cmd_state[0]=DOWN;//下降
//			 down_flag3=2;//结束降落
//				flag_down=0;
//			}
//	}
//	if((turn_L_flag3<91)&&(flag_crt_T==0)&&(Go_flag3==1))//左转135
//	{
//		program_ctrl.cmd_state[0]=0x0A;//左转
//		turn_L_flag3++;
//	}
//	if(flag_crt_T==1)
//	{
//		program_ctrl.cmd_state[0]=0x05;//ZUO移动前
//	}
//			//上升
//	if((Fly_flag3 ==250)&&(Go_flag3==0))
//	{
//		program_ctrl.cmd_state[0]=0x03;//上升
//		if(camera_crt.HIGH>H)
//		{
//		Go_flag3=1;
//		flag_crt_T=1;
//				SetPwm_Crt_B(100);
//		program_ctrl.cmd_state[0]=0;
//		}
//	}		
//		//投放时间
//	if((Fly_flag3<250)&&(camera_crt.HIGH<low_H))//遥控最左边的拨杆
//	{
//		if(Fly_flag3>150)
//		{
//		SetPwm_Crt_B(duoji);	//下降稳定后投放				
//		}
//		program_ctrl.cmd_state[0]=0;
//		Fly_flag3++;
//	}

//}		
///////////////////////////////////////////////
/////////////第二点处理/
//A区起飞+A区右转90+飞到第二个区域
//down_flag1=3为C计划ACB//
//down_flag1=1\2为B计划ABC///////////////
//if((down_flag==2)&&(down_flag1<2))
//	{
//	if(turn_R_flag1==90)//开启树莓派控制
//		{
//			USART_SendData(USART3,'y');//开启树莓派控制
//			USART_SendData(USART3,'y');//开启树莓派控制
//			turn_R_flag1++;
//		}
//	if(turn_R_flag1==91)//开启树莓派控制
//	{
//		program_ctrl.cmd_state[0]=camera_crt.crt;//指令赋值
//		High_crt_b();//控制高度
//		if(camera_crt.crt==98)//假如是B就下降
//		{
//			program_ctrl.cmd_state[0]=DOWN;
//			down_flag1=1;//第二次在第二个区域为B降落
//			camera_crt.crt=0;
//		}
//		if((down_flag1==1)&&(camera_crt.HIGH>low_H))
//		{
//		program_ctrl.cmd_state[0]=DOWN;
//		}
//		if(((camera_crt.HIGH<jiangluo))
//		{
//			program_ctrl.cmd_state[0]=DOWN;//下降
//		  flag_down=1;//降低下降速度	
//		}
//		if(camera_crt.HIGH<low_H)
//		{
//		program_ctrl.cmd_state[0]=DOWN;
//		down_flag1=2;
//		flag_down=0;
//		}
//	}		
//	if((Go_flag1)&&(turn_R_flag1<90))//A区右转90
//	{
//		program_ctrl.cmd_state[0]=0x0A;//右转
//		turn_R_flag1++;
//	}
//	if((Fly_flag1 ==200)&&(Go_flag1==0))//A区上升
//	{
//		program_ctrl.cmd_state[0]=0x03;//上升
//		if(camera_crt.HIGH>H)
//		{
//		Go_flag1=1;
//		program_ctrl.cmd_state[0]=0;
//					SetPwm_Crt_A(100);
//		}
//	}	

//	if((Fly_flag1<200)&&(camera_crt.HIGH<6))//A区投放时间
//	{
//		if(Fly_flag1>100)
//		{
//		SetPwm_Crt_A(duoji);	//下降稳定后投放				
//		}
//		program_ctrl.cmd_state[0]=0;
//		Fly_flag1++;
//	}

//}

//	//////////*A区*//H起飞+前进到A+A下降////////////////////
//	if(down_flag<2)	
//{
//	if(Go_flag==1)//开启树莓派控制
//	{
//			if(down_flag==0)//
//		{
//			//USART_SendData(USART3,'y');//开启树莓派控制
//			program_ctrl.cmd_state[0]=camera_crt.crt;//指令赋值
//			High_crt_a();//控制高度
//		}


//		if(camera_crt.crt==97)////A区第一次降落
//		{
//			program_ctrl.cmd_state[0]=DOWN;//下降
//			down_flag=1;
//		}
//		if((down_flag==1)&&(camera_crt.HIGH>5))
//		{
//			program_ctrl.cmd_state[0]=DOWN;//下降
//		}
//		if((down_flag==1)&&(camera_crt.HIGH<jiangluo))
//		{
//			program_ctrl.cmd_state[0]=DOWN;//下降
//		  flag_down=1;//降低下降速度的标志位	
//		}
//		if((down_flag==1)&&(camera_crt.HIGH<low_H))
//		{
//			program_ctrl.cmd_state[0]=DOWN;
//			flag_down=0;//清零标志位
//			down_flag=2;//a点投放结束
//			flag_a=1;
//		}	
//	}		
//		//上升
//	if((Fly_flag ==2)&&(Go_flag==0))
//	{
//		program_ctrl.cmd_state[0]=0x03;//上升
//		
//		if(camera_crt.HIGH>20)
//		{
//			Go_flag=1;
//			program_ctrl.cmd_state[0]=0;
//			USART_SendData(USART3,'y');//开启树莓派控制
//		}
//	}

//	//遥控开启一键起飞
//	if((flag.flight_mode == LOC_HOLD)&&(Fly_flag<2))//遥控最左边的拨杆
//	{
//		
//		program_ctrl.cmd_state[0]=0x01;//起飞
//		Fly_flag++;
//	}
//}
///////////////////////////////////////////////


///////////命令与速度处理////////////////////////
//	Spd_set();

//}
