#pragma once

#if defined(__AVR_ATxmega128A1U__) || defined(__atxmega128a1u__)
#   include "atxmega128a1u/device.hpp"
#elif defined(__AVR_ATxmega128A4U__) || defined(__atxmega128a4u__)
#   include "atxmega128a4u/device.hpp"
#elif defined(__AVR_ATxmega256A3U__) || defined(__atxmega256a3u__)
#   include "atxmega256a3u/device.hpp"
#else
#   error "No processor specified! be sure to define the system processor example: __atxmega128a1u__"
#endif
