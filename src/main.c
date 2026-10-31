#include "log.h"
#include "puh_metadata.h"
#include "multiboot.h"
#include "framebuffer.h"
#include "extra/font8x8_basic.h"

extern void big_boobs();

void kmain(uint32_t magic, uint32_t mbi_addr) {

    // we do de ting👅👅👅👅
    uint8_t* ptr = (uint8_t*)(uintptr_t)mbi_addr + 8;
    uint32_t total_size = *(uint32_t*)(uintptr_t)mbi_addr;

    while (ptr < (uint8_t*)(uintptr_t)mbi_addr + total_size) {
        struct multiboot_tag* mb_tag = (struct multiboot_tag*)ptr;

        if (mb_tag->type == 0) break;

        if (mb_tag->type == 8) {
            struct multiboot_tag_framebuffer* fb = (struct multiboot_tag_framebuffer*)mb_tag;

            puhfb_init(
                fb->address,
                fb->pitch,
                fb->width,
                fb->height,
                fb->bpp,
                fb->framebuffer_type
            );

            break;
        }

        ptr += (mb_tag->size + 7) & ~7;
    }

    puhlog_print("WELCOME TO\n");
    puhlog_print("BRAZZERS IS FREE!\n");
    

    while (1) {
        asm volatile(
            "cli\n\t"
            "1:\n\t"
            "hlt\n\t"
            "jmp 1b"
            : : : "memory"
        );
    }
}