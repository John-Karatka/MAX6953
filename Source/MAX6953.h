#ifndef MAX6953_H_
#define MAX6953_H_

#include <stdint.h>

#define INVERT_LEDS_ON true
#define INVERT_LEDS_OFF false
#define CONFIG_DEFAULT 0x01
#define MAX6953_EN_BLINK true
#define MAX6953_NO_BLINK false
#define BLINK_FAST 1
#define BLINK_SLOW 0
#define DIGIT_0_P0 0x20
#define DIGIT_0_P1 0x40
#define INTENSITY_10 0x01
#define INTENSITY_32 0x02
#define MAX_BRIGHT 0x77
#define EN_ALL_DIGIT 0x01
#define CONFIGURATION 0x04
#define MAX_INIT_SUCCESS 0
#define CUSTOM_FONT_ADDR 0x05
#define RAM_WRITE_ADDR_0 0x80
#define RAM_WRITE_ADDR_1 0x85
#define RAM_WRITE_ADDR_2 0x8A
#define RAM_WRITE_ADDR_3 0x8F
#define RAM_WRITE_ADDR_4 0x94
#define RAM_WRITE_ADDR_5 0x99
#define RAM_WRITE_ADDR_6 0x9E
#define RAM_WRITE_ADDR_7 0xA3
#define RAM_WRITE_ADDR_8 0xA8
#define RAM_WRITE_ADDR_9 0xAD
#define RAM_WRITE_ADDR_10 0xB2
#define RAM_WRITE_ADDR_11 0xB7
#define RAM_WRITE_ADDR_12 0xBC
#define RAM_WRITE_ADDR_13 0xC1
#define RAM_WRITE_ADDR_14 0xC6
#define RAM_WRITE_ADDR_15 0xCB
#define RAM_WRITE_ADDR_16 0xD0
#define RAM_WRITE_ADDR_17 0xD5
#define RAM_WRITE_ADDR_18 0xDA
#define RAM_WRITE_ADDR_19 0xDF
#define RAM_WRITE_ADDR_20 0xE4
#define RAM_WRITE_ADDR_21 0xE9
#define RAM_WRITE_ADDR_22 0xEE
#define RAM_WRITE_ADDR_23 0xF3
#define RAM_DISPLAY_ADDR_0 0x00
#define RAM_DISPLAY_ADDR_1 0x01
#define RAM_DISPLAY_ADDR_2 0x02
#define RAM_DISPLAY_ADDR_3 0x03
#define RAM_DISPLAY_ADDR_4 0x04
#define RAM_DISPLAY_ADDR_5 0x05
#define RAM_DISPLAY_ADDR_6 0x06
#define RAM_DISPLAY_ADDR_7 0x07
#define RAM_DISPLAY_ADDR_8 0x08
#define RAM_DISPLAY_ADDR_9 0x09
#define RAM_DISPLAY_ADDR_10 0x0A
#define RAM_DISPLAY_ADDR_11 0x0B
#define RAM_DISPLAY_ADDR_12 0x0C
#define RAM_DISPLAY_ADDR_13 0x0D
#define RAM_DISPLAY_ADDR_14 0x0E
#define RAM_DISPLAY_ADDR_15 0x0F
#define RAM_DISPLAY_ADDR_16 0x10
#define RAM_DISPLAY_ADDR_17 0x11
#define RAM_DISPLAY_ADDR_18 0x12
#define RAM_DISPLAY_ADDR_19 0x13
#define RAM_DISPLAY_ADDR_20 0x14
#define RAM_DISPLAY_ADDR_21 0x15
#define RAM_DISPLAY_ADDR_22 0x16
#define RAM_DISPLAY_ADDR_23 0x17

class MAX6953 {
  private:
    uint8_t address;
  public:
    MAX6953(uint8_t MAX_I2C_ADDRESS);
    int init();
	int init(bool EN_BLINK, bool BLINK_RATE);
    uint16_t getBrightness();
    void setBrightness(uint8_t BRIGHTNESS);
    void updateDisplayPane0(char DIGIT_1, char DIGIT_2, char DIGIT_3, char DIGIT_4);
	void updateDisplayPane0(char DIGIT_1, char DIGIT_2, char DIGIT_3, char DIGIT_4, bool INVERT_LEDS);
    void updateDisplayPane1(char DIGIT_1, char DIGIT_2, char DIGIT_3, char DIGIT_4);
	void updateDisplayPane1(char DIGIT_1, char DIGIT_2, char DIGIT_3, char DIGIT_4, bool INVERT_LEDS);
    uint8_t readReg(uint8_t REGISTER);
    void setReg(uint8_t REGISTER, uint8_t DATA);
	void setCustomCharacter(uint8_t RAM_REG_START_ADDR, uint8_t FONT_0, uint8_t FONT_1, uint8_t FONT_2, uint8_t FONT_3, uint8_t FONT_4);
};

#endif
