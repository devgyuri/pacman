/*
 * user_LCD.c
 *
 *  Created on: May 13, 2021
 *      Author: sangho
 */

#include "user_LCD.h"
#include "user_font.h"
#include <math.h>

#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }

uint8_t food[8][8] = {
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,1,1,0,0,0},
		{0,0,0,1,1,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
};

uint8_t pacman[8][8] = {
		{0,0,0,1,1,0,0,0},
		{0,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,0},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{0,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,0},
		{0,0,0,1,1,0,0,0},
};

uint8_t ghost[8][8] = {
		{0,0,0,1,1,0,0,0},
		{0,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,0},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,0,1,1,0,1,1},
		{1,1,0,1,1,0,1,1},
};

//uint16_t LCD_buf[240][360] = {0};

void LCD_BL_on()
{
	HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_SET);
}

void LCD_BL_off()
{
	HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_RESET);
}


void LCD_Check_ID()
{
	uint16_t temp;
	BANK1_index = 0xd3;
	temp = BANK1_A10_data; //dummy
	temp = BANK1_A10_data; //0x00
	temp = BANK1_A10_data; //0x93
	temp <<= 8;
	temp |= BANK1_A10_data; //0x41
	temp = 0;
}

void LCD_init()
{
	BANK1_index = 0xCF;
	BANK1_A10_data = 0x00;
	BANK1_A10_data = 0xC1;
	BANK1_A10_data = 0X30;
	BANK1_index = 0xED;
	BANK1_A10_data = 0x64;
	BANK1_A10_data = 0x03;
	BANK1_A10_data = 0X12;
	BANK1_A10_data = 0X81;
	BANK1_index = 0xE8;
	BANK1_A10_data = 0x85;
	BANK1_A10_data = 0x10;
	BANK1_A10_data = 0x7A;
	BANK1_index = 0xCB;
	BANK1_A10_data = 0x39;
	BANK1_A10_data = 0x2C;
	BANK1_A10_data = 0x00;
	BANK1_A10_data = 0x34;
	BANK1_A10_data = 0x02;
	BANK1_index = 0xF7;
	BANK1_A10_data = 0x20;
	BANK1_index = 0xEA;
	BANK1_A10_data = 0x00;
	BANK1_A10_data = 0x00;
	BANK1_index = 0xC0;    //Power control
	BANK1_A10_data = 0x1B;   //VRH[5:0]
	BANK1_index = 0xC1;    //Power control
	BANK1_A10_data = 0x01;   //SAP[2:0];BT[3:0]
	BANK1_index = 0xC5;    //VCM control
	BANK1_A10_data = 0x30; 	 //3F
	BANK1_A10_data = 0x30; 	 //3C
	BANK1_index = 0xC7;    //VCM control2
	BANK1_A10_data = 0XB7;
	BANK1_index = 0x36;    // Memory Access Control
	BANK1_A10_data = 0x48;
	BANK1_index = 0x3A;
	BANK1_A10_data = 0x55;
	BANK1_index = 0xB1;
	BANK1_A10_data = 0x00;
	BANK1_A10_data = 0x1A;
	BANK1_index = 0xB6;    // Display Function Control
	BANK1_A10_data = 0x0A;
	BANK1_A10_data = 0xA2;
	BANK1_index = 0xF2;    // 3Gamma Function Disable
	BANK1_A10_data = 0x00;
	BANK1_index = 0x26;    //Gamma curve selected
	BANK1_A10_data = 0x01;
	BANK1_index = 0xE0;    //Set Gamma
	BANK1_A10_data = 0x0F;
	BANK1_A10_data = 0x2A;
	BANK1_A10_data = 0x28;
	BANK1_A10_data = 0x08;
	BANK1_A10_data = 0x0E;
	BANK1_A10_data = 0x08;
	BANK1_A10_data = 0x54;
	BANK1_A10_data = 0XA9;
	BANK1_A10_data = 0x43;
	BANK1_A10_data = 0x0A;
	BANK1_A10_data = 0x0F;
	BANK1_A10_data = 0x00;
	BANK1_A10_data = 0x00;
	BANK1_A10_data = 0x00;
	BANK1_A10_data = 0x00;
	BANK1_index = 0XE1;    //Set Gamma
	BANK1_A10_data = 0x00;
	BANK1_A10_data = 0x15;
	BANK1_A10_data = 0x17;
	BANK1_A10_data = 0x07;
	BANK1_A10_data = 0x11;
	BANK1_A10_data = 0x06;
	BANK1_A10_data = 0x2B;
	BANK1_A10_data = 0x56;
	BANK1_A10_data = 0x3C;
	BANK1_A10_data = 0x05;
	BANK1_A10_data = 0x10;
	BANK1_A10_data = 0x0F;
	BANK1_A10_data = 0x3F;
	BANK1_A10_data = 0x3F;
	BANK1_A10_data = 0x0F;
	BANK1_index = 0x2B;   //Page Address Set
	BANK1_A10_data = 0x00;
	BANK1_A10_data = 0x00;
	BANK1_A10_data = 0x01;
	BANK1_A10_data = 0x3f;
	BANK1_index = 0x2A;   //Column Address Set
	BANK1_A10_data = 0x00;
	BANK1_A10_data = 0x00;
	BANK1_A10_data = 0x00;
	BANK1_A10_data = 0xef;
	BANK1_index = 0x11; //Exit Sleep
	HAL_Delay(120);
	BANK1_index = 0x29; //display on
}


