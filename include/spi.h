#ifndef SPI_H
#define SPI_H

#include <stdint.h>


/**
 * @defgroup GROUP_SPI SPI
 * @brief Hardware SPI protocol implementation
 * @{
 */

/**
 * @brief Init SPI master
 * @param clock SPI speed
 * @param ddr   SPI Data Direction Register
 * @param port  SPI Port Register
 * @param ss    SPI SS pin number
 * @param mosi  SPI MOSI pin number
 * @param miso  SPI MISO pin number
 * @param sck   SPI SCK pin number
 */
void spi_master_init(uint32_t clock, volatile uint8_t *ddr, volatile uint8_t *port, uint8_t ss, uint8_t mosi, uint8_t miso, uint8_t sck);

/**
 * @brief Send a byte
 * @param p
 */
uint8_t spi_master_write(uint8_t b);

/**
 * @brief Send a buffer
 * @param buf
 * @param buf_len
 */
void spi_master_write_buf(uint8_t *buf, uint16_t buf_len);

/**
 * @}
 */

#endif
