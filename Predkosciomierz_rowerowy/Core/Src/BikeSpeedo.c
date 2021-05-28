#include "BikeSpeedo.h"
#include "LCD_Touch.h"
#include "Debug.h"
#include "tim.h"
#include "Utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <assert.h>


float g_wheelSize = 0.0f;
float g_newWheelSize = 0.0f;
int g_STATE = MAINMENU;
int g_xNew = 0;
int g_yNew = 0;
int g_xOld = 0;
int g_yOld = 0;
#define PI 3.14


void showMain(void)
{
    LCD_Clear(LCD_BACKGROUND);
    if(sLCD_DIS.LCD_Dis_Column > sLCD_DIS.LCD_Dis_Page) 
		{
			GUI_DisString_EN(40, 20, "BikeSpeedo", &Font24, WHITE, BLUE);
			GUI_DrawLine(0, 55, LCD_WIDTH, 55, RED, LINE_SOLID, DOT_PIXEL_3X3);
			GUI_DrawRectangle(40, 120, 215, 190, RED, DRAW_EMPTY, DOT_PIXEL_2X2);
			GUI_DrawRectangle(262, 120, 440, 190, RED, DRAW_EMPTY, DOT_PIXEL_2X2);
			GUI_DisString_EN(72, 147, "VELOCITY", &Font20, WHITE, BLUE);
			GUI_DisString_EN(315, 147, "SETUP", &Font20, WHITE, BLUE);
			GUI_DisString_EN(170, 270, "Realised by:", &Font16, WHITE, BLUE);
			GUI_DisString_EN(220, 285, "Eng. Krzysztof Pokora", &Font16, WHITE, BLUE);
			GUI_DisString_EN(220, 300, "Eng. Norbert Ligas", &Font16, WHITE, BLUE);
    } 
}

void showConfig(void)
{		
    LCD_Clear(LCD_BACKGROUND);
    if(sLCD_DIS.LCD_Dis_Column > sLCD_DIS.LCD_Dis_Page) 
		{
			GUI_DisString_EN(33, 20, "BikeSpeedo", &Font24, WHITE, BLUE);
			GUI_DrawLine(0, 55, LCD_WIDTH, 55, RED, LINE_SOLID, DOT_PIXEL_3X3);
			
			GUI_DisString_EN(15, 80, "Set size of wheel", &Font20, WHITE, BLUE);	
			GUI_DrawRectangle(40, 120, 150, 160, RED, DRAW_EMPTY, DOT_PIXEL_2X2);
			
			int size = snprintf(0, 0, "%.2f", g_wheelSize); // wheel size float to string
			char str[size + 1];
			snprintf(str, sizeof(str), "%.2f", g_wheelSize);
			GUI_DisString_EN(45, 132, str, &Font20, WHITE, BLUE);	
			
			GUI_DisString_EN(170, 132, "inches.", &Font20, WHITE, BLUE);	
			GUI_DisString_EN(380, 145, "<", &Font24, WHITE, BLUE);	
			GUI_DisString_EN(25, 220, "0  1  2  3  4  5  6  7  8  9  .", &Font20, WHITE, BLUE);	
			
			GUI_DisString_EN(20, 290, "Return", &Font20, WHITE, BLUE);
			GUI_DisString_EN(380, 290, "Enter", &Font20, WHITE, BLUE);
    } 
}

