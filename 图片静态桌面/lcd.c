#include "lcd.h"
int lcd_fd = -1; // ȫ�ֵ�lcd������fd
unsigned int* plcd=NULL;
unsigned int* back_buffer=NULL;
//��������������������������������lcd ��ʼ��������������������������������������
void Lcd_Init()
{
    lcd_fd = open("/dev/fb0",O_RDWR);//��ȡ�豸
    if(-1==lcd_fd)
    {
        perror("open fb0 error");
        exit(1);
    }
    back_buffer = (unsigned int*)malloc(800 * 480 * 4);
    if(back_buffer == NULL) 
    {
        perror("malloc error for back_buffer");
        exit(1);
    }

    
    //����ӳ��-���Ч��
    plcd = mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);
    if(plcd == MAP_FAILED)
    {
        perror("mmap error");
        return;
    }
}
//���������������������������������ر�lcd�豸������������������������
void Lcd_close()
{
    munmap(plcd,800*480*4);
    close(lcd_fd);
}
