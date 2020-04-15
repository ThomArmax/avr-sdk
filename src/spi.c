/**
 * @file spi.c
 */

#include "spi.h"
#include <avr/io.h>

void spi_master_init(uint32_t clock, volatile uint8_t *ddr, volatile uint8_t *port, uint8_t ss, uint8_t mosi, uint8_t miso, uint8_t sck)
{
    *ddr |=  _BV(mosi);     // SDI output (MOSI)
    *ddr |=  _BV(sck);      // SCK output (Clock)
    *ddr |=  _BV(ss);	    // Slave Select Output
    *ddr &= ~_BV(miso);	    // SDO input (MISO)

    *port |=  _BV(miso);	// Pull-up MISO

    SPCR = //_BV(SPIE)  |   // Interupt Enable
        _BV(SPE)   |        // Enable SPI
        //_BV(DORD)  |      // LSB first
        _BV(MSTR)  |        // Master
        //_BV(CPOL)  |      // Clock Polarity (0 => Leading edge Raising + Railling Edge Falling)
        //                  //                (1 => Leading edge Falling + Railling Edge Raising)
        //_BV(CPHA)  |      // Clock phase (0 => Leading edge Sample + Trailing Edge Setup)
        //                  //             (1 => Leading edge Setup + Trailing Edge Sample)
        _BV(SPR0);          // fck/16

    SPSR &= ~_BV(SPI2X);    // Disable 2x speed
}

uint8_t spi_master_write(uint8_t b)
{
    SPDR = b;
    while(!(SPSR & _BV(SPIF)));
    return SPDR;
}

void spi_master_write_buf(uint8_t *buf, uint16_t buf_len)
{
    for (uint16_t i = 0; i < buf_len; i++)
    {
        SPDR = buf[i];
        while(!(SPSR & _BV(SPIF)));
    }
}