void showVelocity(void)
{
	LCD_Clear(LCD_BACKGROUND);
	g_xNew = 0;
	g_yNew = 0;
	g_xOld = 0;
	g_yOld = 0;	
	
	if(g_wheelSize != 0.0f) 
	{
		GUI_DisString_EN(33, 20, "BikeSpeedo", &Font24, WHITE, BLUE);
		GUI_DrawLine(0, 55, LCD_WIDTH, 55, RED, LINE_SOLID, DOT_PIXEL_3X3);
		GUI_DisString_EN(5, 80, "Velocity [km/h]:", &Font20, WHITE, BLUE);	
		GUI_DisString_EN(20, 290, "Return", &Font20, WHITE, BLUE);
		
		GUI_DrawLine(35, 260, 35, 110, BLUE, LINE_SOLID, DOT_PIXEL_2X2); // vertical
		GUI_DrawLine(35, 260, 460, 260, BLUE, LINE_SOLID, DOT_PIXEL_2X2); // horizontal
		GUI_DrawLine(35, 110, 25, 130, BLUE, LINE_SOLID, DOT_PIXEL_2X2); // y arrow
		GUI_DrawLine(35, 110, 45, 130, BLUE, LINE_SOLID, DOT_PIXEL_2X2); // y arrow
		GUI_DrawLine(460, 260, 440, 250, BLUE, LINE_SOLID, DOT_PIXEL_2X2);// x arrow
		GUI_DrawLine(460, 260, 440, 270, BLUE, LINE_SOLID, DOT_PIXEL_2X2); // x arrow
		
		GUI_DrawLine(35, 160, 403, 160, BLUE, LINE_SOLID, DOT_PIXEL_1X1); // horiontal 50km/h
		GUI_DisString_EN(5, 155, "50", &Font20, WHITE, BLUE);
		
		GUI_DisString_EN(10, 115, "V", &Font20, WHITE, BLUE);	
		GUI_DisString_EN(440, 270, "t", &Font20, WHITE, BLUE);	
	} 
	else 
	{ 
		GUI_DisString_EN(33, 20, "BikeSpeedo", &Font24, WHITE, BLUE);
		GUI_DrawLine(0, 55, LCD_WIDTH, 55, RED, LINE_SOLID, DOT_PIXEL_3X3);
		GUI_DisString_EN(35, 147, "Please set size of the wheel.", &Font20, WHITE, BLUE);
		GUI_DisString_EN(20, 290, "Return", &Font20, WHITE, BLUE);
	}
}

void updateChart(int velocity)
{
	g_yNew = velocity * 2;
	g_xNew = g_xOld + 2;
	
	GUI_DrawLine(37 + g_xOld, 256 - g_yOld, 37 + g_xNew, 256 - g_yNew, RED, LINE_SOLID, DOT_PIXEL_1X1);
	GUI_DrawPoint(37 + g_xNew, 256 - g_yNew, RED, DOT_PIXEL_2X2, DOT_STYLE_DFT);
	
	g_xOld = g_xNew;
	g_yOld = g_yNew;
	
	if ( g_xNew > (440 - 39))
	{
		LCD_SetArealColor(37, 130, 440, 258, FONT_BACKGROUND);
		GUI_DrawLine(35, 160, 403, 160, BLUE, LINE_SOLID, DOT_PIXEL_1X1); // horizontal 50km/h
		g_xNew = 0;
		g_xOld = 0;
	}
}

void updateVelocityValue(int time)
{
	if(g_STATE == VELOCITY && g_wheelSize != 0.f)
	{
		float velocity = 0.0f;

		if (time != 0)
		{
			velocity = ((g_wheelSize * 0.0254f * 3.14f)/((float)time/1000.0f))*3.6f; // km/h
		}

		LCD_SetArealColor(240, 80, 410, 95, FONT_BACKGROUND);
		
		if (velocity > 0.f)
		{
			int size = snprintf(0, 0, "%.2f", velocity); // float to string
			char s[size + 1];
			snprintf(s, sizeof(s), "%.2f", velocity);
			
			GUI_DisString_EN(240, 80, s, &Font20, WHITE, BLUE);		
		}
		
		updateChart(velocity);
	}
}

void fullRender(void)
{
	switch(g_STATE)
	{
		case MAINMENU:
		{
			showMain();
			break;
		}
		case CONFIGURATION:
		{
			showConfig();
			break;
		}
		case VELOCITY:
		{
			showVelocity();
			break;
		}
		default:
		{
			assert(1); // State out of range
			break;
		}
	}
}

int updateConfigValue(float v)
{
	int size = snprintf(0, 0, "%.2f", v); // convertion float to string
	char s[size + 1];
	snprintf(s, sizeof(s), "%.2f", v);
	
	LCD_SetArealColor(43, 123, 147, 157, FONT_BACKGROUND);
	int tmp = GUI_DisStringInBox_EN(45, 132, 145, 155, s, &Font20, WHITE, BLUE); // display
	
	HAL_Delay(200);
	
	if(tmp < 0) // check errors
	{
		// here is endless loop if g_wheelSize is causing tmp < 0
		updateConfigValue(g_newWheelSize);
	}
	return tmp;
}

