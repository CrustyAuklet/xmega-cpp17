#include "board.h"
#include <util/delay.h>

int main( void ) {
    board::SerialC0.init<9600, true>();
    board::SerialC0.start();

    while(1) {
        _delay_ms(1000);  // Wait for 1/2 second
        board::SerialC0.write("Hello World\n", 12);
    }
}
