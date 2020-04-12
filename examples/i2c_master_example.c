/**
 * @example i2c_master_example.c
 * This is an example of how to use the I2C layer for master sending
 */

#include "i2c.h"
#include "utils.h"

#include <avr/io.h>
#include <util/delay.h>

#define SLAVE_ADDR 4

void i2c_led_init()
{
    // This is for Arduino Uno,
    // use the LED on D13 pin to notify
    // about I2C activity

    bit_set(DDRB, PINB5);       // D13 in output
    bit_clear(PORTB, PINB5);    // D13 0L
}

void i2c_led_blink()
{
    bit_set(PORTB, PINB5);      // D13 1L
    _delay_ms(25);
    bit_clear(PORTB, PINB5);    // D13 0L
}

int main()
{
    i2c_master_config_t master;
    master.speed = i2c_speed_standard;

    i2c_master_init(&master);
    i2c_led_init();

    static const uint8_t buf[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    while (1)
    {
        i2c_master_start(SLAVE_ADDR, i2c_direction_write);
        i2c_master_write('a');
        i2c_master_stop();

        i2c_master_start(SLAVE_ADDR, i2c_direction_write);
        i2c_master_write_buf((uint8_t*)&buf, sizeof(buf));
        i2c_master_stop();

        i2c_led_blink();

        _delay_ms(1000);
    }

    return -1;
}
