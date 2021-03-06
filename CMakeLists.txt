cmake_minimum_required(VERSION 3.15)
project(xmega-hal
        DESCRIPTION "Demo project for generic c++17 hal/bsp"
        LANGUAGES C CXX )

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(bsp)

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
        "-fno-exceptions"
        "-fno-rtti"
        "-funsigned-char"
        "-funsigned-bitfields"
        "-Wall"
)

#set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT SIMULATION_BUILD)
    # all post build steps in a generic file. Include after add_executable!
    include(scripts/avr-gcc.cmake)

    target_compile_options(${PROJECT_NAME}
        PUBLIC
            $<$<CONFIG:Debug>:-O1>    # avr delay doesn't work with no optimization
            "-fpack-struct"
            "-fshort-enums"
    )
    target_link_options(${PROJECT_NAME}
        INTERFACE
            #"-Wl,-u,vfprintf -lprintf_flt -lm"     # if we want flaoting point support from avr-libc
    )

else()
    target_compile_options(${PROJECT_NAME}
        PUBLIC
    )
endif()
