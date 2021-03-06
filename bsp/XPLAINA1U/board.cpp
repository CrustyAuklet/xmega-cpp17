#include "board.hpp"

#include <util/delay_basic.h>
#include <stdio.h>

#include <algorithm>

extern "C" void _putchar(char character) {
    board::EDBG_VCOM.put(character);
}

//extern "C" int EDBG_putchar(char c, FILE* stream) {
//    board::EDBG_VCOM.put(c);
//    return 0;
//}
//
//extern "C" int EDBG_getchar(FILE* stream) {
//    return board::EDBG_VCOM.get();
//}
//
//FILE EDBG_STREAM{ .flags = _FDEV_SETUP_WRITE, .put = EDBG_putchar, .get = EDBG_getchar, .udata = 0, };

bool board::init() noexcept {
    SerialC0.init<CPUFreq, 9600, true>();
    SerialC0.start();
    EDBG_VCOM.init<CPUFreq, 9600, true>();
    EDBG_VCOM.start();
    I2C_C.init<CPUFreq, 100'000>();
    I2C_C.start();
    UserLED.init();

    ADC.init(drivers::ADC::RESOLUTION::_12BIT);
    ADC.start();
    device::PA0.set_analog();

    //stdout = &EDBG_STREAM;
    return true;
}

extern void __builtin_avr_delay_cycles(unsigned long);

template<uint16_t MS>
void delay_ms() noexcept {
    constexpr uint32_t ticks = ((board::CPUFreq) / 1'000UL) * MS;
    __builtin_avr_delay_cycles(ticks);
}

template<uint16_t US>
void delay_us() noexcept {
    constexpr uint32_t ticks = ((board::CPUFreq) / 1'000'000UL) * US;
    __builtin_avr_delay_cycles(ticks);
}

void board::delay_ms(uint16_t ms) noexcept {
    const uint32_t tmp = std::max(((board::CPUFreq) / 4'000UL) * ms, 1UL);

    if (tmp > 65535) {
        //	ticks = requested delay in 1/10 ms
        auto ticks = static_cast<uint16_t>(ms * 10UL);
        while (ticks) {
            // wait 1/10 ms
            _delay_loop_2(((board::CPUFreq) / 4'000UL) / 10UL);
            --ticks;
        }
    } else {
        auto ticks = static_cast<uint16_t>(tmp);
        _delay_loop_2(ticks);
    }
}

void board::delay_us(uint16_t us) noexcept {
    const uint32_t tmp = std::max(((board::CPUFreq) / 3'000'000UL) * us, 1UL);
    const uint32_t tmp2 = std::max(((board::CPUFreq) / 4'000'000UL) * us, 1UL);

    if (tmp2 > 65535) {
        board::delay_ms(us / 1000);
    } else if (tmp > 255) {
        auto ticks = static_cast<uint16_t>(tmp2);
        _delay_loop_2(ticks);
    } else {
        auto ticks = static_cast<uint8_t>(tmp);
        _delay_loop_1(ticks);
    }
}
