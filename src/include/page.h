#include <stdint.h>

#ifndef PAGE
#define PAGE

#define PG_PR		0x1		// Persent
#define PG_RW		0x2		// Read & Write
#define PG_US		0x4		// User
#define PG_WT		0x8		// Page Write-Through
#define PG_CD		0x10	// Page Cache Disable
#define PG_AC		0x20	// Accessed
#define PG_ET_DT	0x40	// Dirty
#define PG_ET_4M	0x80	// Page Size
#define PG_ET_GO	0x1	// Global

typedef struct page_t {
	uint32_t flags : 8;
	uint32_t go : 1;
	uint32_t os : 3;
	uint32_t base : 20;
} __attribute__((packed)) page_t;

void map(page_t *p, uint16_t number, uint32_t base, uint8_t flags, uint8_t go, uint8_t os);
void umap(page_t *p, uint16_t number);

#endif
