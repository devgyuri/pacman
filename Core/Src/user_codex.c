/*
 * user_codex.c
 *
 *  Created on: May 4, 2021
 *      Author: sangho
 */

#include "user_codex.h"

extern SPI_HandleTypeDef hspi1;
uint16_t rec[256];

void Codex_MIDI_Set_Instrument(uint8_t ch, uint8_t inst)
{
	HAL_GPIO_WritePin(VS_XCS_GPIO_Port, VS_XCS_Pin, GPIO_PIN_SET);
	Codex_SDI_Tx(MIDI_CHAN_PROGRAM|ch);
	Codex_SDI_Tx(inst-1);
	HAL_GPIO_WritePin(VS_XCS_GPIO_Port, VS_XCS_Pin, GPIO_PIN_RESET);

}


void Codex_MIDI_Set_Ch_Vol(uint8_t ch, uint8_t vol)
{
	HAL_GPIO_WritePin(VS_XCS_GPIO_Port, VS_XCS_Pin, GPIO_PIN_SET);
	Codex_SDI_Tx(MIDI_CHAN_MSG|ch);
	Codex_SDI_Tx(MIDI_CHAN_VOLUME);
	Codex_SDI_Tx(vol);
	HAL_GPIO_WritePin(VS_XCS_GPIO_Port, VS_XCS_Pin, GPIO_PIN_RESET);

}

void Codex_MIDI_Set_Ch_Bank(uint8_t ch, uint8_t bank)
{
	HAL_GPIO_WritePin(VS_XCS_GPIO_Port, VS_XCS_Pin, GPIO_PIN_SET);
	Codex_SDI_Tx(MIDI_CHAN_MSG|ch);
	Codex_SDI_Tx(MIDI_CHAN_BANK);
	Codex_SDI_Tx(bank);
	HAL_GPIO_WritePin(VS_XCS_GPIO_Port, VS_XCS_Pin, GPIO_PIN_RESET);

}

void Codex_MIDI_NoteOn(uint8_t ch, uint8_t note, uint8_t pressure)
{
	HAL_GPIO_WritePin(VS_XCS_GPIO_Port, VS_XCS_Pin, GPIO_PIN_SET);
	Codex_SDI_Tx(MIDI_NOTE_ON|ch);
	Codex_SDI_Tx(note);
	Codex_SDI_Tx(pressure);
	HAL_GPIO_WritePin(VS_XCS_GPIO_Port, VS_XCS_Pin, GPIO_PIN_RESET);

}

void Codex_MIDI_NoteOff(uint8_t ch, uint8_t note, uint8_t pressure)
{
	HAL_GPIO_WritePin(VS_XCS_GPIO_Port, VS_XCS_Pin, GPIO_PIN_SET);
	Codex_SDI_Tx(MIDI_NOTE_OFF|ch);
	Codex_SDI_Tx(note);
	Codex_SDI_Tx(pressure);
	HAL_GPIO_WritePin(VS_XCS_GPIO_Port, VS_XCS_Pin, GPIO_PIN_RESET);

}

