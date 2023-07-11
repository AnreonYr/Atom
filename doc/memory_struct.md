# Memory Map

SIZE

- page_directory_entry 4K
- page_table_entry 4M

page_directory_entry -> pde
page_table_entry -> pte

mapping pde to pte[0]

pte is in kernel lower area that is of 4M size
