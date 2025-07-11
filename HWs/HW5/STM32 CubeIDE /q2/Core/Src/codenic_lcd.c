// codenic_lcd.c
#include "codenic_lcd.h"
#include <stdio.h>
#include <string.h>

#define RS_PIN GPIO_PIN_1
#define E_PIN  GPIO_PIN_2
#define D4_PIN GPIO_PIN_10
#define D5_PIN GPIO_PIN_11
#define D6_PIN GPIO_PIN_12
#define D7_PIN GPIO_PIN_13
#define LCD_GPIO GPIOB

static void LCD_EnablePulse(void) {
    HAL_GPIO_WritePin(LCD_GPIO, E_PIN, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(LCD_GPIO, E_PIN, GPIO_PIN_RESET);
    HAL_Delay(1);
}

static void LCD_Send4Bits(uint8_t data) {
    HAL_GPIO_WritePin(LCD_GPIO, D4_PIN, (data >> 0) & 0x01);
    HAL_GPIO_WritePin(LCD_GPIO, D5_PIN, (data >> 1) & 0x01);
    HAL_GPIO_WritePin(LCD_GPIO, D6_PIN, (data >> 2) & 0x01);
    HAL_GPIO_WritePin(LCD_GPIO, D7_PIN, (data >> 3) & 0x01);
}

static void LCD_SendCommand(uint8_t cmd) {
    HAL_GPIO_WritePin(LCD_GPIO, RS_PIN, GPIO_PIN_RESET);
    LCD_Send4Bits(cmd >> 4);
    LCD_EnablePulse();
    LCD_Send4Bits(cmd & 0x0F);
    LCD_EnablePulse();
    HAL_Delay(2);
}

static void LCD_SendData(uint8_t data) {
    HAL_GPIO_WritePin(LCD_GPIO, RS_PIN, GPIO_PIN_SET);
    LCD_Send4Bits(data >> 4);
    LCD_EnablePulse();
    LCD_Send4Bits(data & 0x0F);
    LCD_EnablePulse();
    HAL_Delay(1);
}

void LCD_Init(void) {
    HAL_Delay(50);
    LCD_Send4Bits(0x03); LCD_EnablePulse(); HAL_Delay(5);
    LCD_Send4Bits(0x03); LCD_EnablePulse(); HAL_Delay(5);
    LCD_Send4Bits(0x03); LCD_EnablePulse(); HAL_Delay(5);
    LCD_Send4Bits(0x02); LCD_EnablePulse(); HAL_Delay(1);

    LCD_SendCommand(0x28); // 4-bit, 2-line
    LCD_SendCommand(0x0C); // Display on, cursor off
    LCD_SendCommand(0x06); // Entry mode
    LCD_SendCommand(0x01); // Clear display
    HAL_Delay(2);
}

void LCD_Clear(void) {
    LCD_SendCommand(0x01);
    HAL_Delay(2);
}

void LCD_SetCursor(uint8_t col, uint8_t row) {
    uint8_t row_offsets[] = {0x00, 0x40};
    LCD_SendCommand(0x80 | (col + row_offsets[row]));
}

void LCD_Print(char* str) {
    while (*str) {
        LCD_SendData(*str++);
    }
}

void LCD_PrintFloat(float value, uint8_t precision) {
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%.*f", precision, value);
    LCD_Print(buffer);
}

void LCD_PrintInt(int value) {
    char buffer[12];
    snprintf(buffer, sizeof(buffer), "%d", value);
    LCD_Print(buffer);
}
