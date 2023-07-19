#include "../include/mem.h"
#include <stdint.h>

extern page_t pde[1024];
extern page_t pte[1024];

void map(uint32_t va, uint32_t pa, uint8_t flags, uint8_t os) {
	uint32_t num1 = (va >> 22);
	pde[num1].base = (uint32_t)pte;
	pde[num1].flags = PG_PR | PG_US | PG_RW | PG_ET_GO;
	pde[num1].os = 0;
	uint32_t num2 = ((va >> 12) & 0x3ff);
	pte[num2].base = pa;
	pte[num2].flags = flags;
	pte[num2].os = os;
}

void umap(uint32_t va) {
	uint32_t num1 = (va >> 22);
	pde[num1].base = 0;
	pde[num1].flags = 0;
	pde[num1].os = 0;
	uint32_t num2 = ((va >> 12) & 0x3ff);
	pte[num2].base = 0;
	pte[num2].flags = 0;
	pte[num2].os = 0;
}
