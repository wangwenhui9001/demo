#ifndef __JUDGE_H__
#define __JUDGE_H__

#define ROW 10
#define COL 10

void Arr_Init(char arr[ROW][COL]);      //�Լ�¼���ݵ�������г�ʼ��
int IsWin(char board[ROW][COL], int row, int col, int a, int b); //�ж�ʤ��
int judge_final_win(char a,int b);//�ж�����ʤ��
#endif
