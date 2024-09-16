#ifndef __PICTURE_H__
#define __PICTURE_H_

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h> 
#include <linux/input.h>
#include <string.h>
#include "lcd.h"
#include "touch.h"
#include <pthread.h>
//*************����ĺ���********************
void point(int x, int y, unsigned int color) ;
//*****************��ӱ�����ɫ-color************
void display_bgm(int color);
//��������������������������������������ʾͼƬ�ĺ�����������������
//1. ������У�����lcd��С��ͼƬ��Ҫ����
//2. �ض�С��ͼƬ������Ҫ������ʾ
//��������� 1. ͼƬ���� 2. ���꣺xy 3. �Ƿ���Ҫ������ʾ
// choice �� 1--��Ҫ������ʾ  0--����Ҫ������ʾ
void show_bmp(const char* filename, int x0,int y0,char choice);
//****************��Ч��غ���***************//
void Displaysql(int w, int h, int x0, int y0, unsigned int color);
void Displaycir(int radios, int x0, int y0,unsigned int color);
void DisplayNo(int width, int height, int x0, int y0, unsigned int *color);
void DisplayDelay(int width, unsigned int *color);
void DisplayCircle(int width, int height, int x0, int y0, unsigned int *color);
void DisplayBmpPicVideo(const char *pic, int state);
void Display_4(int width, int height, int x0, int y0, unsigned int *color);
void ShowPicture(void);
#endif // !__PICTURE_H_

