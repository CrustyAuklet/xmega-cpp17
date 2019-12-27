#pragma once

#include "stdio.h"
#include "drivers/flash.hpp"
#include <type_traits>

using namespace flash::flash_literals;

namespace nonstd {

    template<typename T, typename... Args>
    std::enable_if_t<T::in_flash, int> print(T fmt, const Args&... args) {
        static_assert(T::in_flash, "format string must be a string in flash!");
        return printf_P(fmt, args...);
    }

    // enable this code section if you want to allow format string to be non-flash
#if defined(IO_ENABLE_NON_FLASH_FORMAT)
    template<typename... Args >
    int print(const char* fmt, const Args&... args) {
        return printf(fmt, args...);
    }
#endif
}