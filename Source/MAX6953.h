#ifndef MAX6953_H_
#define MAX6953_H_

#include <stdint.h>

#define DIGIT_0_P0 0x20
#define DIGIT_0_P1 0x40
#define INTENSITY_10 0x01
#define INTENSITY_32 0x02
#define MAX_BRIGHT 0x77
#define EN_ALL_DIGIT 0x01
#define CONFIGURATION 0x04
#define MAX_INIT_SUCCESS 0
#define BLINK_ON 0x0D
#define BLINK_OFF 0X01

class MAX6953 {
  private:
    uint8_t address;
  public:
    MAX6953(uint8_t MAX_I2C_ADDRESS);
    int init(bool EN_BLINK);
    uint16_t getBrightness();
    void setBrightness(uint8_t BRIGHTNESS);
    void updateDisplayPane0(char DIGIT_1, char DIGIT_2, char DIGIT_3, char DIGIT_4);
    void updateDisplayPane1(char DIGIT_1, char DIGIT_2, char DIGIT_3, char DIGIT_4);
    uint8_t readReg(uint8_t REGISTER);
    void setReg(uint8_t REGISTER, uint8_t DATA);
};

#endif