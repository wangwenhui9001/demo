#include "touch.h"



//*********�����¼���ʼ��*********
int touch_fd;//��Ļ�豸
void touch_evntInit(void)
{
    // int fd = open(TOUCH_PATH,O_RDONLY);//ֻ����
    // if(fd<0)
    // {
    //     perror("open fail");
    //     return 0;
    // }
    touch_fd=open(TOUCH_PATH,O_RDONLY);
    if(touch_fd<0)
    {
        perror("open touch_fd fail");
        return ;
    }
}

//************��ȡ��������*********
//����ֵ���������򣬾��嶨���ں궨�崦
int Get_TouchDirection(void)
{
    struct input_event ev;
    int x_start=-1,y_start=-1;	//����ĳ�ֵ
    int x_end = -1,y_end = -1;    //�����յ�
    int flag=0;
    while(1)
    {
        //2.��ͣ�ش��ļ��ж�ȡ����
        int r=read(touch_fd, &ev, sizeof(struct input_event));
        if(sizeof(ev)!=r)//�ȴ���Ӧ--�����ʱû��Ӧ���������̣����еȴ�
        {
            usleep(10);
            flag++;
            if(flag>=10)
            {
                perror("read ev error");
                break;
            }
            continue;
        }
        flag=0;
        //3.��������
        if(ev.type == EV_ABS)   //�����¼� 
        {
            if(ev.code == ABS_X)
            {
                if (-1 == x_start)        //x��
                {
                    x_start = ev.value;	//���
                }
                x_end = ev.value;      //�յ�
                
            }
            if(ev.code == ABS_Y)		//y��
            {
                if (-1 == y_start)
                {
                    y_start = ev.value;
                }
                y_end = ev.value;      //�յ�
                
            }
            if(ev.code ==ABS_PRESSURE && ev.value == 0)
            {
                if(x_start != -1 && y_start != -1)
                {
                    break;
                }
            }
        }
        
        if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)   //����⵽���������ͷţ�������������ʱ���˳���ǰ�Ĵ������ѭ����
        {
            if(x_start != -1 && y_start != -1)
            {
                return Touch_Click;
            }
        }

        if (abs(x_end - x_start) > (y_end - y_start))
        {
            if (x_end - x_start > 0)
            {
                return Touch_Right;
            }
            else
            {
                return Touch_Left;
            }
            
        }
        if (abs(x_end - x_start) < (y_end - y_start))
        {
            if (y_end - y_start > 0)
            {
                return Touch_Down;
            }
            else
            {
                return Touch_Up;
            }
            
        }
    }
    
    //��ӡ����
    //printf("%d , %d\n", x_end, y_start);   
}

//**************��ȡ����λ��--����ʶ�𳤰�****
//*****************��ȡ������λ��*********
// ����ֵ�������һ��TouchPOint�Ľṹ�壬
//xyΪ�������λ�ã�ԭʼ����--δ����lcd�봥������С��һ��������
//is_long_pressΪ�Ƿ񳤰���0--δ����  1--����
TouchPoint Get_TouchPosition()
{
    TouchPoint point = {-1, -1, 0};  // ��ʼ�� x, y �� is_long_press
    struct input_event ev;
    int start_time = 0;  // ���ڼ�¼��ʼ������ʱ��
    int current_time = 0;  // ���ڼ�¼��ǰʱ��
    const int LONG_PRESS_THRESHOLD = 2000;  // ���峤����ʱ����ֵ��������2�룩
    int flag=0;
    while(1) //������
    {
        int r = read(touch_fd, &ev, sizeof(struct input_event));
        if(sizeof(ev) != r) {
            usleep(10);
            flag++;
            if(flag >= 10) {
                perror("read ev error");
                break;
            }
            continue;
        }
        flag = 0;
        if(ev.type == EV_ABS) 
        {   usleep(1000);
            if(ev.code == ABS_X) 
            {
                point.x = ev.value;
            }
            if(ev.code == ABS_Y) 
            {
                point.y = ev.value;
            }
        }
        if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0) 
        {
            point.is_long_press = 0;  // ���ó�����־λ
            break;
        }

        if(point.x !=-1&& point.y !=-1)
        {
            // ����Ƿ񳤰�
            if (start_time == 0) 
            {
                start_time = current_time;  // ��¼��ʼ������ʱ��
            } 
            else 
            {
                if ((current_time - start_time) >= LONG_PRESS_THRESHOLD) 
                {
                    point.is_long_press = 1;  // ���ó�����־λΪ1
                }
            }
            printf("Touch Position: (%d, %d %d)\n", point.x, point.y, point.is_long_press);
            return point;
        }
    }
}


//�����������رմ�����������������
void Close_Touchfd()
{
    close(touch_fd);
}


