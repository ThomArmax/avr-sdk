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
 * @def bit_set
 * @brief Set a bit to 1L
 * @param byte
 * @param nbit
 */
#define bit_set(byte,nbit)   ((byte) |=  (1<<(nbit)))
/**
 * @def bit_clear
 * @brief Set a bit to 0L
 * @param byte
 * @param nbit
 */
#define bit_clear(byte,nbit) ((byte) &= ~(1<<(nbit)))
/**
 * @def bit_flip
 * @brief Toggle/Invert a bit
 * @param byte
 * @param nbit
 */
#define bit_flip(byte,nbit)  ((byte) ^=  (1<<(nbit)))
/**
 * @def bit_check
 * @brief Check whether or not a bit is set
 * @param byte
 * @param nbit
 */
#define bit_check(byte,nbit) ((byte) &   (1<<(nbit)))

/**
 * @}
 */

#endif // UTILS_H