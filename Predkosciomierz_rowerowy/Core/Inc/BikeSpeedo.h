#ifndef _BIKESPEEDO_H_
#define _BIKESPEEDO_H_

#include "stm32f4xx_hal.h"

void Update(void);
void Show_Main(void);
void Show_Config(void);
void Update_Config();
void Show_Speed(void);
void Update_Speed(uint32_t time);
void Update_Chart(uint32_t speed);

#endif
