#include "draw.h"
#include "lcd.h"
extern unsigned int* plcd;

// ��ʾһ�����ص�
//posx��posyΪ���ص�����꣬colorΪ���ص����ɫֵ
void lcd_draw_pixel(int posx, int posy, int color)
{
	//�ж����ص������Ƿ���LCD��Ļ��Χ��
    if (posx >= 0 && posx < 800 && posy >= 0 && posy < 480)
		//�ڶ�Ӧλ��д����ɫֵ
        *(plcd + posy * 800 + posx) = color;
}
// ��ʼ��lcd��Ļ
void lcd_init()
 {
     //��lcd�豸�ļ�
     lcd_fd = open(LCD_PATH, O_RDWR);
     if (lcd_fd == -1)//�����ʧ��
     {
         perror("open lcd failed");
         return;
     }
     //��ȡlcd��Ļ�ĵ�ǰ��Ϣ
     struct fb_var_screeninfo lcd_info;//����ṹ����������ڴ洢lcd��Ļ��Ϣ
     ioctl(lcd_fd, FBIOGET_VSCREENINFO, &lcd_info);//ͨ��ioctl������ȡlcd��Ļ��Ϣ

     //��lcd�ڴ�ӳ�䵽���̵ĵ�ַ�ռ��У�ʹ�ÿ���ֱ�Ӷ�дlcd�ڴ� 
     int mem_size = lcd_info.xres * lcd_info.yres * (lcd_info.bits_per_pixel / 8);
// 	//�����ڴ��С 
     lcd_fp = mmap(NULL, mem_size, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);
 	//ӳ���ڴ�
     if (lcd_fp == MAP_FAILED)//���ӳ��ʧ�� 
     {
         perror("mmap failed");
         close(lcd_fd);
         lcd_fd = -1;//����lcd�豸�ļ�Ϊ-1����ʾ��ʧ��  
         exit(0);
     }
     return;
 }
