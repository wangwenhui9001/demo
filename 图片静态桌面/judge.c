#include "judge.h"
//�����ʼ��
void Arr_Init(char arr[ROW][COL])
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			arr[i][j] = ' ';//����ǰλ������Ϊ�ո��ַ�
		}
	}
}

//�ж�ʤ��
int IsWin(char board[ROW][COL], int row, int col, int a, int b)
{
	int zcount = 0;//��¼������������������
	int fcount = 0;//��¼������������������
	
	//�жϺ����Ƿ�����,�����ж������ӵ�Ϊ���ĵ����4�����ұ��ĸ������Լ�����λ�ã��ܹ��Ÿ�λ��
	for (int i = -4; i <= 4; i++)
	{
		//�����λ���Ƿ�����Ч��Χ��  
		if (b + i >= 0 && b + i < col)
		{
			//�����ǰλ�������w�����ӣ����������������������b���������� 
			if (board[a][b + i] == 'w')
			{
				zcount++;
				fcount = 0;
			}
			//�����ǰλ�������b�����ӣ����������������������w����������
			else if (board[a][b + i] == 'b')
			{
				fcount++;
				zcount = 0;
			}
			else //�Ȳ�����1���ֲ��ǵ���0��˵����λ��Ϊ�տո����߶�����
			{
				fcount = 0;
				zcount = 0;
				continue;
			}
		}
		//������w����������ӣ�����1��ʾ�׷�Ӯ����Ϸ
		if (zcount == 5)
		{
			return 1;
		}
		//������b����������ӣ�����-1��ʾ�ڷ�Ӯ����Ϸ 
		if (fcount == 5)
		{
			return -1;
		}
	}

	//�жϴ�ֱ�����Ƿ�����
	for (int i = -4; i <= 4; i++)
	{
		if (a + i >= 0 && a + i < col)
		{
			if (board[a + i][b] == 'w')
			{
				zcount++;
				fcount = 0;
			}
			else if (board[a + i][b] == 'b')
			{
				fcount++;
				zcount = 0;
			}
			else
			{
				fcount = 0;
				zcount = 0;
				continue;
			}
		}
		if (zcount == 5)
		{
			return 1;
		}
		if (fcount == 5)
		{
			return -1;
		}
	}

	//������������б�����ж��Ƿ�����
	for (int i = -4; i <= 4; i++)
	{
		//����к���λ���Ƿ�����Ч��Χ��  
		if (a + i >= 0 && a + i < col && b + i >= 0 && b + i < col)
		{
			if (board[a + i][b + i] == 'w')
			{
				zcount++;
				fcount = 0;
			}
			else if (board[a + i][b + i] == 'b')
			{
				zcount = 0;
				fcount++;
			}
			else
			{
				zcount = 0;
				fcount = 0;
				continue;
			}
		}
		if (zcount == 5)
		{
			return 1;
		}
		if (fcount == 5)
		{
			return -1;
		}
	}

	//������������б�����ж��Ƿ�����
	for (int i = -4; i <= 4; i++)
	{
		//����к���λ���Ƿ�����Ч��Χ��
		if (a + i >= 0 && a + i < col && b - i >= 0 && b - i < col)
		{
			if (board[a + i][b - i] == 'w')
			{
				zcount++;
				fcount = 0;
			}
			else if (board[a + i][b - i] == 'b')
			{
				zcount = 0;
				fcount++;
			}
			else
			{
				zcount = 0;
				fcount = 0;
				continue;
			}
		}
		if (zcount == 5)
		{
			return 1;
		}
		if (fcount == 5)
		{
			return -1;
		}
	}
}

//�ж����յ�ʤ��
int judge_final_win(char a,int b)
{
	//��������w�ҵ÷ִ��ڵ���3���򷵻�1��ʾ�׷�Ӯ����Ϸ  
	if(a=='w'&&b>=3)
	{
		return 1;
	}
	//��������b�ҵ÷ִ��ڵ���3���򷵻�-1��ʾ�ڷ�Ӯ����Ϸ  
	else if(a=='b'&&b>=3)
	{
		return -1;
	}
	//�����������0��ʾ��Ϸ�������л�û��Ӯ�� 
	return 0;
}
