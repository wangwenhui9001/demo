#include "menu.h"

//ѡ��ģʽ����
int Select_Mode(const char *pathname1)
{
    //��ӡ��Ϸ����
    Show_pictures(0, 0, "/home/zz/bmp/wuziqi_1.bmp");

    //����Game_interface�������������Ҷ�ս����1���˳���Ϸ����0
    return Game_interface();
}
