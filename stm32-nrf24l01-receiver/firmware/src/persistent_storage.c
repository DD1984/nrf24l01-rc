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

#include "platform.h"
#include "persistent_storage.h"


#define FLASH_PAGE_SIZE   	1024UL
#define FLASH_SIZE   		(16*1024UL)
#define FLASH_LAST_PAGE		(FLASH_BASE + (FLASH_SIZE - FLASH_PAGE_SIZE))

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

// ****************************************************************************
void load_persistent_storage(uint8_t *data)
{
    uint32_t num = NUMBER_OF_PERSISTENT_ELEMENTS;
    
    if (num <= FLASH_PAGE_SIZE)
    {
        uint16_t num_to_read;
        uint16_t tmp;
        __IO uint16_t *pflash = (__IO uint16_t*)FLASH_LAST_PAGE;
        
        num_to_read = (num + 1) >> 1;

        while (num_to_read--)
        {
            tmp = *pflash++;
            *data++ = tmp & 0x00FF;
            num--;
            if (num)
            {
                *data++ = (tmp >>8) & 0x00FF;
                num--;
            }
        }
    }
}


// ****************************************************************************
void save_persistent_storage(uint8_t new_data[])
{
    uint32_t num = NUMBER_OF_PERSISTENT_ELEMENTS;
    
    if (num <= FLASH_PAGE_SIZE)
    {
        UnlockFlash();
        ErasePage(FLASH_LAST_PAGE);

        __IO uint16_t *pflash = (__IO uint16_t*)FLASH_LAST_PAGE;
        uint32_t num_to_write = (num + 1) >> 1;
        while(num_to_write--)
        {
            uint16_t tmp = *new_data++;
            num--;
            if (num)
            {
                tmp |= (*new_data++) << 8;
                num--;
            }

            FLASH->CR |= FLASH_CR_PG;
            *pflash++ = tmp; 
            while ((FLASH->SR & FLASH_SR_BSY) != 0);
            if ((FLASH->SR & FLASH_SR_EOP) != 0) 
            {
                FLASH->SR |= FLASH_SR_EOP;
            }
                FLASH->CR &= ~FLASH_CR_PG;
            }

        LockFlash();
    }
}