void LCD_SetPos(uint16_t xPos, uint16_t yPos)
{
	BANK1_index = LCD_xpos_cmd;
	BANK1_A10_data = xPos>>8;
	BANK1_A10_data = xPos&0xff;
	BANK1_index = LCD_ypos_cmd;
	BANK1_A10_data = yPos>>8;
	BANK1_A10_data = yPos&0xff;
}


void LCD_Clear(uint16_t Color)
{
	int i;
	LCD_SetPos(0,0);
	//LCD_buf[10][11] = Color;
	BANK1_index = LCD_wram_cmd;
	for(i = 0; i < LCD_width * LCD_height; i++)
	{
		BANK1_A10_data = Color;
	}
}

void LCD_Draw_Point(uint16_t x, uint16_t y, uint16_t Color)
{
	LCD_SetPos(x,y);
	BANK1_index = LCD_wram_cmd;
	BANK1_A10_data = Color;
}

void LCD_Draw_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t Color)
{
	int16_t steep = abs(y2 - y1) > abs(x2 - x1);
    if (steep) {
        _swap_int16_t(x1, y1);
        _swap_int16_t(x2, y2);
    }

    if (x1 > x2) {
        _swap_int16_t(x1, x2);
        _swap_int16_t(y1, y2);
    }

    int16_t dx, dy;
    dx = x2 - x1;
    dy = abs(y2 - y1);

    int16_t err = dx / 2;
    int16_t ystep;

    if (y1 < y2) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; x1<=x2; x1++) {
        if (steep) {
        	LCD_Draw_Point(y1, x1, Color);
        } else {
        	LCD_Draw_Point(x1, y1, Color);
        }
        err -= dy;
        if (err < 0) {
            y1 += ystep;
            err += dx;
        }
    }

//    if(x2-x1 > y2-y1) {
//    	for(i=x1, k=0; i<=x2; i++, k++) {
//    		j = y1 + (uint16_t)(((float) k * (y2 - y1)) / (x2 - x1));
//    		LCD_Draw_Point(i, j, Color);
//    	}
//    }
}

void LCD_Draw_Circle(uint16_t x, uint16_t y, uint16_t r, uint16_t Color)
{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x0 = 0;
	int16_t y0 = r;

	LCD_Draw_Point(x  , y+r, Color);
	LCD_Draw_Point(x  , y-r, Color);
	LCD_Draw_Point(x+r, y  , Color);
	LCD_Draw_Point(x-r, y  , Color);

	while (x0<y0) {
		if (f >= 0) {
			y0--;
			ddF_y += 2;
			f += ddF_y;
		}
		x0++;
		ddF_x += 2;
		f += ddF_x;

		LCD_Draw_Point(x + x0, y + y0, Color);
		LCD_Draw_Point(x - x0, y + y0, Color);
		LCD_Draw_Point(x + x0, y - y0, Color);
		LCD_Draw_Point(x - x0, y - y0, Color);
		LCD_Draw_Point(x + y0, y + x0, Color);
		LCD_Draw_Point(x - y0, y + x0, Color);
		LCD_Draw_Point(x + y0, y - x0, Color);
		LCD_Draw_Point(x - y0, y - x0, Color);
	}


//	uint16_t cx = x + (uint16_t)(cos(theta) * r);
//	uint16_t cy = y + (uint16_t)(sin(theta) * r);
//
//	for(i=0; i<5*r; i++) {
//		theta = (double)i * 2.0 * 3.141592 / (r * 5);
//		cx = x + (int)(cos(theta) * r);
//		cy = y + (int)(sin(theta) * r);
//		LCD_Draw_Point(cx, cy, Color);
//	}
}

