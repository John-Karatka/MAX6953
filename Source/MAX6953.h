#include <stddef.h>
#ifndef MAX6953_H_
#define MAX6953_H_

#include <stdint.h>

#define INVERT_LEDS_ON true
#define INVERT_LEDS_OFF false
#define CONFIG_DEFAULT 0x01
#define DIGIT_0_P0 0x20
#define DIGIT_0_P1 0x40
#define INTENSITY_10 0x01
#define INTENSITY_32 0x02
#define MAX_BRIGHT 0x77
#define EN_ALL_DIGIT 0x01
#define CONFIGURATION 0x04
#define MAX_INIT_SUCCESS 0
#define CUSTOM_FONT_ADDR 0x05

typedef enum {
	RAM_DISPLAY_ADDR_0 = 0x00,
	RAM_DISPLAY_ADDR_1,
	RAM_DISPLAY_ADDR_2,
	RAM_DISPLAY_ADDR_3,
	RAM_DISPLAY_ADDR_4,
	RAM_DISPLAY_ADDR_5,
	RAM_DISPLAY_ADDR_6,
	RAM_DISPLAY_ADDR_7,
	RAM_DISPLAY_ADDR_8,
	RAM_DISPLAY_ADDR_9,
	RAM_DISPLAY_ADDR_10,
	RAM_DISPLAY_ADDR_11,
	RAM_DISPLAY_ADDR_12,
	RAM_DISPLAY_ADDR_13,
	RAM_DISPLAY_ADDR_14,
	RAM_DISPLAY_ADDR_15,
	RAM_DISPLAY_ADDR_16,
	RAM_DISPLAY_ADDR_17,
	RAM_DISPLAY_ADDR_18,
	RAM_DISPLAY_ADDR_19,
	RAM_DISPLAY_ADDR_20,
	RAM_DISPLAY_ADDR_21,
	RAM_DISPLAY_ADDR_22,
	RAM_DISPLAY_ADDR_23
}ramDisplayAddr_t;

typedef enum {
	RAM_WRITE_ADDR_0 = 0x80,
	RAM_WRITE_ADDR_1 = 0x85,
	RAM_WRITE_ADDR_2 = 0x8A,
	RAM_WRITE_ADDR_3 = 0x8F,
	RAM_WRITE_ADDR_4 = 0x94,
	RAM_WRITE_ADDR_5 = 0x99,
	RAM_WRITE_ADDR_6 = 0x9E,
	RAM_WRITE_ADDR_7 = 0xA3,
	RAM_WRITE_ADDR_8 = 0xA8,
	RAM_WRITE_ADDR_9 = 0xAD,
	RAM_WRITE_ADDR_10 = 0xB2,
	RAM_WRITE_ADDR_11 = 0xB7,
	RAM_WRITE_ADDR_12 = 0xBC,
	RAM_WRITE_ADDR_13 = 0xC1,
	RAM_WRITE_ADDR_14 = 0xC6,
	RAM_WRITE_ADDR_15 = 0xCB,
	RAM_WRITE_ADDR_16 = 0xD0,
	RAM_WRITE_ADDR_17 = 0xD5,
	RAM_WRITE_ADDR_18 = 0xDA,
	RAM_WRITE_ADDR_19 = 0xDF,
	RAM_WRITE_ADDR_20 = 0xE4,
	RAM_WRITE_ADDR_21 = 0xE9,
	RAM_WRITE_ADDR_22 = 0xEE,
	RAM_WRITE_ADDR_23 = 0xF3
}ramWriteAddr_t;

typedef enum {
	SCROLL_SPEED_50MS = 50,
	SCROLL_SPEED_100MS = 100,
	SCROLL_SPEED_150MS = 150,
	SCROLL_SPEED_200MS = 200,
	SCROLL_SPEED_300MS = 300,
	SCROLL_SPEED_400MS = 400,
	SCROLL_SPEED_500MS = 500
}scroll_speed_t;

typedef enum {
	BLINK_OFF = 0x00,
	BLINK_ON
}blinkSetting_t;

typedef enum {
	BLINK_SLOW = 0x00,
	BLINK_FAST
}blinkRate_t;

class MAX6953 {
  private:
	uint8_t address;
  public:
	MAX6953(uint8_t MAX_I2C_ADDRESS);
	int init();
	int init(blinkSetting_t blinkSetting, blinkRate_t blinkRate);
	uint16_t getBrightness();
	void setBrightness(uint8_t brightness);
	void updateDisplayPane0(char digit_0, char digit_1, char digit_2, char digit_3);
	void updateDisplayPane0(char digit_0, char digit_1, char digit_2, char digit_3, bool invertLeds);
	void updateDisplayPane1(char digit_0, char digit_1, char digit_2, char digit_3);
	void updateDisplayPane1(char digit_0, char digit_1, char digit_2, char digit_3, bool invertLeds);
	uint8_t readReg(uint8_t reg);
	void setReg(uint8_t reg, uint8_t data);
	void setCustomCharacter(ramWriteAddr_t ramRegCustAddr, uint8_t fontColumn_1, uint8_t fontColumn_2, uint8_t fontColumn_3, uint8_t fontColumn_4, uint8_t fontColumn_5);
	void displayScrollText(const char *textArray, size_t textLength, scroll_speed_t scroll_speed);
};

#endif
