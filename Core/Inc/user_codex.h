/*
 * user_codex.h
 *
 *  Created on: May 4, 2021
 *      Author: sangho
 */

#ifndef INC_USER_CODEX_H_
#define INC_USER_CODEX_H_

#include "main.h"


#define CODEX_READ	0x03
#define CODEX_WRITE	0x02

#define CODEX_REG_MODE		0x00
#define CODEX_REG_CLOCKF	0x03
#define CODEX_REG_AUDATA	0x05
#define CODEX_REG_WRAM		0x06
#define CODEX_REG_WRAMADDR	0x07
#define CODEX_REG_HDAT0		0x08
#define CODEX_REG_HDAT1		0x09
#define CODEX_REG_VOL		0x0b

#define CODEX_REG_AIADDR	0x0a
#define CODEX_REG_AICTRL0	0x0c
#define CODEX_REG_AICTRL1	0x0d
#define CODEX_REG_AICTRL2	0x0e
#define CODEX_REG_AICTRL3	0x0f

#define CODEX_MEM_DDR		0xc017
#define CODEX_MEM_ODATA		0xc019

#define CODEX_MODE_SM_DIFF		0x0001
#define CODEX_MODE_SM_LAYER12 	0x0002
#define CODEX_MODE_SM_RESET 	0x0004
#define CODEX_MODE_SM_CANCEL	0x0008
#define CODEX_MODE_SM_EARSPKLO 	0x0010
#define CODEX_MODE_SM_TESTS 	0x0020
#define CODEX_MODE_SM_STREAM 	0x0040
#define CODEX_MODE_SM_SDINEW 	0x0800
#define CODEX_MODE_SM_ADPCM 	0x1000
#define CODEX_MODE_SM_LINE1 	0x4000
#define CODEX_MODE_SM_CLKRANGE  0x8000

#define CODEX_MEM_CHIP_ID0		0x1e00
#define CODEX_MEM_CHIP_ID1		0x1e01
#define CODEX_MEM_VERSION		0x1e02
#define CODEX_MEM_CONFIG1		0x1e03
#define CODEX_MEM_BYTESLEFT1	0x1e2a
#define CODEX_MEM_BYTESLEFT2	0x1e2b



#define CODEX_BANK_DEFAULT 0x00
#define CODEX_BANK_DRUMS1 0x78
#define CODEX_BANK_DRUMS2 0x7F
#define CODEX_BANK_MELODY 0x79

#define MIDI_NOTE_ON  0x90
#define MIDI_NOTE_OFF 0x80
#define MIDI_CHAN_MSG 0xB0
#define MIDI_CHAN_BANK 0x00
#define MIDI_CHAN_VOLUME 0x07
#define MIDI_CHAN_PROGRAM 0xC0

void Codex_Sin_Test(uint8_t n, uint16_t ms);

void Codex_on();
void Codex_off();
void Codex_reg_read(uint8_t addr, uint16_t* data);
void Codex_reg_write(uint8_t addr, uint16_t data);

void Codex_Vol_off();
void Codex_Vol(uint16_t vol);
void Codex_Speaker_on();
void Codex_Speaker_off();

void Codex_Start_Record();
uint8_t Codex_Record();
void Codex_Send_Music(uint8_t *data);


void Codex_MIDI_Set_Instrument(uint8_t ch, uint8_t inst);
void Codex_MIDI_Set_Ch_Vol(uint8_t ch, uint8_t vol);
void Codex_MIDI_Set_Ch_Bank(uint8_t ch, uint8_t bank);
void Codex_MIDI_NoteOn(uint8_t ch, uint8_t note, uint8_t pressure);
void Codex_MIDI_NoteOff(uint8_t ch, uint8_t note, uint8_t pressure);
void Codex_MIDI_Mode();
void Codex_SDI_Tx(uint8_t data);

void Codex_HW_Reset();
void Codex_SW_Reset();

#endif /* INC_USER_CODEX_H_ */
