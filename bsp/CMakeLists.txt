cmake_minimum_required(VERSION 3.15)

# configuration setting to define the board type
set(BOARD_NAME "" CACHE STRING "The hardware to compile for")
set(128A1U_BOARDS "UTB;UTE;UTF;UTG;UTI;XPLAINA1U")
set(128A4U_BOARDS "UTA;UTC;UTD")
set(256A3U_BOARDS "UTH")
set(VALID_BOARDS ${128A1U_BOARDS} ${128A4U_BOARDS} ${256A3U_BOARDS})
set_property(CACHE BOARD_NAME PROPERTY STRINGS ${VALID_BOARDS})

# is this a simulation build? if so build for desktop.
option(SIMULATION_BUILD "Is this a simulation build" OFF)

if(BOARD_NAME IN_LIST 128A1U_BOARDS)
    set(SEAL_SYSTEM_PROCESSOR "atxmega128a1u")
    message("Configuring for ${BOARD_NAME} hardware with ATXMega128A1U processor...")
elseif(BOARD_NAME IN_LIST 128A4U_BOARDS)
    set(SEAL_SYSTEM_PROCESSOR "atxmega128a4u")
    message("Configuring for ${BOARD_NAME} hardware with ATXMega128A4U processor...")
elseif(BOARD_NAME IN_LIST 256A3U_BOARDS)
    set(SEAL_SYSTEM_PROCESSOR "atxmega256a3u")
    message("Configuring for ${BOARD_NAME} hardware with ATXMega256A3U processor...")
elseif(BOARD_NAME STREQUAL "" )
    message(SEND_ERROR "No Board defined for the BSP layer!")
else()
    message(SEND_ERROR "Unknown board: ${BOARD_NAME}")
endif()

# if we are cross compiling for an embedded target then system name will be Generic
if(CMAKE_SYSTEM_NAME STREQUAL "Generic")
    set(SIMULATION_BUILD OFF CACHE BOOL "indicates if this is a simulation build" FORCE)
    message("${CMAKE_SYSTEM_NAME} System, Building for hardware...")
else()
    set(SIMULATION_BUILD ON CACHE BOOL "indicates if this is a simulation build" FORCE)
    message("${CMAKE_SYSTEM_NAME} System, Building for simulation...")
endif()

add_library(bsp INTERFACE)
add_library(avr::bsp ALIAS bsp)

add_subdirectory(hal)

target_compile_definitions(bsp
    INTERFACE
        __${SEAL_SYSTEM_PROCESSOR}__            # system processor
        __${BOARD_NAME}__                       # name of the hardware board
        $<$<CONFIG:Debug>:DEBUG>    # avr atmel studio usually defines this
        SIMULATION_BUILD=$<IF:$<BOOL:${SIMULATION_BUILD}>,1,0>
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
        nonstd/cstdio.hpp

        peripherals/peripheral_types.hpp
        peripherals/motion/BMA250X.hpp
)

include(${BOARD_NAME}/CMakeLists.txt)
