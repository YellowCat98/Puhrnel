#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "define.h"

void puhfb_init(uint64_t address, uint32_t pitch, uint32_t width, uint32_t height, uint8_t bpp, uint8_t type);
void puhfb_putpixel(uint32_t x, uint32_t y, uint32_t color);
void puhfb_putchar(unsigned char character, uint32_t x, uint32_t y, uint32_t color, const char (*font)[8]);
void puhfb_clear(uint32_t color);

#endif