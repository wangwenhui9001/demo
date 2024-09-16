#ifndef __DRAW_H__
#define __DRAW_H__

#include <stdio.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include "judge.h"
#define LCD_PATH ("/dev/fb0")
int lcd_fd;
int *lcd_fp;

extern const char *arr1[10];

void lcd_init(void);
void lcd_draw_pixel(int posx, int posy, int color);
void LCD_board_dispaly(void);                            // ��ӡ����
void LCD_play_chess(int x, int y, int *color, char arr); // ���ӻ���
void Show_Game_Options(void);                            // ��ʾѡ�����
void Show_End_Screen(void);                              // ��ӡ��������
void Show_Start_Screen(void);
void Show_pictures(int posx, int posy, const char *str);
void Display_retract_false(int x, int y);
void LCD_Dispaly_Black_Recording_Board(int count); // ��ӡ����÷�
void LCD_Dispaly_white_Recording_Board(int count);
#endif
