#include "gobang_touch.h"


//����Ͷ������
int Retract_chess(char arr[][COL], int x, int y, int a, int b, int c, int d, int *color, int *flag)
{

    //����
    if (x > 500 && y > 130 && y < 230)
    {
        printf("00000\n");
        return 2;
    }
    else if (x > 500 && y > 250 && y < 345)
    {
        if (*flag == 1)
        {
            printf("1111\n");
            Display_retract_false(a, b);
            arr[c][d] = ' ';
            *color = -1;
            (*flag)--;
            printf("flag:=%d", flag);
            return 0;
        }
    }
    else if (x > 500 && y > 350 && y < 424)
    {
        if (*color == 1) //����ʤ��
        {
            return 1;
        }
        else if (*color == -1)//����ʤ��
        {
            return -1;
        }
    }
}

//�������ӹ���
void Touch_function(char arr[][COL], const char *pathname4, const char *pathname5, const char *pathname6) // ��������
{
	////�������ʤ�������Ͱ���ʤ������֮�ʹ��ڵ���5��������ʤ������
    if (black_win_count + white_win_count >= 5)
    {
        black_win_count = 0;
        white_win_count = 0;
    }
    int count = 0;//��ʼ��������
    int flag = 0;//��ʼ����־λ
    int ret = 0;//��ʼ������ֵ
    FILE *abs_screen = fopen("/dev/input/event0", "r");
    if (abs_screen == NULL)//�����ʧ��
        exit(0);//���˳�����

    //����һ���ṹ��input_event��������ȡ�¼���
    struct input_event ev;
    int x = 0, y = 0;//��ʼ�������������
    int board_x = 0, board_y = 0;//��ʼ�������ϵ�����
    int color = 1;//��ʼ�����ӵ���ɫ���������Ϊ���壨ֵΪ1��  
    //ѭ����ȡ
    while (1)
    {
        int size = fread(&ev, sizeof(ev), 1, abs_screen);
        if (size == 0)//�����ȡʧ�ܻ�û���¼��ɶ�
            continue; //�������һ��ѭ������ִ������Ĵ���

        // �ж��¼�����
        if (ev.type == EV_ABS) // �����¼�
        {
            // ��ȡX�����ֵ
            if (ev.code == ABS_X)
            {
                x = ev.value * 0.78;
            }
        }
        if (ev.type == EV_ABS) // �����¼�
        {
            // ��ȡY�����ֵ
            if (ev.code == ABS_Y)
            {
                y = ev.value * 0.78;
            }
        }

        //�ж�ѹ�У�����ʱev.valueΪ1��̧��ʱΪ0��
        if (ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)
        {
			//�жϴ������Ƿ�������������
            if (x >= 36 && x <= 450 && y >= 24 && y <= 456)
            {
                if (x >= 36 && y > 24 && x <= 450 && y <= 456)
                {
					//��x�����y�������������ȷ�����������̸��ӵ����������Ա����ȷ�ض�λ����λ��
                    if (x % 48 > 24)
                    {
                        x = x - x % 48 + 48;
                    }
                    else
                    {
                        x = x - x % 48;
                    }
                    if (y % 48 > 24)
                    {
                        y = y - y % 48 + 48;
                    }
                    else
                    {
                        y = y - y % 48;
                    }
                }
				//��ӡ��ǰ����������꣬���ڵ��Ի���ʾ
                printf("x:%d,y:%d\n", x, y);
                if (color == 1 && arr[(y - 1) / 48][(x - 16) / 48] == ' ')
                {
					//��¼���������͵�ǰ����ɫ�����壩  
                    board_x = x;
                    board_y = y;
                    flag = 1;//���ñ�־λ����ʾ��������򼴽�����  
                    arr[(y - 1) / 48][(x - 16) / 48] = 'w';//�������Ϸ��ð���
                    LCD_play_chess(x + 16, y, &color, arr[(y - 1) / 48][(x - 16) / 48]);
                    count++; //���������һ�����ڼ�¼�Ѿ����˶��ٲ���  
                }
                else if (color == -1 && arr[(y - 1) / 48][(x - 16) / 48] == ' ')
                {
                    board_x = x;
                    board_y = y;
                    flag = 1;
                    arr[(y - 1) / 48][(x - 16) / 48] = 'b';
                    LCD_play_chess(x + 16, y, &color, arr[(y - 1) / 48][(x - 16) / 48]);
                    count++;
                }

                if (arr[(y - 1) / 48][(x - 16) / 48] == 'w')
                {
					//���ú����жϰ����Ƿ�ʤ��
                    if (IsWin(arr, ROW, COL, (y - 1) / 48, (x - 16) / 48) == 1)
                    {
                        //�������ʤ������ӡ��Ϣ������ʤ�������ͻغ���������LCD����ʾʤ����Ϣ���ȴ�2�����ʾʤ����ͼƬ���ٵȴ�3����ж��Ƿ������Ϸ 
                        printf("white win!\n");
                        white_win_count++;
                        round1++;
                        LCD_Dispaly_white_Recording_Board(white_win_count);
                        sleep(2);
                        Show_pictures(0, 0, pathname4); // ����ʤ��
                        sleep(3);
                        int ret1 = judge_final_win(arr[(y - 1) / 48][(x - 16) / 48], white_win_count);
                        if (ret1 == 1)
                        {
                            goto loop1;
                        }
                        break;
                    }
                }
                else if (arr[(y - 1) / 48][(x - 16) / 48] == 'b')
                {
					 //���ú����жϺ����Ƿ�ʤ�� 
                    if (IsWin(arr, ROW, COL, (y - 1) / 48, (x - 16) / 48) == -1)
                    {
                        printf("black win!\n");
                        black_win_count++;
                        round1++;
                        LCD_Dispaly_Black_Recording_Board(black_win_count);
                        sleep(2);
                        Show_pictures(0, 0, pathname5); // ����ʤ��
                        sleep(3);
                        int ret1 = judge_final_win(arr[(y - 1) / 48][(x - 16) / 48], black_win_count);
                        if (ret1 == -1)
                        {
                            goto loop2;
                        }
                        break;
                    }
                }
                //����Ѿ������������ӣ��ж��Ƿ�ƽ�֣�����ӡ�����Ϣ�����ӻغ�����Ȼ���˳�ѭ��
                if (count == ROW * COL)
                {
                    printf("ƽ��\n");
                    round1++;
                    break;
                }
                printf("%c %d %d \n", arr[(y - 1) / 48][(x - 16) / 48], (y - 1) / 48, (x - 16) / 48);
            }

            if (x > 500)
                ret = Retract_chess(arr, x, y, board_x + 16, board_y, (board_y - 1) / 48, (board_x - 16) / 48, &color, &flag);
            //������˺�������ֵΪ2����ʾ��ֺ���
			if (ret == 2)
            {
                printf("draw/tie in chess or other board games!\n");
                Show_pictures(0, 0, pathname6); //����
                sleep(2);
                break;//�˳���ǰѭ��
            }
            else if (ret == 1 && count > 5)
            {

                printf("black win!\n");
                Show_pictures(0, 0, pathname5);//����ʤ��
                sleep(2);
                break;//�˳���ǰѭ��
            }
            else if (ret == -1 && count > 5)
            {
                printf("white win!\n");
                Show_pictures(0, 0, pathname4);//����ʤ��
                sleep(2);
                break;//�˳���ǰѭ��
            }
		//�������ʤ�������ﵽ3�λ��ߺ���ʤ�������ﵽ3�Σ�ֱ���˳�ѭ��
        loop1:
        loop2:
            if (white_win_count >= 3 || black_win_count >= 3)
            {
                break;//�˳���ǰѭ��
            }
        }
    }
    
}

