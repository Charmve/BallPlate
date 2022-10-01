#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "usmart.h"  
#include "usart2.h"  
#include "timer.h" 
#include "ov2640.h" 
#include "dcmi.h" 
#include "string.h"
#include "pwm.h"


//ALIENTEK ̽����STM32F407������ ʵ��35
//����ͷ ʵ�� -�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK


//JPEG�ߴ�֧���б�
const u16 jpeg_img_size_tbl[][2]=
{
	176,144,	//QCIF
	160,120,	//QQVGA
	352,288,	//CIF
	320,240,	//QVGA
	640,480,	//VGA
	800,600,	//SVGA
	1024,768,	//XGA
	1280,1024,	//SXGA
	1600,1200,	//UXGA
}; 


void TIM3_Int_Init(u16 arr,u16 psc);
//RGB565����
//RGB����ֱ����ʾ��LCD����
void rgb565_test(void)
{ 
	u8 key;
	LCD_Clear(WHITE);
  POINT_COLOR=RED; 
	
  OV2640_ImageWin_Set((800-480)/2,(600-600)/2,480,600);
	OV2640_RGB565_Mode();	//RGB565ģʽ
	My_DCMI_Init();			//DCMI����
	DCMI_DMA_Init((u32)&LCD->LCD_RAM,1,DMA_MemoryDataSize_HalfWord,DMA_MemoryInc_Disable);//DCMI DMA����  
 	OV2640_OutSize_Set(lcddev.width,600); 
	DCMI_Start(); 		//��������
	while(1)
	{ 
		key=KEY_Scan(0); 
		if(key)
		{ 
			DCMI_Stop(); //ֹͣ��ʾ
			switch(key)
			{				    
				case KEY0_PRES:	//�Աȶ�����
		
					break;
				case KEY1_PRES:	//���Ͷ�Saturation
				
					break;
				case KEY2_PRES:	//��Ч����				 
				
					break;
				case WKUP_PRES:		    
					
					break;
			}
			
			DCMI_Start();//���¿�ʼ����
		} 
		delay_ms(10);		
	}    
} 




u16 rgb_buf[144][176];        
u16 gray;
extern u8 flag;
u16 hang=0;
u8 X_MAX,Y_MAX=0;    //С���������Ϣ
u8 X_MAX_LSAT, X_MIN_LSAT, Y_MAX_LSAT, Y_MIN_LSAT=0;   //��һ��С������λ����Ϣ
u8 X,Y=0;      //С���������Ϣ
u8 X_MIN,Y_MIN=180;

int PWM_X,PWM_Y=0;          //pid������ʼ��
float Err_X,Err_Y=0;
float Err_X_LAST,Err_Y_LAST=0;
float Aim_X,Aim_Y=0;
float Kp,Ki,Kd=0;

int main(void)
{ 
    u16 i,j;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200 
	usart2_init(42,115200);		//��ʼ������2������Ϊ115200
	LED_Init();					//��ʼ��LED 
 	LCD_Init();					//LCD��ʼ��  
 	KEY_Init();					//������ʼ�� 
	TIM3_Int_Init(200-1,8400-1);//10Khz����,1�����ж�һ��
	
	TIM14_PWM_Init(10000-1,168-1);	//��װ��ֵ10000������PWMƵ��Ϊ 150hz.      //���Ԥ��
	TIM11_PWM_Init(10000-1,336-1);	//��װ��ֵ10000������PWMƵ��Ϊ 150hz.	
	
 	usmart_dev.init(84);		//��ʼ��USMART
 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");	
	LCD_ShowString(30,70,200,16,16,"OV2640 TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2014/5/14");  	 
	while(OV2640_Init())//��ʼ��OV2640
	{
		LCD_ShowString(30,130,240,16,16,"OV2640 ERR");
		delay_ms(200);
	    LCD_Fill(30,130,239,170,WHITE);
		delay_ms(200);
	}
	LCD_ShowString(30,130,200,16,16,"OV2640 OK");  
    
    OV2640_OutSize_Set(176,144); 
    OV2640_RGB565_Mode();	//RGB565ģʽ
    My_DCMI_Init();			//DCMI����
    DCMI_DMA_Init((u32)rgb_buf,sizeof(rgb_buf)/4,DMA_MemoryDataSize_HalfWord,DMA_MemoryInc_Enable);//DCMI DMA����
    DCMI_Start(); 		//��������
	
	
	
    while(1)
    {
            hang=0;
            LCD_SetCursor(0,0);  
            LCD_WriteRAM_Prepare();		//��ʼд��GRAM
            for(i=0;i<144;i++)
            {
                for(j=0;j<176;j++)
                {
                    if(j==175)
                    {
                        hang++;
                        LCD_SetCursor(0,i+1);  
                        LCD_WriteRAM_Prepare();		//��ʼд��GRAM
                    }
                    gray=((rgb_buf[i][j]>>11)*19595+((rgb_buf[i][j]>>5)&0x3f)*38469 +(rgb_buf[i][j]&0x1f)*7472)>>16;
                    if(gray>=23)
                    {
											  
											  if(i>8&&i<136&&j<160&&j>16)
												{
											    if(i>X_MAX) X_MAX=i;
										     	if(i<X_MIN) X_MIN=i;
											 
								 			
									      
											    if(j>Y_MAX) Y_MAX=j;
										     	if(j<Y_MIN) Y_MIN=j;
											 
												}
                        LCD->LCD_RAM=WHITE;
                    }
                    else
                    {
											 
                        LCD->LCD_RAM=BLACK;
                    }
                }
            }
						
					X_MAX_LSAT =	X_MAX;    //����pid��real������Ϣ ������������������ٴα������ֵ ��Сֵ
				  X_MIN_LSAT =	X_MIN;
				  Y_MAX_LSAT =	Y_MAX;
				  Y_MIN_LSAT =	Y_MIN;    
						
				  X_MAX=0;
				  X_MIN=180;
					Y_MAX=0;
				  Y_MIN=180;
						
					X=(X_MAX_LSAT+X_MIN_LSAT)/2;
				  Y=(Y_MAX_LSAT+Y_MIN_LSAT)/2;
					
			//		TIM_SetCompare1(TIM14,9340);	//�޸ıȽ�ֵ���޸�ռ�ձ�
			
			//		TIM_SetCompare1(TIM11,9300);	//�޸ıȽ�ֵ���޸�ռ�ձ�
						
    }
}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
	{

		Kp=3.4;
		Kd=80.9;

		Aim_X=72;
		Aim_Y=88;
		
		Err_X=X-Aim_X;
		Err_Y=Y-Aim_Y;
		
		
		PWM_X=9340+(Err_X*Kp+(Err_X-Err_X_LAST)*Kd);
		PWM_Y=9300+(Err_Y*Kp+(Err_Y-Err_Y_LAST)*Kd);
		
		if(PWM_Y>9370)PWM_Y=9370;
		if(PWM_Y<9230)PWM_Y=9230;
		
		if(PWM_X>9410)PWM_X=9410;
		if(PWM_X<9270)PWM_X=9270;
		
		Err_X_LAST=Err_X;
		Err_Y_LAST=Err_Y;
		
			TIM_SetCompare1(TIM14,PWM_X);	//�޸ıȽ�ֵ���޸�ռ�ձ�
			TIM_SetCompare1(TIM11,PWM_Y);	//�޸ıȽ�ֵ���޸�ռ�ձ�
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
}








