#include "login.h"
#include "picture.h"
#include "touch.h"

int k=0,flag=0;
//************����������******************
//������������x��ֵ
//����ֵ���ɹ�����1 ʧ�ܷ���0 
int show_hua(int t_x)
{
    for(int y=400;y<430;y++)
    {
        for(int x=0;x<800;x++)
        {
            if(x>t_x-50&&x<t_x+50)//С�̰�
            {
                point(x, y,0x0000ff00);  // ��ɫ����
            }
            else//��С�̰�û�о����ı�ɺ�ɫ
            {
                point(x, y, 0x00000000);// ��ɫ����
            }
            if(x<=t_x-50)//��С�̰徭���Ķ������ɫ
            {
                point(x, y,0x0000ff00); // ��������ɫ����
            }          
        }
    }
    //����������Ҫ�й���
    if(t_x>=100&&t_x<=200)
    {
        if(flag == 0 )
        {
            k++;
            flag++;
        }
    }
    if( t_x>=300&&t_x<=400)
    {
        if(flag == 1 )
        {
            k++;
            flag++;
        }
    }
    if( t_x>=500&&t_x<=600)
    {
        if(flag == 2 )
        {
            k++;
            flag++;
        }
    }
    if( t_x>=610&&t_x<=700)
    {
        if(flag == 3 )
        {
            k++;
            flag++;
        }
    }
    //�ж��Ƿ�����ɹ�
    if(t_x>=600&&k==4)
    {
        printf("�����ɹ�\n");
        return 1;
    }
    return 0;
}



/**
 * @brief ��ȡ������ֵ������������
 * 
 * @param x ��������
 * @param y ��������
 * @return UNLOCK_KEY ���ؼ�ֵ
 */
static UNLOCK_KEY unlock_GetKey(int x, int y)
{ 
    printf("����ȷ�Ϻ���x,y--(%d  %d )",x,y);
  /* ȷ�ϼ� */
    if(( x >= UNLOCK_CONFIRM_X_START ) && ( x <= UNLOCK_CONFIRM_X_END ) &&
        ( y >= UNLOCK_CONFIRM_Y_START ) && ( y <= UNLOCK_CONFIRM_Y_END ))
    {
        return UNLOCK_CONFIRM;
        printf("confirm\n");
    }
    
  /* ���ؼ� */
    else if(( x >= UNLOCK_BS_X_START ) && ( x <= UNLOCK_BS_X_END ) &&
            ( y >= UNLOCK_BS_Y_START ) && ( y <= UNLOCK_BS_Y_END ))
    {
        return UNLOCK_BS;
        printf("backspace\n");
    }
    

  /* 0 */
    else if(( x >= UNLOCK_0_X_START ) && ( x <= UNLOCK_0_X_END ) &&
            ( y >= UNLOCK_0_Y_START ) && ( y <= UNLOCK_0_Y_END ))
    {
        return UNLOCK_0;
        printf("key 0\n");
    }

  /* 1 */
    else if(( x >= UNLOCK_1_X_START ) && ( x <= UNLOCK_1_X_END ) &&
            ( y >= UNLOCK_1_Y_START ) && ( y <= UNLOCK_1_Y_END ))
    {
        return UNLOCK_1;
        printf("key 1\n");
    }

  /* 2 */
    else if(( x >= UNLOCK_2_X_START ) && ( x <= UNLOCK_2_X_END ) &&
            ( y >= UNLOCK_2_Y_START ) && ( y <= UNLOCK_2_Y_END ))
    {
        return UNLOCK_2;
        printf("key 2\n");
    }

  /* 3 */
    else if(( x >= UNLOCK_3_X_START ) && ( x <= UNLOCK_3_X_END ) &&
            ( y >= UNLOCK_3_Y_START ) && ( y <= UNLOCK_3_Y_END ))
    {
        return UNLOCK_3;
        printf("key 3\n"); 
    }

  /* 4 */
    else if(( x >= UNLOCK_4_X_START ) && ( x <= UNLOCK_4_X_END ) &&
            ( y >= UNLOCK_4_Y_START ) && ( y <= UNLOCK_4_Y_END ))
    {
        return UNLOCK_4;
        printf("key 4\n");  
    }
    
    
  /* 5 */
    else if(( x >= UNLOCK_5_X_START ) && ( x <= UNLOCK_5_X_END ) &&
            ( y >= UNLOCK_5_Y_START ) && ( y <= UNLOCK_5_Y_END ))
    {
        return UNLOCK_5;
        printf("key 5\n");  
    }
    

  /* 6 */
    else if(( x >= UNLOCK_6_X_START ) && ( x <= UNLOCK_6_X_END ) &&
            ( y >= UNLOCK_6_Y_START ) && ( y <= UNLOCK_6_Y_END ))
    {
        return UNLOCK_6;
        printf("key 6\n"); 
    }

  /* 7 */
    else if(( x >= UNLOCK_7_X_START ) && ( x <= UNLOCK_7_X_END ) &&
            ( y >= UNLOCK_7_Y_START ) && ( y <= UNLOCK_7_Y_END ))
    {
        return UNLOCK_7;
        printf("key 7\n"); 
    } 
    

  /* 8 */
    else if(( x >= UNLOCK_8_X_START ) && ( x <= UNLOCK_8_X_END ) &&
            ( y >= UNLOCK_8_Y_START ) && ( y <= UNLOCK_8_Y_END ))
    {
        return UNLOCK_8;
        printf("key 8\n"); 
    }

  /* 9 */
    else if(( x >= UNLOCK_9_X_START ) && ( x <= UNLOCK_9_X_END ) &&
            ( y >= UNLOCK_9_Y_START ) && ( y <= UNLOCK_9_Y_END ))
    {
        return UNLOCK_9;
        printf("key 9\n");
    }
    
    return UNLOCK_NONE;
}


