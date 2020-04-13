/**
 * @example gpio_output_example.c
 * This is an example of how to use the I2C layer for master sending
 */

#include "gpio.h"
#include <avr/io.h>
#include <util/delay.h>

#define D13_PIN &PORTB, PIN5

int main()
{
    // D13 pin init
    // Set in output mode
    // Set LOW
    gpio_set_mode(D13_PIN, gpio_mode_output);
    gpio_clear(D13_PIN);

    while (1)
    {
        // Blink the LED using gpio_set and gpio_clear functions
        for (int i = 0; i < 10; i++)
        {
            gpio_set(D13_PIN); // equivalent of gpio_set(&PORTB, PIN)
            _delay_ms(125);

            gpio_clear(D13_PIN);
            _delay_ms(125); // equivalent of gpio_clear(&PORTB, PIN)
        }

        _delay_ms(2000);

        // Blink the LED using gpio_toggle function
        for (int i = 0; i < 20; i++)
        {
            gpio_toggle(D13_PIN);
            _delay_ms(125);
        }
    }
}
