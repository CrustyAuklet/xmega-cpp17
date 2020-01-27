![bsp](https://user-images.githubusercontent.com/9755578/73143960-ce40b880-4054-11ea-91c0-b040259f80ba.png)

# Board Support Layer

The board support layer is an abstraction for a specific product, development board, or breadboard layout. 
The board support layer should only depend on the device layer, and mainly interacts with the device description file.
It is also the lowest layer that should generate any code, or use resources. The board layer API will be used by any
operating system, upper level framework, or application code to access board resources.

# Board Support Layer API

The specific implementation of the four parts of this layer creates the *BSP API* that any OS, Framework, or application
will rely on. The design decisions and implementation of this layer should be documented for use by higher layers.

## The board support layer consists of 4 parts:

- **Hardware Abstraction Layer** : The HAL layer as a subproject for the appropriate device used on this board.
- **External Peripheral Drivers** : Drivers for external peripherals that may be present on the board,
SD cards, I2C sensors, and analog sensors are all examples of external peripherals. These drivers *may* use 
resources as needed (for example a FIFO or reading cache), but only if the driver is used.
- **Board Libraries** : A collection of libraries for design decisions that should be made at the board level.
For example IO (fmt, printf, or iostreams?).
- **Board Description File** : A header, or collection of headers, that describes how the different parts of
a board are wired together. This described the boards API to all higher layers.

## Project structure:

- `/hal` *Hardware Abstraction Layer*
- `/nonstd` *Board Libraries*
- `/peripherals` *External Peripheral Drivers*
- `/some-board-name` *Board Description Files for a specific board*
- `board.hpp` *board include file*
