#ifndef __TOUCH_H__
#define __TOUCH_H__

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h> 
#include <linux/input.h>
#include <string.h>
#include "lcd.h"
#include <pthread.h>
#define Touch_Up 1
#define Touch_Down 2
#define Touch_Left 3
#define Touch_Right 4
#define Touch_Click 5
#define TOUCH_PATH "/dev/input/event0"

extern int touch_fd;//��Ļ�豸
//----����ͼ��ĺ궨��
//��һ��ͼ���λ�á������
#define PhotoAlbum_X_START 20
#define PhotoAlbum_Y_START 20
#define PhotoAlbum_X_END 150
#define PhotoAlbum_Y_END 90

//�ڶ���ͼ���λ�á������� Drawing board
#define DrawingBoard_X_START 135
#define DrawingBoard_Y_START 20
#define DrawingBoard_X_END 200
#define DrawingBoard_Y_END 90

// ������ͼ���λ�á���������gobang

#define Gobang_X_START 300
#define Gobang_Y_START 20
#define Gobang_X_END 400
#define Gobang_Y_END 85
//���ĸ�ͼ��λ��-- ɫ�����ϵͳsemang 
#define Semang_X_START 400
#define Semang_Y_START 20
#define Semang_X_END 500
#define Semang_Y_END 85
//APP ID 
#define PhotoAlbum 1
#define DrawingBoard 2
#define Gobang 3
#define Semang 4
// ���崥����Ľṹ��//�������ܳ�ʼ��
typedef struct {
    int x;
    int y;
    int is_long_press;//�Ƿ񳤰�
} TouchPoint;

//********lzs--��ȡ����ķ���ֵ************//
typedef enum
{
    TouchError = 0,//һ������ֵ
    TouchClick,
    TouchUp,
    TouchDown,
    TouchLeft,
    TouchRight,
    TouchOther,
    TouchExit
}TouchDir;


//*********�����¼���ʼ��*********
void touch_evntInit(void);
//************��ȡ��������*********
//����ֵ���������򣬾��嶨���ں궨�崦
int Get_TouchDirection(void);
//*****************��ȡ������λ��*********
//**************��ȡ����λ��--����ʶ�𳤰�****
// ����ֵ�������һ��TouchPOint�Ľṹ�壬
//xyΪ�������λ�ã�
//is_long_pressΪ�Ƿ񳤰���0--δ����  1--����
TouchPoint Get_TouchPosition();

//����TOUCH_FD
void Close_Touchfd();
//����ͼ��λ��
int desktop_touch();
//monitor �˳�
void* camera_touch(void* argv);
//�߳�---���ʱʹ�û�ȡ��ǰ״̬
void *GetState(void *argv);
// ****�߳�-�������***********//
//void *eMusic_albums_touch(void * argv);
//***********lzs--��ȡ����*************//
TouchDir GetTouchDir(void);

#endif
