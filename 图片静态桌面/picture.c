#include "picture.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>




//unsigned int* back_buffer = NULL;//һ����̨buffer,��������Ƶ��������Ļ
unsigned char color_buf;
//*************����ĺ���********************
void point(int x, int y, unsigned int color) 
{
    if (x >= 0 && x < 800 && y >= 0 && y < 480) 
    {
        *(plcd + y * 800 + x) = color;
    }
}


//*****************��ӱ�����ɫ-color************
void display_bgm(int color) {
    int w =800,h=480;
    int x, y;
    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            point(x , y , color);
        }
    }
}

//��������������������������������������ʾͼƬ�ĺ�����������������
//1. ������У�����lcd��С��ͼƬ��Ҫ����
//2. �ض�С��ͼƬ������Ҫ������ʾ
//��������� 1. ͼƬ���� 2. ���꣺xy 3. �Ƿ���Ҫ������ʾ
// choice �� 1--��Ҫ������ʾ  0--����Ҫ������ʾ
void show_bmp(const char* filename, int x0,int y0,char choice)
{

    //1.��bmp�ļ�
    int bmp_fd = open(filename, O_RDONLY);
    if(-1 == bmp_fd)
    {
        perror("open bmp error");
        return;
    }
    //2. �ж��Ƿ������bmp�ļ�
    unsigned char buf[2];
    read(bmp_fd,buf,2);
    if(buf[0]!=0x42 || buf[1]!= 0x4d)//�����ͷ����BM ��ASCII������BMP�ļ�
    {
        printf("NOT a BMP !!\n");
        return ;
    }
    //3.��ȡͼƬ����
    int width,height,depth;
    lseek(bmp_fd,0x12,SEEK_SET);
    read(bmp_fd,&width,4);//�ĸ��ֽ�--���
    read(bmp_fd,&height,4);//�߶�--���Լ������¶�
    lseek(bmp_fd,0x1c,SEEK_SET);
    read(bmp_fd,&depth,4);//Ҳ������2���ֽ�
    //ֻ֧��ɫ��24��32
    if(!(depth == 24 || depth == 32))
    {
        printf("NOT Support!\n");
        return;
    }
    //printf("width = %d height = %d depth = %d \n", width,height,depth);
    //4.������е����
    if (1 == choice)//��Ҫ������ʾ
    {
        display_bgm(0xFFFFFF);//������ʾ��Ҫ����������ˢ��������ɫ
        if(width<800||height<480)
        {
            x0 = (int)(800-width)/2;
            y0 = (int)(480-height)/2;
        }
    }

    //5.��ȡ��������
    int line_valid_bytes = abs(width)*depth/8;//ÿһ���������ݵ���Ч�ֽ���
    int line_bytes;//ÿ�е����ֽ���
    int laizi=0;
    if(line_valid_bytes%4)//�����ĸ������ֽ�
    {
        laizi = 4-line_valid_bytes%4;
    }
    line_bytes = line_valid_bytes+laizi;

    int total_bytes = line_bytes*abs(height);//������������Ĵ�С
    unsigned char *piexl = (unsigned char *)malloc(total_bytes);
    lseek(bmp_fd,54,SEEK_SET);
    read(bmp_fd,piexl,total_bytes);

    //6.ʹ���������黭ͼ
    unsigned char a,r,g,b;
    unsigned char a1,r1,g1,b1;
    unsigned char *p = color_buf;   //Ϊ�˷���������ݣ�ͨ��ָ��p������
    int color = 0;
    int i=0;
    int x;
    int y;
    for( y=0; y<abs(height); y++)
    {
        for( x=0;x<abs(width);x++)
        {
            //a  r  g  b  0xargb
            b=piexl[i++];
            g=piexl[i++];
            r=piexl[i++];
         
            if(depth == 32)
            {
                a=piexl[i++];
                
            }
            else
            {
                a=0;//͸����
              
            }
            color=(a<<24)|(r<<16)|(g<<8)|(b);
            //����Ļ�ϻ���
            point(width>0?x0+x:x0+abs(width)-x-1,height>0?y0+abs(height)-y-1:y0+y,color);
        }
        i+=laizi;//��ÿһ�е�ĩβ�������
    }
    //update_screen();
    free(piexl);
    close(bmp_fd);
}

//**************��һ������*****************//
void Displaysql(int w, int h, int x0, int y0,unsigned int color)
{
	int x, y;
	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w; x++)
		{
			point(x + x0, y + y0, color);
		}
	}
}

//*****************��һ��Ȧ*********************//
void Displaycir(int x0,int y0,int r,unsigned int color)
{
    for (int y = y0-r; y < y0+r; y++)
    {
        for (int x = x0-r; x < x0+r; x++)
        {
            if ((y-y0)*(y-y0)+(x-x0)*(x-x0) <= r*r)
            {
                //�����ص���Բ�ڼ�Բ�ϵĵ�
                point(x,y,color);
            }
        }
    }
}

