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

extern int touch_fd;//屏幕设备
//----桌面图标的宏定义
//第一个图标的位置——相册
#define PhotoAlbum_X_START 20
#define PhotoAlbum_Y_START 20
#define PhotoAlbum_X_END 150
#define PhotoAlbum_Y_END 90

//第二个图标的位置——画板 Drawing board
#define DrawingBoard_X_START 135
#define DrawingBoard_Y_START 20
#define DrawingBoard_X_END 200
#define DrawingBoard_Y_END 90

// 第三个图标的位置——五子棋gobang

#define Gobang_X_START 300
#define Gobang_Y_START 20
#define Gobang_X_END 400
#define Gobang_Y_END 85
//第四个图标位置-- 色弱检测系统semang 
#define Semang_X_START 400
#define Semang_Y_START 20
#define Semang_X_END 500
#define Semang_Y_END 85
//APP ID 
#define PhotoAlbum 1
#define DrawingBoard 2
#define Gobang 3
#define Semang 4
// 定义触摸点的结构体//变量不能初始化
typedef struct {
    int x;
    int y;
    int is_long_press;//是否长按
} TouchPoint;

//********lzs--获取方向的方向值************//
typedef enum
{
    TouchError = 0,//一个错误值
    TouchClick,
    TouchUp,
    TouchDown,
    TouchLeft,
    TouchRight,
    TouchOther,
    TouchExit
}TouchDir;


//*********触摸事件初始化*********
void touch_evntInit(void);
//************获取触摸方向*********
//返回值：触摸方向，具体定义在宏定义处
int Get_TouchDirection(void);
//*****************获取触摸点位置*********
//**************获取触摸位置--可以识别长按****
// 返回值是上面的一个TouchPOint的结构体，
//xy为触摸点的位置，
//is_long_press为是否长按，0--未长按  1--长按
TouchPoint Get_TouchPosition();

//销毁TOUCH_FD
void Close_Touchfd();
//桌面图标位置
int desktop_touch();
//monitor 退出
void* camera_touch(void* argv);
//线程---相册时使用获取当前状态
void *GetState(void *argv);
// ****线程-用于相册***********//
//void *eMusic_albums_touch(void * argv);
//***********lzs--获取方向*************//
TouchDir GetTouchDir(void);

#endif