// ��������ʱ�Ļ�ȡ����ʵʩapp�ĺ���
// ����APP��ID
int desktop_touch()
{
    TouchPoint desktop_point;
    desktop_point = Get_TouchPosition();
    desktop_point.x=desktop_point.x*800/1024;
    desktop_point.y=desktop_point.y*480/600;
    //tc.x*800/1024,tc.y*480/600
    // printf("DesktoppointX :%d\n", desktop_point.x);
    // printf("desktop_point.is_long_press: %d\n", desktop_point.is_long_press);
    switch (desktop_point.is_long_press)
    {
    case 1://�����Ļ�--ʲô������
        break;
    
    case 0://�̰���򿪸�APP
        //��ᰴ��
        if ((desktop_point.x > PhotoAlbum_X_START )&& (desktop_point.y > PhotoAlbum_Y_START)&& 
            (desktop_point.x<PhotoAlbum_X_END)&& (desktop_point.y<PhotoAlbum_Y_END))
            {
                
                printf("PhotoAlbum APP started...\n");
                return PhotoAlbum;
            }
        // ����
        else if ((desktop_point.x>DrawingBoard_X_START)&&(desktop_point.x<DrawingBoard_X_END)&&
            (desktop_point.y>DrawingBoard_Y_START)&&(desktop_point.y<DrawingBoard_Y_END))
            {
                
                printf("DrawingBoard APP started...\n");
                return DrawingBoard;
            }
        // ������
        else if ((desktop_point.x>Gobang_X_START)&&(desktop_point.x<Gobang_X_END)&&
            (desktop_point.y>Gobang_Y_START)&&(desktop_point.y<Gobang_Y_END))
            {
                
                printf("Gobang APP started...\n");
                return Gobang;
            }
            else if ((desktop_point.x>Semang_X_START)&&(desktop_point.x<Semang_X_END)&&
            (desktop_point.y>Semang_Y_START)&&(desktop_point.y<Semang_Y_END))
            {
                
                printf("Semang APP started...\n");
                return Semang;
            }
        break;

    default:
        //return 0;
        break;
    }
}



//**************��ȡ��������2*****************//
//��ȡ����������
TouchDir GetTouchDir(void)
{
    //������������� һ�㴥�����Ĳ����ǲ���������  ���������Ҫʵ����ѭ��
    struct input_event ev;//
    int flag = 0;//��ʱ��flag
    int ev_x0,ev_y0,ev_x,ev_y;
    while(1)
    {
        //�������ȡ����ֵ  ��ô���Ǵ�����ļ������ȡ����
        int r = read(touch_fd,&ev,sizeof(ev));
        if(sizeof(ev) != r)//�������������
        {
            usleep(10);
            flag++;
            if(10 <= flag)
            {
                //��ʱ̫����  ������
                perror("read ev error");
                return TouchError;//����һ������ķ���
            }
            continue;
        }
        flag = 0;
        //�����ݴ�ӡ��������
        //printf("type:%d code:%d value:%d\n",ev.type,ev.code,ev.value);
        //��ȡ����
        if(EV_ABS == ev.type)//�����������ݾ�������
        {
            if(REL_X == ev.code)//x��
            {
                ev_x = ev.value;
            }
            else if(REL_Y == ev.code)//y��
            {
                ev_y = ev.value;
            }
        }
        if(0x01 == ev.type && BTN_TOUCH == ev.code && 0x01 == ev.value)//�ְ���ȥ��ʱ��
        {
            ev_x0 = ev_x;
            ev_y0 = ev_y;
        }
        else if(0x01 == ev.type && BTN_TOUCH == ev.code && 0x00 == ev.value)//��̧����
        {
            printf("%d %d %d %d\n",ev_x0,ev_y0,ev_x,ev_y);
            //ʵ�ֵ���ͷ����ж�
            if(ev_x0 == ev_x && ev_y0 == ev_y)//�����û�ж�
            {
                printf("���\n");
                if(ev_x0 >=900&&ev_y0<=100)
                {
                    return TouchExit;
                }
                return TouchClick;
            }
            else//���� �����ͻ��з���
            {
                if(ev_x > ev_x0 && abs(ev_x - ev_x0) > abs(ev_y - ev_y0))
                {
                    printf("�һ�\n");
                    return TouchRight;
                }
                else if(ev_x < ev_x0 && abs(ev_x - ev_x0) > abs(ev_y - ev_y0))
				{
					printf("��\n");
					// music_i = 2;
					// system("killall -9 madplay");
					return TouchLeft;
				}
				else if(ev_y > ev_y0 && abs(ev_x - ev_x0) < abs(ev_y - ev_y0))
				{
					printf("�»�\n");
					// music_i = 3;
					// system("killall -9 madplay");
					return TouchDown;
				}
				else if(ev_y < ev_y0 && abs(ev_x - ev_x0) < abs(ev_y - ev_y0))
				{
					printf("�ϻ�\n");
					// music_i = 4;
					// system("killall -9 madplay");
					return TouchUp;
				}
                else
                {
                    return TouchOther;
                }
            }
        }

    }
}





extern TouchDir dir;

void * GetState(void * argv)
{
	pthread_detach(pthread_self());

	while(1)
	{
		dir = GetTouchDir();
		sleep(1);
	}
}



//���ٴ�����
void DestoryTouch(void)
{
    close(touch_fd);
}
