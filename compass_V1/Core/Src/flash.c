#include "flash.h"

void Flash_Delete(uint32_t pageAddress) 
{ 
   while (FLASH->SR & FLASH_SR_BSY);
		if (FLASH->SR & FLASH_SR_EOP) {
				FLASH->SR = FLASH_SR_EOP;
		}

		FLASH->CR |= FLASH_CR_PER;
		FLASH->AR = pageAddress;
		FLASH->CR |= FLASH_CR_STRT;
		while (!(FLASH->SR & FLASH_SR_EOP));
		FLASH->SR = FLASH_SR_EOP;
		FLASH->CR &= ~FLASH_CR_PER;
}
void Flash_Write(uint32_t Flash_Address,uint16_t Flash_Data)
{ 
    HAL_FLASH_Unlock();
    Flash_Delete(Flash_Address);
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,Flash_Address,Flash_Data);
    HAL_FLASH_Lock();
}
uint32_t Flash_Read(uint32_t Flash_Address)
{
    uint32_t Flash_Data;
    Flash_Data = *(uint32_t*)Flash_Address;
    return Flash_Data;	
}