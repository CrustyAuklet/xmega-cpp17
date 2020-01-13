#include "board.hpp"
#include "nonstd/cstdio.hpp"
//#include <avr/eeprom.h>

[[gnu::OS_main]] int main() {
	const bool accel_good = board::accelerometer.start();
    const bool fifo_on = board::accelerometer.startFIFO(board::acceleration::SLEEP_DURATION::D_100MS);

    nonstd::print("\n\n%S version %d\n"_fstr, board::name, static_cast<uint8_t>(board::board_version));
    nonstd::print("\tAccelerometer: %S"_fstr, accel_good ? board::accelerometer.name() : "Failed"_fstr );
    if(accel_good && fifo_on) {
        nonstd::print(", Fifo at 10Hz\n"_fstr);
    }
    else {
        nonstd::print(", Fifo failed\n"_fstr);
    }

    for(;;) {
        board::delay_ms(750); // delay 1 second
		board::LED.on();
        board::delay_ms(250);
        board::LED.off();

		const auto r1 = board::accelerometer.FIFO_Status();
		nonstd::print("FIFO count: %d (overflow: %d)\n"_fstr, r1.first, r1.second);
		std::array<peripheral::accel::Acceleration, 32> buf{};
        const auto r2 = board::accelerometer.readFIFO(buf, r1.first);
		for(uint8_t i = 0; r2.has_value() && i < r2.value(); ++i) {
		    nonstd::print("  %d %d %d\n"_fstr,
		            board::accelerometer.scale_reading(buf[i].x, peripheral::accel::BMA250X::RANGE::R_2G),
		            board::accelerometer.scale_reading(buf[i].y, peripheral::accel::BMA250X::RANGE::R_2G),
		            board::accelerometer.scale_reading(buf[i].z, peripheral::accel::BMA250X::RANGE::R_2G));
		}

		const auto time = board::rtc.read_time();
        nonstd::print("Time:  %d-%d-%d %d:%d:%d\n"_fstr, time->day, time->month, time->year, time->hour, time->minute, time->second);
    }
}
