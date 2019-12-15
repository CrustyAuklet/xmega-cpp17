#pragma once

#if defined(__atxmega128a1u__) || defined(__UTB__) || defined(__UTE__) || defined(__UTF__) || defined(__UTG__) || defined(__UTI__)
#include "atxmega128a1u/device.hpp"
#elif defined(__atxmega128a4u__) || defined(__UTA__) || defined(__UTC__) || defined(__UTD__)
#include "atxmega128a4u/device.hpp"
#elif defined(__atxmega256a3u__) || defined(__UTH__)
#include "atxmega256a3u/device.hpp"
#else
#   error "Not a supported processor - be sure to define the system processor example: __atxmega128a1u__"
#endif
