#include "../include/dt.h"
#include <stdint.h>

extern gdt_t gdt[512];
gptr_t gptr = {sizeof(gdt)-1, gdt};

void gdt_init() {
	gdt_create(0, 0, 0, 0, 0);
	gdt_create(1, 0xffff, 0xC0800000, DT_AC_RW | DT_AC_EX | DT_AC_CD | DT_AC_PR, DT_FG_32);
	gdt_create(2, 0xffff, 0xC0800000, DT_AC_RW | DT_AC_CD | DT_AC_PR, DT_FG_32);
	asm volatile ("lgdt gptr");
}

void gdt_create(uint16_t number, uint32_t limit, uint32_t base, uint8_t access, uint8_t flags) {
	gdt[number].limit_l = (limit & 0xffff);
	gdt[number].limit_h = ((limit >> 16) & 0xf);
	gdt[number].base_l = (base & 0xffff);
	gdt[number].base_m = ((base >> 16) & 0xff);
	gdt[number].base_h = (base >> 24);
	gdt[number].access = access;
	gdt[number].flags = (flags & 0xf);
}

void gdt_delete(uint16_t number) {
	gdt[number].limit_l = 0;
	gdt[number].limit_h = 0;
	gdt[number].base_l = 0;
	gdt[number].base_m = 0;
	gdt[number].base_h = 0;
	gdt[number].access = 0;
	gdt[number].flags = 0;
}
