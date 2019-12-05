#pragma once

#include "device.hpp"
#include "drivers/uart.hpp"
#include "drivers/led.hpp"

namespace board {

    inline constexpr uint32_t CPUFreq = F_CPU;              //< CPU frequency
    inline constexpr bool simulation = SIMULATION_BUILD;    //< true if this is a simulation build

    inline constexpr drivers::Uart_Basic SerialC0(device::USARTC0, device::PC2, device::PC3);
    inline constexpr drivers::LedInverted UserLED(device::PQ3);

}   // namespace board