void LCD_Draw_Filled_Circle(uint16_t x, uint16_t y, uint16_t r, uint16_t Color)
{
	LCD_Draw_Filled_Rect(x, y-r, 1, 2*r+1, Color);
	int16_t f     = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x0    = 0;
	int16_t y0    = r;
	int16_t px    = x0;
	int16_t py    = y0;
	int16_t delta = 0;
	uint8_t corners = 3;

	delta++; // Avoid some +1's in the loop

	while(x0 < y0) {
		if (f >= 0) {
			y0--;
			ddF_y += 2;
			f     += ddF_y;
		}
		x0++;
		ddF_x += 2;
		f     += ddF_x;
		// These checks avoid double-drawing certain lines, important
		// for the SSD1306 library which has an INVERT drawing mode.
		if(x0 < (y0 + 1)) {
			if(corners & 1) LCD_Draw_Filled_Rect(x+x0, y-y0, 1, 2*y0+delta, Color);
			if(corners & 2) LCD_Draw_Filled_Rect(x-x0, y-y0, 1, 2*y0+delta, Color);
		}
		if(y0 != py) {
			if(corners & 1) LCD_Draw_Filled_Rect(x+py, y-px, 1, 2*px+delta, Color);
			if(corners & 2) LCD_Draw_Filled_Rect(x-py, y-px, 1, 2*px+delta, Color);
			py = y0;
		}
		px = x0;
	}
}

void LCD_Draw_Filled_Rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t Color) {
	int i, j;
	for(i=0; i<w; i++) {
		if(x+i > 240) {
			break;
		}
		for(j=0; j<h; j++) {
			if(y+j > 360) {
				break;
			}
			LCD_Draw_Point(x+i, y+j, Color);
		}
	}
}

void LCD_Draw_Block(int16_t x, int16_t y) {
	int i, j;
	x += 1;
	y += 1;
	for(i=0; i<6; i++) {
		if(x+i > 240) {
			break;
		}
		for(j=0; j<6; j++) {
			if(y+j > 360) {
				break;
			}
			LCD_Draw_Point(x+i, y+j, COLOR_BLUE);
		}
	}
}

void LCD_Draw_Food(int16_t x, int16_t y) {
	int i, j;
	for(i=0; i<8; i++) {
		if(x+i > 240) {
			break;
		}
		for(j=0; j<8; j++) {
			if(y+j > 360) {
				break;
			}
			if(food[i][j] == 1) {
				LCD_Draw_Point(x+i, y+j, COLOR_WHITE);
			}
		}
	}
}

// state 1:draw 0:delete
void LCD_Draw_Pacman(int16_t x, int16_t y, uint8_t state) {
	int i, j;
	for(i=0; i<8; i++) {
		for(j=0; j<8; j++) {
			if(pacman[i][j] == 1) {
				if(state) {
					LCD_Draw_Point(x+j-5, y+i-4, COLOR_YELLOW);
				} else {
					LCD_Draw_Point(x+j-5, y+i-4, COLOR_BLACK);
				}
			}
		}
	}
}

void LCD_Draw_Ghost(int16_t x, int16_t y, uint8_t number, uint8_t state) {
	int i, j;
	for(i=0; i<8; i++) {
		for(j=0; j<8; j++) {
			if(ghost[i][j] == 1) {
				if(state) {
					switch(number) {
					case 1:
						LCD_Draw_Point(x+j-5, y+i-4, COLOR_RED); break;
					case 2:
						LCD_Draw_Point(x+j-5, y+i-4, COLOR_PINK); break;
					case 3:
						LCD_Draw_Point(x+j-5, y+i-4, COLOR_SYAN); break;
					case 4:
						LCD_Draw_Point(x+j-5, y+i-4, COLOR_ORANGE); break;
					}
				} else {
					LCD_Draw_Point(x+j-5, y+i-4, COLOR_BLACK);
				}
			}
		}
	}
}

