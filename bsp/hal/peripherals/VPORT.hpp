/**
 * XMEGAAU-VPORT (id I6075)
 * Virtual Ports
 */
#pragma once

#include "register.hpp"
#include <stdint.h>

namespace device {

namespace VPORT {

}   // namespace VPORT

/**
 * VPORT
 * Virtual Port
 * Size: 4 bytes
 */
template <addressType BASE_ADDRESS>
struct VPORT_t {
    static constexpr addressType BaseAddress = BASE_ADDRESS;

    /// I/O Port Data Direction - 1 bytes
    static constexpr struct DIR_t : reg_t<uint8_t, BASE_ADDRESS + 0x0000> {
    } DIR = {};

    /// I/O Port Output - 1 bytes
    static constexpr struct OUT_t : reg_t<uint8_t, BASE_ADDRESS + 0x0001> {
    } OUT = {};

    /// I/O Port Input - 1 bytes
    static constexpr struct IN_t : reg_t<uint8_t, BASE_ADDRESS + 0x0002> {
    } IN = {};

    /// Interrupt Flag Register - 1 bytes
    static constexpr struct INTFLAGS_t : reg_t<uint8_t, BASE_ADDRESS + 0x0003> {
        static constexpr bitfield_t<INTFLAGS_t, 0x02, 1> INT1IF = {};    //< Port Interrupt 1 Flag
        static constexpr bitfield_t<INTFLAGS_t, 0x01, 0> INT0IF = {};    //< Port Interrupt 0 Flag
    } INTFLAGS = {};

};

} // namespace device
