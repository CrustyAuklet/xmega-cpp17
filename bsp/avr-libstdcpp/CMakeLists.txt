cmake_minimum_required(VERSION 3.15)

add_library(libstdcpp INTERFACE)
add_library(avr::libstdcpp ALIAS libstdcpp)

target_include_directories(libstdcpp
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_sources(libstdcpp
    INTERFACE
        # ${CMAKE_CURRENT_LIST_DIR}/src/chrono.cc
        # ${CMAKE_CURRENT_LIST_DIR}/src/functexcept.cc
        # ${CMAKE_CURRENT_LIST_DIR}/src/hash_bytes.cc
        # ${CMAKE_CURRENT_LIST_DIR}/src/limits.cc
        # ${CMAKE_CURRENT_LIST_DIR}/src/nothrow.cc
)
