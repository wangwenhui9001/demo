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
	//初始化测试界面
	Lcd_Init();//lcd 初始化
    touch_evntInit();//触摸事件初始化
    //show_bmp("/home/zz/bmp/semang01.bmp",0,0,1);//开始界面 
	show_bmp("/home/zz/bmp/semang_start.bmp",0,0,1);//开始界面 
	int touch_fd;//屏幕设备
	TouchPoint point;
	//point = Get_TouchPosition();//获取点击的x，y值 
	char auth_ans[5] = {'3', '2', '2','1','2'};//官方参考答案
	char usr_ans[5] = {0};//用户测试答案
	while(1){
		point = Get_TouchPosition();
		char path[48]={0};
		if((100 < point.x && point.x < 900 ) && (150 < point.y && point.y <350)) 
		{
		show_bmp("/home/zz/bmp/semang01.bmp",0,0,1);//第一道题 
        }
		if((340 < point.x && point.x < 380 ) && (440 < point.y && point.y <480)) //选择答案是第一个
		{	
		    Displaycir(295, 370,10,0x00FF0000);
			usr_ans[b] = '1';
			printf("==== %c\n",usr_ans[b]);
		}
		
		if((450 < point.x && point.x < 500 ) && (440 < point.y && point.y <480) )//选择答案是第二个
		{	Displaycir(385, 370,10,0x00FF0000);
			usr_ans[b] = '2';
			printf("==== %c\n",usr_ans[b]);
		}
		if((590 < point.x && point.x < 640 ) && (440 < point.y && point.y <480)) //选择答案是第三个
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
				//切换到下一张图片测试
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
			    //测试完成，打印结果
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
            case PhotoAlbum:/*相册 */
                ShowPicture();
                show_bmp("/home/zz/bmp/Desktop_bmp.bmp",0,0,1);
                break;
            case DrawingBoard:/* 画板 */
                InitCanve();
                PaintRun();
                show_bmp("/home/zz/bmp/Desktop_bmp.bmp",0,0,1);
                break;
            case Gobang: /*五子棋*/
                GobangRun();
                show_bmp("/home/zz/bmp/Desktop_bmp.bmp",0,0,1);
                break;
            case Semang: /*色盲*/
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
        TouchPoint touch_pos=Get_TouchPosition();//获取触摸位置
        int result = show_hua(touch_pos.x*800/1024);
        if (result == 1)
        {
            printf("解锁完成,请你在显示屏处输入正确的密码\n");
            break;
        }
    }
    
}

void password_run()
{
    while (1)
    {
        if(unlock_passward())  //密码输入界面****
        {
            printf("密码正确,可以开始使用APP了\n");
            break;
        }
    }
}


int main()
{
    Lcd_Init();//lcd 初始化
    touch_evntInit();//触摸事件初始化
    TouchPoint point;
    show_bmp("/home/zz/bmp/lockx.bmp",0,0,1);//背景图片居中显示解锁前的界面
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
