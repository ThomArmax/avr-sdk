/**
 * @example gpio_input_example.c
 */
#include "gpio.h"
#include "utils.h"
#include <avr/io.h>
#include <util/delay.h>

int main()
{
    // D12 in input
    gpio_set_mode(PORTB, PIN4, gpio_mode_input);

    // D13 in output will replicate the D12 state
    gpio_set_mode(PORTB, PIN5, gpio_mode_output);
    gpio_clear(&PORTB, PIN5);

    volatile uint8_t d12State = 0;
    while (1)
    {
        d12State = gpio_get(&PINB, PIN4);
        
        if (d12State)
            gpio_set(&PORTB, PIN5);
        else
            gpio_clear(&PORTB, PIN5);
    }

    return 0;
}
