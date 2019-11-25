# C++ HAL and BSP for XMega devices
This repository is an attempt to use modern C++ techniques to create a HAL and BSP for
XMega based devices, while _NOT_ being stuck with a pre-c++11 compiler. The IAR compiler for AVR
uses a standard called Embedded C++. This is not a standard in line with the normal C++ standards,
and eliminates a lot of useful things like namespaces, templates, etc. It is closest to C++98 though
the STL provided seems to be C++03. You can compare this project to the IAR version [HERE](https://github.com/CrustyAuklet/xmega-ecpp)

The HAL layer is heavily inspired by [c++-register-access](https://yogiken.wordpress.com/2010/02/10/on-publishing/) by Ken Smith, 
[One Approach to Using Hardware Registers in C++](https://accu.org/index.php/journals/1606) by Martin Moene, 
and [modm](https://github.com/modm-io) by Niklas Hauser et all.

Inspiration and some CMake ideas from [Łukasz Kostka](https://github.com/luqasz)'s [AVR Playground](https://github.com/luqasz/avr)

The device HAL is generated with Python and Jinja2 using [ATDF-parse](https://github.com/CrustyAuklet/ATDF-parse).
