#ifndef _GOBANG_H_
#define _GOBANG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "menu.h"
#include "gobang_touch.h"

// const char *arr1[10];
// //����ȫ�ֱ�������¼�����ʤ������ 
// int white_win_count = 0;
// //����ȫ�ֱ�������¼�����ʤ������ 
// int black_win_count = 0;
// //����ȫ�ֱ��������ڼ�¼��Ϸ�غϴ���
// int round1 = 0;

//����һ���ṹ�����ͣ����ڴ洢��Ϸ��ص�·����Ϣ
typedef struct pathname
{
    char str1[10]; //����·��
    char str2[10]; //�����ұߵ�Ͷ������ͼƬ·��
    char str3[10]; //�Ƿ������ͼƬ·��
    char str4[10]; //�����ʤ
    char str5[10]; //�����ʤ
    char str6[10]; //����
    char str7[10]; //�Ʒְ�
    int count;
} pathname;

void GobangRun();



#endif // !_GOBANG_H_
