#include "kernel/cpu/GDT.h"

extern void gdt_flush(addr_t);

struct gdt_entry_struct gdt_entries[5];
struct gdt_prt_struct gdt_prt;

void initGdt(){
    gdt_prt.limit = (sizeof(struct gdt_entry_struct) * 5) -1;
    gdt_prt.base = &gdt_entries;
    setGdtGate(0,0,0,0,0);
    setGdtGate(1,0,0xFFFFFFFF,0x9A,0xCF);
    setGdtGate(2,0,0xFFFFFFFF,0x92,0xCF);
    setGdtGate(3,0,0xFFFFFFFF,0xFA,0xCF);
    setGdtGate(4,0,0xFFFFFFFF,0xF2,0xCF);
    gdt_flush(&gdt_prt);
}
void setGdtGate(uint32_t num, uint32_t base,uint32_t limit, uint8_t access, uint8_t gran){
    gdt_entries[num].base_low = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high = (base >> 24) & 0xFF;

    gdt_entries[num].limit = (limit & 0xFFFF);
    gdt_entries[num].flags = (limit >> 16) & 0x0F;
    gdt_entries[num].flags |= (gran & 0xF0);

    gdt_entries[num].access = access;

}