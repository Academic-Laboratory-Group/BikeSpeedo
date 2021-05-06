#include "BikeSpeedo.h"
#include "LCD_Touch.h"
#include <math.h>
#include <stdlib.h>
#include "Debug.h"
#include "tim.h"

char SIZE_CIRCLE [3];
int size_tab = 0;
float size_circle = 0;
int STATE = 1;
int X_new = 0;
int Y_new = 0;
int X_old = 0;
int Y_old = 0;
#define PI 3.14

int intToStr(int x, char str[], int d) 
{ 
	int i = 0; 
	int k = 0; 
	int tmp;

	do
	{ 
			str[i++] = (x % 10) + '0'; 
			x = x / 10; 
	} 
	while(x);

	while (i < d) 
			str[i++] = '0';

	//reverse
	int l = i - 1;
	while (k < l) 
	{ 
		tmp = str[k]; 
		str[k] = str[l]; 
		str[l] = tmp; 
		k++; 
		l--; 
	}
	//
	str[i] = '\0'; 
	return i; 
} 

void Update(void)
{
    TP_Scan(0);
    if (sTP_DEV.chStatus & TP_PRESS_DOWN) {		//Press the button
        //Horizontal screen
        if (sTP_Draw.Xpoint < sLCD_DIS.LCD_Dis_Column &&
            //Determine whether the law is legal
            sTP_Draw.Ypoint < sLCD_DIS.LCD_Dis_Page) {
            //Judgment is horizontal screen
            if(sLCD_DIS.LCD_Dis_Column > sLCD_DIS.LCD_Dis_Page) 
						{
							if ( size_tab == 4 )
							{
								size_tab = 0;
							}
							if ((sTP_Draw.Xpoint > 40 && sTP_Draw.Xpoint < 215) && (sTP_Draw.Ypoint > 120 && sTP_Draw.Ypoint < 190) && STATE == 1)
							{
								X_new = 0;
								Y_new = 0;
								X_old = 0;
								Y_old = 0;		
								Show_Speed();
							}
							else if ((sTP_Draw.Xpoint > 262 && sTP_Draw.Xpoint < 440) && (sTP_Draw.Ypoint > 120 && sTP_Draw.Ypoint < 190) && STATE == 1)
							{
								STATE = 3;
								Show_Config();
								size_tab = 0;
								for(int i = 0; i < 4; i++)
								{
									SIZE_CIRCLE[i] = 0;
								}
							}
							else if (sTP_Draw.Xpoint < 100 && sTP_Draw.Ypoint > 280 && (STATE == 2 || STATE == 3 || STATE == 4))
							{
								STATE = 1;
								Show_Main();
								size_tab = 0;
								for(int i = 0; i < 4; i++)
								{
									SIZE_CIRCLE[i] = 0;
								}
							}
							else if ((sTP_Draw.Xpoint > 0 && sTP_Draw.Xpoint < 52) && (sTP_Draw.Ypoint > 200 && sTP_Draw.Ypoint < 260) && STATE == 3)
							{
								SIZE_CIRCLE[size_tab] = 1;
								Update_Config();
								size_tab++;
							}
							else if ((sTP_Draw.Xpoint > 52 && sTP_Draw.Xpoint < 95) && (sTP_Draw.Ypoint > 200 && sTP_Draw.Ypoint < 260) && STATE == 3)
							{
								SIZE_CIRCLE[size_tab] = 2;
								Update_Config();
								size_tab++;
							}
							else if ((sTP_Draw.Xpoint > 95 && sTP_Draw.Xpoint < 138) && (sTP_Draw.Ypoint > 200 && sTP_Draw.Ypoint < 260) && STATE == 3)
							{
								SIZE_CIRCLE[size_tab] = 3;
								Update_Config();
								size_tab++;
							}
							else if ((sTP_Draw.Xpoint > 138 && sTP_Draw.Xpoint < 181) && (sTP_Draw.Ypoint > 200 && sTP_Draw.Ypoint < 260) && STATE == 3)
							{
								SIZE_CIRCLE[size_tab] = 4;
								Update_Config();
								size_tab++;
							}
							else if ((sTP_Draw.Xpoint > 181 && sTP_Draw.Xpoint < 224) && (sTP_Draw.Ypoint > 200 && sTP_Draw.Ypoint < 260) && STATE == 3)
							{
								SIZE_CIRCLE[size_tab] = 5;
								Update_Config();
								size_tab++;
							}
							else if ((sTP_Draw.Xpoint > 224 && sTP_Draw.Xpoint < 267) && (sTP_Draw.Ypoint > 200 && sTP_Draw.Ypoint < 260) && STATE == 3)
							{
								SIZE_CIRCLE[size_tab] = 6;
								Update_Config();
								size_tab++;
							}
							else if ((sTP_Draw.Xpoint > 267 && sTP_Draw.Xpoint < 310) && (sTP_Draw.Ypoint > 200 && sTP_Draw.Ypoint < 260) && STATE == 3)
							{
								SIZE_CIRCLE[size_tab] = 7;
								Update_Config();
								size_tab++;
							}
							else if ((sTP_Draw.Xpoint > 310 && sTP_Draw.Xpoint < 353) && (sTP_Draw.Ypoint > 200 && sTP_Draw.Ypoint < 260) && STATE == 3)
							{
								SIZE_CIRCLE[size_tab] = 8;
								Update_Config();
								size_tab++;
							}
							else if ((sTP_Draw.Xpoint > 353 && sTP_Draw.Xpoint < 396) && (sTP_Draw.Ypoint > 200 && sTP_Draw.Ypoint < 260) && STATE == 3)
							{
								SIZE_CIRCLE[size_tab] = 9;
								Update_Config();
								size_tab++;
							}
							else if ((sTP_Draw.Xpoint > 396 && sTP_Draw.Xpoint < 439) && (sTP_Draw.Ypoint > 200 && sTP_Draw.Ypoint < 260) && STATE == 3)
							{
								SIZE_CIRCLE[size_tab] = 0;
								Update_Config();
								size_tab++;
							}
							else if ((sTP_Draw.Xpoint > 439 && sTP_Draw.Xpoint < 480) && (sTP_Draw.Ypoint > 200 && sTP_Draw.Ypoint < 260) && STATE == 3)
							{
								SIZE_CIRCLE[size_tab] = '.';
								Update_Config();
								size_tab++;
							}		
							else if ((sTP_Draw.Xpoint > 370 && sTP_Draw.Xpoint < 480) && (sTP_Draw.Ypoint > 280 && sTP_Draw.Ypoint < 320) && STATE == 3)
							{
								STATE = 1;
								Show_Main();

							}									
             //Vertical screen
            } 
						else 
						{
                
             // Horizontal(pionowy) screen
            }
        }
    }

}

