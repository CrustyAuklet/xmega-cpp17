cmake_minimum_required(VERSION 3.13)

add_library(bsp INTERFACE)
add_library(avr::bsp ALIAS bsp)

add_subdirectory(avr-libstdcpp)
add_subdirectory(hal)

target_compile_definitions(bsp
    INTERFACE
        F_CPU=2000000UL
        __${CMAKE_SYSTEM_PROCESSOR}__           # system processor
        __${CMAKE_SYSTEM_PROCESSOR_FAMILY}__    # system processor familt (for different register layouts)
        $<$<CONFIG:Debug>:DEBUG>    # avr atmel studio usually defines this
)

target_link_libraries(bsp
    INTERFACE
        avr::hal
        avr::libstdcpp
)

set(MCPU_FLAGS "-mmcu=${CMAKE_SYSTEM_PROCESSOR}")

target_compile_options(bsp
    INTERFACE
        ${MCPU_FLAGS}
        "-fdata-sections"
        "-ffunction-sections"
)

target_link_options(bsp
    INTERFACE
        ${MCPU_FLAGS}
        "-Wl,--gc-sections"
        "-Wl,-Map=xmega-hal.map"
        "-mrelax"
)

target_include_directories(bsp
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}
)

target_sources(bsp
    INTERFACE
)

# from older toolchain file, better to use target_compile_options && target_link_options. Temporarily kept for reference.
# set(MCPU_FLAGS "-mmcu=avrxmega7")
# set(CMAKE_C_FLAGS   "${MCPU_FLAGS} -fdata-sections -ffunction-sections" CACHE INTERNAL "c compiler flags")
# set(CMAKE_CXX_FLAGS "${MCPU_FLAGS} -fdata-sections -ffunction-sections" CACHE INTERNAL "cxx compiler flags")
# set(CMAKE_ASM_FLAGS "${MCPU_FLAGS} -x assembler-with-cpp" CACHE INTERNAL "asm compiler flags")
# set(CMAKE_EXE_LINKER_FLAGS "${MCPU_FLAGS} -nostartfiles -Wl,--gc-sections" CACHE INTERNAL "exe link flags")