void Codex_SDI_Tx(uint8_t data)
{
	uint8_t TxData[2];
	uint8_t RxData[2];
	TxData[0] = data;
	TxData[1] = 0;

	HAL_GPIO_WritePin(VS_XDCS_GPIO_Port, VS_XDCS_Pin, GPIO_PIN_SET);
	HAL_SPI_TransmitReceive(&hspi1, TxData, RxData, 2, 100);
	HAL_GPIO_WritePin(VS_XDCS_GPIO_Port, VS_XDCS_Pin, GPIO_PIN_RESET);
}
void Codex_MIDI_Mode()
{
	uint16_t temp;
	Codex_reg_write(CODEX_REG_WRAMADDR, 0x8050);
	Codex_reg_write(CODEX_REG_WRAM, 0x0030);
	Codex_reg_write(CODEX_REG_WRAM, 0x0715);
	Codex_reg_write(CODEX_REG_WRAM, 0xb080);
	Codex_reg_write(CODEX_REG_WRAM, 0x3400);
	Codex_reg_write(CODEX_REG_WRAM, 0x0007);

	Codex_reg_write(CODEX_REG_WRAM, 0x9255);
	Codex_reg_write(CODEX_REG_WRAM, 0x3d00);
	Codex_reg_write(CODEX_REG_WRAM, 0x0024);
	Codex_reg_write(CODEX_REG_WRAM, 0x0030);
	Codex_reg_write(CODEX_REG_WRAM, 0x0295);

	Codex_reg_write(CODEX_REG_WRAM, 0x6890);
	Codex_reg_write(CODEX_REG_WRAM, 0x3400);
	Codex_reg_write(CODEX_REG_WRAM, 0x0030);
	Codex_reg_write(CODEX_REG_WRAM, 0x0495);
	Codex_reg_write(CODEX_REG_WRAM, 0x3d00);

	Codex_reg_write(CODEX_REG_WRAM, 0x0024);
	Codex_reg_write(CODEX_REG_WRAM, 0x2908);
	Codex_reg_write(CODEX_REG_WRAM, 0x4d40);
	Codex_reg_write(CODEX_REG_WRAM, 0x0030);
	Codex_reg_write(CODEX_REG_WRAM, 0x0200);

	Codex_reg_write(CODEX_REG_AIADDR, 0x0050);

	HAL_Delay(10);

	Codex_reg_write(CODEX_REG_MODE, 0x0c00);

	HAL_Delay(10);
}


void Codex_temp()
{
	uint16_t ID[2];
	uint16_t version;
	Codex_reg_write(CODEX_REG_WRAMADDR, CODEX_MEM_CHIP_ID0);
	Codex_reg_read(CODEX_REG_WRAM, ID);

	Codex_reg_write(CODEX_REG_WRAMADDR, CODEX_MEM_CHIP_ID1);
	Codex_reg_read(CODEX_REG_WRAM, ID+1);

	Codex_reg_write(CODEX_REG_WRAMADDR, CODEX_MEM_VERSION);
	Codex_reg_read(CODEX_REG_WRAM, &version);

	version = 0;

}


uint8_t Codex_Record()
{
	uint8_t state = 0;
	uint16_t temp;
	int i;
	Codex_reg_read(CODEX_REG_HDAT1, &temp);
	if(temp >= 256)
	{
		for(i = 0 ; i < 256 ; i++)
			Codex_reg_read(CODEX_REG_HDAT0, rec + i);
		state = 1;
	}


	return state;
}

