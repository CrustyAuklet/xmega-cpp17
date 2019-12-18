#include "board.hpp"
#include "stdio.h"

[[gnu::OS_main]] int main() {
	uint16_t counter = 0;

    for(;;) {
        board::delay_ms(1000); // delay 1 second
        printf("Hello World! %d\n", counter);
		board::LED.on();
        board::delay_ms(250);
        board::LED.off();
		counter++;

		if( const auto chipid = board::I2C_Isolated.read_reg8(0x18<<1, 0x00); chipid ) {
            printf("BMA250 ID: 0x%02X\n", chipid.value());
		}
    }
}
