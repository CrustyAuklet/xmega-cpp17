#include "register.hpp"
#include "mio.hpp"
#include <cstdio>
#include <system_error>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

class MemoryMock {
public:
    MemoryMock(const char* path, const std::size_t length) {
        std::error_code error;
        // create file if it doesn't exist
        if(!fs::exists(path, error)) {
            std::ofstream ofs(path);
            ofs.close();
            fs::resize_file(path, length);
        }

        m_mmap.map(path, 0, length, error);
        if(error) {
            handle_error(error);
            std::exit(error.value());
        }
    }

    uint8_t read8(size_t addr) const {
        return m_mmap[addr];
    }

    void write8(size_t addr, const uint8_t val) {
        m_mmap[addr] = val;
        std::error_code error;
        m_mmap.sync(error);
        if(error) {
            handle_error(error);
            std::exit(error.value());
        }
    }

private:
    static int handle_error(const std::error_code& error) {
        const auto& errmsg = error.message();
        std::printf("error mapping file: %s, exiting...\n", errmsg.c_str());
        return error.value();
    }

    mio::ummap_sink m_mmap;                             //< read-write memory mapped file handle
};

static MemoryMock mm("./memory-map.bin", 0x10000);

void* ucpp::registers::sim::get_mem_address(const uint32_t addr) noexcept {
    return nullptr;
}

template<typename T>
T ucpp::registers::sim::read(const uint32_t addr) noexcept {
    const T value = mm.read8(addr);
    std::printf("Read:  0x%08X as 0x%02X\n", addr, value);
    fflush(stdout);
    return value;
}

template<typename T>
void ucpp::registers::sim::write(const uint32_t addr, const T val) noexcept {
    std::printf("Write: 0x%08X, 0x%02X --> 0x%02X\n", addr, mm.read8(addr), val);
    fflush(stdout);
    mm.write8(addr, val);
}

template void ucpp::registers::sim::write<uint8_t>(const uint32_t addr, const uint8_t val) noexcept;
template uint8_t ucpp::registers::sim::read<uint8_t>(const uint32_t addr) noexcept;
