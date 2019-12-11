cmake_minimum_required(VERSION 3.15)

add_library(printf INTERFACE)
add_library(mpaland::printf ALIAS printf)

target_include_directories(printf
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}
)

target_sources(printf
    INTERFACE
        printf.h
        printf.c
)

target_compile_definitions(printf
    INTERFACE
        PRINTF_DISABLE_SUPPORT_FLOAT
        PRINTF_DISABLE_SUPPORT_EXPONENTIAL
        PRINTF_DISABLE_SUPPORT_LONG_LONG
        PRINTF_DISABLE_SUPPORT_PTRDIFF_T
)