// ��ӡ�����ϳ�ʼ�������
void DisPlay_Five_point(void)
{
	//��ʼ��lcd��Ļ
    lcd_init();
	//��������������
    int x0 = 144 + 16, y0 = 144;
    int x1 = 336 + 16, y1 = 144;
    int x2 = 240 + 16, y2 = 240;
    int x3 = 144 + 16, y3 = 336;
    int x4 = 336 + 16, y4 = 336;
	//��ÿ������Χ����һ��Բ��ͼ����ͨ���ж����ص��Ƿ���Բ�ڣ�Ȼ����ƺ�ɫ���أ�
    for (int w = x0 - 48; w < x0 + 48; w++)//wѭ������Բ�Ŀ��  
    {
        for (int h = y0 - 48; h < y0 + 48; h++) //hѭ������Բ�ĸ߶�  
        {
			//�жϵ�ǰ���ص��Ƿ���Բx0��y0��
            if ((w - x0) * (w - x0) + (h - y0) * (h - y0) <= 25)//Բ�İ뾶��25����
                lcd_draw_pixel(w, h, 0x000000); //��Բ�ڻ��ƺ�ɫ���ص� 
        }
    }
	//ͬ��Ϊ�����ĸ������Բ��ͼ�� 
    for (int w = x1 - 48; w < x1 + 48; w++)
    {
        for (int h = y1 - 48; h < y1 + 48; h++)
        {
            if ((w - x1) * (w - x1) + (h - y1) * (h - y1) <= 25)
                lcd_draw_pixel(w, h, 0x000000);
        }
    }
    for (int w = x2 - 48; w < x2 + 48; w++)
    {
        for (int h = y2 - 48; h < y2 + 48; h++)
        {
            if ((w - x2) * (w - x2) + (h - y2) * (h - y2) <= 25)
                lcd_draw_pixel(w, h, 0x000000);
        }
    }
    for (int w = x3 - 48; w < x3 + 48; w++)
    {
        for (int h = y3 - 48; h < y3 + 48; h++)
        {
            if ((w - x3) * (w - x3) + (h - y3) * (h - y3) <= 25)
                lcd_draw_pixel(w, h, 0x000000);
        }
    }
    for (int w = x4 - 48; w < x4 + 48; w++)
    {
        for (int h = y4 - 48; h < y4 + 48; h++)
        {
            if ((w - x4) * (w - x4) + (h - y4) * (h - y4) <= 25)
                lcd_draw_pixel(w, h, 0x000000);
        }
    }
    close(lcd_fd);
}
//��ӡ����
void lcd_draw_board()
{
    for (int h = 0; h < 480; h++) //��ӡ���̵ĺ���
    {
        for (int w = 0; w < 496; w++)//��ӡ���̵���
        {
			 //Ϊ���̵�ÿ�����ӻ���һ�����ص㣬��ɫΪ0xa42d00��һ�ֻ�ɫ��
            lcd_draw_pixel(w, h, 0xa42d00);
            //��������̵ı߽�λ�ã�����ƺ�ɫ���ص�
            if (w <= 16)
            {
                lcd_draw_pixel(w, h, 0x000000);
            }
			//�����h��48�ı�������ʾ����һ���µĺ��ߣ�����ƺ�ɫ���ص���Ϊ�ָ���  
            if (h % 48 == 0)
            {
                lcd_draw_pixel(w, h, 0x000000);//�ָ���Ϊ��ɫ 
            }
        }
    }
    for (int w = 0; w < 496; w++) // ��ӡ���̵�����
    {
        for (int h = 0; h < 480; h++)
        {
			//�����w��48�ı�����32����ʾ����һ���µ����ߣ�����ƺ�ɫ���ص���Ϊ�ָ���  
            if ((w + 32) % 48 == 0)
            {
                lcd_draw_pixel(w, h, 0x000000);
            }
        }
    }
	//�ڻ��������̺���ʾ�����ʼ��
    DisPlay_Five_point();
}
//���Ӵ�ӡ�����������������Ϸ������Ӳ���ʾ����ɫ
void LCD_play_chess(int x, int y, int *color, char arr)
{
    lcd_init();
    //���ݴ�����ַ���b��w���ж��Ǻ��廹�ǰ��壬����Ӧ�ػ�������  
    if (arr == 'b')//b������壬��ɫΪ��ɫ 
    {
        for (int w = x - 48; w < x + 48; w++)//�����ӵ���Χ����һ��Բ�����򣨰뾶Ϊ48���أ�Ϊ��ɫ  
        {
            for (int h = y - 48; h < y + 48; h++)
            {
                if ((w - x) * (w - x) + (h - y) * (h - y) <= 125)//����Բ�ĺͰ뾶�ж����ص��Ƿ���Բ��  
                {

                    lcd_draw_pixel(w, h, 0x000000);//��Բ�ڻ��ƺ�ɫ���ص㣬��ʾ�����˺���
                    *color *= -1;//������ɫ״̬����ʾ�Ѿ������˺��壬�´η��ð���
                }
            }
        }
    }
    else if (arr == 'w')//w������壬��ɫΪ��ɫ
    {
        for (int w = x - 48; w < x + 48; w++)//�����ӵ���Χ����һ��Բ�����򣨰뾶Ϊ48���أ�Ϊ��ɫ  
        {
            for (int h = y - 48; h < y + 48; h++)
            {
                if ((w - x) * (w - x) + (h - y) * (h - y) <= 125)
                {

                    lcd_draw_pixel(w, h, 0xffffff);
                    *color *= -1;
                }
            }
        }
    }
}
// ��ʾ��Ϸѡ�Χ
void Show_Game_Options(void)
{
    lcd_init();
	//��ָ�������귶Χ�ڻ��ƺ�ɫ���ص㣬�γ���Ϸѡ��ı����� 
    for (int h = 200; h < 285; h++)
    {
        for (int w = 90; w < 250; w++)
        {
            lcd_draw_pixel(w, h, 0x000000);//���ƺ�ɫ���ص� 
        }
        //����һָ�������귶Χ�ڻ��ƺ�ɫ���ص㣬�γ���һ��������
        for (int h = 200; h < 285; h++)
        {
            for (int w = 500; w < 670; w++)
            {
                lcd_draw_pixel(w, h, 0x000000);
            }
        }
    }
    close(lcd_fd);
}
// ��ӡ��������
void Show_End_Screen(void)
{
    lcd_init();
	//��ӡȫ���ĺ�ɫ����ʾ��Ϸ�Ľ������� 
    for (int h = 0; h < 480; h++) // ��ӡ����
    {
        for (int w = 0; w < 800; w++)
        {
            lcd_draw_pixel(w, h, 0x000000);//���ƺ�ɫ���ص�
        }
    }
    close(lcd_fd);
}
//��ӡͼ
void Show_pictures(int posx, int posy, const char *str)
{
    //lcd_init();
	
    int pic_id = open(str, O_RDONLY);//��ָ����ͼƬ�ļ���ֻ����ʽ
    if (pic_id == -1)//�����ʧ��
    {
        perror("open picture failed");//��ӡ������Ϣ
        return;
    }
    //����һ��4�ֽڵĿռ�ȥ�洢��ȡ��������
    unsigned char data[4] = {0};
    read(pic_id, data, 2);
    //�ж��Ƿ�ΪBMPͼƬ
    if (data[0] != 0x42 || data[1] != 0x4d)
	{
        puts("this picture not bmp file!");
        return;
	}
    //��ȡ���������ƫ��������
    lseek(pic_id, 0x0a, SEEK_SET);//��λ���ļ���0x0Aλ�� 
    read(pic_id, data, 4);//��ȡ4�ֽ�����
    //���ݻ�ԭ��ȡ����С��ģʽ���õ����������ƫ����  
    int offset = data[3] << 24 | data[2] << 16 | data[1] << 8 | data[0];
    
	//��ȡͼƬ��ȣ�������λ���ļ���0x12λ�ã�4�ֽڳ���  
    lseek(pic_id, 0x12, SEEK_SET);
    read(pic_id, data, 4);
    //���ݻ�ԭ��ȡ����С��ģʽ���õ�ͼƬ�Ŀ��
    int width = data[3] << 24 | data[2] << 16 | data[1] << 8 | data[0];
    
	//��ȡͼƬ�߶ȣ������ſ�����ݺ��棬4�ֽڳ���
    read(pic_id, data, 4);
    //���ݻ�ԭ��ȡ����С��ģʽ���õ�ͼƬ�ĸ߶�
    int height = data[3] << 24 | data[2] << 16 | data[1] << 8 | data[0];
    
	//��ȡɫ�������λ���ļ���0x1Cλ�ã�2�ֽڳ���
    lseek(pic_id, 0x1c, SEEK_SET);
    read(pic_id, data, 2);
    //���ݻ�ԭ��ȡ����С��ģʽ���õ�ͼƬ��ɫ�ÿ���ص�λ����  
    int depth = data[1] << 8 | data[0];
    
	printf("��ȣ�%d,�߶ȣ�%d,ɫ�%d\n", width, height, depth);
    //ƫ�Ƶ����������λ��
    lseek(pic_id, offset, SEEK_SET);//��λ����������Ŀ�ʼλ��  
    
	//��������ֽ�������ΪBMPͼƬ��ÿ������������Ҫ��4�ı���������Ļ���Ҫ���  
    int fills = 0;
    
	if ((width * depth / 8) % 4)  //���ÿ���������ݵ��ֽ�������4�ı���  
    {  
        fills = 4 - (width * depth / 8) % 4;  //������Ҫ�����ֽ���  
    }  
  
    //ʵ��һ�е��ֽ��������������ֽ���  
    int real_width = width * depth / 8 + fills;  
  
    //�������������Ĵ�С����ʵ��һ�е��ֽ�������ͼƬ�ĸ߶ȣ�����ֵ��  
    int pixel_array_size = real_width * abs(height);  
  
    //��ȡ������������ݣ�malloc������Ӧ��С���ڴ�ռ�  
    unsigned char *color_point = malloc(sizeof(char) * pixel_array_size);  
    printf("���������С%d\n", pixel_array_size);  //��ӡ��������Ĵ�С  
    if (color_point == NULL)  //����ڴ����ʧ��  
    {  
        printf("error !!!!!!!!!!!!!\n");  //��ӡ������Ϣ  
    }

    read(pic_id, color_point, pixel_array_size);
    //��ʾͼƬ
    int i = 0;
    for (int h = 0; h < abs(height); h++)
    {
        for (int w = 0; w < width; w++)
        {
            unsigned char a, r, g, b;
            b = color_point[i++];
            g = color_point[i++];
            r = color_point[i++];
            a = depth == 24 ? 0 : color_point[i++];
            //������ɫ
			//����ɫֵ����Ϊһ��32λ����������ʽΪARGB
            int color = a << 24 | r << 16 | g << 8 | b;
			//��LCD�ϻ�һ�����أ�λ����x��yȷ������ɫΪ�������ϵ���ɫֵ
            lcd_draw_pixel(w + posx, ((height < 0) ? h : height - 1 - h) + posy, color);
        }
        // ÿһ�н�����������ֽ�
        i = i + fills;}//���µ���һ����Ҫ���Ƶ����ص�λ�ã�ͬʱ�����˿��ܵ�����ֽ�  
    //�ͷ��ڴ�
	free(color_point);
    close(pic_id);
}

