#include "MAX6953.h"
#include <stdint.h>
#include <Wire.h>

MAX6953::MAX6953(uint8_t MAX_I2C_ADDRESS) {
	address = MAX_I2C_ADDRESS;
	Wire.begin();
}

int MAX6953::init() {
	int ack;
	Wire.beginTransmission(address);
	Wire.write(CONFIGURATION);
	Wire.write(CONFIG_DEFAULT);
	Wire.endTransmission();
	delay(100);
	Wire.beginTransmission(address);
	Wire.write(INTENSITY_10);
	Wire.write(MAX_BRIGHT); //Set brightness of digit 0 and digit 2
	Wire.write(MAX_BRIGHT); //Set brightness of digit 1 and digit 3
	Wire.write(EN_ALL_DIGIT);
	ack = Wire.endTransmission();
	return(ack);
}

int MAX6953::init(blinkSetting_t blinkSetting, blinkRate_t blinkRate) {
	int ack;
	uint8_t config_data = CONFIG_DEFAULT;
	Wire.beginTransmission(address);
	Wire.write(CONFIGURATION);
	if (blinkSetting == BLINK_ON) {
		config_data = config_data | (1<<3);
	}
	if (blinkRate == BLINK_FAST) {
		config_data = config_data | (1<<2);
	}
	Wire.write(config_data);
	Wire.endTransmission();
	delay(100);
	Wire.beginTransmission(address);
	Wire.write(INTENSITY_10);
	Wire.write(MAX_BRIGHT); //Set brightness of digit 0 and digit 2
	Wire.write(MAX_BRIGHT); //Set brightness of digit 1 and digit 3
	Wire.write(EN_ALL_DIGIT);
	ack = Wire.endTransmission();
	return(ack);
}

uint16_t MAX6953::getBrightness() {
	uint16_t brightness;
	uint8_t readData[2];
	int readLength = 2;
	
	Wire.beginTransmission(address);
	Wire.write(INTENSITY_10);
	Wire.endTransmission(false);
	Wire.requestFrom(address, readLength);
	while (Wire.available()) {
		for (int i = 0; i < readLength; i++) {
			readData[i] = Wire.read();
		}
	}
	brightness = (((uint16_t)readData[1] & 0x00FF) | (((uint16_t)readData[1] << 8) & 0xFF00));
	return(brightness);
}

void MAX6953::setBrightness(uint8_t brightness) {
	Wire.beginTransmission(address);
	Wire.write(INTENSITY_10);
	Wire.write(brightness);
	Wire.write(brightness);
	Wire.endTransmission();
}

void MAX6953::updateDisplayPane0(char digit_0, char digit_1, char digit_2, char digit_3) {
	Wire.beginTransmission(address);
	Wire.write(DIGIT_0_P0);
	Wire.write(digit_0);
	Wire.write(digit_1);
	Wire.write(digit_2);
	Wire.write(digit_3);
	Wire.endTransmission();
}

void MAX6953::updateDisplayPane0(char digit_0, char digit_1, char digit_2, char digit_3, bool invertLeds) {
	if (invertLeds) {
		digit_0 = digit_0 | (1<<7);
		digit_1 = digit_1 | (1<<7);
		digit_2 = digit_2 | (1<<7);
		digit_3 = digit_3 | (1<<7);
  	}
  	else {
    		digit_0 = digit_0 & ~(1<<7);
		digit_1 = digit_1 & ~(1<<7);
		digit_2 = digit_2 & ~(1<<7);
		digit_3 = digit_3 & ~(1<<7);
  	}
	
	Wire.beginTransmission(address);
	Wire.write(DIGIT_0_P0);
	Wire.write(digit_0);
	Wire.write(digit_1);
	Wire.write(digit_2);
	Wire.write(digit_3);
	Wire.endTransmission();
}

void MAX6953::updateDisplayPane1(char digit_0, char digit_1, char digit_2, char digit_3) {
	Wire.beginTransmission(address);
	Wire.write(DIGIT_0_P1);
	Wire.write(digit_0);
	Wire.write(digit_1);
	Wire.write(digit_2);
	Wire.write(digit_3);
	Wire.endTransmission();
}

void MAX6953::updateDisplayPane1(char digit_0, char digit_1, char digit_2, char digit_3, bool invertLeds) {
	if (invertLeds) {
		digit_0 = digit_0 | (1<<7);
		digit_1 = digit_1 | (1<<7);
		digit_2 = digit_2 | (1<<7);
		digit_3 = digit_3 | (1<<7);
	}
	else {
		digit_0 = digit_0 & ~(1<<7);
		digit_1 = digit_1 & ~(1<<7);
		digit_2 = digit_2 & ~(1<<7);
		digit_3 = digit_3 & ~(1<<7);
	}
	
	Wire.beginTransmission(address);
	Wire.write(DIGIT_0_P1);
	Wire.write(digit_0);
	Wire.write(digit_1);
	Wire.write(digit_2);
	Wire.write(digit_3);
	Wire.endTransmission();
}

uint8_t MAX6953::readReg(uint8_t reg) {
	int readLength = 1;
	uint8_t readData[1];
	Wire.beginTransmission(address);
	Wire.write(reg);
	Wire.endTransmission(false);
	Wire.requestFrom(address, readLength);
	while (Wire.available()) {
		for (int i = 0; i < readLength; i++) {
			readData[i] = Wire.read();
		}
	}
	return(readData[0]);
}

void MAX6953::setReg(uint8_t reg, uint8_t data) {
	Wire.beginTransmission(address);
	Wire.write(reg);
	Wire.write(data);
	Wire.endTransmission();
}

void MAX6953::setCustomCharacter(ramWriteAddr_t ramRegCustAddr, uint8_t fontColumn_1, uint8_t fontColumn_2, uint8_t fontColumn_3, uint8_t fontColumn_4, uint8_t fontColumn_5) {
	Wire.beginTransmission(address);
	Wire.write(CUSTOM_FONT_ADDR);
	Wire.write(ramRegCustAddr);
	Wire.write((fontColumn_1 & ~(1<<7)));
	Wire.write((fontColumn_2 & ~(1<<7)));
	Wire.write((fontColumn_3 & ~(1<<7)));
	Wire.write((fontColumn_4 & ~(1<<7)));
	Wire.write((fontColumn_5 & ~(1<<7)));
	Wire.endTransmission();
}

void MAX6953::displayScrollText(const char *textArray, size_t textLength, scroll_speed_t scrollSpeed) {
	if ((textLength == 0) || (textArray == NULL)) {
		return;
	}

	char newText[textLength + 8];
	for (int n = 0; n < textLength; n++) {
		newText[n + 4] = textArray[n];
	}

	//Add space characters to beginning and end
	newText[0] = ' ';
	newText[1] = ' ';
	newText[2] = ' ';
	newText[3] = ' ';
	newText[textLength + 3] = ' ';
	newText[textLength + 4] = ' ';
	newText[textLength + 5] = ' ';
	newText[textLength + 6] = ' ';
	
	for (int i = 0; i < textLength + 4; i++) {
		for (int y = 0; y < 4; y++) {
			updateDisplayPane0(newText[i], newText[i + 1], newText[i + 2], newText[i + 3]);
		}
		delay((int)scrollSpeed);
	}
}
