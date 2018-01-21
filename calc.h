#ifndef _CALC_H_
#define _CALC_H_

#include "inttypes.h"

#define COUNT_FILTER    512
#define COUNT_RSHIFT    9

typedef union
{
   uint32_t Val;
   struct
   {
        uint32_t Flag:1;       //���� ���������� �����
        uint32_t Index;       //�������� ������� ������
        uint32_t Filter_sum; //������� ����� ��� ����������
    }Reg;
} FILTER_REG;

void CalcInit();
void CalcUpdate();
void CalcSendData();
uint8_t CalcGetCharge();

#endif