void Show_Main(void)
{
    LCD_Clear(LCD_BACKGROUND);
    if(sLCD_DIS.LCD_Dis_Column > sLCD_DIS.LCD_Dis_Page) 
		{
			GUI_DisString_EN(33, 20, "Predkosciomierz rowerowy", &Font24, WHITE, BLUE);
			GUI_DrawLine(0, 55, LCD_WIDTH, 55, RED, LINE_SOLID, DOT_PIXEL_3X3);
			GUI_DisString_EN(35, 80, "Wybierz czym chcesz zarzadzac", &Font20, WHITE, BLUE);
			GUI_DrawRectangle(40, 120, 215, 190, RED, DRAW_EMPTY, DOT_PIXEL_2X2);
			GUI_DrawRectangle(262, 120, 440, 190, RED, DRAW_EMPTY, DOT_PIXEL_2X2);
			GUI_DisString_EN(75, 147, "PREDKOSC", &Font20, WHITE, BLUE);
			GUI_DisString_EN(267, 147, "KONFIGURACJA", &Font20, WHITE, BLUE);
			GUI_DisString_EN(190, 270, "Wykonawcy:", &Font16, WHITE, BLUE);
			GUI_DisString_EN(135, 285, "inz. Krzysztof Pokora", &Font16, WHITE, BLUE);
			GUI_DisString_EN(150, 300, "inz. Norbert Ligas", &Font16, WHITE, BLUE);
    } 
		else 
		{ //Vertical screen display

    }
}

void Show_Config(void)
{		
    LCD_Clear(LCD_BACKGROUND);
    if(sLCD_DIS.LCD_Dis_Column > sLCD_DIS.LCD_Dis_Page) 
		{
			GUI_DisString_EN(33, 20, "Predkosciomierz rowerowy", &Font24, WHITE, BLUE);
			GUI_DrawLine(0, 55, LCD_WIDTH, 55, RED, LINE_SOLID, DOT_PIXEL_3X3);
			
			GUI_DisString_EN(15, 80, "Wprowadz rozmiar kola rowerowego", &Font20, WHITE, BLUE);	
			GUI_DrawRectangle(40, 120, 150, 160, RED, DRAW_EMPTY, DOT_PIXEL_2X2);
			GUI_DisString_EN(170, 132, "w calach", &Font20, WHITE, BLUE);	
			GUI_DisString_EN(25, 220, "1  2  3  4  5  6  7  8  9  0  .", &Font20, WHITE, BLUE);	
			
			GUI_DisString_EN(20, 290, "Powrot", &Font20, WHITE, BLUE);
			
			GUI_DisString_EN(380, 290, "Enter", &Font20, WHITE, BLUE);
    } 
		else 
		{ //Vertical screen display

    }
}

