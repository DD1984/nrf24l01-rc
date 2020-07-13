#ifndef __CRC_H__
#define __CRC_H__

#include <stdint.h>
#include <stddef.h>

uint16_t crc16(uint8_t *data, size_t length, uint16_t seed, uint16_t final);

#endif
