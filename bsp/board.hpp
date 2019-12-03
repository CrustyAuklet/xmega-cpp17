#pragma once

#include "device.hpp"
#include "drivers/uart.hpp"
#include "drivers/led.hpp"

namespace board {

static constexpr drivers::Uart_Basic SerialC0(device::USARTC0, device::PC2, device::PC3);
static constexpr drivers::LedInverted UserLED(device::PQ3);

}   // namespace board