//�������´�ӡ�ò��ֵ�����
//���ָ��λ����Χ��24x24�����ڵ�LCD���ݣ��������������λ������Ϊ��ɫ  
//����x��yָ�����������ʼλ��  
void Display_retract_false(int x, int y)
{
    lcd_init();
    //ѭ������ָ�������ÿ�����أ����������  
    for (int w = x - 24; w < x + 24; w++)
    {
        for (int h = y - 24; h < y + 24; h++)
        {
            lcd_draw_pixel(w, h, 0xa42d00);
        }
    }
    //��ָ��λ�û�һ����ɫ�Ĵ�ֱ��
    for (int w = x - 24; w < x + 24; w++)
    {
        lcd_draw_pixel(w, y, 0x000000);
    }
    //��ָ��λ�û�һ����ɫ��ˮƽ�� 
    for (int h = y - 24; h < y + 24; h++)
    {
        lcd_draw_pixel(x, h, 0x000000);
    }

    close(lcd_fd);
}
//��ʼ��LCD����ӡ���̣�Ȼ��ر�LCD���� 
void LCD_board_dispaly(void)
{
    //lcd_init();       //LCD��ʼ��
    lcd_draw_board(); //��ӡ����
    //close(lcd_fd);
}
//��ӡ��¼��ĵ÷�
//����count��ֵ��ʾ�ڷ��ĵ÷ֻ�״̬��LCD�� 
void LCD_Dispaly_Black_Recording_Board(int count)
{
    if (count == 1)
    {
        Show_pictures(560, 15, "/home/zz/bmp/wuziqi_8.bmp");
    }
    else if (count == 2)
    {
        Show_pictures(560, 15, "/home/zz/bmp/wuziqi_9.bmp");
    }
    else if (count == 3)
    {
        Show_pictures(560, 15, "/home/zz/bmp/wuziqi_10.bmp");
    }
    else if (count == 4)
    {
        Show_pictures(560, 15, "/home/zz/bmp/wuziqi_11.bmp");
    }
    else if (count == 5)
    {
        Show_pictures(560, 15, "/home/zz/bmp/wuziqi_12.bmp");
    }
}
//����count��ֵ��ʾ�׷��ĵ÷ֻ�״̬��LCD�ϣ�����һ���������ƣ���λ�ò�ͬ
void LCD_Dispaly_white_Recording_Board(int count)
{
    if (count == 1)
    {
        Show_pictures(705, 20, "/home/zz/bmp/wuziqi_8.bmp");
    }
    else if (count == 2)
    {
        Show_pictures(705, 15, "/home/zz/bmp/wuziqi_9.bmp");
    }
    else if (count == 3)
    {
        Show_pictures(705, 15, "/home/zz/bmp/wuziqi_10.bmp");
    }
    else if (count == 4)
    {
        Show_pictures(705, 15, "/home/zz/bmp/wuziqi_11.bmp");
    }
    else if (count == 5)
    {
        Show_pictures(705, 15, "/home/zz/bmp/wuziqi_12.bmp");
    }
}
