#pragma once

struct idt_entry{
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags){
    /* We'll leave you to try and code this function: take the
    *  argument 'base' and split it up into a high and low 16-bits,
    *  storing them in idt[num].base_hi and base_lo. The rest of the
    *  fields that you must set in idt[num] are fairly self-
    *  explanatory when it comes to setup */
}

/*void idt_install(){
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = &idt;

    memset(&idt;, 0, sizeof(struct idt_entry) * 256);
    idt_load();
}*/