//��Ϸ���津��
int Game_interface(void)
{
    //��LCD���ļ�
    // FILE *screen_file = fopen("/dev/input/event0", "r");
    // if (screen_file == NULL)
    // {
    //     printf("open screen_file error\n");
    //     return -1;
    // }
    struct input_event ev;//���������¼��ṹ��
    int x = 0, y = 0;
    while (1)//����ѭ����������ȡ�����¼� 
    {
        int flag;
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
                return 0;//����һ������ķ���
            }
            continue;
        }
        //�ж��¼�����
        if (ev.type == EV_ABS)
        {
            //��ȡX�����ֵ
            if (ev.code == ABS_X)
            {
                x = ev.value * 0.78;
            }
        }
        if (ev.type == EV_ABS)
        {
            //��ȡY�����ֵ
            if (ev.code == ABS_Y)
            {
                y = ev.value * 0.78;
            }
        }
        if (ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)//����¼������ǰ����¼��������Ǵ��������µ��¼���ֵΪ0�� 
        {
            if (x >= 300 && x <= 450 && y >= 130 && y <= 200)
            {
                return ONE;//�ڵ�һ�������ڴ���������ONE 
            }
            if (x >= 300 && x <= 450 && y >= 250 && y <= 320)
            {
                return TWO;//�ڵڶ��������ڴ���������TWO  
            }
            else if (x >= 300 && x <= 450 && y >= 370 && y <= 420)
            {
                return ZERO;//�ڵ����������ڴ���������ZERO
            }
        }
    }
}

int Continue_or_quit(void)
{
    // ��LCD���ļ�
    // FILE *screen_file = fopen("/dev/input/event0", "r");
    // if (screen_file == NULL)
    // {
    //     printf("open screen_file error\n");
    //     return -1;
    // }

    struct input_event ev;
    int x = 0, y = 0;
    while (1)
    {
        int flag;
        int r = read(touch_fd,&ev,sizeof(ev));
        if(sizeof(ev) != r)//�������������
        {
            usleep(10);
            flag++;
            if(10 <= flag)
            {
                //��ʱ̫����  ������
                perror("read ev error");
                return 0;//����һ������ķ���
            }
            continue;
        }
        // �ж��¼�����
        if (ev.type == EV_ABS)
        {
            // ��ȡX�����ֵ
            if (ev.code == ABS_X)
            {
                x = ev.value * 0.78;
            }
        }
        if (ev.type == EV_ABS)
        {
            // ��ȡY�����ֵ
            if (ev.code == ABS_Y)
            {
                y = ev.value * 0.78;
            }
        }

        if (ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)
        {
            if (x > 90 && x < 250)
            {
                return 1;
            }
            else if (x > 500 && x < 670)
            {
                return 0;
            }
        }
    }
}
