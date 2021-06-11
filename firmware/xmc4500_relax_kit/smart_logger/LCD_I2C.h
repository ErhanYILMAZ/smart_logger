/*
 * LCD_I2C.h
 *
 *  Created on: 28 Feb 2019
 *      Author: erhan
 */

#ifndef LCD_I2C_H_
#define LCD_I2C_H_



void LCDWriteData(uint8_t data);
void LCDWriteCommand(uint8_t command);
void LCDWriteString(char *s);
void LCDInit(void);
void LCDCursorXY(uint8_t x, uint8_t y);


#endif /* LCD_I2C_H_ */
