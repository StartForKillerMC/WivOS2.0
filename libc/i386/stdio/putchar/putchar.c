#include "putchar.h"

extern size_t terminal_column;
extern size_t terminal_row;
extern uint8_t FG;
extern uint8_t BG;

inline uint8_t make_color(uint8_t fg, uint8_t bg)
{
    return fg | bg << 4;
}

inline uint16_t make_vgaentry(char c, uint8_t color)
{
    return ((uint16_t)c | (uint16_t)color << 8);
}

void putchar(char c)
{
    const size_t index = (terminal_row * 80 + terminal_column);
    uint16_t* VideoMemory = (uint16_t)0xB8000;
    uint8_t terminal_color = make_color(FG,BG);
    
    VideoMemory[index] = make_vgaentry(' ', terminal_color);
    VideoMemory[index+1] = make_vgaentry(' ', terminal_color);
    
    VideoMemory[index] = (VideoMemory[index] & 0xFF00)|c;
    terminal_column++;
}