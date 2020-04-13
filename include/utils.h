/**
 * @file utils.h
 */

#ifndef UTILS_H
#define UTILS_H

/**
 * @defgroup GROUP_UTILS Utils
 * @brief Tooling functions and macros
 * @{
 */

/**
 * @brief Set a bit to `1L`
 * @param byte
 * @param nbit
 */
#define BIT_SET(byte,nbit) ((byte) |= (1<<(nbit)))
/**
 * @brief Set a bit to `0L`
 * @param byte
 * @param nbit
 */
#define BIT_CLEAR(byte,nbit) ((byte) &= ~(1<<(nbit)))
/**
 * @brief Toggle a bit
 * @param byte
 * @param nbit
 */
#define BIT_TOGGLE(byte,nbit) ((byte) ^= (1<<(nbit)))
/**
 * @brief Check whether or not a bit is set
 * @param byte
 * @param nbit
 */
#define BIT_CHECK(byte,nbit) ((byte) & (1<<(nbit)))

/**
 * @brief Set a bit to `1L`
 * @param reg
 * @param nbit
 */
static inline void bit_set(volatile uint8_t* reg, uint8_t nbit)
{
    *reg |= (1 << nbit);
}

/**
 * @brief Set a bit to `0L`
 * @param reg
 * @param nbit
 */
static inline void bit_clear(volatile uint8_t* reg, uint8_t nbit)
{
    *reg &= ~(1 << nbit);
}

/**
 * @brief Toggle a bit
 * @param reg
 * @param nbit
 */
static inline void bit_toggle(volatile uint8_t* reg, uint8_t nbit)
{
    *reg ^= (1 << nbit);
}

/**
 * @brief Check whether or not a bit is set
 * @param byte
 * @param nbit
 * @return `1` if bit is set; `0` otherwise
 */
static inline uint8_t bit_check(uint8_t reg, uint8_t nbit)
{
    return (reg & (1 << nbit));
}

/**
 * @}
 */

#endif // UTILS_H