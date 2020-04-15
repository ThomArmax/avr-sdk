/**
 * @file hw_reg.h
 */

#include <stdint.h>

static inline void hw_reg_8_write(uintptr_t addr, uint8_t value)
{
	*(volatile uint8_t*)addr = value;
}

static inline uint8_t hw_reg_8_read(uintptr_t addr)
{
    return *(volatile uint8_t*)addr;
}

static inline void hw_reg_8_set_bit(uintptr_t addr, uint8_t nbit)
{
    hw_reg_8_write(addr, hw_reg_8_read(addr) | (1 << nbit));
}

static inline void hw_reg_8_clear_bit(uintptr_t addr, uint8_t nbit)
{
    hw_reg_8_write(addr, hw_reg_8_read(addr) & ~(1 << nbit));
}

static inline void hw_reg_8_toggle_bit(uintptr_t addr, uint8_t nbit)
{
    hw_reg_8_write(addr, hw_reg_8_read(addr) ^ (1 << nbit));
}
