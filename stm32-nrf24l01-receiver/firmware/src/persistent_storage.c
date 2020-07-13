/******************************************************************************

    Use IAP to program the flash
    A single page of 64 bytes should be sufficient
    Top 32 bytes of RAM needed
    RAM buffer with data needs to be on word boundary
    Uses 148 bytes of stack space
    Use compare function to only write changes
    Interrupts must be disabled during erase and write operations
    Q: How long does erase and write take?

******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "platform.h"
#include "persistent_storage.h"
#include "crc.h"

#define FLASH_PAGE_SIZE   	1024UL
#define FLASH_SIZE   		(16*1024UL)
#define FLASH_LAST_PAGE		(FLASH_BASE + (FLASH_SIZE - FLASH_PAGE_SIZE))

nvram_t nvram;

// ****************************************************************************
static inline void UnlockFlash (void)
{
    while ((FLASH->SR & FLASH_SR_BSY) != 0) {}
    if ((FLASH->CR & FLASH_CR_LOCK) != 0)
    {
        FLASH->KEYR = FLASH_FKEY1;
        FLASH->KEYR = FLASH_FKEY2;
    }
}

// ****************************************************************************
static inline void LockFlash (void)
{
    FLASH->CR |= FLASH_CR_LOCK;
}

// ****************************************************************************
static inline void ErasePage (uint32_t addr)
{
    FLASH->CR |= FLASH_CR_PER;
    FLASH->AR = addr;
    FLASH->CR |= FLASH_CR_STRT;
    while ((FLASH->SR & FLASH_SR_BSY) != 0)	{}
    if ((FLASH->SR & FLASH_SR_EOP) != 0)
    {
        FLASH->SR |= FLASH_SR_EOP;
    }
    FLASH->CR &= ~FLASH_CR_PER;
}

void flash_write(uint32_t dst, uint8_t *data, size_t size)
{
	UnlockFlash();

	//стирание флагов после программирования основной памяти отладчиком
	//иначе следующая операция стирания страницы и как следсвтие программирование
	//неудачно
	CLEAR_BIT(FLASH->CR, (FLASH_CR_PG | FLASH_CR_PER | FLASH_CR_MER));

	ErasePage(FLASH_LAST_PAGE);

	__IO uint16_t *pflash = (__IO uint16_t*)dst;

	uint32_t num_to_write = (size + 1) >> 1;
	uint32_t i = 0;
	while (i < num_to_write)
	{
		FLASH->CR |= FLASH_CR_PG;
		*pflash++ = ((uint16_t *)data)[i];

		while ((FLASH->SR & FLASH_SR_BSY) != 0);

		if ((FLASH->SR & FLASH_SR_EOP) != 0)
			FLASH->SR |= FLASH_SR_EOP;

		FLASH->CR &= ~FLASH_CR_PG;

		i++;
	}

	LockFlash();
}

int _nvram_get(off_t off, size_t size, uint8_t *buf)
{
	entry_p_t *entry_p = (entry_p_t *)(FLASH_LAST_PAGE + off);

	uint16_t crc16_calc = crc16(entry_p->data, size - sizeof(entry_hdr_t), 0xffff, 0);

	if (crc16_calc == entry_p->hdr.crc16) {
		memcpy(buf, entry_p->data, size);
		return 0;
	}

	return -1;
}


void _nvram_set(off_t off, size_t size, uint8_t *buf)
{
	uint8_t page_buf[sizeof(nvram_t)];
	memcpy(page_buf, (void *)FLASH_LAST_PAGE, sizeof(nvram_t));

	entry_p_t *entry_p = (entry_p_t *)(page_buf + off);

	memcpy(entry_p->data, buf, size - sizeof(entry_hdr_t));
	entry_p->hdr.crc16 = crc16(entry_p->data, size - sizeof(entry_hdr_t), 0xffff, 0);

	flash_write(FLASH_LAST_PAGE, page_buf, sizeof(nvram_t));
}
