#include <stdint.h>

#ifndef MEM
#define MEM

#define PG_PR		0x1		// Persent
#define PG_RW		0x2		// Read & Write
#define PG_US		0x4		// User
#define PG_WT		0x8		// Page Write-Through
#define PG_CD		0x10	// Page Cache Disable
#define PG_AC		0x20	// Accessed
#define PG_ET_DT	0x40	// Dirty
#define PG_ET_4M	0x80	// Page Size
#define PG_ET_GO	0x100	// Global

typedef struct page_t {
	uint32_t flags : 9;
	uint32_t os : 3;
	uint32_t base : 20;
} __attribute__((packed)) page_t;

void map(uint32_t va, uint32_t pa, uint8_t flags, uint8_t os);
void umap(uint32_t va);

#endif
