#include "define.h"

struct idt_entry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type;
    uint16_t offset_high;
} __attribute__((packed));

struct idt_pointer {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_pointer idtr;

extern void syscall_handler();

void idt_init() {
    uint32_t address = (uint32_t)syscall_handler;

    uint16_t code_selector;
    asm volatile ("mov %%cs, %0" : "=r"(code_selector));

    // accessible by ring 3
    idt[0x80].offset_low = address & 0xFFFF;
    idt[0x80].selector = code_selector;
    idt[0x80].zero = 0;
    idt[0x80].type = 0xEE;
    idt[0x80].offset_high = address >> 16;

    idtr.limit = sizeof(idt) - 1;
    idtr.base = (uint32_t)idt;

    asm volatile ("lidt %0" : : "m"(idtr));
}