#include <stdio.h>
#include "picture.h"
#include "lcd.h"
#include "touch.h"
#include "login.h"
#include "paint.h"
#include "gobang.h"
void semang(void)
{
	char path[48]={0}; 
	int b=0,k=1;
	int i,count=0;
	//��ʼ�����Խ���
	Lcd_Init();//lcd ��ʼ��
    touch_evntInit();//�����¼���ʼ��
    //show_bmp("/home/zz/bmp/semang01.bmp",0,0,1);//��ʼ���� 
	show_bmp("/home/zz/bmp/semang_start.bmp",0,0,1);//��ʼ���� 
	int touch_fd;//��Ļ�豸
	TouchPoint point;
	//point = Get_TouchPosition();//��ȡ�����x��yֵ 
	char auth_ans[5] = {'3', '2', '2','1','2'};//�ٷ��ο���
	char usr_ans[5] = {0};//�û����Դ�
	while(1){
		point = Get_TouchPosition();
		char path[48]={0};
		if((100 < point.x && point.x < 900 ) && (150 < point.y && point.y <350)) 
		{
		show_bmp("/home/zz/bmp/semang01.bmp",0,0,1);//��һ���� 
        }
		if((340 < point.x && point.x < 380 ) && (440 < point.y && point.y <480)) //ѡ����ǵ�һ��
		{	
		    Displaycir(295, 370,10,0x00FF0000);
			usr_ans[b] = '1';
			printf("==== %c\n",usr_ans[b]);
		}
		
		if((450 < point.x && point.x < 500 ) && (440 < point.y && point.y <480) )//ѡ����ǵڶ���
		{	Displaycir(385, 370,10,0x00FF0000);
			usr_ans[b] = '2';
			printf("==== %c\n",usr_ans[b]);
		}
		if((590 < point.x && point.x < 640 ) && (440 < point.y && point.y <480)) //ѡ����ǵ�����
		{			
		    Displaycir(475, 370,10,0x00FF0000);
			usr_ans[b] = '3';
			printf("==== %c\n",usr_ans[b]);
		}
		if((509 < point.x && point.x < 700 ) && (500 < point.y && point.y < 600 ))
		{
			if(usr_ans[b]==auth_ans[b]){
				system("madplay /home/zz/MP3/semang_true.mp3 &");
				count++;
			}
			else {
				sprintf(path,"madplay /home/zz/MP3/semang0%d.mp3 &",b+1);
				system(path);
			}
			b++;
				//�л�����һ��ͼƬ����
			if(k <= 6)
			{
					k++;   
				sprintf(path,"/home/zz/bmp/semang0%d.bmp",k);
				show_bmp(path,0,0,1);
			   
			   
				point.x=0;
				point.y=0; 
				printf("%d %d ",point.x,point.y);
				printf("%d\n",k);
				sleep(1);   
			}	
				
			if(k  > 6 )
			{               
			    //������ɣ���ӡ���
				if(count>=4)
				{
					show_bmp("/home/zz/bmp/semang_pass.bmp" , 0 ,0,1);
				}
				else
				{
					show_bmp("/home/zz/bmp/semang_out.bmp" , 0 ,0,1);
				}
				sleep(2);
				printf("the test is done!!\n");
				break;
			}	
		}
		

	}

}
void App_Run()
{   
    int App_ID=0;
    while (1)
    {
        App_ID = desktop_touch();
        
        switch (App_ID)
        {
            case PhotoAlbum:/*��� */
                ShowPicture();
                show_bmp("/home/zz/bmp/Desktop_bmp.bmp",0,0,1);
                break;
            case DrawingBoard:/* ���� */
                InitCanve();
                PaintRun();
                show_bmp("/home/zz/bmp/Desktop_bmp.bmp",0,0,1);
                break;
            case Gobang: /*������*/
                GobangRun();
                show_bmp("/home/zz/bmp/Desktop_bmp.bmp",0,0,1);
                break;
            case Semang: /*ɫä*/
	            semang();
	            show_bmp("/home/zz/bmp/Desktop_bmp.bmp",0,0,1);
	            break;
            break;
            default:
                
                break;
        }
    }
}

void login_run()
{
    while(1)
    {
        TouchPoint touch_pos=Get_TouchPosition();//��ȡ����λ��
        int result = show_hua(touch_pos.x*800/1024);
        if (result == 1)
        {
            printf("�������,��������ʾ����������ȷ������\n");
            break;
        }
    }
    
}

void password_run()
{
    while (1)
    {
        if(unlock_passward())  //�����������****
        {
            printf("������ȷ,���Կ�ʼʹ��APP��\n");
            break;
        }
    }
}


int main()
{
    Lcd_Init();//lcd ��ʼ��
    touch_evntInit();//�����¼���ʼ��
    TouchPoint point;
    show_bmp("/home/zz/bmp/lockx.bmp",0,0,1);//����ͼƬ������ʾ����ǰ�Ľ���
    login_run();
    password_run();
    while(1)
    {    
         
        show_bmp("/home/zz/bmp/Desktop_bmp.bmp",0,0,1);
        App_Run();
        
    }
    Lcd_close();
    Close_Touchfd();
    return 0;
}
