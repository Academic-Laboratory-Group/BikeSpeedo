/*****************************************************************************
* | File      	:	LCD_Touch.h
* | Author      :   Waveshare team
* | Function    :	LCD Touch Pad Driver and Draw
* | Info        :
*   Image scanning
*      Please use progressive scanning to generate images or fonts
*----------------
* |	This version:   V1.0
* | Date        :   2017-08-16
* | Info        :   Basic version
*
******************************************************************************/
#ifndef __LCD_TOUCH_H_
#define __LCD_TOUCH_H_

#include "MacroAndConst.h"

#include "DEV_Config.h"
#include "spi.h"

#include "LCD_Driver.h"
#include "LCD_GUI.h"

#define TP_PRESS_DOWN           0x80
#define TP_PRESSED              0x40
	
extern int STATE;
//Touch screen structure
typedef struct {
	POINT Xpoint0;
	POINT Ypoint0;
	POINT Xpoint;
	POINT Ypoint;
	uint8_t chStatus;
	uint8_t chType;
	int16_t iXoff;
	int16_t iYoff;
	float fXfac;
	float fYfac;
	//Select the coordinates of the XPT2046 touch \
	  screen relative to what scan direction
	LCD_SCAN_DIR TP_Scan_Dir;
}TP_DEV;

//Brush structure
typedef struct{
	POINT Xpoint;
	POINT Ypoint;
	COLOR Color;
	DOT_PIXEL DotPixel; 
}TP_DRAW;


void TP_GetAdFac(void);
void TP_Adjust(void);
void TP_Dialog(void);
void TP_DrawBoard(void);
void TP_Temp(void);
void TP_Show_Main(void);
void TP_Show_Config(void);
void TP_Update_Config();
void TP_Show_Speed(void);
void TP_Update_Speed(uint32_t time);
void TP_Update_Chart(uint32_t speed);
int intToStr(int x, char str[], int d);
char* float_to_string(float n, int afterpoint) ;
void TP_Init( LCD_SCAN_DIR Lcd_ScanDir );
#endif
