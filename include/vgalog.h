#ifndef VGALOG_H
#define VGALOG_H

#include "define.h"

#define VGA_ADDRESS 0xB8000
#define VGA_HEIGHT 25
#define VGA_WIDTH 80

enum vga_color {
    vgaColorBlack = 0,
    vgaColorGreen = 2,
    vgaColorRed = 4,
    vgaColorGrey = 7,
    vgaColorWhite = 15,
};

void puhvgalog_clear();
void puhvgalog_print(const char* message); // THIS IS SIMPLY A WRAPPER AROUND puhvgalog_printc! DEFAULTS TO WHITE.
void puhvgalog_printc(const char* message, uint8_t color);

#endif