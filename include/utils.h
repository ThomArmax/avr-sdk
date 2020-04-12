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

#define bit_set(byte,nbit)   ((byte) |=  (1<<(nbit)))
#define bit_clear(byte,nbit) ((byte) &= ~(1<<(nbit)))
#define bit_flip(byte,nbit)  ((byte) ^=  (1<<(nbit)))
#define bit_check(byte,nbit) ((byte) &   (1<<(nbit)))

/**
 * @}
 */

#endif // UTILS_H