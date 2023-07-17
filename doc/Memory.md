# Memory Map

## Kernel space

kernel

- code
- stack
- heap
- page
- gdt
- idt

Kernel is at high address space and is of 1GB size

### Page

Size

- page_directory_entry 4K
- page_table_entry 4M

page_directory_entry -> pde
page_table_entry -> pte

mapping pde -> pde[0] -> pte[0]

pte is in kernel lower area that is of 4M size
