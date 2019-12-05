cmake_minimum_required(VERSION 3.15)

add_library(hal INTERFACE)
add_library(avr::hal ALIAS hal)

target_include_directories(hal
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}
)

target_sources(hal
    INTERFACE
        device.hpp
        gpio.hpp
        register.hpp
        drivers/led.hpp
        drivers/twi.hpp
        drivers/uart.hpp
)
