#include "../include/dt.h"
#include <stdint.h>

extern gdt_t gdt[GDT_SIZE];
pointer_t gdt_ptr = {sizeof(gdt)-1, (uint32_t *)gdt};

void gdt_init() {
	gdt_create(0, 0, 0, 0, 0, 0, 0, 0);
	gdt_create(1, 0xffff, 0xC0000000, GT_AC_RW | GT_AC_EX, GT_CD, SU, GT_PR, GT_FG_32 | GT_FG_GR);
	gdt_create(2, 0xffff, 0xC0000000, GT_AC_RW, GT_CD, SU, GT_PR, GT_FG_32 | GT_FG_GR);
	asm volatile ("lgdt gdt_ptr");
}

void gdt_create(uint16_t number, uint32_t limit, uint32_t base, uint8_t type, uint8_t s, uint8_t dpl, uint8_t p, uint8_t flags) {
	gdt[number].limit_l = (limit & 0xffff);
	gdt[number].limit_h = ((limit >> 16) & 0xf);
	gdt[number].base_l = (base & 0xffff);
	gdt[number].base_m = ((base >> 16) & 0xff);
	gdt[number].base_h = (base >> 24);
	gdt[number].type = type;
	gdt[number].s = s;
	gdt[number].dpl = dpl;
	gdt[number].p = p;
	gdt[number].flags = (flags & 0xf);
}

void gdt_delete(uint16_t number) {
	gdt[number].limit_l = 0;
	gdt[number].limit_h = 0;
	gdt[number].base_l = 0;
	gdt[number].base_m = 0;
	gdt[number].base_h = 0;
	gdt[number].type = 0;
	gdt[number].s = 0;
	gdt[number].dpl = 0;
	gdt[number].p = 0;
	gdt[number].flags = 0;
}
