#include "../include/dt.h"
#include <stdint.h>

extern idt_t idt[IDT_SIZE];
pointer_t idt_ptr = {sizeof(idt)-1, idt};

void idt_init() {
	asm volatile ("lidt idt_ptr");
}

void idt_create(uint16_t number, uint32_t offset, uint16_t selector, uint8_t type, uint8_t dpl, uint8_t p) {
	idt[number].offset_l = (offset & 0xffff);
	idt[number].offset_h = (offset >> 16);
	idt[number].selector = selector;
	idt[number].type = type;
	idt[number].dpl = dpl;
	idt[number].p = p;
}

void idt_delete(uint16_t number) {
	idt[number].offset_l = 0;
	idt[number].offset_h = 0;
	idt[number].selector = 0;
	idt[number].type = 0;
	idt[number].dpl = 0;
	idt[number].p = 0;
}