void Codex_Start_Record()
{
	uint16_t temp;
	//if(mic == 1)

	//else
	//	Codex_reg_write(CODEX_REG_MODE,  CODEX_MODE_SM_LINE1 | CODEX_MODE_SM_ADPCM | CODEX_MODE_SM_SDINEW);

	Codex_reg_write(CODEX_REG_AICTRL0, 8000);
	Codex_reg_write(CODEX_REG_AICTRL1, 1024);
	Codex_reg_write(CODEX_REG_AICTRL2, 0);
	Codex_reg_write(CODEX_REG_AICTRL3, 6);
	Codex_reg_write(CODEX_REG_CLOCKF, 0x2000);
	//Codex_reg_write(CODEX_REG_AIADDR, 0x34);
	Codex_reg_write(CODEX_REG_MODE, CODEX_MODE_SM_ADPCM | CODEX_MODE_SM_SDINEW|CODEX_MODE_SM_RESET);
	//Codex_reg_write(CODEX_REG_MODE, CODEX_MODE_SM_SDINEW|CODEX_MODE_SM_RESET);

	HAL_Delay(5);

	Codex_reg_write(CODEX_REG_WRAMADDR, 0x8010);
	Codex_reg_write(CODEX_REG_WRAM, 0x3e12);
	Codex_reg_write(CODEX_REG_WRAM, 0xb817);
	Codex_reg_write(CODEX_REG_WRAM, 0x3e14);

	Codex_reg_write(CODEX_REG_WRAM, 0xf812);
	Codex_reg_write(CODEX_REG_WRAM, 0x3e01);
	Codex_reg_write(CODEX_REG_WRAM, 0xb811);
	Codex_reg_write(CODEX_REG_WRAM, 0x0007);
	Codex_reg_write(CODEX_REG_WRAM, 0x9717);
	Codex_reg_write(CODEX_REG_WRAM, 0x0020);
	Codex_reg_write(CODEX_REG_WRAM, 0xffd2);
	Codex_reg_write(CODEX_REG_WRAM, 0x0030);

	Codex_reg_write(CODEX_REG_WRAM, 0x11d1);
	Codex_reg_write(CODEX_REG_WRAM, 0x3111);
	Codex_reg_write(CODEX_REG_WRAM, 0x8024);
	Codex_reg_write(CODEX_REG_WRAM, 0x3704);
	Codex_reg_write(CODEX_REG_WRAM, 0xc024);
	Codex_reg_write(CODEX_REG_WRAM, 0x3b81);
	Codex_reg_write(CODEX_REG_WRAM, 0x8024);
	Codex_reg_write(CODEX_REG_WRAM, 0x3101);

	Codex_reg_write(CODEX_REG_WRAM, 0x8024);
	Codex_reg_write(CODEX_REG_WRAM, 0x3b81);
	Codex_reg_write(CODEX_REG_WRAM, 0x8024);
	Codex_reg_write(CODEX_REG_WRAM, 0x3f04);
	Codex_reg_write(CODEX_REG_WRAM, 0xc024);
	Codex_reg_write(CODEX_REG_WRAM, 0x2808);
	Codex_reg_write(CODEX_REG_WRAM, 0x4800);
	Codex_reg_write(CODEX_REG_WRAM, 0x36f1);

	Codex_reg_write(CODEX_REG_WRAM, 0x9811);
	Codex_reg_write(CODEX_REG_WRAMADDR, 0x8028);
	Codex_reg_write(CODEX_REG_WRAM, 0x2a00);
	Codex_reg_write(CODEX_REG_WRAM, 0x040e);



	while(1)
	{
		Codex_reg_read(CODEX_REG_HDAT1, &temp);
		if(!(temp>>8)) break;
	}

}

void Codex_Stop_Recode()
{
	Codex_reg_write(CODEX_REG_AICTRL3, 1);
}

