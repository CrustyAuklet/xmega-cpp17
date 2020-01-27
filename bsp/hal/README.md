![device](https://user-images.githubusercontent.com/9755578/73143982-2f688c00-4055-11ea-9b6b-17e3a46f102e.png)

# Device Abstraction Layer

The device abstraction layer is an abstraction for a specific microcontroller. The majority of the
code in this layer is generated using device description files (SVD files for ARM or ATDF files for AVR).
No code should be generated directly by this layer, and no resources should be used.

# Device Layer API

The specific implementation of the five parts of this layer creates the *DEVICE API* that any board layer will rely on.
The design decisions and implementation of this layer should be documented for use by the baord layer.

## The device layer consists of 5 parts:

- **SFR Abstraction layer** : header only and templated SFR access library for a specific microcontroller. 
This is generated code created from a device description file.
- **Device Description** : A header `device.hpp` that describes the memory layout of the specific chip, creating
specific types from the SFR template classes declared in the SFR Abstraction Layer.
- **Pin Types** : A header `pin_types.hpp` that describes different pin types for use by the board layer when describing the baord layout. These types
can do things like define the default initilization for a pin type, group pins, etc.
- **Peripheral Drivers** : Drivers for chip peripherals such as IO interfaces, RTC counters, etc. There are two types
of drivers that should be provided.
  - **Zero-Overhead Drivers** : These are templated drivers that simply wrap the SFR abstraction layer, grouping register
  actions into logical operations. These can also provide constexpr functions and enum types. The
  main purpose is to provide a very simple driver with no overhead that can be used to create more complex drivers with 
  more expressive code.
  - **Complex Drivers** : These drivers build on top of the zero-overhead drivers. They *may* allocate resources if needed
  (for a FIFO or cache for example) but should explicitley document this. Examples for these types of drivers are things like
  asyncronous IO, buffered IO, etc.
- **Interface Libraries** : A collection of libraries for design decisions that should be made at the device level. 
For example error reporting strategies, std::span instead of pointers and sizes, etc.

## Project structure:

- `/device-manufacturer-number` *SFR Abstraction layer for specific device*
- `/drivers` *peripheral drivers*
- `/nonstd` *Interface Libraries*
- `device.hpp` *device description header*
- `pin_types.hpp` *pin type header*
