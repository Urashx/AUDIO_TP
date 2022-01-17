/*
 * ui.c
 *
 *  Created on: Nov 21, 2021
 *      Author: sydxrey
 *
 *
 *      LCD and touchscreen management for project User Interface.
 */

#include <ui.h>
#include <math.h>
#include <stdio.h>
#include "arm_math.h"

/**
 * Display basic UI information.
 */
void uiDisplayBasic(void) {

	LCD_Clear(LCD_COLOR_WHITE);

	//LCD_SetTextColor(LCD_COLOR_BLUE);
	//LCD_FillRect(0, 0, LCD_GetXSize(), 90);

	LCD_SetStrokeColor(LCD_COLOR_BLACK);
	LCD_SetBackColor(LCD_COLOR_WHITE);
	LCD_SetFont(&Font24);
	LCD_DrawString(0, 0, (uint8_t*) "SIA 2021 - RT AUDIO FX", CENTER_MODE, true);

	LCD_SetFont(&Font12);
	LCD_DrawString(10, 30, (uint8_t*) "Input L =", LEFT_MODE, true);
	LCD_DrawString(10, 50, (uint8_t*) "Input R =", LEFT_MODE, true);

	/* Set the LCD Text Color */
	//LCD_SetTextColor(LCD_COLOR_BLUE);
	//LCD_DrawRect(10, 100, LCD_GetXSize() - 20, LCD_GetYSize() - 110);
	//LCD_DrawRect(11, 101, LCD_GetXSize() - 22, LCD_GetYSize() - 112);
}

#define  LCD_SCREEN_WIDTH    480
#define  LCD_SCREEN_HEIGHT   272
int x=10;
/**
 * Displays FFT on screen
 **/
void uiDisplayFFT(float* fftabs, int fftsize) {
	float maxvalue = 40;
	float minvalue = 12;
	//arm_max_f32(fftabs, fftsize, &maxvalue, NULL);
	//arm_min_f32(fftabs, fftsize, &minvalue, NULL);
	for(int i=0; i<fftsize; i++){
		float val = 20.*log10(fftabs[i]/fftsize);
		if(val<minvalue)
			val=minvalue;
		//if(val>maxvalue)
		//	val=maxvalue;
		double normval = (val-minvalue)/(maxvalue-minvalue);
		uint16_t color = normval * 0x7FFF;
		//LCD_SetStrokeColor(color);
		LCD_DrawPixel_Color(x, LCD_SCREEN_HEIGHT-i,color);
	}
	x++;
	if(x>LCD_SCREEN_WIDTH-10)
		x=10;

}


/**
 * Displays line or microphones input level on the LCD.
 */
void uiDisplayInputLevel(double inputLevelL, double inputLevelR) {

	uint8_t buf[50];

	LCD_SetStrokeColor(LCD_COLOR_BLACK);
	LCD_SetBackColor(LCD_COLOR_WHITE);
	LCD_SetFont(&Font12);

	/*sprintf((char *)buf, "%d     ", (int)(inputLevelL));
	 LCD_DisplayStringAt(90, 30, (uint8_t *)buf, LEFT_MODE);

	 sprintf((char *)buf, "%d     ", (int)(inputLevelR));
	 LCD_DisplayStringAt(90, 50, (uint8_t *)buf, LEFT_MODE);*/

	if (inputLevelL > 0) {
		int lvl_db = (int) (20. * log10(inputLevelL));
		sprintf((char*) buf, "%d dB   ", lvl_db);
		LCD_DrawString(90, 30, (uint8_t*) buf, LEFT_MODE, true);
	} else
		LCD_DrawString(90, 30, (uint8_t*) "-inf dB", LEFT_MODE, true);

	if (inputLevelR > 0) {
		int lvl_db = (int) (20. * log10(inputLevelR));
		sprintf((char*) buf, "%d dB   ", lvl_db);
		LCD_DrawString(90, 50, (uint8_t*) buf, LEFT_MODE, true);
	} else
		LCD_DrawString(90, 50, (uint8_t*) "-inf dB", LEFT_MODE, true);

}
