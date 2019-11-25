#include "board.h"
#include <util/delay.h>

typedef board::Serial_C0 SerialOut;

int main( void ) {
    SerialOut::init<9600, true>();
    SerialOut::start();

    while(1) {
        _delay_ms(1000);  // Wait for 1/2 second
        SerialOut::write("Hello World\n", 12);
    }
}