void floor2d(float* v)
{
	*v *= 100.0f;
	*v = roundf(*v);
	*v /= 100.0f;
}

void floor3d(float* v)
{
	*v *= 1000.0f;
	*v = roundf(*v);
	*v /= 1000.0f;
}

void inputtingValue()
{
	static float multiplier = 10.0f;
	float newWheelSize = g_newWheelSize;
	
	if (sTP_Draw.Xpoint < 440 && sTP_Draw.Ypoint > 200 && sTP_Draw.Ypoint < 260 && roundf(100.0f * multiplier) >= 1.0f)
	{
		int tmp = sTP_Draw.Xpoint / 44;
		
		if((int)multiplier == 10)
		{
			newWheelSize = newWheelSize * multiplier + tmp;
		}
		else
		{			
			newWheelSize += tmp * multiplier;
			multiplier /= 10.0f;
		}
	}
	else if (sTP_Draw.Xpoint >= 440 && sTP_Draw.Ypoint > 200 && sTP_Draw.Ypoint < 260 && (int)multiplier == 10) // .
	{
		multiplier = 0.10f;
	}		
	else if(sTP_Draw.Xpoint >= 300 && sTP_Draw.Ypoint > 140 && sTP_Draw.Ypoint < 200) // <
	{
		if((int)multiplier == 10)
		{
			newWheelSize = (float)((int)newWheelSize / 10);
		}
		else
		{
			newWheelSize -= fmodf(newWheelSize,multiplier*100.f);
			multiplier *= 10.0f;
			
			if(multiplier > 0.9f && multiplier < 1.1f) // float precision
			{
				multiplier = 10.0f;
				newWheelSize /= 10.0f;
			}
		}
	}
	
	floor2d(&newWheelSize); // because of float multiplication precision
	floor3d(&multiplier); // multiplier cannot be lower than 0.01f
	if(updateConfigValue(newWheelSize) == 0) // Check if new number fits in the frame
	{
		g_newWheelSize = newWheelSize;
	}
	else
	{
		newWheelSize = g_newWheelSize;
	}
}

void init(void)
{
	showMain();
}

void processInput()
{
	TP_Scan(0);
	if (sTP_DEV.chStatus & TP_PRESS_DOWN) // Update only when sth was touched
	{		
		if (sTP_Draw.Xpoint < sLCD_DIS.LCD_Dis_Column &&
		//Determine whether the law is legal
		sTP_Draw.Ypoint < sLCD_DIS.LCD_Dis_Page)
		{
			switch(g_STATE)
			{
				case MAINMENU:
				{
					if (sTP_Draw.Xpoint > 40 && sTP_Draw.Xpoint < 215 && sTP_Draw.Ypoint > 120 && sTP_Draw.Ypoint < 190) // Velocity
					{
						g_STATE = VELOCITY;
						fullRender();
						HAL_TIM_Base_Start_IT(&htim6); // must be after render
					}
					else if (sTP_Draw.Xpoint > 262 && sTP_Draw.Xpoint < 440 && sTP_Draw.Ypoint > 120 && sTP_Draw.Ypoint < 190) // Configuration
					{
						g_STATE = CONFIGURATION;
						fullRender();
					}
					break;
				}
				case CONFIGURATION:
				{
					if(sTP_Draw.Ypoint > 140 && sTP_Draw.Ypoint < 260) // Values
					{
						inputtingValue();
					}
					else if ((sTP_Draw.Xpoint < 100 || sTP_Draw.Xpoint > 370) && sTP_Draw.Ypoint > 260) // Return || Enter
					{
						if (sTP_Draw.Xpoint > 370 ) // Enter
						{
							g_wheelSize = g_newWheelSize;
						}
						g_newWheelSize = 0.0f;
						g_STATE = MAINMENU;
						fullRender();
					}
					break;
				}
				case VELOCITY:
				{
					if (sTP_Draw.Xpoint < 100 && sTP_Draw.Ypoint > 280) // Return
					{
						HAL_TIM_Base_Stop_IT(&htim6);
						g_STATE = MAINMENU;
						fullRender();
					}
					break;
				}
				default:
				{
					assert(1); // State out of range
				}
			}
		}
	}
}

