#pragma once
#if __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "readability-static-accessed-through-instance"
#endif

#include "pin_types.hpp"
#include "device.hpp"
#include <cstdint>

namespace drivers {

    namespace CLK {
        using SYSTEM_SOURCE = sfr::CLK::SCLKSELv;
        using RTC_SOURCE = sfr::CLK::RTCSRCv;
        using USB_SOURCE = sfr::CLK::USBSRCv;
        using PRESCALE_A = sfr::CLK::PSADIVv;
        using PRESCALE_B_C = sfr::CLK::PSBCDIVv;
        using PRESCALE_USB = sfr::CLK::USBPSDIVv;

    } // namespace CLK

    template <typename CLK_INSTANCE>
    class CLK_Basic {
//        CLK_INSTANCE m_instance;
        decltype(device::CLK) m_instance;  // NOTE: This is only to assist in auto-complete. Comment out for compile.
    public:
        constexpr CLK_Basic(const CLK_INSTANCE clkInst) : m_instance(clkInst) {}

        constexpr void set_system_clock(const CLK::SYSTEM_SOURCE src, const CLK::PRESCALE_A preA, const CLK::PRESCALE_B_C preBC) const noexcept {
            m_instance.CTRL = m_instance.CTRL.SCLKSEL.shift(src);
            m_instance.PSCTRL = m_instance.PSCTRL.PSADIV.shift(preA) | m_instance.PSCTRL.PSBCDIV.shift(preBC);
        }

        constexpr void enable_rtc(const CLK::RTC_SOURCE src) const noexcept {
            m_instance.RTCCTRL = m_instance.RTCCTRL.RTCSRC.shift(src) | m_instance.RTCCTRL.RTCEN.shift(true);
        }
        constexpr void disable_rtc(const CLK::RTC_SOURCE src) const noexcept {
            m_instance.RTCCTRL &= ~m_instance.RTCCTRL.RTCEN.shift(false);
        }

        constexpr void enable_usb(const CLK::USB_SOURCE src, const CLK::PRESCALE_USB prescale) const noexcept {
            m_instance.USBCTRL = m_instance.USBCTRL.USBPSDIV.shift(prescale) | m_instance.USBCTRL.USBSRC.shift(src) | m_instance.USBCTRL.USBSEN.shift(true);
        }
        constexpr void disable_usb(const CLK::RTC_SOURCE src) const noexcept {
            m_instance.USBCTRL &= ~m_instance.USBCTRL.USBSEN.shift(false);
        }
    };

} // namespace drivers

#if __clang__
#pragma clang diagnostic pop
#endif
