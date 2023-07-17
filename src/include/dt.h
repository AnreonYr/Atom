// descriptor table

#include <stdint.h>

#ifndef GDT
#define GDT

#define DT_AC_AC		0x1			// access
#define DT_AC_RW		0x2			// readable for code selector & writeable for data selector
#define DT_AC_DC		0x4			// direction
#define DT_AC_EX		0x8			// code segment
#define DT_AC_CD		0x10		// code || data
#define DT_AC_PL(x)		(x << 5)	// DPL
#define DT_AC_PR		0x80		// persent in memory

#define DT_FG_GR 0x8		// page granularity, limit in 4k blocks
#define DT_FG_32 0x4		// 32 bit
#define DT_FG_64 0x2		// 64 bit

typedef struct gdt_t {
	uint16_t limit_l;
	uint16_t base_l;
	uint8_t base_m;
	uint8_t access;
	uint8_t limit_h : 4;
	uint8_t flags : 4;
	uint8_t base_h;
}  __attribute__((packed)) gdt_t;

typedef struct gptr_t {
	uint16_t length;
	gdt_t* index;
} __attribute__((packed)) gptr_t;

typedef struct idt_t {
	uint16_t offset_l;
	uint16_t selector;
	uint8_t null;
	uint8_t type : 4;
	uint8_t s : 1;
	uint8_t dpl : 2;
	uint8_t p : 1;
	uint16_t offset_h;
} __attribute__((packed)) idt_t;

typedef struct selector_t {
	uint16_t rpl : 2;
	uint16_t ti : 1;
	uint16_t index : 13;
} __attribute__((packed)) selector_t;

void gdt_init();
void gdt_create(uint16_t number, uint32_t limit, uint32_t base, uint8_t access, uint8_t flags);
void gdt_delete(uint16_t number);

#endif
