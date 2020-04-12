#include "i2c.h"
#include "utils.h"

#include <avr/io.h>
#include <util/delay.h>

void i2c_led_init()
{
    // This is for Arduino Uno,
    // use the LED on D13 pin to notify
    // about I2C activity
    bit_set(DDRB, PINB5);
    bit_clear(PORTB, PINB5);
}

void i2c_led_blink()
{
    bit_set(PORTB, PINB5);
    _delay_ms(25);
    bit_clear(PORTB, PINB5);
}

int main()
{
    i2c_master_config_t master;
    master.speed = i2c_speed_standard;

    i2c_master_init(&master);
    i2c_led_init();

    while (1)
    {
        i2c_master_start(4, i2c_direction_write);
        i2c_master_write_byte('a');
        i2c_master_stop();

        i2c_led_blink();

        _delay_ms(1000);
    }

    return -1;
}
