#include "log.h"
#include "framebuffer.h"
#include "define.h"
#include "extra/font8x8_basic.h"

static uint32_t cursorX = 0;
static uint32_t cursorY = 0;

void puhlog_clear(void) {
    puhfb_clear(0x000000);
}

void puhlog_print(const char* message) {
    for (const char* p = message; *p != '\0'; ++p) {
        char c = *p;

        if (c == '\n') {
            cursorX = 0;
            cursorY += 1;
            continue;
        }

        puhfb_putchar(c, cursorX * 8, cursorY * 8, 0xAAAAAA, font8x8_basic);
        // multiplying by 8 so the distance between each character is 8 pixels
        cursorX++;
    }
}