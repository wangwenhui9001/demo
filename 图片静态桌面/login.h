#ifndef __LOGIN_H__
#define __LOGIN_H_

#include <stdio.h>
//*************Ŀ����Ϊ���ṩһ����ȷ�Ĳ�������*************
#include <stdbool.h>//�������� bool �Լ�����Ԥ����ĳ��� true �� false

#define UNLOCK_WORD_LEN         6           /* ���볤�� */
#define UNLOCK_PASSWORD         "000000"    /* �������� */

//#define UNLOCK_WALLPAPER_PATH   "./data/unlock/unlock_wallpaper.bmp"  /* ��ֽ */

#define UNLOCK_WALLPAPER_PATH   "/home/zz/bmp/password.bmp"
#define UNLOCK_FEEDBACK_PATH    "click.bmp"  /* ��������Ч��ͼ */

/* ��������----------------------------- */
#define UNLOCK_TEXT_COLOR       0x000000FF  /* ������ɫ������ɫ */
#define UNLOCK_TEXT_START_X     400         /* ����������Ե���ʼx���� */ 
#define UNLOCK_TEXT_START_Y     53          /* ����������Ե���ʼy���� */ 

/* ����ͼƬ����ڰ�����ƫ��(Ϊ����ʾЧ����һ��żӵ��������) */
#define UNLOCK_FB_DELTA_X       (-10)
#define UNLOCK_FB_DELTA_Y       (-10)
/* ����-------------------------------- */
/* ��ֵ------ */
typedef enum UNLOCK_KEY
{
    UNLOCK_0,
    UNLOCK_1,
    UNLOCK_2,
    UNLOCK_3,
    UNLOCK_4,
    UNLOCK_5,
    UNLOCK_6,
    UNLOCK_7,
    UNLOCK_8,
    UNLOCK_9,  
    UNLOCK_CONFIRM,
    UNLOCK_BS,
    UNLOCK_NONE     /* �޼�ֵ */
}UNLOCK_KEY;

/* �������귶Χ---*/
/* ȷ�ϼ� */
#define UNLOCK_CONFIRM_X_START  260
#define UNLOCK_CONFIRM_X_END    360
#define UNLOCK_CONFIRM_Y_START  380
#define UNLOCK_CONFIRM_Y_END    480

/* ���ؼ� "BackSpace" */
#define UNLOCK_BS_X_START       490
#define UNLOCK_BS_X_END         580
#define UNLOCK_BS_Y_START       380
#define UNLOCK_BS_Y_END         480

/* 0 */
#define UNLOCK_0_X_START        390
#define UNLOCK_0_X_END          460
#define UNLOCK_0_Y_START        380
#define UNLOCK_0_Y_END          480

/* 1 */
#define UNLOCK_1_X_START        260
#define UNLOCK_1_X_END          360
#define UNLOCK_1_Y_START        260
#define UNLOCK_1_Y_END          360

/* 2 */
#define UNLOCK_2_X_START        390
#define UNLOCK_2_X_END          460
#define UNLOCK_2_Y_START        260
#define UNLOCK_2_Y_END          360

/* 3 */
#define UNLOCK_3_X_START        490
#define UNLOCK_3_X_END          580
#define UNLOCK_3_Y_START        260
#define UNLOCK_3_Y_END          360

/* 4 */
#define UNLOCK_4_X_START        260
#define UNLOCK_4_X_END          360
#define UNLOCK_4_Y_START        140
#define UNLOCK_4_Y_END          240

/* 5 */
#define UNLOCK_5_X_START        390
#define UNLOCK_5_X_END          460
#define UNLOCK_5_Y_START        140
#define UNLOCK_5_Y_END          240

/* 6 */
#define UNLOCK_6_X_START        490
#define UNLOCK_6_X_END          580
#define UNLOCK_6_Y_START        140
#define UNLOCK_6_Y_END          240

/* 7 */
#define UNLOCK_7_X_START        260
#define UNLOCK_7_X_END          360
#define UNLOCK_7_Y_START        25
#define UNLOCK_7_Y_END          125

/* 8 */
#define UNLOCK_8_X_START        390
#define UNLOCK_8_X_END          460
#define UNLOCK_8_Y_START        25
#define UNLOCK_8_Y_END          125

/* 9 */
#define UNLOCK_9_X_START        490
#define UNLOCK_9_X_END          580
#define UNLOCK_9_Y_START        25
#define UNLOCK_9_Y_END          125


//************����������******************
//������������x��ֵ
//����ֵ���ɹ�����1 ʧ�ܷ���0 
int show_hua(int t_x);

/**
 * @brief ��ȡ������ֵ������������
 * 
 * @param x ��������
 * @param y ��������
 * @return UNLOCK_KEY ���ؼ�ֵ
 */
static UNLOCK_KEY unlock_GetKey(int x, int y);

//*************�����������*****************
// ����ֵ--ture or false ֻ�н�����ɲŻ᷵��ture
bool unlock_passward();

#endif
