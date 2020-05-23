#ifndef __ADC_H__
#define __ADC_H__

extern ADC_HandleTypeDef hadc1;

int MX_ADC1_Init(void);
float Adc_getVoltage(uint32_t channel);

#endif // !__ADC_H__
