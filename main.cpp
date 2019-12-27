#include "board.hpp"
#include "stdio.h"
#include "drivers/flash.hpp"
//#include <avr/eeprom.h>
#include <array>
#include "nonstd/static_vector.hpp"
using namespace flash::flash_literals;

// text	   data	    bss	    dec
// 4106	    114	     26	   4246 std::array
// 4106	    114	     26	   4246 constexpr std::array
// 4206	     14	     26	   4246 constexpr std::array in FLASH
// 4310	     14	     26	   4350 constexpr std::array in FLASH from init function using CTAD
// 4206	     14	     26	   4246 constexpr std::array in FLASH from init function with explicit type
// 4206	     14	     26	   4246 constexpr std::array in FLASH using auto and factory function

constexpr auto make_table_impl() noexcept {
    constexpr int size = 50;
    std::experimental::fixed_capacity_vector<uint8_t, 1024> v{};
    for(int i = 0; i < size; ++i) {
        v.push_back(i*2);
    }
    return v;
}

constexpr auto make_table() noexcept {
    constexpr auto data = make_table_impl();
    std::array<uint8_t, data.size() > table{};
    for(unsigned i = 0; i < data.size(); ++i) {
        table[i] = data[i];
    }
    return table;
}

[[gnu::progmem]] constexpr auto test = make_table();

[[gnu::OS_main]] int main() {
	const bool accel_good = board::accelerometer.start();
    const bool fifo_on = board::accelerometer.startFIFO(board::acceleration::SLEEP_DURATION::D_100MS);

    printf_P("\n\n%S version %d1\n"_fstr, board::name, static_cast<uint8_t>(board::board_version));
    printf_P("\tAccelerometer: %S"_fstr, accel_good ? board::accelerometer.name() : "Failed"_fstr );
    if(accel_good && fifo_on) {
        printf_P(", Fifo at 10Hz\n"_fstr);
    }
    else {
        printf_P(", Fifo failed\n"_fstr);
    }

    for(const auto& n : test) {
        printf_P("%d, "_fstr, flash::read(n));
    }
    printf_P("\n\n"_fstr);

    for(;;) {
        board::delay_ms(750); // delay 1 second
		board::LED.on();
        board::delay_ms(250);
        board::LED.off();

		const auto r1 = board::accelerometer.FIFO_Status();
		printf_P("FIFO count: %d (overflow: %d)\n"_fstr, r1.first, r1.second);
		std::array<peripheral::accel::Acceleration, 32> buf{};
        const auto r2 = board::accelerometer.readFIFO(buf, r1.first);
		for(uint8_t i = 0; r2.has_value() && i < r2.value(); ++i) {
		    printf_P("  %d %d %d\n"_fstr,
		            board::accelerometer.scale_reading(buf[i].x, peripheral::accel::BMA250X::RANGE::R_2G),
		            board::accelerometer.scale_reading(buf[i].y, peripheral::accel::BMA250X::RANGE::R_2G),
		            board::accelerometer.scale_reading(buf[i].z, peripheral::accel::BMA250X::RANGE::R_2G));
		}
    }
}
