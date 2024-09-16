#ifndef __GOBANG_TOUCH_H__
#define __GOBANG_TOUCH_H__

#include <stdio.h>
#include <linux/input.h> // �¼��ṹ���ͷ�ļ�
#include <stdlib.h>
#include "draw.h"
#include "judge.h"
#include "touch.h"
#include "lcd.h"
#include "menu.h"

extern int white_win_count;
extern int black_win_count;
extern int round1;

// �������˳��Ĵ����ж�
int Continue_or_quit(void);

// ��Ϸ���津��
int Game_interface(void);

// ���Ӵ���
void Touch_function(char arr[][COL], const char *pathname4, const char *pathname5, const char *pathname6);

// ���崥��
int Retract_chess(char arr[][COL], int x, int y, int a, int b, int c, int d, int *color, int *flag);

#endif
