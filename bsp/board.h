#ifndef SEAL_BSP_FILE_XPLAINEDA1U
#define SEAL_BSP_FILE_XPLAINEDA1U

#include "device.hpp"
#include "drivers/uart.h"

namespace board {

static constexpr drivers::Uart_Basic SerialC0(device::USARTC0, device::PC2, device::PC3);
//using Serial_C0 = drivers::Uart_Basic< decltype(device::USARTC0), decltype(device::PC2), decltype(device::PC3) >;

}   // namespace board

#endif  // SEAL_BSP_FILE_XPLAINEDA1U
