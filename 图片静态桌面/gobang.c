#include "Gobang.h"

const char *arr1[10];
//����ȫ�ֱ�������¼�����ʤ������ 
int white_win_count = 0;
//����ȫ�ֱ�������¼�����ʤ������ 
int black_win_count = 0;
//����ȫ�ֱ��������ڼ�¼��Ϸ�غϴ���
int round1 = 0;

void game_continue(pathname path)
{
    char arr[ROW][COL] = {0};
    Arr_Init(arr);                    //��ʼ���ַ�����
    LCD_board_dispaly();              //LCD���̴�ӡ
    Show_pictures(496, 0, "/home/zz/bmp/wuziqi_7.bmp"); //��ӡ�Ʒְ�
    LCD_Dispaly_Black_Recording_Board(black_win_count);
    LCD_Dispaly_white_Recording_Board(white_win_count);
    Show_pictures(496, 70, "/home/zz/bmp/wuziqi_2.bmp"); //��ʾ�ұ߹��ܿ�
    Touch_function(arr, "/home/zz/bmp/wuziqi_4.bmp", "/home/zz/bmp/wuziqi_5.bmp","/home/zz/bmp/wuziqi_6.bmp"); //ִ�����ӳ���
}

//���·��
void game(pathname path)
{
	//����һ����ά�ַ����飬���ڴ洢�����ϵ��ַ�
    char arr[ROW][COL] = {0};
    Arr_Init(arr);       //��ʼ���ַ�����
    LCD_board_dispaly(); //LCD���̴�ӡ
	//����Show_pictures��������ʾ�Ʒְ壨��ʼ״̬��  
    Show_pictures(496, 0, "/home/zz/bmp/wuziqi_7.bmp");
	//ѭ����ʾ�ұ߹��ܿ�ͼƬ���Ӹ߶�70��ʼ�������ƶ�  
    for (int i = 200; i >= 70; i--)
    {
        Show_pictures(496, i, "/home/zz/bmp/wuziqi_2.bmp"); //��ʾ�ұ߹��ܿ�
    }
	//ִ�����ӳ���
    Touch_function(arr, "/home/zz/bmp/wuziqi_4.bmp", "/home/zz/bmp/wuziqi_5.bmp","/home/zz/bmp/wuziqi_6.bmp");

loop1:
    //��ӡ�Ƿ������Ϸ��ͼƬ
    Show_pictures(0, 0, "/home/zz/bmp/wuziqi_3.bmp");
	//����Continue_or_quit�������ж��Ƿ������Ϸ
    if (Continue_or_quit())
    {
		//���������Ϸ�������game_continue�����������Ϸ�ִλ�ʤ������������������ת����ͬ�ı�ǩλ�� 
        game_continue(path);
        if (round1 >= 5 || white_win_count >= 3 || black_win_count >= 3)
        {
            goto loop2;
        }
        goto loop1;
    }
loop2:
    //����ʤ����������
    white_win_count = 0;
    black_win_count = 0;
    close(lcd_fd); //�ر�LCD_fd
}

void test(int *x, pathname path)
{
    
	//ʹ��switch�������û�ѡ�����Ϸģʽ���ò�ͬ�ĺ���
    switch (*x = Select_Mode("/home/zz/bmp/wuziqi_1.bmp"))
    {
    case ONE://���ѡ��ģʽΪ1�������game������ʼ��Ϸ 
        game(path);
        break;
		
    case ZERO://���ѡ��ģʽΪ0������ʾ������Ļ���˳���Ϸ
        Show_End_Screen();
        printf("�˳���Ϸ\n");
        break;
    }
}


//*****������������*********//
void GobangRun()
{
    int x;
    pathname path;
    do
    {
        test(&x, path);
    }
    while (x);
    return ;

}
