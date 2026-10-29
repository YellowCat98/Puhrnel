// FUCK VGA TEXT MODE

#include "framebuffer.h"

static volatile uint8_t *fb;
static uint32_t fb_width;
static uint32_t fb_height;
static uint32_t fb_pitch;

void puhfb_init(uint64_t address, uint32_t pitch, uint32_t width, uint32_t height, uint8_t bpp, uint8_t type) {
    if (bpp != 32 || type != 1) {
        return;
    }

    fb = (volatile uint8_t *)(uintptr_t)address;
    fb_pitch = pitch;
    fb_width = width;
    fb_height = height;
}

void puhfb_putpixel(uint32_t x, uint32_t y, uint32_t color) {
    if (!fb || x >= fb_width || y >= fb_height) return;

    volatile uint32_t* pixel = (volatile uint32_t *)(fb + y * fb_pitch + x * 4);

    *pixel = color;
}