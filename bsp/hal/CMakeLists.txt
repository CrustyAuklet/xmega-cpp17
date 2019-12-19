cmake_minimum_required(VERSION 3.15)

add_library(hal INTERFACE)
add_library(avr::hal ALIAS hal)

target_compile_features(hal
    INTERFACE
        cxx_std_17
)

target_include_directories(hal
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}
)

target_sources(hal
    INTERFACE
        register.hpp
        pin_types.hpp
        drivers/twi.hpp
        drivers/uart.hpp
        drivers/spi.hpp
        drivers/adc.hpp
        drivers/clk.hpp

        nonstd/span.hpp
        nonstd/expected.hpp
)

if(SIMULATION_BUILD)
    # implementation files if this is a simulation run
    target_sources(hal INTERFACE register.cpp)
else()
    set(MCPU_FLAGS "-mmcu=${SEAL_SYSTEM_PROCESSOR}")

    target_compile_options(hal
        INTERFACE
            ${MCPU_FLAGS}
            # size optomization flags: https://www.avrfreaks.net/forum/code-size-gets-bigger-each-new-version-gcc
            "-fdata-sections"
            "-ffunction-sections"
            "-fno-inline-small-functions"
            "-fno-split-wide-types"
            "-fno-tree-scev-cprop"
            "-g3"
    )

    target_link_options(hal
        INTERFACE
            ${MCPU_FLAGS}
            "-Wl,--gc-sections"
            "-Wl,-Map=xmega-hal.map"
            "-Wl,--relax"               # replace CALL statements with RCALL when possible
    )
endif()
