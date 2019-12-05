cmake_minimum_required(VERSION 3.15)

add_library(bsp INTERFACE)
add_library(avr::bsp ALIAS bsp)

add_subdirectory(hal)

target_compile_definitions(bsp
    INTERFACE
        F_CPU=2000000UL             # certain portions of avrlibc need this define
        $<$<CONFIG:Debug>:DEBUG>    # avr atmel studio usually defines this
)

target_link_libraries(bsp
    INTERFACE
        avr::hal
)

add_dependencies(bsp avr::hal)

target_include_directories(bsp
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}
)

target_sources(bsp
    INTERFACE
        board.hpp
)

if(CMAKE_CROSSCOMPILING)
    add_subdirectory(avr-libstdcpp)
    target_link_libraries(bsp
        INTERFACE
            avr::libstdcpp
    )
endif()
