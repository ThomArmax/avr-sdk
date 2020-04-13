/**
 * @file gpio.h
 */

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include "utils.h"

/**
 * @defgroup GROUP_GPIO GPIO
 * @brief General Purpose Input Output management
 * 
 * This example shows how to use GPIO as output
 * @include gpio_output_example.c
 * 
 * This example shows how to use GPIO as input.
 * The read GPIO state will be replacated on another pin (configured in output)
 * @include gpio_input_example.c
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
volatile uint8_t* gpio_port_to_ddr(uint8_t port);

/**
 * @brief Configures a GPIO
 * @param port
 * @param pin
 * @param mode
 */
void gpio_set_mode(uint8_t port, uint8_t pin, gpio_mode_t mode);

/**
 * @brief Sets a GPIO to `1L`
 * @param port
 * @param pin
 * @sa gpio_clear()
 * @sa gpio_toggle()
 * @note The GPIO must be previously configured in OUTPUT
 */
void gpio_set(volatile uint8_t * port, uint8_t pin);

/**
 * @brief Sets a GPIO to `0L`
 * @param port
 * @param pin
 * @sa gpio_set()
 * @sa gpio_toggle()
 * @note The GPIO must be previously configured in OUTPUT
 */
void gpio_clear(volatile uint8_t * port, uint8_t pin);

/**
 * @brief Toggles the GPIO
 * @brief If the GPIO is `1L` then it will flip to `0L`.
 * If the GPIO is `0L` then it will flip to `1L`.
 * @param port
 * @param pin
 * @note The GPIO must be previously configured in OUTPUT
 * @sa gpio_set()
 * @sa gpio_clear()
 */
void gpio_toggle(volatile uint8_t * port, uint8_t pin);

/**
 * @brief Returns the state of a GPIO
 * @param port
 * @param pin
 * @return `1` if pin is high, `0` otherwise
 */
uint8_t gpio_get(volatile uint8_t * port , uint8_t pin);

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
 */
#define GPIO_SET(port, pin) BIT_SET(port, pin)
/**
 * @brief Sets a GPIO to `0L`
 */
#define GPIO_CLEAR(port, pin) BIT_CLEAR(port, pin)
/**
 * @brief Toggles the GPIO
 */
#define GPIO_TOGGLE(port, pin) BIT_TOGGLE(port, pin)
/**
 * @brief Returns the state of a GPIO
 */
#define GPIO_GET(port, pin) BIT_CHECK(port, pin)

/**
 * @}
 */

#endif // GPIO_H