void Update_Config(void)
{
	size_circle = 0;
	float divider = 1.0;
	int tmp = 0;
	for(int i = size_tab; i >= 0; i--)
	{
		if(SIZE_CIRCLE[i] == '.')
		{
			tmp = 1;
		}
		else
		{
			if (SIZE_CIRCLE[i - 1] == '.')
			{
				size_circle += SIZE_CIRCLE[i] * 0.1 ;
			}
			else
			{
				size_circle += SIZE_CIRCLE[i] * divider;
				divider = divider * 10.0;
			}
		}
	}
	
	char *size_circle_string = (char*)malloc(13);
	
	int ipart = (int)size_circle; 
	float fpart = size_circle - (float)ipart; 

	int i = intToStr(ipart, size_circle_string, 0); 

	if (tmp != 0) 
	{ 
		size_circle_string[i] = '.';
		fpart = fpart * pow(10, 1); 
		intToStr((int)fpart, size_circle_string + i + 1, 1); 
	} 
	LCD_SetArealColor(43, 123, 147, 157, FONT_BACKGROUND);
	GUI_DisString_EN(45, 132, size_circle_string, &Font20, WHITE, BLUE);	
	
	free(size_circle_string);
	HAL_Delay(200);
	
}
void Show_Speed(void)
{
	LCD_Clear(LCD_BACKGROUND);
	if(size_circle != 0.0) 
	{
		STATE = 2;
		GUI_DisString_EN(33, 20, "Predkosciomierz rowerowy", &Font24, WHITE, BLUE);
		GUI_DrawLine(0, 55, LCD_WIDTH, 55, RED, LINE_SOLID, DOT_PIXEL_3X3);
		
		GUI_DisString_EN(5, 80, "Twoja aktualna predkosc:     km/h", &Font20, WHITE, BLUE);	
		
		GUI_DisString_EN(20, 290, "Powrot", &Font20, WHITE, BLUE);
		
		GUI_DrawLine(35, 260, 35, 110, BLUE, LINE_SOLID, DOT_PIXEL_2X2); //pionowa
		GUI_DrawLine(35, 260, 460, 260, BLUE, LINE_SOLID, DOT_PIXEL_2X2); // pozioma
		GUI_DrawLine(35, 110, 25, 130, BLUE, LINE_SOLID, DOT_PIXEL_2X2); //górnastrzalka
		GUI_DrawLine(35, 110, 45, 130, BLUE, LINE_SOLID, DOT_PIXEL_2X2); //górnastrzalka
		GUI_DrawLine(460, 260, 440, 250, BLUE, LINE_SOLID, DOT_PIXEL_2X2);//dolnastrzalka	
		GUI_DrawLine(460, 260, 440, 270, BLUE, LINE_SOLID, DOT_PIXEL_2X2); //dolnastrzalka
		
		GUI_DrawLine(35, 160, 403, 160, BLUE, LINE_SOLID, DOT_PIXEL_1X1); // pozioma 50km/h
		GUI_DisString_EN(5, 155, "50", &Font20, WHITE, BLUE);
		
		GUI_DisString_EN(10, 115, "V", &Font20, WHITE, BLUE);	
		GUI_DisString_EN(440, 270, "t", &Font20, WHITE, BLUE);	
	} 
	else 
	{ 
		STATE = 4;
		GUI_DisString_EN(33, 20, "Predkosciomierz rowerowy", &Font24, WHITE, BLUE);
		GUI_DrawLine(0, 55, LCD_WIDTH, 55, RED, LINE_SOLID, DOT_PIXEL_3X3);
		
		GUI_DisString_EN(35, 147, "WPIERW PRZEJDZ DO KONFIGURACJI", &Font20, WHITE, BLUE);
		
		GUI_DisString_EN(20, 290, "Powrot", &Font20, WHITE, BLUE);
	}
}

void Update_Speed(uint32_t time)
{
	float speed = 0.0;
	
	speed = ((size_circle * 0.0254 * 3.14)/((float)time/1000.0))*3.6;//km/h
	
	char *speed_string = (char*)malloc(13);
	
	int ipart = (int)speed; 
	float fpart = speed - (float)ipart; 

	int i = intToStr(ipart, speed_string, 0); 

	speed_string[i] = '.';
	fpart = fpart * pow(10, 1); 
	intToStr((int)fpart, speed_string + i + 1, 1);
	
	LCD_SetArealColor(340, 80, 410, 95, FONT_BACKGROUND);
	GUI_DisString_EN(340, 80, speed_string, &Font20, WHITE, BLUE);		
	free(speed_string);
	
	Update_Chart(speed);
}

void Update_Chart(uint32_t speed)
{
	Y_new = (int)speed * 2;
	X_new = X_old + 2;
	
	GUI_DrawLine(37 + X_old, 257 - Y_old, 37 + X_new, 257 - Y_new, RED, LINE_SOLID, DOT_PIXEL_1X1);
	GUI_DrawPoint(37 + X_new, 257 - Y_new, RED, DOT_PIXEL_2X2, DOT_STYLE_DFT);
	
	X_old = X_new;
	Y_old = Y_new;
	
	if ( X_new > (440 - 39))
	{
		LCD_SetArealColor(37, 130, 440, 258, FONT_BACKGROUND);
		GUI_DrawLine(35, 160, 403, 160, BLUE, LINE_SOLID, DOT_PIXEL_1X1); // pozioma 50km/h
		X_new = 0;
		X_old = 0;
	}
}
