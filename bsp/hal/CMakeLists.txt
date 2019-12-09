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
        device.hpp
        gpio.hpp
        drivers/led.hpp
        drivers/twi.hpp
        drivers/uart.hpp
        drivers/adc.hpp

        # implementation files if this is a simulation run
        $<$<NOT:$<BOOL:${CMAKE_CROSSCOMPILING}>>:${CMAKE_CURRENT_LIST_DIR}/register.cpp>
)

target_compile_definitions(hal
    INTERFACE
        __${CMAKE_SYSTEM_PROCESSOR}__           # system processor
        __${CMAKE_SYSTEM_PROCESSOR_FAMILY}__    # system processor family (for different register layouts)
        SIMULATION_BUILD=$<IF:$<BOOL:${CMAKE_CROSSCOMPILING}>,0,1>
)

if(CMAKE_CROSSCOMPILING)
    set(MCPU_FLAGS "-mmcu=${CMAKE_SYSTEM_PROCESSOR}")

    target_compile_options(hal
        INTERFACE
            ${MCPU_FLAGS}
    )

    target_link_options(hal
        INTERFACE
            ${MCPU_FLAGS}
            "-Wl,--gc-sections"
            "-Wl,-Map=xmega-hal.map"
            "-mrelax"
    )
endif()
