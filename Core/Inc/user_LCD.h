/*
 * user_LCD.h
 *
 *  Created on: May 13, 2021
 *      Author: sangho
 */

#ifndef INC_USER_LCD_H_
#define INC_USER_LCD_H_

#include "main.h"


#define BANK1_index		*((uint16_t *)0x6c000000)
#define BANK1_A10_data	*((uint16_t *)0x6c000800)

#define LCD_wram_cmd	0x2c
#define LCD_xpos_cmd	0x2a
#define LCD_ypos_cmd	0x2b

#define LCD_width	240
#define LCD_height	320


#define COLOR_BLACK		0x0000
#define COLOR_WHITE		0xffff
#define COLOR_BLUE		0x001f
#define COLOR_GREEN		0x07e0
#define COLOR_RED		0xf800
#define COLOR_YELLOW	0xff83
#define COLOR_ORANGE	0xfbe0
#define COLOR_VIOLET	0xa03c
#define COLOR_INDIGO	0x18d4
#define COLOR_PINK		0xf8d8
#define COLOR_SYAN		0x1edf

void LCD_BL_on();
void LCD_BL_off();


void LCD_Check_ID();

void LCD_init();
void LCD_SetPos(uint16_t xPos, uint16_t yPos);
void LCD_Clear(uint16_t Color);

void LCD_Draw_Point(uint16_t x, uint16_t y, uint16_t Color);
void LCD_Draw_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t Color);
void LCD_Draw_Circle(uint16_t x, uint16_t y, uint16_t r, uint16_t Color);
void LCD_Draw_Filled_Circle(uint16_t x, uint16_t y, uint16_t r, uint16_t Color);
void LCD_Draw_Filled_Rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t Color);
void LCD_Draw_Block(int16_t x, int16_t y);
void LCD_Draw_Food(int16_t x, int16_t y);
void LCD_Draw_Pacman(int16_t x, int16_t y, uint8_t state);
//void LCD_Delete_Character(int16_t x, int16_t y);
void LCD_Draw_Ghost(int16_t x, int16_t y, uint8_t number, uint8_t state);
void LCD_Draw_Score(int score, uint8_t state);
void LCD_Draw_Final_Score(int score);
void LCD_Draw_Life(int life, uint8_t state);
void LCD_Draw_Level(int level);
void LCD_Draw_Char(uint16_t x, uint16_t y, uint8_t Char, uint16_t Color, uint16_t font_size);
void LCD_Draw_Str(uint16_t x, uint16_t y, uint8_t* str, uint16_t Color, uint16_t font_size);
#endif /* INC_USER_LCD_H_ */
