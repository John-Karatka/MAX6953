#include "MAX6953.h"
#include <stdint.h>
#include <Wire.h>

MAX6953::MAX6953(uint8_t MAX_I2C_ADDRESS) {
	address = MAX_I2C_ADDRESS;
	Wire.begin();
}

int MAX6953::init(bool EN_BLINK) {
	int ack;
	Wire.beginTransmission(address);
	Wire.write(CONFIGURATION);
	if (EN_BLINK) {
		Wire.write(BLINK_ON);
	}
	else {
		Wire.write(BLINK_OFF);
	}
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

void MAX6953::setBrightness(uint8_t BRIGHTNESS) {
	Wire.beginTransmission(address);
	Wire.write(INTENSITY_10);
	Wire.write(BRIGHTNESS);
	Wire.write(BRIGHTNESS);
	Wire.endTransmission();
}

void MAX6953::updateDisplayPane0(char DIGIT_1, char DIGIT_2, char DIGIT_3, char DIGIT_4) {
	Wire.beginTransmission(address);
	Wire.write(DIGIT_0_P0);
	Wire.write(DIGIT_1);
	Wire.write(DIGIT_2);
	Wire.write(DIGIT_3);
	Wire.write(DIGIT_4);
	Wire.endTransmission();
}

void MAX6953::updateDisplayPane0(char DIGIT_1, char DIGIT_2, char DIGIT_3, char DIGIT_4, bool INVERT_LEDS) {
	if (INVERT_LEDS) {
		DIGIT_1 = DIGIT_1 | (1<<7);
		DIGIT_2 = DIGIT_2 | (1<<7);
		DIGIT_3 = DIGIT_3 | (1<<7);
		DIGIT_4 = DIGIT_4 | (1<<7);
  }
  else {
    DIGIT_1 = DIGIT_1 & ~(1<<7);
		DIGIT_2 = DIGIT_2 & ~(1<<7);
		DIGIT_3 = DIGIT_3 & ~(1<<7);
		DIGIT_4 = DIGIT_4 & ~(1<<7);
  }
	
	Wire.beginTransmission(address);
	Wire.write(DIGIT_0_P0);
	Wire.write(DIGIT_1);
	Wire.write(DIGIT_2);
	Wire.write(DIGIT_3);
	Wire.write(DIGIT_4);
	Wire.endTransmission();
}

void MAX6953::updateDisplayPane1(char DIGIT_1, char DIGIT_2, char DIGIT_3, char DIGIT_4) {
	Wire.beginTransmission(address);
	Wire.write(DIGIT_0_P1);
	Wire.write(DIGIT_1);
	Wire.write(DIGIT_2);
	Wire.write(DIGIT_3);
	Wire.write(DIGIT_4);
	Wire.endTransmission();
}

uint8_t MAX6953::readReg(uint8_t REGISTER) {
	int readLength = 1;
	uint8_t readData[1];
	Wire.beginTransmission(address);
	Wire.write(REGISTER);
	Wire.endTransmission(false);
	Wire.requestFrom(address, readLength);
	while (Wire.available()) {
		for (int i = 0; i < readLength; i++) {
			readData[i] = Wire.read();
		}
	}
	return(readData[0]);
}

void MAX6953::setReg(uint8_t REGISTER, uint8_t DATA) {
	Wire.beginTransmission(address);
	Wire.write(REGISTER);
	Wire.write(DATA);
	Wire.endTransmission();
}

void MAX6953::setCustomCharacter(uint8_t RAM_REG_START_ADDR, uint8_t FONT_0, uint8_t FONT_1, uint8_t FONT_2, uint8_t FONT_3, uint8_t FONT_4) {
	Wire.beginTransmission(address);
	Wire.write(CUSTOM_FONT_ADDR);
	Wire.write(RAM_REG_START_ADDR);
	Wire.write((FONT_0 & ~(1<<7)));
	Wire.write((FONT_1 & ~(1<<7)));
	Wire.write((FONT_2 & ~(1<<7)));
	Wire.write((FONT_3 & ~(1<<7)));
	Wire.write((FONT_4 & ~(1<<7)));
	Wire.endTransmission();
}
