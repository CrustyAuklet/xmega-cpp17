
target_include_directories(bsp
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}
)

target_sources(bsp
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/board.hpp
        ${CMAKE_CURRENT_LIST_DIR}/board.cpp
)