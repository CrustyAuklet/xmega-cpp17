# C++ HAL and BSP for XMega devices

![system](https://user-images.githubusercontent.com/9755578/73144520-5aee7500-405b-11ea-94c3-6152b7e8354f.png)

## Purpose

This repository is an attempt to use modern C++ techniques to create a HAL and BSP for
XMega based devices, while _NOT_ being stuck with a pre-c++11 compiler. The IAR compiler for AVR
uses a standard called Embedded C++. This is not a standard in line with the normal C++ standards,
and eliminates a lot of useful things like namespaces, templates, etc. It is closest to C++98 though
the STL provided seems to be C++03. You can compare this project to the IAR version [HERE](https://github.com/CrustyAuklet/xmega-ecpp)

## Theory

C++ allows for abstraction without overhead. This abstraction is not only code abstraction but also 
abstraction of *expertise*. This means that domain experts should be able to code types and 
algorithms that encapsulate thier knowledge, and allow other developers to safely build upon that 
work without needed to know the underlying implementation. In the context of an embedded system project 
this means that the "application" should not need to know the details of the underlying hardware.

This flies in the face of typical embedded programming practice, since often abstration leads to a 
loss of effeciency (in terms of speed or code space). Wrapping register manipulation in a function 
creates code space overhead and function call overhead! C++, and expecially modern C++ with constexpr, 
provides the tools to create types and functions to allow very expressive low level hardware access
with *little to NO overhead*.

All things have tradeoffs though. To get abstraction without overhead this project assumes that a developer with
somewhat advanced C++ knowledge is available to implement the lower level support structure. 
Using C++17 makes the situation somewhat less messy (with featuers like CTAD, inline variables, etc). 
An *Application* developers using this framework should, in theory, not need the advanced 
C++ and embedded knowledge of the library developer.

 This project explores the limits of these ideas.

## References

The HAL layer is heavily inspired by [c++-register-access](https://yogiken.wordpress.com/2010/02/10/on-publishing/) by Ken Smith, 
[One Approach to Using Hardware Registers in C++](https://accu.org/index.php/journals/1606) by Martin Moene, 
and [modm](https://github.com/modm-io) by Niklas Hauser et all.

The specific register access techniques used in this version of the project were inspired by [Alexis Jeandet's](https://github.com/jeandet) [ucpp project](https://github.com/jeandet/ucpp)

Many AVR specific code tricks and CMake magic comes from [Łukasz Kostka](https://github.com/luqasz)'s [AVR Playground](https://github.com/luqasz/avr)

The device HAL is generated with Python and Jinja2 using [ATDF-parse](https://github.com/CrustyAuklet/ATDF-parse).
