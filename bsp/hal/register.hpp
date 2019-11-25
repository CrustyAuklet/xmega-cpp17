#ifndef CPP_REGISTER_ACCESS_TEMPALTES
#define CPP_REGISTER_ACCESS_TEMPALTES

#include <stdint.h>

typedef uint8_t  registerType;
typedef uint16_t addressType;

struct ro_reg8_t {
    static unsigned read_reg(volatile registerType* reg) {
        return *reg;
    }
};

struct wo_reg8_t {
    static void write_reg(volatile registerType* reg, const registerType value) {
        *reg = value;
    }
};

// for writing a whole word reading and writing are just combined. Class provided for consistancy.
struct rw_reg8_t : public ro_reg8_t, public wo_reg8_t { };

template<addressType address, class mutability_policy = rw_reg8_t>
struct reg8_t{
    static constexpr addressType ADDRESS = address;
    static void write(registerType value) {
        mutability_policy::write_reg(reinterpret_cast<volatile registerType*>(address),value);
    }
    static registerType read() {
        return mutability_policy::read_reg(reinterpret_cast<volatile registerType*>(address));
    }
};

/// AVR requires 16-bit registers to be read and written and two 8-bit accesses in specific order
template<addressType address, class mutability_policy = rw_reg8_t>
struct reg16_t{
    using LB = reg8_t<address, mutability_policy>;
    using HB = reg8_t<address+1, mutability_policy>;
    static void write(const addressType value) {
        LB::write(value);
        HB::write(value>>8);
    }
    static addressType read() {
        const registerType lb = LB::read();
        return lb | (HB::read() << 8);
    }
    // TODO: need field access for 16 bit registers, that spans the bytes (counter in USB has 10 bit field and then other stuff in the rest of HB)
};

/*** Structures for accessing bitfields within 8-bit registers ***/

struct ro_field_t {
    static unsigned read_field(volatile registerType* reg, const registerType valMask, const registerType offset) {
        return (*reg >> offset) & valMask;
    }
};

struct wo_field_t {
    static void write_field(volatile registerType* reg, const registerType valMask, const registerType offset, const registerType value) {
        *reg = (value & valMask) << offset;
    }
};

struct rw_field_t : public ro_field_t {
    static void write_field(volatile registerType* reg, const registerType valMask, const registerType offset, const registerType value) {
        *reg = (*reg & ~(valMask << offset))|((value & valMask) << offset);
    }
};

template<addressType address, registerType mask, registerType offset, typename FieldType = registerType, class mutability_policy = rw_field_t>
struct reg_field_t{
    static constexpr registerType VAL_MASK = mask >> offset;
    static constexpr registerType BIT_MASK = mask;
    static constexpr registerType SHIFT    = offset;
    static void write(FieldType value) {
        mutability_policy::write_field(reinterpret_cast<volatile registerType*>(address),VAL_MASK,offset,static_cast<registerType>(value));
    }
    static FieldType read() {
        return static_cast<FieldType>(mutability_policy::read_field(reinterpret_cast<volatile registerType*>(address),VAL_MASK,offset));
    }
};

#endif // CPP_REGISTER_ACCESS_TEMPALTES
