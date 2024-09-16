#include "paint.h"

int mode=0, color=0x0000ff, size=10;
int color_buf;

void InitCanve()
{
    Displaysql(800, 480, 0, 0, 0xffffff);
    //��Сѡ��
    Displaycir(10, 20, 20, 0x000000);
    Displaycir(15, 45, 20, 0x000000);
    Displaycir(20, 80, 20, 0x000000);
    //��ɫѡ��
    Displaycir(20, 120, 20, 0xff0000);
    Displaycir(20, 150, 20, 0x00ff00);
    Displaycir(20, 180, 20, 0x0000ff);
    //ģʽѡ��
    show_bmp("/home/zz/bmp/Draw1.bmp",480,25,0);
    show_bmp("/home/zz/bmp/draw2.bmp",530,25,0);
    show_bmp("/home/zz/bmp/draw3.bmp",580,25,0);
    show_bmp("/home/zz/bmp/draw4.bmp",750,25,0);
}

void PaintRun()
{
    //������������� һ�㴥�����Ĳ����ǲ���������  ���������Ҫʵ����ѭ��
    struct input_event ev;//
    int flag = 0;//��ʱ��flag
    int ev_x0,ev_y0,ev_x,ev_y,move_x,move_y;
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
                return ;//����һ������ķ���
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
            ev_x0 = ev_x * 800 / 1200;
            ev_y0 = ev_y * 480 / 600;
        }
        if(0x03 == ev.type)
        {
            if(0x00 == ev.code){
                move_x = ev.value * 800  / 1024 / 2;
            }
            if(0x01 == ev.code){
                move_y = ev.value * 480  / 600 / 2;
            }
            printf("%d %d\n", move_x, move_y);
            if(move_y>45){
                Displaycir(size, move_x, move_y, color);
            }
            //printf("���ڻ滭\n");
        }
        else if(0x01 == ev.type && BTN_TOUCH == ev.code && 0x00 == ev.value)//��̧����
        {
            //printf("ev_x0:%d ev_y0:%d\n",ev_x0,ev_y0);
            //ʵ�ֵ���ͷ����ж�
            if(ev_x0 == ev_x && ev_y0 == ev_y)//�����û�ж�
            {
                printf("���\n");
                //return;
            }
            if ((ev_x0 > 0 && ev_x0 < 30) && (ev_y0 > 0 && ev_y0 < 50))
            {
                size = 10;
                printf("С��\n");
            }
            if ((ev_x0 > 60 && ev_x0 < 90) && (ev_y0 > 0 && ev_y0 < 50))
            {
                size = 20;
                printf("����\n");
            }
            if ((ev_x0 > 120 && ev_x0 < 150) && (ev_y0 > 0 && ev_y0 < 50))
            {
                size = 30;
                printf("����\n");
            }
            if ((ev_x0 > 180 && ev_x0 < 210) && (ev_y0 > 0 && ev_y0 < 50))
            {
                color = 0xff0000;
                printf("��ɫ\n");
            }
            if ((ev_x0 > 240 && ev_x0 < 270) && (ev_y0 > 0 && ev_y0 < 50))
            {
                color = 0x00ff00;
                printf("��ɫ\n");
            }
            if ((ev_x0 > 290 && ev_x0 < 320) && (ev_y0 > 0 && ev_y0 < 50))
            {
                color = 0x0000ff;
                printf("��ɫ\n");
            }
            if ((ev_x0 > 410 && ev_x0 < 450) && (ev_y0 > 0 && ev_y0 < 80))
            {
                color = color_buf;
                printf("��ͼ\n");
            }
            if ((ev_x0 > 460 && ev_x0 < 490) && (ev_y0 > 0 && ev_y0 < 70))
            {
                color_buf = color;
                printf("��Ƥ��\n");
                color = 0xffffff;
            }
            if ((ev_x0 > 500 && ev_x0 < 530) && (ev_y0 > 0 && ev_y0 < 70))
            {
                InitCanve();
                printf("����\n");
            }
            if ((ev_x0 > 650 && ev_x0 < 685) && (ev_y0 > 0 && ev_y0 < 70))
            {
                printf("�˳�\n");
                return;
            }
        }
    }
}
