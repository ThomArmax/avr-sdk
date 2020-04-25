#ifndef TWI_H
#define TWI_H

#include <stdint.h>

#ifndef TWI_FREQ
#define TWI_FREQ 400000UL
#endif

#ifndef TWI_BUFFER_LENGTH
#define TWI_BUFFER_LENGTH 64
#endif

#ifdef __cplusplus
extern "C" {
#endif

void TWI_init();
void TWI_send_byte(uint8_t address, uint8_t b, void (*callback)(uint8_t, uint8_t *));
void TWI_write_byte(uint8_t b, void (*callback)(uint8_t, uint8_t *));
void TWI_write(uint8_t address, uint8_t* data, uint8_t length, void (*callback)(uint8_t, uint8_t *));
void TWI_read(uint8_t address, uint8_t length, void (*callback)(uint8_t, uint8_t *));
uint8_t *TWI_wait();

void TWI_start_write(uint8_t address);
void TWI_stop(void);

#ifdef __cplusplus
}
#endif

#endif
