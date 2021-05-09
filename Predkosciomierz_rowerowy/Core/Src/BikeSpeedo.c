#include "BikeSpeedo.h"
#include "LCD_Touch.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Debug.h"
#include "tim.h"
#include "Utils.h"
#include <assert.h>


#define MAX_DIGITS 4;
char SIZE_CIRCLE [4];
char OLDSIZE_CIRCLE [4];
int size_tab = 0;
float size_circle = 0;
int STATE = MAINMENU;
int X_new = 0;
int Y_new = 0;
int X_old = 0;
int Y_old = 0;
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
			GUI_DisString_EN(45, 132, SIZE_CIRCLE, &Font20, WHITE, BLUE);	
			GUI_DisString_EN(170, 132, "inches.", &Font20, WHITE, BLUE);	
			GUI_DisString_EN(25, 220, "1  2  3  4  5  6  7  8  9  0  .", &Font20, WHITE, BLUE);	
			
			GUI_DisString_EN(20, 290, "Return", &Font20, WHITE, BLUE);
			
			GUI_DisString_EN(380, 290, "Enter", &Font20, WHITE, BLUE);
    } 
}

void showVelocity(void)
{
	LCD_Clear(LCD_BACKGROUND);
	X_new = 0;
	Y_new = 0;
	X_old = 0;
	Y_old = 0;	
	
	if(size_circle != 0.0f) 
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
	Y_new = velocity * 2;
	X_new = X_old + 2;
	
	GUI_DrawLine(37 + X_old, 256 - Y_old, 37 + X_new, 256 - Y_new, RED, LINE_SOLID, DOT_PIXEL_1X1);
	GUI_DrawPoint(37 + X_new, 256 - Y_new, RED, DOT_PIXEL_2X2, DOT_STYLE_DFT);
	
	X_old = X_new;
	Y_old = Y_new;
	
	if ( X_new > (440 - 39))
	{
		LCD_SetArealColor(37, 130, 440, 258, FONT_BACKGROUND);
		GUI_DrawLine(35, 160, 403, 160, BLUE, LINE_SOLID, DOT_PIXEL_1X1); // horizontal 50km/h
		X_new = 0;
		X_old = 0;
	}
}

void updateVelocityValue(int time)
{
	if(STATE == VELOCITY && size_circle != 0.f)
	{
		float velocity = 0.0f;

		if (time != 0)
		{
			velocity = ((size_circle * 0.0254f * 3.14f)/((float)time/1000.0f))*3.6f; // km/h
		}

		LCD_SetArealColor(240, 80, 410, 95, FONT_BACKGROUND);
		
		if (velocity > 0.f)
		{
			int size = snprintf(0, 0, "%.2f", velocity);
			char velocityString[size + 1];
			snprintf(velocityString, sizeof(velocityString), "%.2f", velocity);
			
			GUI_DisString_EN(240, 80, velocityString, &Font20, WHITE, BLUE);		
			free(velocityString);
		}
		
		updateChart(velocity);
	}
}

