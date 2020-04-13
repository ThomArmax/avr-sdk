/**
 * @example gpio_input_example.c
 */
#include "gpio.h"
#include "utils.h"
#include <avr/io.h>
#include <util/delay.h>

#define D12_INPUT_PIN   &PORTB, PORTB4
#define D13_OUTPUT_PIN  &PORTB, PORTB5

int main()
{
    // D12 in input
    gpio_set_mode(D12_INPUT_PIN, gpio_mode_input);

    // D13 in output will replicate the D12 state
    gpio_set_mode(D13_OUTPUT_PIN, gpio_mode_output);
    gpio_clear(D13_OUTPUT_PIN);

    volatile uint8_t d12_state = 0;
    while (1)
    {
        d12_state = gpio_get(D12_INPUT_PIN);
        
        if (d12_state)
            gpio_set(D13_OUTPUT_PIN);
        else
            gpio_clear(D13_OUTPUT_PIN);
    }

    return 0;
}
