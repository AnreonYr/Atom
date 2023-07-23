#include "../include/mem.h"
#include <stdint.h>

uint32_t *pde = (uint32_t *)(0xC0300000);
uint32_t *pte = (uint32_t *)(0xC0000000);

void mmap(uint32_t va, uint32_t pa, uint32_t flags) {
	uint32_t offset_pde = (va >> 22);
	uint32_t offset_pte = ((va >> 22) * 0x400);
	*(pde + offset_pde) = ((0x100000 + offset_pte * 4)| flags);
	*(pte + offset_pte) = (pa | flags);
}

void ummap(uint32_t va) {
	uint32_t offset_pde = (va >> 22);
	uint32_t offset_pte = ((va >> 22) * 0x400);
	*(pde + offset_pde) = 0;
	*(pte + offset_pte) = 0;
}
