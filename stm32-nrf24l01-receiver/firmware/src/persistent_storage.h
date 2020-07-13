#pragma once

#include <stdint.h>
#include <sys/types.h>

typedef struct {
	uint16_t crc16; 
} entry_hdr_t;

typedef struct {
	entry_hdr_t hdr;
	uint8_t data[];
} entry_p_t;

#define ADD_ENTRY(name, size) \
	struct { \
		entry_hdr_t hdr; \
		uint8_t data[size]; \
	} __attribute__ ((aligned(4))) name


typedef struct {
	ADD_ENTRY(BIND_DATA, 25);
#ifdef ESC
	ADD_ENTRY(BAT_CALIBR, sizeof(uint16_t));
#endif
}   nvram_t;

extern nvram_t nvram;

int _nvram_get(off_t off, size_t size, uint8_t *buf);
void _nvram_set(off_t off, size_t size, uint8_t *buf);

#define ENTRY_OFFSET(name)  (uint32_t)(&(((nvram_t *)0)->name))
#define ENTRY_SIZE(name) sizeof(nvram.name)

#define nvram_get(name, buf) _nvram_get(ENTRY_OFFSET(name), ENTRY_SIZE(name), buf)
#define nvram_set(name, buf) _nvram_set(ENTRY_OFFSET(name), ENTRY_SIZE(name), buf)
