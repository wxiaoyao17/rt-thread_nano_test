#include "config.h"
#include "iwdg.h"
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//�������Ź���������
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2017/4/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

IWDG_HandleTypeDef IWDG_Handler; //�������Ź����

//��ʼ���������Ź�
//prer:��Ƶ��:IWDG_PRESCALER_4~IWDG_PRESCALER_256
//rlr:�Զ���װ��ֵ,0~0XFFF.
//ʱ�����(���):Tout=((4*2^prer)*rlr)/32 (ms).
// eg: IWDG_Init(IWDG_PRESCALER_64,500);  	//��Ƶ��Ϊ64,����ֵΪ500,���ʱ��Ϊ1s
int IWDG_Init(uint8_t prer, uint16_t rlr)
{
    IWDG_Handler.Instance = IWDG;
    IWDG_Handler.Init.Prescaler = prer; //����IWDG��Ƶϵ��
    IWDG_Handler.Init.Reload = rlr;     //��װ��ֵ
    HAL_IWDG_Init(&IWDG_Handler);       //��ʼ��IWDG,Ĭ�ϻῪ���������Ź�

    return 0;
}

// INIT_BOARD_EXPORT(IWDG_Init);

//ι�������Ź�
void IWDG_Feed(void)
{
    HAL_IWDG_Refresh(&IWDG_Handler); //ι��
}
