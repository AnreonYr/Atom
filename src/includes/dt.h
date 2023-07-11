// Copyright (c) 2023 AnreonYr. All Rights Reserved.
// descriptor table

#include <stdint.h>

#ifndef GDT
#define GDT

typedef struct gdt {
  uint16_t limit_low;
  uint32_t base_low : 24;
  uint8_t type : 4;
  uint8_t dpl : 2;
  uint8_t p : 1;
  uint8_t limit_high : 4;
  uint8_t flags : 4;
  uint16_t base_high;
} gdt;

typedef struct idt {
  uint16_t offset_low;
  uint16_t selector;
  uint8_t null;
  uint8_t type : 4;
  uint8_t s : 1;
  uint8_t dpl : 2;
  uint8_t p : 1;
  uint16_t offset_high;
} idt;

typedef struct selector {
  uint16_t rpl : 2;
  uint16_t ti : 1;
  uint16_t index : 13;
} selector;

#endif
