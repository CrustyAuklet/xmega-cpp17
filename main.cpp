#include "board.hpp"
#include "printf.h"

static inline float si705x_celsius(const uint16_t READING) { return ((175.72 * READING) / 65536) - 46.85; }
	
static uint8_t bitswap(uint8_t input){
    unsigned char output = 0;
    for (int k = 0; k < 8; k++) {
        output |= ((input >> k) & 0x01) << (7 - k);
    }
    return output;
}

static uint8_t crc8(void* inData, uint8_t len, uint8_t init){
    uint8_t* data = (uint8_t*)inData;
    uint8_t crc = bitswap(init);

    for (int i=0; i<len;i++)
    {
        uint8_t inbyte = bitswap(data[i]);
        for (uint8_t j=0;j<8;j++)
        {
            uint8_t mix = (crc ^ inbyte) & 0x01;
            crc >>= 1;
            if (mix)
            crc ^= 0x8C;

            inbyte >>= 1;
        }
    }
    return bitswap(crc);
}

[[gnu::OS_main]] int main() {
    board::init();
	uint16_t counter = 0;

    while(1) {
        board::delay_ms(1000); // delay 1 second
        printf("Hello World! %d\n", counter);
		board::UserLED.toggle();
		counter++;
		
		uint8_t buf[3] = {0xE3};
		board::I2C_C.write(0x80, buf, 1);
		board::I2C_C.read(0x80, buf, 3);
		const uint16_t temp_code = (buf[0] << 8U) | buf[1];

		if( !(crc8(buf, 2, 0x00) == buf[2]) ) {
            printf("CRC doesn't match!");
        }
		else {
		    printf("Read: 0x%02X 0x%02X 0x%02X --> %3.2f\n", buf[0], buf[1], buf[2], static_cast<double>(si705x_celsius(temp_code)) );
		}

		uint16_t adc_reading = board::ADC.read(0);
		printf("ADC Read: 0x%02X 0x%02X --> %d\n", adc_reading >> 8, adc_reading & 0xFFU, adc_reading);
    }
}
