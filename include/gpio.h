/**
 * @file gpio.h
 */

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

/**
 * @defgroup GROUP_GPIO GPIO
 * @brief General Purpose Input Output management
 * @{
 */

/**
 * @brief Defines the GPIO mode
 */
typedef enum
{
    gpio_mode_input,    ///< GPIO configured in INPUT
    gpio_mode_output    ///< GPIO configured in OUTPUT
} gpio_mode_t;

/**
 * @brief Returns the Data Direction Register for the given port
 * @param port
 * @return the Data Direction Register for the given port
 */
uint8_t gpio_port_to_ddr(uint8_t port);

/**
 * @brief Configures a GPIO
 * @param port
 * @param pin
 * @param mode
 */
void gpio_set_mode(uint8_t port, uint8_t pin, gpio_mode_t mode);

/**
 * @brief Configure a GPIO in output mode
 */
#define GPIO_SET_MODE_OUTPUT(port, pin) gpio_set_mode(port, pin, gpio_mode_output)

/**
 * @brief Configure a GPIO in input mode
 */
#define GPIO_SET_MODE_INPUT(port, pin) gpio_set_mode(port, pin, gpio_mode_input)

/**
 * @brief Sets a GPIO to `1L`
 * @param port
 * @param pin
 * @sa gpio_clear()
 * @sa gpio_toggle()
 * @note The GPIO must be previously configured in OUTPUT
 */
void gpio_set(uint8_t port, uint8_t pin);

/**
 * @brief Sets a GPIO to `0L`
 * @param port
 * @param pin
 * @sa gpio_set()
 * @sa gpio_toggle()
 * @note The GPIO must be previously configured in OUTPUT
 */
void gpio_clear(uint8_t port, uint8_t pin);

/**
 * @brief Toggles the GPIO
 * @param port
 * @param pin
 * @note The GPIO must be previously configured in OUTPUT
 * @sa gpio_set()
 * @sa gpio_clear()
 */
void gpio_toggle(uint8_t port, uint8_t pin);

/**
 * @}
 */

#endif // GPIO_H