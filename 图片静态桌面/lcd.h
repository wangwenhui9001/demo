#ifndef __LCD_H__
#define __LCD_H__
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h> 
#include <linux/input.h>
#include <string.h>

extern unsigned int* plcd ;//ӳ��ɹ������׵�ַ
extern unsigned int* back_buffer;//һ����̨buffer,��������Ƶ��������Ļ

//��������������������������������lcd ��ʼ��������������������������������������
void Lcd_Init();
//���������������������������������ر�lcd�豸������������������������
void Lcd_close();

#endif // !__LCD_H__

