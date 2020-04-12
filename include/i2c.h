/**
 * @file i2c.h
 */

#ifndef I2C_H
#define I2C_H

#include "common.h"

/**
 * @brief Defines the I2C bus speed
 */
typedef enum
{
    i2c_speed_standard, ///< 100 kbit/s
    i2c_speed_full,     ///< 400 kbit/s
    i2c_speed_fast,     ///<   1 mbit/s
    i2c_speed_higth     ///< 3.2 mbit/s
} i2c_speed;

/**
 * @brief Defines the I2C data direction
 * @sa i2c_master_start()
 */
typedef enum
{
    i2c_direction_write,///< Write operation
    i2c_direction_read  ///< Read operation
} i2c_direction;

/**
 * @brief I2C master bus configuration
 */
typedef struct i2c_master_config_s
{
    i2c_speed speed;    ///< Bus speed
} i2c_master_config_t;

/**
 * @brief Initializes the I2C master bus
 * @param config
 * @return `err_ok` if succeeded; `err_fail` otherwise
 */
err_t i2c_master_init(i2c_master_config_t *config);

/**
 * @brief Deinitializes the I2C master bus
 */
err_t i2c_master_deinit();

/**
 * @brief Initiates a transmission
 * @param addr
 * @param direction
 * @return `err_ok` if succeeded; `err_fail` otherwise
 */
err_t i2c_master_start(uint8_t addr, i2c_direction direction);
/**
 * @brief Stops the I2C transmission
 * @return `err_ok` if succeeded; `err_fail` otherwise
 */
err_t i2c_master_stop();
/**
 * @brief Transmits the given byte @p b
 * @param b
 * @return `err_ok` if succeeded; `err_fail` otherwise
 */
err_t i2c_master_write_byte(uint8_t b);

/**
 * @brief Convenient all in one function which sends a buffer to a slave.
 * @details Start and Stop are managed internally
 * @param addr Slave address
 * @param buff Data to send
 * @param len Lenght of input buffer @p buff
 * @return `err_ok` if succeeded; `err_fail` otherwise
 */
err_t i2c_master_send(uint8_t addr, void *buff, uint32_t len);

#endif // I2C_H
