/**
 * @file i2c.c
 */

#include "i2c.h"
#include "utils.h"

#include <avr/io.h>
#include <util/twi.h>

static uint32_t i2c_speed_enum_to_uint(i2c_speed speed)
{
    switch (speed)
    {
        case i2c_speed_standard : return  100000UL;
        case i2c_speed_full     : return  400000UL;
        case i2c_speed_fast     : return 1000000UL;
        case i2c_speed_higth    : return 3200000UL;
        default                 : return  100000UL;
    }
}

static inline uint8_t i2c_direction_enum_to_twi_val(i2c_direction dir)
{
    switch (dir)
    {
        case i2c_direction_read : return TW_READ;
        case i2c_direction_write: return TW_WRITE;
        default                 : return TW_WRITE;
    }
}

err_t i2c_master_init(i2c_master_config_t *config)
{
    // The PRTWI bit in ”Minimizing Power Consumption” on page 51 must be written to zero to enable the 2-wire Serial Interface.
    // from datasheet
    //bit_clear(PRR, PRTWI);

    // Configure bit rate register and prescaler according to
    // SCL clk = CPU clk / ((16 + 2*TWBR)*PrescalerValue)
    uint32_t i2cFreq = i2c_speed_enum_to_uint(config->speed);
    TWBR = (uint8_t)(((F_CPU / i2cFreq) - 16) / 2);
    bit_clear(TWSR, TWPS0);
    bit_clear(TWSR, TWPS1);

    // Enable TWI module
    TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWEA);

    return err_ok;
}

err_t i2c_master_deinit()
{
    /// TODO
    return err_fail;
}

err_t i2c_master_start(uint8_t addr, i2c_direction direction)
{
    // Send START condition
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    // Wait for TWINT Flag set. 
    // This indicates that the START condition has been transmitted
    while (!(TWCR & (1 << TWINT)));

    // Check value of TWI Status Register. Mask prescaler bits.
    // If status different from TW_START or TW_REP_START
    // exit with error
    if ((TW_STATUS != TW_START) && (TW_STATUS != TW_REP_START))
        return err_fail;

    // Load address into TWDR register.
    // Clear TWINT bit in TWCR to start transmission of address
    TWDR = (addr << 1) + i2c_direction_enum_to_twi_val(direction);
    TWCR = (1 << TWINT) | (1 << TWEN);

    // Wait for TWINT flag set.
    // This indicates that the SLA+W has been transmitted, and ACK/NACK has been received.
    while (!(TWCR & (1 << TWINT)));

    // Check value of TWI status register.
    // Mask prescaler bits.
    // If status different from TW_MT_SLA_ACK return failed
    if ((TW_STATUS != TW_MT_SLA_ACK) && (TW_STATUS != TW_MR_SLA_ACK))
        return err_fail;

    return err_ok;
}

err_t i2c_master_stop()
{
    // Transmit STOP condition
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
    return err_ok;
}

err_t i2c_master_write_byte(uint8_t b)
{
    // Load DATA into TWDR register.
    // Clear TWINT bit in TWCR to start transmission of data
    TWDR = b;
    TWCR = (1 << TWINT) | (1 << TWEN);

    // Wait for TWINT flag set.
    // This indicates that the data has been transmitted, and ACK/NACK has been received.
    while (!(TWCR & (1 << TWINT)));

    // Check value of TWI status register.
    // Mask prescaler bits. If status different from MT_DATA_ACK return failed
    if (TW_STATUS != TW_MT_DATA_ACK)
        return err_fail;

    return err_ok;
}

err_t i2c_master_send(uint8_t addr, void *buff, uint32_t len)
{
    return err_fail;
}
