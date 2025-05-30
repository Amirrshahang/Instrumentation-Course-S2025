// codenic_lcd.h
#ifndef __CODENIC_LCD_H__
#define __CODENIC_LCD_H__

#include "stm32f1xx_hal.h"

void LCD_Init(void);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t col, uint8_t row);
void LCD_Print(char* str);
void LCD_PrintFloat(float value, uint8_t precision);
void LCD_PrintInt(int value);

#endif