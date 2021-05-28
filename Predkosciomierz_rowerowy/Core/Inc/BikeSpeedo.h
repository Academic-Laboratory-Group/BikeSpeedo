#ifndef _BIKESPEEDO_H_
#define _BIKESPEEDO_H_

#include "stm32f4xx_hal.h"

enum States
{
	MAINMENU,
	CONFIGURATION,
	VELOCITY
};

void processInput(void);
void init(void);
void updateVelocityValue(int time);

#endif