void Codex_Send_Music(uint8_t *data)
{
	int i;
	uint8_t RxData[32];

	while(HAL_GPIO_ReadPin(VS_DERQ_GPIO_Port, VS_DERQ_Pin) ==  GPIO_PIN_RESET);

	HAL_GPIO_WritePin(VS_XCS_GPIO_Port, VS_XCS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(VS_XDCS_GPIO_Port, VS_XDCS_Pin, GPIO_PIN_SET);

	HAL_SPI_TransmitReceive(&hspi1, data, RxData, 32, 100);

	HAL_GPIO_WritePin(VS_XDCS_GPIO_Port, VS_XDCS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(VS_XCS_GPIO_Port, VS_XCS_Pin, GPIO_PIN_RESET);
}

void Codex_Sin_Test(uint8_t n, uint16_t ms)
{
	uint8_t pTxData1[8] = {0x53, 0xef, 0x6e, n, 0x00, 0x00, 0x00, 0x00};
	uint8_t pTxData2[8] = {0x45, 0x78, 0x69, 0x74, 0x00, 0x00, 0x00, 0x00};

	uint8_t pRxData[8];

	Codex_Vol(0x5a70);
	Codex_reg_write(CODEX_REG_MODE, 0x0820);

	while(!HAL_GPIO_ReadPin(VS_DERQ_GPIO_Port, VS_DERQ_Pin));


	HAL_GPIO_WritePin(VS_XCS_GPIO_Port, VS_XCS_Pin, GPIO_PIN_RESET);  //CS low
	HAL_SPI_TransmitReceive(&hspi1, pTxData1, pRxData, 8, 100);
	HAL_GPIO_WritePin(VS_XCS_GPIO_Port, VS_XCS_Pin, GPIO_PIN_SET);  //CS high
	HAL_Delay(ms);

	HAL_GPIO_WritePin(VS_XCS_GPIO_Port, VS_XCS_Pin, GPIO_PIN_RESET);  //CS low
	HAL_SPI_TransmitReceive(&hspi1, pTxData2, pRxData, 8, 100);
	HAL_GPIO_WritePin(VS_XCS_GPIO_Port, VS_XCS_Pin, GPIO_PIN_SET);  //CS high


}

void Codex_on()
{
	HAL_GPIO_WritePin(VS_RST_GPIO_Port, VS_RST_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
}

void Codex_off()
{
	HAL_GPIO_WritePin(VS_RST_GPIO_Port, VS_RST_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
}

void Codex_reg_read(uint8_t addr, uint16_t* data)
{
	uint8_t pTxData[4];
	uint8_t pRxData[4];

	pTxData[0] = CODEX_READ;
	pTxData[1] = addr;


	while(HAL_GPIO_ReadPin(VS_DERQ_GPIO_Port, VS_DERQ_Pin) ==  GPIO_PIN_RESET);

	HAL_GPIO_WritePin(VS_XCS_GPIO_Port, VS_XCS_Pin, GPIO_PIN_RESET);  //CS low
	HAL_SPI_TransmitReceive(&hspi1, pTxData, pRxData, 4, 100);
	HAL_GPIO_WritePin(VS_XCS_GPIO_Port, VS_XCS_Pin, GPIO_PIN_SET);  //CS high


	*data = (pRxData[2]<<8) | pRxData[3];
}

void Codex_reg_write(uint8_t addr, uint16_t data)
{
	uint8_t pTxData[4];
	uint8_t pRxData[4];

	pTxData[0] = CODEX_WRITE;
	pTxData[1] = addr;
	pTxData[2] = 0xff & (data >> 8);
	pTxData[3] = 0xff & data;


	while(HAL_GPIO_ReadPin(VS_DERQ_GPIO_Port, VS_DERQ_Pin) ==  GPIO_PIN_RESET);

	HAL_GPIO_WritePin(VS_XCS_GPIO_Port, VS_XCS_Pin, GPIO_PIN_RESET);  //CS low
	HAL_SPI_TransmitReceive(&hspi1, pTxData, pRxData, 4, 100);
	HAL_GPIO_WritePin(VS_XCS_GPIO_Port, VS_XCS_Pin, GPIO_PIN_SET);  //CS high

}

void Codex_Vol_off()
{
	Codex_reg_write(CODEX_REG_VOL, 0xffff);
}

void Codex_Vol(uint16_t vol)
{
	Codex_reg_write(CODEX_REG_VOL, vol);
}



void Codex_Speaker_on()
{
	Codex_reg_write(CODEX_REG_WRAMADDR, CODEX_MEM_DDR);
	Codex_reg_write(CODEX_REG_WRAM, 0x10);

	Codex_reg_write(CODEX_REG_WRAMADDR, CODEX_MEM_ODATA);
	Codex_reg_write(CODEX_REG_WRAM, 0x10);
}

void Codex_Speaker_off()
{
	Codex_reg_write(CODEX_REG_WRAMADDR, CODEX_MEM_DDR);
	Codex_reg_write(CODEX_REG_WRAM, 0x10);

	Codex_reg_write(CODEX_REG_WRAMADDR, CODEX_MEM_ODATA);
	Codex_reg_write(CODEX_REG_WRAM, 0x00);
}


void Codex_HW_Reset()
{
	  Codex_off();
	  Codex_on();
}

void Codex_SW_Reset()
{
	Codex_reg_write(CODEX_REG_MODE, CODEX_MODE_SM_RESET);
	HAL_Delay(100);
}

