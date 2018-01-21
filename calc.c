#include "calc.h"
#include "adc.h"
#include "utility.h"

uint8_t* pu8_result;
uint16_t u16_result;
uint8_t charge;

uint16_t adc_buf_a[COUNT_FILTER];
FILTER_REG reg_a;

uint8_t i_send;

static uint16_t  filter_sred(uint16_t adc_val,uint16_t* buf, FILTER_REG* filter_reg)
{
    if (filter_reg->Reg.Flag)
    {
        filter_reg->Reg.Filter_sum-=buf[filter_reg->Reg.Index];
        filter_reg->Reg.Filter_sum+=adc_val;
        buf[filter_reg->Reg.Index]=adc_val;
        if (filter_reg->Reg.Index>=COUNT_FILTER-1)  filter_reg->Reg.Index=0;
        else      									filter_reg->Reg.Index++;
    }
    else
    {
        filter_reg->Reg.Filter_sum+=adc_val;
        buf[filter_reg->Reg.Index]=adc_val;
        if (filter_reg->Reg.Index>=COUNT_FILTER-1)
        {
            filter_reg->Reg.Index=0;
            filter_reg->Reg.Flag=1;
        }
        else filter_reg->Reg.Index++;
    }
    return (filter_reg->Reg.Filter_sum >> COUNT_RSHIFT);
}

void CalcInit()
{
	pu8_result =(uint8_t*) &u16_result;
	for(uint16_t i = 0; i< COUNT_FILTER;i++) CalcUpdate();
}

/*void CalcSendData()
{
	for(i_send = 0;i_send < 4; i_send++)
		UsartSend(USART1,pu8_result[i_send]);
}*/

uint8_t buf;
void CalcUpdate()
{
	u16_result =  filter_sred(AdcGet(),adc_buf_a,&reg_a);
	if(u16_result > 1706) 	buf = (uint8_t)((float)(u16_result - 1706)/5.7f);
	else 					charge = 0;
	if(buf > 100) charge = 100;
	else		  charge = buf;
}

uint8_t CalcGetCharge(){ return charge; }
