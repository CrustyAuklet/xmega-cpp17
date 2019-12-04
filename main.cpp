#include "board.hpp"
#include <util/delay.h>

[[gnu::OS_main]] int main() {
    board::SerialC0.init<board::CPUFreq, 9600, true>();
    board::SerialC0.start();
    board::UserLED.init();

    while(1) {
        _delay_ms(1000);  // Wait for 1/2 second
        board::SerialC0.write("Hello World\n", 12);
		board::UserLED.toggle();
    }
}
