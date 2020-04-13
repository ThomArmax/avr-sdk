/**
 * @file gpio.c
 */

#include "gpio.h"
#include "utils.h"

#include <avr/io.h>

volatile uint8_t* gpio_port_to_ddr(uint8_t port)
{
#ifdef PORTA
    if (port == PORTA) return &DDRA;
#endif
#ifdef PORTB
    if (port == PORTB) return &DDRB;
#endif
#ifdef PORTC
    if (port == PORTC) return &DDRC;
#endif
#ifdef PORTD
    if (port == PORTD) return &DDRD;
#endif
#ifdef PORTE
    if (port == PORTE) return &DDRE;
#endif
#ifdef PORTF
    if (port == PORTF) return &DDRF;
#endif
#ifdef PORTG
    if (port == PORTG) return &DDRG;
#endif
#ifdef PORTH
    if (port == PORTH) return &DDRH;
#endif
#ifdef PORTI
    if (port == PORTI) return &DDRI;
#endif
#ifdef PORTJ
    if (port == PORTJ) return &DDRJ;
#endif
#ifdef PORTK
    if (port == PORTK) return &DDRK;
#endif
#ifdef PORTL
    if (port == PORTL) return &DDRL;
#endif

    return 0x0;
}

inline void gpio_set_mode(uint8_t port, uint8_t pin, gpio_mode_t mode)
{
    volatile uint8_t * ddrReg = gpio_port_to_ddr(port);
    if (mode == gpio_mode_output)
        bit_set(ddrReg, pin);
    else
        bit_clear(ddrReg, pin);
}

inline void gpio_set(volatile uint8_t * port, uint8_t pin)
{
    bit_set(port, pin);
}

inline void gpio_clear(volatile uint8_t * port, uint8_t pin)
{
    bit_clear(port, pin);
}

inline void gpio_toggle(volatile uint8_t * port, uint8_t pin)
{
    bit_toggle(port, pin);
}
