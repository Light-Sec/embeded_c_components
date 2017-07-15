#ifndef __COMMON_H
#define __COMMON_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HI_UINT16(a) (((a) >> 8) & 0xFF)
#define LO_UINT16(a) ((a) & 0xFF)

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) < (b) ? (b) : (a))

#define IS_POWER_OF_TWO(A) ( ((A) != 0) && ((((A) - 1) & (A)) == 0) )


//��lengthת��Ϊ��word���㵥λ
#define ROUND_UP_WORDS_COUNT(length, unit) (((length) -1)/(unit) + 1)

//���������С
#define ARRAY_LEN(a)            (sizeof(a)/sizeof(a[0]))


//����ָ��
typedef void (*timer_init_callback_t)(void);                    //���ⲿʵ�� 1�������Զ�ʱ����ʼ��
typedef void (*timer_restart_callback_t)(uint32_t ms_interval); //���ⲿʵ�� 1�������Զ�ʱ��������
typedef void (*timer_hander_callback_t)(void);                  //���ⲿʵ�� 1�������Զ�ʱ����timeout hander


//���⺯���ӿ�


#ifdef __cplusplus
}
#endif

#endif
