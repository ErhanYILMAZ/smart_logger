
#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "LCD_I2C.h"



void delay(int n) //Universal delay routine
{
 int i=0,j=0;
 for(i=0;i<=n;i++)
 for(j=0;j<=10;j++);
}

void LCDWriteData(uint8_t data)
{

	uint8_t temp;
	temp = (data & 0xf0) + 9;
	I2C_MASTER_Transmit(&I2C_LCD,true,0x4e,&temp,1,true);

	temp = temp + 0x4;
	I2C_MASTER_Transmit(&I2C_LCD,true,0x4e,&temp,1,true);
	temp = temp & 0xFA;
	I2C_MASTER_Transmit(&I2C_LCD,true,0x4e,&temp,1,true);

	temp = ((data << 4) & 0xf0) + 9;
	I2C_MASTER_Transmit(&I2C_LCD,true,0x4e,&temp,1,true);

	temp = temp + 0x4;
	I2C_MASTER_Transmit(&I2C_LCD,true,0x4e,&temp,1,true);
	temp = temp & 0xFA;
	I2C_MASTER_Transmit(&I2C_LCD,true,0x4e,&temp,1,true);

}

void LCDWriteCommand(uint8_t command)
{

	uint8_t temp;
	temp = (command & 0xf0) + 8;
	I2C_MASTER_Transmit(&I2C_LCD,true,0x4e,&temp,1,true);

	temp = temp + 0x4;
	I2C_MASTER_Transmit(&I2C_LCD,true,0x4e,&temp,1,true);
	temp = temp & 0xFA;
	I2C_MASTER_Transmit(&I2C_LCD,true,0x4e,&temp,1,true);

	temp = ((command << 4) & 0xf0) + 8;
	I2C_MASTER_Transmit(&I2C_LCD,true,0x4e,&temp,1,true);

	temp = temp + 0x4;
	I2C_MASTER_Transmit(&I2C_LCD,true,0x4e,&temp,1,true);
	temp = temp & 0xFA;
	I2C_MASTER_Transmit(&I2C_LCD,true,0x4e,&temp,1,true);

}

void LCDCursorXY(uint8_t x, uint8_t y)
{
	uint8_t address =0;
    switch (x) {
        case (0) : address = 0x80 + (y & 0x0f);
        break;
        case (1) : address = 0xc0 + (y & 0x0f);
        break;
        case (2) : address = 0x94 + (y & 0x0f);
        break;
        case (3) : address = 0xD4 + (y & 0x0f);
        break;
    }

    LCDWriteCommand(address);

}

void LCDWriteString(char *s)
{
	while(*s)
	{
		LCDWriteData(*s);
		s++;
	}
}


void LCDInit(void)
{
	LCDWriteCommand(0x33);
	LCDWriteCommand(0x32);
	LCDWriteCommand(0x28); // 4 bit mode
	LCDWriteCommand(0x01); // clear the screen
	LCDWriteCommand(0x0F); // display on cursor on, cursor blink
	LCDWriteCommand(0x06); // increment cursor
	LCDWriteCommand(0x80); // row 1 column 1
}



