#include "bsp_map.h"
#include "Ano_FlyCtrl.h"
#include "bsp_usart_dma.h"
#include "Drv_pwm_out.h"
#include "Ano_FlightCtrl.h"
#include "ANO_IMU.h"
char flag_a;
char high_flag;//���Ƹ߶ȵı�־λ
char yaw_l_flag;//������������
char yaw_r_flag;//������������
char flag_crt_go;
char flag_crt_go_1;
char flag_crt_T;

char flag_down;
#define  low_H 4
#define  duoji 5000
#define  jiangluo 20
#define  H_CRT 130
#define  H_CRT1 135
//��������߼�
void Spd_set(void)
{
	switch (program_ctrl.cmd_state[0])
{
		case (0x01)://���
		{
			camera_crt.val=0;
			camera_crt.spd=0;
		}
		break;
		case (0x02):	//����
		{
		  camera_crt.val=0;
			camera_crt.spd=0;
		}
		break;
		case (0xA0):	//����ͣ��
		{
			camera_crt.val=0;
			camera_crt.spd=0;		
			
		}
		break;
		case (0x03):	//����
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
		case (0x04):	//�½�
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
		case (0x05):	//ǰ��
		{
			camera_crt.val=30;
			camera_crt.spd=30;
			if(camera_crt .camera [1]==1)	
			{
				camera_crt.val=3;//�߶ȸ�ֵ
				camera_crt.spd=3;//�ٶȸ�ֵ
			}	
			if((camera_crt .camera [1]==1)&&(flag_a))	
			{
				camera_crt.val=3;//�߶ȸ�ֵ
				camera_crt.spd=3;//�ٶȸ�ֵ
			}	
     if(flag_crt_go)
		 {
		 	camera_crt.val=240;//�߶ȸ�ֵ
		  camera_crt.spd=90;//�ٶȸ�ֵ
		 }
     if(flag_crt_go_1)
		 {
		 	camera_crt.val=170;//�߶ȸ�ֵ
		  camera_crt.spd=80;//�ٶȸ�ֵ
		 }
			if(flag_crt_T==1)
			{
				camera_crt.val=20;//�߶ȸ�ֵ
				camera_crt.spd=20;//�ٶȸ�ֵ
			}			 
		}
		break;
		case (0x06):	//����
		{
			camera_crt.val=3;
			camera_crt.spd=3;		
		}
		break;
		case (0x07):	//����
		{
			camera_crt.val=3;
			camera_crt.spd=3;	
			if((camera_crt .camera [1]==1)&&(flag_a))
			{
				camera_crt.val=3;//�߶ȸ�ֵ
				camera_crt.spd=3;//�ٶȸ�ֵ
			}
			if(flag_crt_T==1)
			{
				camera_crt.val=30;//�߶ȸ�ֵ
				camera_crt.spd=30;//�ٶȸ�ֵ
			}	
		}
		break;
		case (0x08):	//����
		{
			camera_crt.val=3;
			camera_crt.spd=3;	
			if((camera_crt .camera [1]==1)&&(flag_a))
			{
				camera_crt.val=3;//�߶ȸ�ֵ
				camera_crt.spd=3;//�ٶȸ�ֵ
			}
			if(flag_crt_T==1)
			{
				camera_crt.val=30;//�߶ȸ�ֵ
				camera_crt.spd=30;//�ٶȸ�ֵ
			}			
			
		}
		break;
		case (0x09):	//��ת
		{
			camera_crt.val=50;//ʱ��
			camera_crt.spd=50;	
		}
		break;
		case (0x0A):	//��ת
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
		case (0x0B):	//���
		{
			camera_crt.val=3;
			camera_crt.spd=3;
			if((camera_crt .camera [1]==1)&&(flag_a))	
			{
				camera_crt.val=3;//�߶ȸ�ֵ
				camera_crt.spd=3;//�ٶȸ�ֵ
			}				
		}
				case (0x0C):	//��ǰ
		{
			camera_crt.val=3;
			camera_crt.spd=3;	
			if((camera_crt .camera [1]==1)&&(flag_a))	
			{
				camera_crt.val=3;//�߶ȸ�ֵ
				camera_crt.spd=3;//�ٶȸ�ֵ
			}			
		}
		break;
				case (0x0D):	//���Һ�
		{
			camera_crt.val=3;
			camera_crt.spd=3;	
			if((camera_crt .camera [1]==1)&&(flag_a))	
			{
				camera_crt.val=3;//�߶ȸ�ֵ
				camera_crt.spd=3;//�ٶȸ�ֵ
			}			
		}
		break;
				case (0x0E):	//��ǰ
		{
			camera_crt.val=3;
			camera_crt.spd=3;
			if((camera_crt .camera [1]==1)&&(flag_a))	
			{
				camera_crt.val=3;//�߶ȸ�ֵ
				camera_crt.spd=3;//�ٶȸ�ֵ
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
//	 program_ctrl.cmd_state[0]=4;//�½�
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
//	 program_ctrl.cmd_state[0]=3;//����
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
	 program_ctrl.cmd_state[0]=4;//�½�
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
	 program_ctrl.cmd_state[0]=3;//����
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
	 program_ctrl.cmd_state[0]=4;//�½�
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
	 program_ctrl.cmd_state[0]=3;//����
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
		 program_ctrl.cmd_state[0]=4;//�½�
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
//	 program_ctrl.cmd_state[0]=4;//�½�
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
//	 program_ctrl.cmd_state[0]=3;//����
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
//		 program_ctrl.cmd_state[0]=4;//�½�
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
	 program_ctrl.cmd_state[0]=4;//�½�
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
	 program_ctrl.cmd_state[0]=3;//����
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
		 program_ctrl.cmd_state[0]=4;//�½�
		 high_flag=1;
	 }
 }
}
void High_crt_a(void)
{
static char flag_crt_up_a;
 if((camera_crt.HIGH>100)&&(flag_crt_go==0)&&(flag_crt_up_a==0))
 {
	 program_ctrl.cmd_state[0]=4;//�½�
	 high_flag=1;
 }
 else
 {
 	high_flag=0;
 } 
}

#define H   70
#define DOWN 4

////////////��һ����ɵ����б�־λ
char Fly_flag;//���
char Go_flag;//��ݮ�ɿ���
char down_flag;//��һ���½�
////////////�ڶ�����ɵ����б�־λ
char turn_L_flag1;//��ת��90��
int turn_R_flag1;//��ת��90��
char down_flag1;//��һ���½�
u16 Fly_flag1;//�ڶ������
char Go_flag1;//��ݮ�ɿ���

////////////��������ɵ����б�־λ
char turn_L_fla2;//��ת��90��
char turn_R_flag2;//��ת��90��
char down_flag2;//�½�
char Fly_flag2;//���
char Go_flag2;//��ݮ�ɿ���
////////////���Ĵ���ɵ����б�־λ
u16 turn_L_flag3;//��ת��90��
u16 turn_R_flag3;//��ת��90��
char down_flag3;//�½�
u16 Fly_flag3;//���
char Go_flag3;//��ݮ�ɿ���
////////////�������ɵ����б�־λ
char turn_L_fla4;//��ת��90��
u16 turn_R_flag4;//��ת��90��
char down_flag4;//�½�
u16 Fly_flag4;//���
char Go_flag4;//��ݮ�ɿ���
void camera_crt_A_45BC(void)
{

//�ƻ�ACB//
//�ڶ���C���+��ת45+ǰ����ʶ��H��+ʶ��C�½�	
if((down_flag3==2)&&(down_flag4<2))
{
		if(turn_R_flag4==131)
	{
    turn_R_flag4++;
		
		USART_SendData(USART3,'h');//������ݮ�ɿ���
		USART_SendData(USART3,'h');//������ݮ�ɿ���
	}
	if(turn_R_flag4==132)
	{
			program_ctrl.cmd_state[0]=camera_crt.crt;//ָ�ֵ
			High_crt_h();
			if(camera_crt.crt=='h')
			{
				down_flag4=1;//�յ�
			}
			if((down_flag4)&&(camera_crt.HIGH>8))
			{
			 program_ctrl.cmd_state[0]=DOWN;
			}
			if((down_flag4==1)&&(camera_crt.HIGH<jiangluo))
			{
			 program_ctrl.cmd_state[0]=DOWN;//�½�
			 flag_down=1;	
			}
			if((down_flag4)&&(camera_crt.HIGH<low_H))
			{
			 program_ctrl.cmd_state[0]=2;
			 down_flag4=2;//��������
			}
	}
	if((turn_R_flag4<131)&&(Go_flag4==1))//��ת270
	{
		program_ctrl.cmd_state[0]=0x09;//
		turn_R_flag4++;
	}
			//����
	if((Fly_flag4 ==250)&&(Go_flag4==0))
	{
		program_ctrl.cmd_state[0]=0x03;//����
		if((camera_crt.HIGH>H)&&(camera_crt.HIGH<3000))
		{
		Go_flag4=1;
		program_ctrl.cmd_state[0]=0;
		}
	}		
		//Ͷ��ʱ��
	if(Fly_flag4<250)//ң������ߵĲ���
	{
		if(Fly_flag4>150)
		{
		SetPwm_Crt_C(duoji);	//�½��ȶ���Ͷ��				
		}
		program_ctrl.cmd_state[0]=0;
		Fly_flag4++;
	}

}
////�ƻ�ACB//
////�ڶ���C���+��ת45+ǰ����ʶ��H��+ʶ��C�½�	
//if((down_flag3==2)&&(down_flag4<2))
//{
//		if(turn_R_flag4==131)
//	{
//    turn_R_flag4++;
//		USART_SendData(USART3,'h');//������ݮ�ɿ���
//		USART_SendData(USART3,'h');//������ݮ�ɿ���
//		USART_SendData(USART3,'h');//������ݮ�ɿ���
//	}
//	if(turn_R_flag4==132)
//	{
//			program_ctrl.cmd_state[0]=camera_crt.crt;//ָ�ֵ
//			High_crt_h();
//			if(camera_crt.crt=='h')
//			{
//				down_flag4=1;//�յ�
//			}
//			if((down_flag4)&&(camera_crt.HIGH>8))
//			{
//			 program_ctrl.cmd_state[0]=DOWN;
//			}
//			if((down_flag4==1)&&(camera_crt.HIGH<jiangluo))
//			{
//			 program_ctrl.cmd_state[0]=DOWN;//�½�
//			 flag_down=1;	
//			}
//			if((down_flag4)&&(camera_crt.HIGH<low_H))
//			{
//			 program_ctrl.cmd_state[0]=2;
//			 down_flag4=2;//��������
//			}
//	}
//	if((turn_R_flag4<131)&&(Go_flag4==1))//��ת270
//	{
//		program_ctrl.cmd_state[0]=0x09;//
//		turn_R_flag4++;
//	}
//			//����
//	if((Fly_flag4 ==250)&&(Go_flag4==0))
//	{
//		program_ctrl.cmd_state[0]=0x03;//����
//		if(camera_crt.HIGH>H)
//		{
//		Go_flag4=1;
//		program_ctrl.cmd_state[0]=0;
//		}
//	}		
//		//Ͷ��ʱ��
//	if((Fly_flag4<250)&&(camera_crt.HIGH<low_H))//ң������ߵĲ���
//	{
//		if(Fly_flag4>150)
//		{
//		SetPwm_Crt_C(duoji);	//�½��ȶ���Ͷ��				
//		}
//		program_ctrl.cmd_state[0]=0;
//		Fly_flag4++;
//	}

//}	
//�ƻ�ACB//
//������B���+��ת45+ǰ����ʶ��ڶ���+ʶ��C�½�	
if((down_flag1==2)&&(down_flag3<2))
{
		if(turn_L_flag3==132)
	{
    turn_L_flag3++;
		USART_SendData(USART3,'y');//������ݮ�ɿ���
	}
	if(turn_L_flag3==133)
	{
			program_ctrl.cmd_state[0]=camera_crt.crt;//ָ�ֵ
			High_crt_c();//���Ƹ߶�
//			if(camera_crt.crt=='c')
//			{
//				down_flag3=1;//�����ν���
//			}
//			if((down_flag3)&&(camera_crt.HIGH>4))
//			{
//			 program_ctrl.cmd_state[0]=DOWN;
//			}
//			if((down_flag3==1)&&(camera_crt.HIGH<jiangluo))
//			{
//				program_ctrl.cmd_state[0]=DOWN;//�½�
//				flag_down=1;	
//			}
			if(camera_crt.HIGH<low_H)
			{
				program_ctrl.cmd_state[0]=DOWN;//�½�
			 down_flag3=2;//��������
				flag_down=0;
			}
	}

	if((turn_L_flag3<133)&&(flag_crt_T==0)&&(Go_flag3==1))//��ת135
	{
		program_ctrl.cmd_state[0]=0x09;//��ת
		turn_L_flag3++;
	}
	if(flag_crt_T==1)
	{
		program_ctrl.cmd_state[0]=0x08;//���ƶ�20
	}
			//����
	if((Fly_flag3 ==250)&&(Go_flag3==0))
	{
		program_ctrl.cmd_state[0]=0x03;//����
		if((camera_crt.HIGH>H)&&(camera_crt.HIGH<3000))
		{
			SetPwm_Crt_B(100);
			Go_flag3=1;
			flag_crt_T=1;
			program_ctrl.cmd_state[0]=0;
		}
	}		
		//Ͷ��ʱ��
	if(Fly_flag3<250)//ң������ߵĲ���
	{
		if(Fly_flag3>150)
		{
		SetPwm_Crt_B(duoji);	//�½��ȶ���Ͷ��				
		}
		program_ctrl.cmd_state[0]=0;
		Fly_flag3++;
	}

}		
///////////////////////////////////////////////
/////////////�ڶ��㴦��/
//A�����+A����ת90+�ɵ��ڶ�������
//down_flag1=3ΪC�ƻ�ACB//
//down_flag1=1\2ΪB�ƻ�ABC///////////////
if((down_flag==2)&&(down_flag1<2))
	{
	if(turn_R_flag1==134)//������ݮ�ɿ���
		{
			USART_SendData(USART3,'y');//������ݮ�ɿ���
//			USART_SendData(USART3,'y');//������ݮ�ɿ���
			turn_R_flag1++;
		}
	if(turn_R_flag1==135)//������ݮ�ɿ���
	{
		program_ctrl.cmd_state[0]=camera_crt.crt;//ָ�ֵ
		High_crt_b();//���Ƹ߶�

		if(camera_crt.HIGH<low_H)
		{
		program_ctrl.cmd_state[0]=DOWN;
		down_flag1=2;
		flag_down=0;
		}
	}	

	if((Go_flag1)&&(turn_R_flag1<134))//A����ת135
	{
		program_ctrl.cmd_state[0]=0x0A;//��ת
		turn_R_flag1++;
	}
	if((Fly_flag1 ==251)&&(Go_flag1==0))//A������
	{
		program_ctrl.cmd_state[0]=0x03;//����
		if((camera_crt.HIGH>H)&&(camera_crt.HIGH<3000))
		{
		SetPwm_Crt_A(100);	//�½��ȶ���Ͷ��		
		Go_flag1=1;
		program_ctrl.cmd_state[0]=0;
		}
	}	

	if(Fly_flag1<250)//A��Ͷ��ʱ��
	{
		if(Fly_flag1>150)
		{
		SetPwm_Crt_A(duoji);	//�½��ȶ���Ͷ��				
		}
		program_ctrl.cmd_state[0]=0;
		Fly_flag1++;
	}

}

	//////////*A��*//H���+ǰ����A+A�½�////////////////////
	if(down_flag<2)	
{
	if(Go_flag==1)//������ݮ�ɿ���
	{
			if(down_flag==0)//
		{
			//USART_SendData(USART3,'y');//������ݮ�ɿ���
			program_ctrl.cmd_state[0]=camera_crt.crt;//ָ�ֵ
			High_crt_a();//���Ƹ߶�
		}


		if(camera_crt.crt==97)////A����һ�ν���
		{
			program_ctrl.cmd_state[0]=DOWN;//�½�
			down_flag=1;
		}
		if((down_flag==1)&&(camera_crt.HIGH>5))
		{
			program_ctrl.cmd_state[0]=DOWN;//�½�
		}
		if((down_flag==1)&&(camera_crt.HIGH<jiangluo))
		{
			program_ctrl.cmd_state[0]=DOWN;//�½�
		  flag_down=1;//�����½��ٶȵı�־λ	
		}
		if((down_flag==1)&&(camera_crt.HIGH<low_H))
		{
			program_ctrl.cmd_state[0]=DOWN;
			flag_down=0;//�����־λ
			down_flag=2;//a��Ͷ�Ž���
			flag_a=1;
		}	
	}	

		//����
	if((Fly_flag ==5)&&(Go_flag==0))
	{
		program_ctrl.cmd_state[0]=0x03;//����
		
		if(camera_crt.HIGH>20)
		{

			Go_flag=1;
			program_ctrl.cmd_state[0]=0;
			USART_SendData(USART3,'y');//������ݮ�ɿ���
		}
	}
	//ң�ؿ���һ�����
	if((flag.flight_mode == LOC_HOLD)&&(Fly_flag<5))//ң������ߵĲ���
	{
		program_ctrl.cmd_state[0]=0x01;//���
		Fly_flag++;
	}
}
///////////////////////////////////////////////


///////////�������ٶȴ���////////////////////////
	Spd_set();

}


















//abc
//void camera_crt_ABC(void)
//{
//�ƻ�ACB//
//�ڶ���C���+��ת45+ǰ����ʶ��H��+ʶ��C�½�	
//if((down_flag3==2)&&(down_flag4<2))
//{
//		if(turn_R_flag4==90)
//	{
//    turn_R_flag4++;
//		USART_SendData(USART3,'h');//������ݮ�ɿ���
//		USART_SendData(USART3,'h');//������ݮ�ɿ���
//		USART_SendData(USART3,'h');//������ݮ�ɿ���
//	}
//	if(turn_R_flag4==91)
//	{
//			program_ctrl.cmd_state[0]=camera_crt.crt;//ָ�ֵ
//			High_crt_h1();
//			if(camera_crt.crt=='h')
//			{
//				down_flag4=1;//�յ�
//			}
//			if((down_flag4)&&(camera_crt.HIGH>8))
//			{
//			 program_ctrl.cmd_state[0]=DOWN;
//			}
//			if((down_flag4==1)&&(camera_crt.HIGH<jiangluo))
//			{
//			 program_ctrl.cmd_state[0]=DOWN;//�½�
//			 flag_down=1;	
//			}
//			if((down_flag4)&&(camera_crt.HIGH<5))
//			{
//			 program_ctrl.cmd_state[0]=2;
//			 down_flag4=2;//��������
//			}
//	}
//	if((turn_R_flag4<90)&&(Go_flag4==1))//��ת270
//	{
//		program_ctrl.cmd_state[0]=0x0A;//
//		turn_R_flag4++;
//	}
//			//����
//	if((Fly_flag4 ==250)&&(Go_flag4==0))
//	{
//		program_ctrl.cmd_state[0]=0x03;//����
//		if(camera_crt.HIGH>H)
//		{
//		Go_flag4=1;
//			SetPwm_Crt_C(100);
//		program_ctrl.cmd_state[0]=0;
//		}
//	}		
//		//Ͷ��ʱ��
//	if((Fly_flag4<250)&&(camera_crt.HIGH<8))//ң������ߵĲ���
//	{
//		if(Fly_flag4>150)
//		{
//		SetPwm_Crt_C(duoji);	//�½��ȶ���Ͷ��				
//		}
//		program_ctrl.cmd_state[0]=0;
//		Fly_flag4++;
//	}

//}	
//�ƻ�ACB//
//������B���+��ת45+ǰ����ʶ��ڶ���+ʶ��C�½�	
//if((down_flag1==2)&&(down_flag3<2))
//{
//		if(turn_L_flag3==91)
//	{
//    turn_L_flag3++;
//		USART_SendData(USART3,'y');//������ݮ�ɿ���
//	}
//	if(turn_L_flag3==92)
//	{
//			program_ctrl.cmd_state[0]=camera_crt.crt;//ָ�ֵ
//			High_crt_c();//���Ƹ߶�
//			if(camera_crt.crt=='c')
//			{
//				down_flag3=1;//�����ν���
//			}
//			if((down_flag3)&&(camera_crt.HIGH>low_H))
//			{
//			 program_ctrl.cmd_state[0]=DOWN;
//			}
//			if((down_flag3==1)&&(camera_crt.HIGH<jiangluo))
//			{
//				program_ctrl.cmd_state[0]=DOWN;//�½�
//				flag_down=1;	
//			}
//			if(camera_crt.HIGH<low_H)
//			{
//			program_ctrl.cmd_state[0]=DOWN;//�½�
//			 down_flag3=2;//��������
//				flag_down=0;
//			}
//	}
//	if((turn_L_flag3<91)&&(flag_crt_T==0)&&(Go_flag3==1))//��ת135
//	{
//		program_ctrl.cmd_state[0]=0x0A;//��ת
//		turn_L_flag3++;
//	}
//	if(flag_crt_T==1)
//	{
//		program_ctrl.cmd_state[0]=0x05;//ZUO�ƶ�ǰ
//	}
//			//����
//	if((Fly_flag3 ==250)&&(Go_flag3==0))
//	{
//		program_ctrl.cmd_state[0]=0x03;//����
//		if(camera_crt.HIGH>H)
//		{
//		Go_flag3=1;
//		flag_crt_T=1;
//				SetPwm_Crt_B(100);
//		program_ctrl.cmd_state[0]=0;
//		}
//	}		
//		//Ͷ��ʱ��
//	if((Fly_flag3<250)&&(camera_crt.HIGH<low_H))//ң������ߵĲ���
//	{
//		if(Fly_flag3>150)
//		{
//		SetPwm_Crt_B(duoji);	//�½��ȶ���Ͷ��				
//		}
//		program_ctrl.cmd_state[0]=0;
//		Fly_flag3++;
//	}

//}		
///////////////////////////////////////////////
/////////////�ڶ��㴦��/
//A�����+A����ת90+�ɵ��ڶ�������
//down_flag1=3ΪC�ƻ�ACB//
//down_flag1=1\2ΪB�ƻ�ABC///////////////
//if((down_flag==2)&&(down_flag1<2))
//	{
//	if(turn_R_flag1==90)//������ݮ�ɿ���
//		{
//			USART_SendData(USART3,'y');//������ݮ�ɿ���
//			USART_SendData(USART3,'y');//������ݮ�ɿ���
//			turn_R_flag1++;
//		}
//	if(turn_R_flag1==91)//������ݮ�ɿ���
//	{
//		program_ctrl.cmd_state[0]=camera_crt.crt;//ָ�ֵ
//		High_crt_b();//���Ƹ߶�
//		if(camera_crt.crt==98)//������B���½�
//		{
//			program_ctrl.cmd_state[0]=DOWN;
//			down_flag1=1;//�ڶ����ڵڶ�������ΪB����
//			camera_crt.crt=0;
//		}
//		if((down_flag1==1)&&(camera_crt.HIGH>low_H))
//		{
//		program_ctrl.cmd_state[0]=DOWN;
//		}
//		if(((camera_crt.HIGH<jiangluo))
//		{
//			program_ctrl.cmd_state[0]=DOWN;//�½�
//		  flag_down=1;//�����½��ٶ�	
//		}
//		if(camera_crt.HIGH<low_H)
//		{
//		program_ctrl.cmd_state[0]=DOWN;
//		down_flag1=2;
//		flag_down=0;
//		}
//	}		
//	if((Go_flag1)&&(turn_R_flag1<90))//A����ת90
//	{
//		program_ctrl.cmd_state[0]=0x0A;//��ת
//		turn_R_flag1++;
//	}
//	if((Fly_flag1 ==200)&&(Go_flag1==0))//A������
//	{
//		program_ctrl.cmd_state[0]=0x03;//����
//		if(camera_crt.HIGH>H)
//		{
//		Go_flag1=1;
//		program_ctrl.cmd_state[0]=0;
//					SetPwm_Crt_A(100);
//		}
//	}	

//	if((Fly_flag1<200)&&(camera_crt.HIGH<6))//A��Ͷ��ʱ��
//	{
//		if(Fly_flag1>100)
//		{
//		SetPwm_Crt_A(duoji);	//�½��ȶ���Ͷ��				
//		}
//		program_ctrl.cmd_state[0]=0;
//		Fly_flag1++;
//	}

//}

//	//////////*A��*//H���+ǰ����A+A�½�////////////////////
//	if(down_flag<2)	
//{
//	if(Go_flag==1)//������ݮ�ɿ���
//	{
//			if(down_flag==0)//
//		{
//			//USART_SendData(USART3,'y');//������ݮ�ɿ���
//			program_ctrl.cmd_state[0]=camera_crt.crt;//ָ�ֵ
//			High_crt_a();//���Ƹ߶�
//		}


//		if(camera_crt.crt==97)////A����һ�ν���
//		{
//			program_ctrl.cmd_state[0]=DOWN;//�½�
//			down_flag=1;
//		}
//		if((down_flag==1)&&(camera_crt.HIGH>5))
//		{
//			program_ctrl.cmd_state[0]=DOWN;//�½�
//		}
//		if((down_flag==1)&&(camera_crt.HIGH<jiangluo))
//		{
//			program_ctrl.cmd_state[0]=DOWN;//�½�
//		  flag_down=1;//�����½��ٶȵı�־λ	
//		}
//		if((down_flag==1)&&(camera_crt.HIGH<low_H))
//		{
//			program_ctrl.cmd_state[0]=DOWN;
//			flag_down=0;//�����־λ
//			down_flag=2;//a��Ͷ�Ž���
//			flag_a=1;
//		}	
//	}		
//		//����
//	if((Fly_flag ==2)&&(Go_flag==0))
//	{
//		program_ctrl.cmd_state[0]=0x03;//����
//		
//		if(camera_crt.HIGH>20)
//		{
//			Go_flag=1;
//			program_ctrl.cmd_state[0]=0;
//			USART_SendData(USART3,'y');//������ݮ�ɿ���
//		}
//	}

//	//ң�ؿ���һ�����
//	if((flag.flight_mode == LOC_HOLD)&&(Fly_flag<2))//ң������ߵĲ���
//	{
//		
//		program_ctrl.cmd_state[0]=0x01;//���
//		Fly_flag++;
//	}
//}
///////////////////////////////////////////////


///////////�������ٶȴ���////////////////////////
//	Spd_set();

//}