//*************�����������*****************
bool pass = false;  /* ������ȷ�ı�־ */
// ����ֵ--ture or false ֻ�н�����ɲŻ᷵��ture
bool unlock_passward()
{    
    UNLOCK_KEY key;  /* ���� */
    int pass_pos = 0;   /* һ�������λ */
    char dis_password_buf[UNLOCK_WORD_LEN+1] = {0}; /* ������ʾ������ */
    char password_buf[UNLOCK_WORD_LEN+1] = {0};//����
    TouchPoint tc;//����״̬--�����벻����--2s
    
    int FB_x, FB_y;   /* ��������ͼ����ʾ������ */
    if(pass==false)
    {
        while(1)
        {
            tc=Get_TouchPosition();//���հ���״̬�Լ���������
            show_bmp(UNLOCK_WALLPAPER_PATH,0,0,0);
            switch (tc.is_long_press)
            {
            case 0://û�г���
                key = unlock_GetKey(tc.x*800/1024,tc.y*480/600);
                //key = unlock_GetKey((tc.x*800/600),(tc.y*480/600));//��ȡ����ֵ
                //--------����ʱ---
                switch (key)  
                {
                    case UNLOCK_0:/* switch(key) "ȷ���û������ֵ" */
                    if (pass_pos < UNLOCK_WORD_LEN)
                    {
                        strcat(password_buf, "0");
                        strcat(dis_password_buf, "*");
                        pass_pos++;
                    }
                    
                    break;
                    case UNLOCK_1:
                    if (pass_pos < UNLOCK_WORD_LEN)
                    {
                        strcat(password_buf, "1");
                        strcat(dis_password_buf, "*");
                        pass_pos++;
                    }

                    break;

                    case UNLOCK_2:
                    if (pass_pos < UNLOCK_WORD_LEN)
                    {
                        strcat(password_buf, "2");
                        strcat(dis_password_buf, "*");
                        pass_pos++;
                    }

                    break;

                    case UNLOCK_3:
                    if (pass_pos < UNLOCK_WORD_LEN)
                    {
                        strcat(password_buf, "3");
                        strcat(dis_password_buf, "*");
                        pass_pos++;
                    }

                    break;

                    case UNLOCK_4:
                    if (pass_pos < UNLOCK_WORD_LEN)
                    {
                        strcat(password_buf, "4");
                        strcat(dis_password_buf, "*");
                        pass_pos++;
                    }

                    break;

                    case UNLOCK_5:
                    if (pass_pos < UNLOCK_WORD_LEN)
                    {
                        strcat(password_buf, "5");
                        strcat(dis_password_buf, "*");
                        pass_pos++;
                    }

                    break;

                    case UNLOCK_6:
                    if (pass_pos < UNLOCK_WORD_LEN)
                    {
                        strcat(password_buf, "6");
                        strcat(dis_password_buf, "*");
                        pass_pos++;
                    }

                    break;

                    case UNLOCK_7:
                    if (pass_pos < UNLOCK_WORD_LEN)
                    {
                        strcat(password_buf, "7");
                        strcat(dis_password_buf, "*");
                        pass_pos++;
                    }

                    break;

                    case UNLOCK_8:
                    if (pass_pos < UNLOCK_WORD_LEN)
                    {
                        strcat(password_buf, "8");
                        strcat(dis_password_buf, "*");
                        pass_pos++;
                    }

                    break;
                    case UNLOCK_9:
                    if (pass_pos < UNLOCK_WORD_LEN)
                    {
                        strcat(password_buf, "9");
                        strcat(dis_password_buf, "*");
                        pass_pos++;
                    }

                    break;
                    
                    case UNLOCK_CONFIRM:
                        if (pass_pos == UNLOCK_WORD_LEN)
                        {
                            printf("cmp...\n");
                            if( strcmp(password_buf, UNLOCK_PASSWORD) == 0 )
                            {
                            printf("passwd true\n");
                            pass = true;
                            }
                            else
                            {
                            printf("passwd error\n");
                            for(char i=0; i<UNLOCK_WORD_LEN; i++)
                            {
                                password_buf[i] = '\0';
                                dis_password_buf[i] = '\0';
                            }
                            pass_pos = 0;
                            }
                        }
                    break;
                    case UNLOCK_BS:
                        if (pass_pos > 0)
                        {
                            password_buf[pass_pos-1] = '\0';
                            dis_password_buf[pass_pos-1] = '\0';
                            pass_pos--;
                        }
                    break;
                    
                    default:

                    break;
                    
                }
                /* end switch(key) "ȷ���û������ֵ" */
                    printf("pass_pos\t%d\n", pass_pos);
                    printf("passwd:\t%s\n", password_buf);
                    printf("dispasswd:\t%s\n", dis_password_buf);
                    ///* ˢ��ͼ�� */
                    //show_bmp(UNLOCK_WALLPAPER_PATH,0,0,1);
                
            break;      //case 0 ������
            // -----����----��ʾͼƬ��Ч
            case 1:
                    key = unlock_GetKey((tc.x*800/600),(tc.y*480/600));//��ȡ����ֵ
                    switch (key)  /* switch(key) "ȷ����������ͼ����ʾ��λ��" */
                    {/* ���ݼ�ֵȷ����������ͼ����ʾ������ */
                        case UNLOCK_0:
                            FB_x = UNLOCK_0_X_START + UNLOCK_FB_DELTA_X;
                            FB_y = UNLOCK_0_Y_START + UNLOCK_FB_DELTA_Y;
                            break;
                        
                        case UNLOCK_1:
                            FB_x = UNLOCK_1_X_START + UNLOCK_FB_DELTA_X;
                            FB_y = UNLOCK_1_Y_START + UNLOCK_FB_DELTA_Y;
                            break;

                        case UNLOCK_2:
                            FB_x = UNLOCK_2_X_START + UNLOCK_FB_DELTA_X;
                            FB_y = UNLOCK_2_Y_START + UNLOCK_FB_DELTA_Y;
                            break;

                        case UNLOCK_3:
                            FB_x = UNLOCK_3_X_START + UNLOCK_FB_DELTA_X;
                            FB_y = UNLOCK_3_Y_START + UNLOCK_FB_DELTA_Y;
                            break;

                        case UNLOCK_4:
                            FB_x = UNLOCK_4_X_START + UNLOCK_FB_DELTA_X;
                            FB_y = UNLOCK_4_Y_START + UNLOCK_FB_DELTA_Y;
                            break;

                        case UNLOCK_5:
                            FB_x = UNLOCK_5_X_START + UNLOCK_FB_DELTA_X;
                            FB_y = UNLOCK_5_Y_START + UNLOCK_FB_DELTA_Y;
                            break;

                        case UNLOCK_6:
                            FB_x = UNLOCK_6_X_START + UNLOCK_FB_DELTA_X;
                            FB_y = UNLOCK_6_Y_START + UNLOCK_FB_DELTA_Y;
                            break;

                        case UNLOCK_7:
                            FB_x = UNLOCK_7_X_START + UNLOCK_FB_DELTA_X;
                            FB_y = UNLOCK_7_Y_START + UNLOCK_FB_DELTA_Y;
                            break;

                        case UNLOCK_8:
                            FB_x = UNLOCK_8_X_START + UNLOCK_FB_DELTA_X;
                            FB_y = UNLOCK_8_Y_START + UNLOCK_FB_DELTA_Y;
                            break;
                        
                        case UNLOCK_9:
                            FB_x = UNLOCK_9_X_START + UNLOCK_FB_DELTA_X;
                            FB_y = UNLOCK_9_Y_START + UNLOCK_FB_DELTA_Y;
                            break;
                            
                        case UNLOCK_CONFIRM:
                            FB_x = UNLOCK_CONFIRM_X_START + UNLOCK_FB_DELTA_X;
                            FB_y = UNLOCK_CONFIRM_Y_START + UNLOCK_FB_DELTA_Y;
                            break;

                        case UNLOCK_BS:
                            FB_x = UNLOCK_BS_X_START + UNLOCK_FB_DELTA_X;
                            FB_y = UNLOCK_BS_Y_START + UNLOCK_FB_DELTA_Y;
                            break;
                        
                        default:
                            FB_x = 400;
                            FB_y = 140;
                            break;
                    }
                    /* end switch(key) "ȷ����������ͼ����ʾ��λ��" */
                    //show_bmp(UNLOCK_WALLPAPER_PATH,0,0,1);//����ͼ
                    show_bmp(UNLOCK_FEEDBACK_PATH,FB_x,FB_y,0);//����ͼ
                    usleep(2000);//����û�з�������Ҫ����

            break;//case 1 ����
            
            default:
                //show_bmp(UNLOCK_WALLPAPER_PATH,0,0,1);//����ͼ
                break;
            }
            /* ������ȷ���˳���ѭ�� */
            if( pass )
            {
                break;
            }
        }
    } 
/*----------------- while(1) end-pass----------------------- */

    return true;

}