/***************** ��Ч���� ******************/
//****************��ͨ��Ч******************
void DisplayNo(int width, int height, int x0, int y0, unsigned int *color)
{
	int x, y, i = 0;
	for (y = height - 1 + y0; y >= y0; y--)
	{
		usleep(10);
		for (x = x0; x < x0 + width; x++)
		{
            point(x, y, color[i++]); 
			//*(plcd + y * 800 + x) = color[i++];
		}		
	}
}
//********************* ������Ч*****************//
void DisplayDelay(int width, unsigned int *color)
{
	int x, y, num;

	for (int i = 3; i > 0; i--)
	{
		for (int j = 0; j < 5; j++)
		{
			for (y = (i * 160) - 1; y >= (i - 1) * 160; y--)
			{
				for (x = j * 160; x < (j + 1) * 160; x++)
				{
					num = y * width + x;
                    point(x, 480-1 -y, color[num]) ;
					//*(plcd + y * 800 + x) = color[num];
				}		
			}
			usleep(5 * 1000 * 10);
		}
	}

}

//*********** ԲȦ��Ч  ******************//
void DisplayCircle(int width, int height, int x0, int y0,unsigned int* color)
{
	int radios = 0, MaxRadios;
	int x, y, i = 0;

	if(800 - x0 >= 400){
		x = 800 - x0;
	}
	else{
		x = x0;
	}

	if(480 - x0 >= 240){
		y = 480 - y0;
	}
	else{
		y = y0;
	}

	MaxRadios = (int)sqrt(pow(x, 2) + pow(y, 2)) + 1;
	printf("���ĵ�����Ļ��Զ����Ϊ��%d\n", MaxRadios);

	while (radios <= MaxRadios+50)
	{
		i = 0;
		for (y = height - 1-y; y >= 0; y--)
		{
			for (x = 0; x < width; x++)
			{
				if(sqrt(pow((x-x0), 2) + pow((y-y0), 2)) < radios){
					//*(plcd + y * 800 + x) = color[i];
                    point(x, y, color[i]) ;
				}
				i++;
			}
		}
		radios += 100;
		usleep(5);
	}
}
void Display_4(int width, int height, int x0, int y0, unsigned int *color)
{
	int x, y, i = 0;
	for (y = height - 1 + y0; y >= y0; y--)
	{
		usleep(50);
		for (x = x0; x < x0 + width; x++)
		{
            point(x, y, color[i++]); 
			//*(plcd + y * 800 + x) = color[i++];
		}		
	}
}


//*******************��ЧͼƬ��ʾ����********//
void DisplayBmpPicVideo(const char *pic, int state)
{
	int fd = open(pic, O_RDONLY);
	if (-1 == fd)
	{
		perror("open error");
		return;
	}
	//�ж����ͼƬ�ǲ������bmp�ļ�
	int width, height, depth=0;
	//��ȡ��ȣ���ƫ����ƫ�Ƶ����
	lseek(fd, 0x12, SEEK_SET);
	read(fd, &width, 4);
	read(fd, &height, 4);

	lseek(fd, 0x1c, SEEK_SET);//ɫ��
	read(fd, &depth, 2);
	//����Ƚϴ���ò��ö�̬����
	int n = (4 - width * (depth / 8) % 4) % 4;
	unsigned char* colorbuf = malloc((width * (depth / 8) + n) * height);
	unsigned int* colordata = malloc(width * height * sizeof(unsigned int));
	//���������������˵ ƫ�ƹ�ͷ��������������
	lseek(fd, 0x36, SEEK_SET);
	read(fd, colorbuf, (width * (depth / 8) + n) * height);

	//�õ�ÿһ�����ص��argb
	unsigned char c_a=0, c_r, c_b ,c_g;
	unsigned int color;
	int i = 0,j = 0;
	int x, y;
	for (y = 0 ; y <=height - 1 ; y++)
	{
		for (x = 0; x < width; x++)
		{
			c_b = colorbuf[i++];
			c_g = colorbuf[i++];
			c_r = colorbuf[i++];
			if(32==depth)
				c_a = colorbuf[i++];
			colordata[j++] = c_a << 24 | c_r << 16 | c_g << 8 | c_b;
		}
		i += n;//ÿ������һ�о�Ҫ����n���ֽ�
	}

	switch (state)
	{
	case 1:
		DisplayNo(width, height, (800 - width)/2, (480 - height)/2, colordata);
	break;
	case 2:
		DisplayDelay(width, colordata);
	break;
	case 3:
		DisplayCircle(width,height, 400, 240, colordata);
	break;
	case 4:
		Display_4(width,height, (800 - width)/2, (480 - height)/2, colordata);
	break;
	default:
		
	break;
	}

	free(colorbuf);
	free(colordata);


	close(fd);
}

TouchDir dir;

void ShowPicture(void)
{    
	while (1)
	{   
	    system("madplay /home/zz/MP3/photo.mp3 &"); 	
	    DisplayBmpPicVideo("/home/zz/bmp/photo_1.bmp", 1);
	    sleep(1);
	    char path[48]={0}; 
	    int k=1,l=4;
	    for(k=2;k<=5;k++){
	    	sprintf(path,"/home/zz/bmp/photo_%d.bmp",k);
	    	DisplayBmpPicVideo(path, l);
	    	if(l>0){
	      	l--;
			}
	    	sleep(2);
		}
		system("killall -9 madplay");
		break;
		}
	    //show_bmp("/home/zz/bmp/lockx.bmp",0,0,1);
	}


