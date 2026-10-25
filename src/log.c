#include "log.h"

static int cursor_x = 0;
static int cursor_y = 0;

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t)uc | (uint16_t)color << 8;
}

static void puhlog_scroll(void) {
    volatile uint16_t* vga_buffer = (volatile uint16_t*)VGA_ADDRESS;

    for (int y = 1; y < VGA_HEIGHT; ++y) {
        for (int x = 0; x < VGA_WIDTH; ++x) {
            vga_buffer[(y - 1) * VGA_WIDTH + x] = vga_buffer[y * VGA_WIDTH + x];
        }
    }

    uint16_t entry = vga_entry(' ', vgaColorBlack);

    for (int x = 0; x < VGA_WIDTH; ++x) {
        vga_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = entry;
    }

    cursor_y = VGA_HEIGHT - 1;
}

void puhlog_clear(void) {
    volatile uint16_t* vga_buffer = (volatile uint16_t*)VGA_ADDRESS;
    uint16_t entry = vga_entry(' ', vgaColorBlack);

    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; ++i) {
        vga_buffer[i] = entry;
    }

    cursor_x = 0;
    cursor_y = 0;
}

void puhlog_print(const char* message) {
    return puhlog_printc(message, vgaColorWhite);
}

void puhlog_printc(const char* message, uint8_t color) {
    volatile uint16_t* vga_buffer = (volatile uint16_t*)VGA_ADDRESS;

    for (int i = 0; message[i] != '\0'; ++i) {
        if (message[i] == '\n') {
            cursor_x = 0;
            cursor_y++;
        } else {
            int index = cursor_y * VGA_WIDTH + cursor_x;
            vga_buffer[index] = vga_entry(message[i], color);
            cursor_x++;
        }

        if (cursor_x >= VGA_WIDTH) {
            cursor_x = 0;
            cursor_y++;
        }

        if (cursor_y >= VGA_HEIGHT) {
            puhlog_scroll();
        }
    }
}