void fullRender(void)
{
	switch(STATE)
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

void updateConfigValue(void)
{
	LCD_SetArealColor(43, 123, 147, 157, FONT_BACKGROUND);
	GUI_DisString_EN(45, 132, SIZE_CIRCLE, &Font20, WHITE, BLUE);
	HAL_Delay(200);
}

void inputtingValue()
{
	if (sTP_Draw.Xpoint > 0 && sTP_Draw.Xpoint < 52 && sTP_Draw.Ypoint > 200 && sTP_Draw.Ypoint < 260)
	{
		SIZE_CIRCLE[size_tab] = '1';
	}
	else if (sTP_Draw.Xpoint > 52 && sTP_Draw.Xpoint < 95 && sTP_Draw.Ypoint > 200 && sTP_Draw.Ypoint < 260)
	{
		SIZE_CIRCLE[size_tab] = '2';
	}
	else if (sTP_Draw.Xpoint > 95 && sTP_Draw.Xpoint < 138 && sTP_Draw.Ypoint > 200 && sTP_Draw.Ypoint < 260)
	{
		SIZE_CIRCLE[size_tab] = '3';
	}
	else if (sTP_Draw.Xpoint > 138 && sTP_Draw.Xpoint < 181 && sTP_Draw.Ypoint > 200 && sTP_Draw.Ypoint < 260)
	{
		SIZE_CIRCLE[size_tab] = '4';
	}
	else if (sTP_Draw.Xpoint > 181 && sTP_Draw.Xpoint < 224 && sTP_Draw.Ypoint > 200 && sTP_Draw.Ypoint < 260)
	{
		SIZE_CIRCLE[size_tab] = '5';
	}
	else if (sTP_Draw.Xpoint > 224 && sTP_Draw.Xpoint < 267 && sTP_Draw.Ypoint > 200 && sTP_Draw.Ypoint < 260)
	{
		SIZE_CIRCLE[size_tab] = '6';
	}
	else if (sTP_Draw.Xpoint > 267 && sTP_Draw.Xpoint < 310 && sTP_Draw.Ypoint > 200 && sTP_Draw.Ypoint < 260)
	{
		SIZE_CIRCLE[size_tab] = '7';
	}
	else if (sTP_Draw.Xpoint > 310 && sTP_Draw.Xpoint < 353 && sTP_Draw.Ypoint > 200 && sTP_Draw.Ypoint < 260)
	{
		SIZE_CIRCLE[size_tab] = '8';
	}
	else if (sTP_Draw.Xpoint > 353 && sTP_Draw.Xpoint < 396 && sTP_Draw.Ypoint > 200 && sTP_Draw.Ypoint < 260)
	{
		SIZE_CIRCLE[size_tab] = '9';
	}
	else if (sTP_Draw.Xpoint > 396 && sTP_Draw.Xpoint < 439 && sTP_Draw.Ypoint > 200 && sTP_Draw.Ypoint < 260)
	{
		SIZE_CIRCLE[size_tab] = '0';
	}
	else if (sTP_Draw.Xpoint > 439 && sTP_Draw.Xpoint < 480 && sTP_Draw.Ypoint > 200 && sTP_Draw.Ypoint < 260)
	{
		SIZE_CIRCLE[size_tab] = '.';
	}		
	size_tab = (size_tab + 1) % MAX_DIGITS;
	updateConfigValue();
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
			switch(STATE)
			{
				case MAINMENU:
				{
					if (sTP_Draw.Xpoint > 40 && sTP_Draw.Xpoint < 215 && sTP_Draw.Ypoint > 120 && sTP_Draw.Ypoint < 190) // Velocity
					{
						STATE = VELOCITY;
						fullRender();
						HAL_TIM_Base_Start_IT(&htim6); // must be after render
					}
					else if (sTP_Draw.Xpoint > 262 && sTP_Draw.Xpoint < 440 && sTP_Draw.Ypoint > 120 && sTP_Draw.Ypoint < 190) // Configuration
					{
						STATE = CONFIGURATION;
						strcpy(OLDSIZE_CIRCLE, SIZE_CIRCLE);
						memset(SIZE_CIRCLE, 0, sizeof(SIZE_CIRCLE));
						fullRender();
					}
					break;
				}
				case CONFIGURATION:
				{
					if (sTP_Draw.Xpoint < 100 && sTP_Draw.Ypoint > 280) // Return
					{
						strcpy(SIZE_CIRCLE, OLDSIZE_CIRCLE);
						STATE = MAINMENU;
						fullRender();
					}	
					else if (sTP_Draw.Xpoint > 370 && sTP_Draw.Xpoint < 480 && sTP_Draw.Ypoint > 280 && sTP_Draw.Ypoint < 320) // Enter
					{
						size_circle = str2float(SIZE_CIRCLE);
						STATE = MAINMENU;
						fullRender();
					}
					else if(sTP_Draw.Ypoint > 200 && sTP_Draw.Ypoint < 260) // Values
					{
						inputtingValue();
					}
					break;
				}
				case VELOCITY:
				{
					if (sTP_Draw.Xpoint < 100 && sTP_Draw.Ypoint > 280) // Return
					{
						HAL_TIM_Base_Stop_IT(&htim6);
						STATE = MAINMENU;
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

