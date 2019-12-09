#include "board.hpp"
#include <cstdio>
#include <cstring>
#include <util/delay.h>

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
	constexpr int BufferSize = 100;
	char buffer[BufferSize];
	uint16_t counter = 0;

    while(1) {
        _delay_ms(1000);  // Wait for 1/2 second
		snprintf(buffer, BufferSize, "Hello World! %d\n", counter);
        board::SerialC0.write(buffer, strlen(buffer));
		board::UserLED.toggle();
		counter++;
		
		uint8_t buf[3] = {0xE3};
		board::I2C_C.write(0x80, buf, 1);
		board::I2C_C.read(0x80, buf, 3);
		const uint16_t temp_code = (buf[0] << 8U) | buf[1];

		if( !(crc8(buf, 2, 0x00) == buf[2]) ) {
            board::EDBG_VCOM.write("CRC doesn't match!", 19);
        }
		else {
			snprintf(buffer, BufferSize, "Read: 0x%02X 0x%02X 0x%02X --> %3.2f\n", buf[0], buf[1], buf[2], si705x_celsius(temp_code));
			board::EDBG_VCOM.write(buffer, strlen(buffer));
		}

		uint16_t acdreading = board::ADC.read(0);
        snprintf(buffer, BufferSize, "ADC Read: 0x%02X 0x%02X --> %d\n", acdreading >> 8, acdreading & 0xFFU, acdreading);
        board::EDBG_VCOM.write(buffer, strlen(buffer));
    }
}