void LCD_Draw_Score(int score, uint8_t state)
{
	int x = 224;
	int y = 20;
	int dx = 0;
	int len = 0;
	int r_score = 0;
	uint16_t font_size = 1;

	while(score) {
		r_score *= 10;
		r_score += score % 10;
		score /= 10;
		len++;
	}

	while(len--)
	{
		if(state) {
			LCD_Draw_Char(x + dx, y, (r_score%10)+'0',COLOR_WHITE,font_size);
		} else {
			LCD_Draw_Char(x + dx, y, (r_score%10)+'0',COLOR_BLACK,font_size);
		}
		r_score /= 10;
		dx -= asc_width[font_size];
	}
}

void LCD_Draw_Final_Score(int score)
{
	int x = 120;
	int y = 140;
	int dx = 0;
	int len = 0;
	int r_score = 0;
	uint16_t font_size = 3;

	while(score) {
		r_score *= 10;
		r_score += score % 10;
		score /= 10;
		len++;
	}
	x += asc_width[font_size]*(len)/2;

	while(len--) {
		LCD_Draw_Char(x + dx, y, (r_score%10)+'0',COLOR_WHITE,font_size);
		r_score /= 10;
		dx -= asc_width[font_size];
	}
}

void LCD_Draw_Life(int life, uint8_t state)
{
	int x = 224;
	int y = 290;
	int dx = 0;

	while(life--)
	{
		if(state) {
			LCD_Draw_Pacman(x + dx, y, 1);
		} else {
			LCD_Draw_Pacman(x + dx, y, 0);
		}
		dx -= 10;
	}
}

void LCD_Draw_Level(int level)
{
	int x = 64;
	int y = 20;
	uint16_t font_size = 1;
	int dx = asc_width[font_size];

	LCD_Draw_Char(x - (dx*6), y, level-1+'0', COLOR_BLACK, font_size);
	LCD_Draw_Char(x - (dx*0), y, 'l', COLOR_WHITE, font_size);
	LCD_Draw_Char(x - (dx*1), y, 'e', COLOR_WHITE, font_size);
	LCD_Draw_Char(x - (dx*2), y, 'v', COLOR_WHITE, font_size);
	LCD_Draw_Char(x - (dx*3), y, 'e', COLOR_WHITE, font_size);
	LCD_Draw_Char(x - (dx*4), y, 'l', COLOR_WHITE, font_size);
	LCD_Draw_Char(x - (dx*5), y, ' ', COLOR_WHITE, font_size);
	LCD_Draw_Char(x - (dx*6), y, level+'0', COLOR_WHITE, font_size);
}

void LCD_Draw_Char(uint16_t x, uint16_t y, uint8_t Char, uint16_t Color, uint16_t font_size)
{
	uint8_t temp;
	int i,j,dx = 0, dy = 0;

	for(i = 0 ; i < asc_length[font_size] ; i++)
	{
		if(font_size == 0) 			temp = asc2_1206[Char - ' '][i];
		else if(font_size == 1) 	temp = asc2_1608[Char - ' '][i];
		else if(font_size == 2) 	temp = asc2_2412[Char - ' '][i];
		else if(font_size == 3) 	temp = asc2_3216[Char - ' '][i];

		for(j = 0 ; j < 8 ; j++, temp <<= 1)
		{
			if((temp&0x80) == 0x80) LCD_Draw_Point(x + dx, y + dy, Color);

			dy++;
			if(dy == asc_height[font_size])
			{
				dy = 0;
				dx--;
			}
		}
	}
}

void LCD_Draw_Str(uint16_t x, uint16_t y, uint8_t* str, uint16_t Color, uint16_t font_size)
{
	int dx = 0;

	while(*str != '\0')
	{
		LCD_Draw_Char(x + dx, y, *str,Color,font_size);
		str++;
		dx -= asc_width[font_size];
	}
}
