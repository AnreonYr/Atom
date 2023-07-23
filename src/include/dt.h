// descriptor table

#include <stdint.h>

#ifndef DT
#define DT

#define GDT_SIZE 256
#define IDT_SIZE 256

#define US 0x3
#define SU 0x0

#define GT_AC_AC 0x1		// access
#define GT_AC_RW 0x2		// readable for code selector & writeable for data selector
#define GT_AC_DC 0x4		// direction
#define GT_AC_EX 0x8		// code segment

#define GT_CD 0x1		// code || data
#define GT_PR 0x1		// persent in memory

#define GT_FG_64 0x2		// 64 bit
#define GT_FG_32 0x4		// 32 bit
#define GT_FG_GR 0x8		// page granularity, limit in 4k blocks

#define IT_TP_TASK 0x5
#define IT_TP_INTR 0x6
#define IT_TP_TRAP 0x7
#define IT_TP_32   0x8

#define IT_PR 0x1		// persent in memory

typedef struct gdt_t {
	uint16_t limit_l;
	uint16_t base_l;
	uint8_t base_m;
	uint8_t type :4;
	uint8_t s : 1;
	uint8_t dpl : 2;
	uint8_t p : 1;
	uint8_t limit_h : 4;
	uint8_t flags : 4;
	uint8_t base_h;
}  __attribute__((packed)) gdt_t;

typedef struct idt_t {
	uint16_t offset_l;
	uint16_t selector;
	uint8_t null;
	uint8_t type : 4;
	uint8_t z : 1;
	uint8_t dpl : 2;
	uint8_t p : 1;
	uint16_t offset_h;
} __attribute__((packed)) idt_t;

typedef struct poniter_t {
	uint16_t length;
	uint32_t *index;
} __attribute__((packed)) pointer_t;

typedef struct selector_t {
	uint16_t rpl : 2;
	uint16_t ti : 1;
	uint16_t index : 13;
} __attribute__((packed)) selector_t;

void gdt_init();
void gdt_create(uint16_t number, uint32_t limit, uint32_t base, uint8_t type, uint8_t s, uint8_t dpl, uint8_t p, uint8_t flags);
void gdt_delete(uint16_t number);

void idt_init();
void idt_create(uint16_t number, uint32_t offset, uint16_t selector, uint8_t type, uint8_t dpl, uint8_t p);
void idt_delete(uint16_t number);

#endif
