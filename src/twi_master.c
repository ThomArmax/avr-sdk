#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/twi.h>
#include <string.h>

#include "twi_master.h"

static volatile uint8_t busy;
static struct {
    uint8_t buffer[TWI_BUFFER_LENGTH];
    uint8_t length;
    uint8_t index;
    void (*callback)(uint8_t, uint8_t *);
} transmission;

void TWI_init() 
{
    TWBR = ((F_CPU / TWI_FREQ) - 16) / 2;
    TWSR = 0; // prescaler = 1

    busy = 0;

    sei();

    TWCR = _BV(TWEN);
}

uint8_t *TWI_wait()
{
    while (busy);
    return &transmission.buffer[1];
}

void TWI_start(void)
{
    TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWIE) | _BV(TWSTA);
}

void TWI_start_write(uint8_t address)
{
    TWI_wait();

    busy = 1;

    transmission.buffer[0] = (address << 1) | TW_WRITE;
    transmission.length = 1;
    transmission.index = 0;
    transmission.callback = NULL;

    TWI_start();
}

void TWI_stop(void)
{
    TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO);
}

void TWI_ack()
{
    TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWIE) | _BV(TWEA);
}

void TWI_nack()
{
    TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWIE);
}

void TWI_send(uint8_t data)
{
    TWDR = data;
}

void TWI_recv()
{
    transmission.buffer[transmission.index++] = TWDR;
}

void TWI_reply()
{
    if (transmission.index < (transmission.length - 1))
        TWI_ack();
    else
        TWI_nack();
}

void TWI_done() 
{
    uint8_t address = transmission.buffer[0] >> 1;
    uint8_t *data = &transmission.buffer[1];

    busy = 0;

    if (transmission.callback != NULL) {
        transmission.callback(address, data);
    }
}

void TWI_send_byte(uint8_t address, uint8_t b, void (*callback)(uint8_t, uint8_t *)) 
{
    TWI_wait();

    busy = 1;

    transmission.buffer[0] = (address << 1) | TW_WRITE;
    transmission.buffer[1] = b;
    transmission.length = 1 + 1;
    transmission.index = 0;
    transmission.callback = callback;

    TWI_start();
}

void TWI_write_byte(uint8_t b, void (*callback)(uint8_t, uint8_t *))
{
    TWI_wait();

    busy = 1;

    TWI_send(b);
    /*
    transmission.buffer[1] = b;
    transmission.length = 1 + 1;
    transmission.index = 1;
    transmission.callback = callback;
    */
}

void TWI_write(uint8_t address, uint8_t* data, uint8_t length, void (*callback)(uint8_t, uint8_t *))
{
    TWI_wait();

    busy = 1;

    transmission.buffer[0] = (address << 1) | TW_WRITE;
    transmission.length = length + 1;
    transmission.index = 0;
    transmission.callback = callback;
    memcpy(&transmission.buffer[1], data, length);

    TWI_start();
}

void TWI_read(uint8_t address, uint8_t length, void (*callback)(uint8_t, uint8_t *)) 
{
    TWI_wait();

    busy = 1;

    transmission.buffer[0] = (address << 1) | TW_READ;
    transmission.length = length + 1;
    transmission.index = 0;
    transmission.callback = callback;

    TWI_start();
}

ISR(TWI_vect) 
{
    switch (TW_STATUS) {
    case TW_START:
    case TW_REP_START:
    case TW_MT_SLA_ACK:
    case TW_MT_DATA_ACK:
        if (transmission.index < transmission.length)
        {
            TWI_send(transmission.buffer[transmission.index++]);
            TWI_nack();
        }
        else
        {
            TWI_stop();
            TWI_done();
        }
        break;

    case TW_MR_DATA_ACK:
        TWI_recv();
        TWI_reply();
        break;

    case TW_MR_SLA_ACK:
        TWI_reply();
        break;

    case TW_MR_DATA_NACK:
        TWI_recv();
        TWI_stop();
        TWI_done();
        break;

    case TW_MT_SLA_NACK:
    case TW_MR_SLA_NACK:
    case TW_MT_DATA_NACK:
    default:
        TWI_stop();
        TWI_done();
        break;
    }
}
