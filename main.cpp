#include "board.hpp"
#include "stdio.h"

#include "peripherals/motion/BMA250X.hpp"

//namespace board {
//    namespace acceleration {
//        using namespace peripheral::accel::BMA250X;
//    }
//    //inline peripheral::accel::BMA250X_simple accelerometer(I2C_Isolated);
//}

[[gnu::OS_main]] int main() {
	uint16_t counter = 0;
	board::accelerometer.start();

    if( board::accelerometer.present() ) {
        if(board::accelerometer.is_250e()) {
            printf("BMA250E found on bus\n");
        }
        else {
            printf("BMA250 found\n");
        }
//        board::accelerometer.set_mode( board::acceleration::MODE::NORMAL);
    }
    else {
        printf("Accelerometer not found!\n");
    }

    const bool fifo_on = board::accelerometer.startFIFO(board::acceleration::SLEEP_DURATION::D_1000MS);
    if(fifo_on){
        printf("Fifo started at 10Hz\n");
    }
    else {
        printf("Fifo failed to start\n");
    }

    for(;;) {
        board::delay_ms(1000); // delay 1 second
        printf("Hello World! %d\n", counter++);
		board::LED.on();
        board::delay_ms(250);
        board::LED.off();

		//const auto r = board::accelerometer.read();
		const auto r = board::accelerometer.FIFO_Status();
		printf("FIFO count: %d (overflow: %d)\n", r.first, r.second);

    }
}
