#ifndef SEAL_BSP_FILE_XPLAINEDA1U
#define SEAL_BSP_FILE_XPLAINEDA1U

#include "device.hpp"
#include "drivers/uart.h"

namespace board {

typedef drivers::Uart_Basic< device::USARTC0, device::PC2, device::PC3 > Serial_C0;

}   // namespace board

#endif  // SEAL_BSP_FILE_XPLAINEDA1U
