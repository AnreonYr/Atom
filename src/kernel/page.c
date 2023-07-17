#include "../include/page.h"
#include <stdint.h>

extern page_t pde[1024];
extern page_t pte[1024];

extern uint8_t text;
extern uint8_t data;
extern uint8_t rodata;
extern uint8_t bss;

void map(page_t *p, uint16_t number, uint32_t base, uint8_t flags, uint8_t go, uint8_t os) {
	p[number].base = (base >> 12);
	p[number].flags = flags;
	p[number].go = go;
	p[number].os = os;
}

void umap(page_t *p, uint16_t number) {
	p[number].base = 0;
	p[number].flags = 0;
	p[number].go = 0;
	p[number].os = 0;
}
