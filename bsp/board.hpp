#pragma once

#include "device.hpp"
#include "drivers/uart.hpp"
#include "drivers/twi.hpp"
#include "drivers/led.hpp"

namespace board {

    inline constexpr uint32_t CPUFreq = F_CPU;              //< CPU frequency
    inline constexpr bool simulation = SIMULATION_BUILD;    //< true if this is a simulation build

    inline constexpr drivers::Uart_Basic SerialC0(device::USARTC0, device::PC2, device::PC3);
    inline constexpr drivers::TWI_Master_Basic I2C_C(device::TWIC, device::PC0, device::PC1);
    inline constexpr drivers::LedInverted UserLED(device::PQ3);

    constexpr bool init() {
        SerialC0.init<CPUFreq, 9600, true>();
        SerialC0.start();
        I2C_C.init<CPUFreq, 100'000>();
        I2C_C.start();
        UserLED.init();
        return true;
    }

}   // namespace board
