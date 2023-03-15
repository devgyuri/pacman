/*
 * user_touch.c
 *
 *  Created on: May 30, 2021
 *      Author: sangho
 */

#include "user_touch.h"
#include <math.h>

# define BUF_SIZE 10

uint16_t zraw, xraw, yraw;
uint16_t xpos, ypos;

void Touch_read()
{
	int i;
	uint8_t dout[3] = {0};
	uint8_t din[3];
	uint16_t z1, z2;
	int32_t z;
	uint16_t data[6] = {0};
	uint16_t xsum = 0, ysum=0;

	for(i=0; i<BUF_SIZE; i++) {
		HAL_GPIO_WritePin(T_CS_GPIO_Port, T_CS_Pin, GPIO_PIN_RESET);

		dout[0] = TOUCH_CMD_RDZ1;
		Touch_spi(dout, din, 3);

		dout[0] = TOUCH_CMD_RDZ2;
		Touch_spi(dout, din, 3);
		z1 = ((din[1]<<8) | din[2])>>3;
		z = z1 + 4095;

		dout[0] = TOUCH_CMD_RDY;
		Touch_spi(dout, din, 3);
		z2 = ((din[1]<<8) | din[2])>>3;
		z -= z2;

		if(z >= Z_THRESHOLD)
		{
			dout[0] = TOUCH_CMD_RDY;
			Touch_spi(dout, din, 3); //dummy

			dout[0] = TOUCH_CMD_RDX;
			Touch_spi(dout, din, 3);
			data[0] = ((din[1]<<8) | din[2])>>3;

			dout[0] = TOUCH_CMD_RDY;
			Touch_spi(dout, din, 3);
			data[1] = ((din[1]<<8) | din[2])>>3;

			dout[0] = TOUCH_CMD_RDX;
			Touch_spi(dout, din, 3);
			data[2] = ((din[1]<<8) | din[2])>>3;

			dout[0] = TOUCH_CMD_RDY;
			Touch_spi(dout, din, 3);
			data[3] = ((din[1]<<8) | din[2])>>3;
		}

		dout[0] = 0xd0;
		Touch_spi(dout, din, 3);
		data[4] = ((din[1]<<8) | din[2])>>3;

		dout[0] = 0x00;
		Touch_spi(dout, din, 3);
		data[5] = ((din[1]<<8) | din[2])>>3;

		HAL_GPIO_WritePin(T_CS_GPIO_Port, T_CS_Pin, GPIO_PIN_SET);

		if( z < 0 ) z = 0;
		if( z < Z_THRESHOLD)
		{
			zraw = 0;
			return;
		}

		if( z > 6000)
		{
			return;
		}
		zraw = z;

		xraw = (data[0] + data[2])/2;
		yraw = (data[1] + data[3])/2;

		// my filter
		xsum += xraw;
		ysum += yraw;

	}

	xpos = (int)((float)(xsum) / BUF_SIZE);
	ypos = (int)((float)(ysum) / BUF_SIZE);

}


void Touch_spi(uint8_t *dout, uint8_t *din, uint8_t size)
{
	int i, j;


	for(j = 0 ; j < size ; j++)
	{
		for(i = 7 ; i >= 0 ; i--)
		{
			HAL_GPIO_WritePin(T_MOSI_GPIO_Port, T_MOSI_Pin, ((dout[j] >> i) & 0x01));

			//HAL_Delay(1);
			Touch_delay();
			HAL_GPIO_WritePin(T_SCL_GPIO_Port, T_SCL_Pin, GPIO_PIN_SET);
			din[j] <<= 1;
			din[j] |= HAL_GPIO_ReadPin(T_MISO_GPIO_Port, T_MISO_Pin);

			//HAL_Delay(1);
			Touch_delay();
			HAL_GPIO_WritePin(T_SCL_GPIO_Port, T_SCL_Pin, GPIO_PIN_RESET);

		}
	}

	//HAL_Delay(1);
	Touch_delay();




}




void Touch_delay()
{
	int i;
	for(i = 0 ; i < 100 ; i++);
}
