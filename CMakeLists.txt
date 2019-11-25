cmake_minimum_required(VERSION 3.13)
project(xmega-hal
        LANGUAGES C CXX )

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(bsp)

# all post build steps in a generic file. Include after add_executable!
include(scripts/avr-gcc.cmake)

target_sources(${PROJECT_NAME}
    PUBLIC
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        avr::bsp
)

target_compile_features(${PROJECT_NAME}
    PUBLIC
        cxx_std_17
)

target_compile_options(${PROJECT_NAME}
    PUBLIC
        $<$<CONFIG:Debug>:-O1>    # avr delay doesn't work with no optimization
        "-fno-exceptions"
        "-fno-rtti"
        "-funsigned-char"
        "-funsigned-bitfields"
        "-fpack-struct"
        "-fshort-enums"
        "-Wall"
)
