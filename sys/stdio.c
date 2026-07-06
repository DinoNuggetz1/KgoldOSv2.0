unsigned short *vga_buffer = (unsigned short *)0xB8000;
int l = 22;
int y = 0;
int x = 0;
char cmd[32]; 
int cmd_idx = 0;
const int char_w = 22;
const int char_h = 28;
int gui_x = 0;
int gui_y = 0;
const int gui_width_limit = 1000;
__attribute__((section(".rodata"))); char *logo =
"||   ||  (_)\n"
"||___||  | |\n"
"||   ||  |_|\n";
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef unsigned long size_t;
#include "Untitled.h"
#include "Background.h"
#define IMG_W 1024
#define IMG_H 768
const char scancode_to_ascii[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' '
};
static inline unsigned char inportb (unsigned short _port) {
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}
static inline void outportb(unsigned short port, unsigned char val) {
    __asm__ __volatile__ ("outb %0, %1" : : "a"(val), "Nd"(port));
}
#include "Taskbar.h"
#include "chars/A2.h"
#include "chars/B2.h"
#include "chars/C2.h"
#include "chars/D2.h"
#include "chars/E2.h"
#include "chars/F2.h"
#include "chars/G2.h"
#include "chars/H2.h"
#include "chars/I2.h"
#include "chars/J2.h"
#include "chars/K2.h"
#include "chars/L2.h"
#include "chars/M2.h"
#include "chars/N2.h"
#include "chars/O2.h"
#include "chars/P2.h"
#include "chars/Q2.h"
#include "chars/R2.h"
#include "chars/S2.h"
#include "chars/T2.h"
#include "chars/U2.h"
#include "chars/V2.h"
#include "chars/W2.h"
#include "chars/X2.h"
#include "chars/Y2.h"
#include "chars/Z2.h"
#include "chars/a1.h"
#include "chars/b1.h"
#include "chars/c1.h"
#include "chars/d1.h"
#include "chars/e1.h"
#include "chars/f1.h"
#include "chars/g1.h"
#include "chars/h1.h"
#include "chars/i1.h"
#include "chars/j1.h"
#include "chars/k1.h"
#include "chars/l1.h"
#include "chars/m1.h"
#include "chars/n1.h"
#include "chars/o1.h"
#include "chars/p1.h"
#include "chars/q1.h"
#include "chars/r1.h"
#include "chars/s1.h"
#include "chars/t1.h"
#include "chars/u1.h"
#include "chars/v1.h"
#include "chars/w1.h"
#include "chars/x1.h"
#include "chars/y1.h"
#include "chars/z1.h"
#include "chars/char_48.h"
#include "chars/char_49.h"
#include "chars/char_50.h"
#include "chars/char_51.h"
#include "chars/char_52.h"
#include "chars/char_53.h"
#include "chars/char_54.h"
#include "chars/char_55.h"
#include "chars/char_56.h"
#include "chars/char_57.h"
//special chars
#include "chars/char_62.h"
#include "chars/char_60.h"
#include "chars/char_33.h"
#include "chars/char_64.h"
#include "chars/char_35.h"
#include "chars/char_36.h"
#include "chars/char_37.h"
#include "chars/char_94.h"
#include "chars/char_38.h"
#include "chars/char_42.h"
#include "chars/char_40.h"
#include "chars/char_41.h"
#include "chars/char_46.h"
#include "chars/char_44.h"
unsigned char get_input_key() {
    unsigned char scancode = 0;
    
    while (!(inportb(0x64) & 1));
    
    scancode = inportb(0x60);
    
    return scancode;
}
const uint16_t* fonts[256] = {0};
void abet(){
fonts['A'] = A2;
fonts['B'] = B2;
fonts['C'] = C2;
fonts['D'] = D2;
fonts['E'] = E2;
fonts['F'] = F2;
fonts['G'] = G2;
fonts['H'] = H2;
fonts['I'] = I2;
fonts['J'] = J2;
fonts['K'] = K2;
fonts['L'] = L2;
fonts['M'] = M2;
fonts['N'] = N2;
fonts['O'] = O2;
fonts['P'] = P2;
fonts['Q'] = Q2;
fonts['R'] = R2;
fonts['S'] = S2;
fonts['T'] = T2;
fonts['U'] = U2;
fonts['V'] = V2;
fonts['W'] = W2;
fonts['X'] = X2;
fonts['Y'] = Y2;
fonts['Z'] = Z2;
fonts['a'] = a1;
fonts['b'] = b1;
fonts['c'] = c1;
fonts['d'] = d1;
fonts['e'] = e1;
fonts['f'] = f1;
fonts['g'] = g1;
fonts['h'] = h1;
fonts['i'] = i1;
fonts['j'] = j1;
fonts['k'] = k1;
fonts['l'] = l1;
fonts['m'] = m1;
fonts['n'] = n1;
fonts['o'] = o1;
fonts['p'] = p1;
fonts['q'] = q1;
fonts['r'] = r1;
fonts['s'] = s1;
fonts['t'] = t1;
fonts['u'] = u1;
fonts['v'] = v1;
fonts['w'] = w1;
fonts['x'] = x1;
fonts['y'] = y1;
fonts['z'] = z1;
fonts['0'] = char_48;
fonts['1'] = char_49;
fonts['2'] = char_50;
fonts['3'] = char_51;
fonts['4'] = char_52;
fonts['5'] = char_53;
fonts['6'] = char_54;
fonts['7'] = char_55;
fonts['8'] = char_56;
fonts['9'] = char_57;

fonts['>'] = char_62;
fonts['<'] = char_60;
fonts['!'] = char_33;
fonts['@'] = char_64;
fonts['#'] = char_35;
fonts['$'] = char_36;
fonts['%'] = char_37;
fonts['^'] = char_94;
fonts['&'] = char_38;
fonts['*'] = char_42;
fonts['('] = char_40;
fonts[')'] = char_41;
fonts['.'] = char_46;
fonts[','] = char_44;
}

void draw_let(uint32_t *fb, int fb_width, int x, int y, const uint16_t *data) {
    int img_h = 25;
    for (int i = 0; i < img_h; i++) {
        
        int img_w = 15;
        for (int j = 0; j < img_w; j++) {
            uint16_t color16 = data[i * img_w + j];
            if (color16 == 0x0000) {continue;}
            uint8_t r5 = (color16 >> 11) & 0x1F;
            uint8_t g6 = (color16 >> 5) & 0x3F;
            uint8_t b5 = (color16) & 0x1F;
            uint32_t r8 = (r5 * 255) / 31;
            uint32_t g8 = (g6 * 255) / 63;
            uint32_t b8 = (b5 * 255) / 31;
            fb[(y + i) * fb_width + (x + j)] = (r8 << 16) | (g8 << 8) | b8;
        }
    }
}

void print_char(char c, unsigned char color) {
    if (c == '\n') {
        x = 0; y++;
    } else {
        vga_buffer[y * 80 + x] = (color << 8) | c;
        if (x >= 79) { x = 0; y++; } else { x++; }
    }
    if (c == '\n') {
        gui_x = 100; 
        gui_y += 28; 
    } else {
        uint32_t *fb = (uint32_t *)0xFD000000;
        const uint16_t *data = fonts[(unsigned char)c];

        if (data != 0) {
            draw_let(fb, 1024, gui_x, gui_y, data);
        }
        gui_x += 15;
        if (gui_x > gui_width_limit) {
            gui_x = 100;
            gui_y += 25;
        }
    }
}

void print_string(char *str, unsigned char color) {
   for (int i = 0; str[i] != '\0'; i++) {
       print_char(str[i], color);
   }
}

void draw_image(uint32_t *fb, int fb_width, int x, int y, int img_w, int img_h, const uint16_t *data) {
    for (int i = 0; i < img_h; i++) {
        for (int j = 0; j < img_w; j++) {
            uint16_t color16 = data[i * img_w + j];
            if (color16 == 0x0000) {continue;}
            uint8_t r5 = (color16 >> 11) & 0x1F;
            uint8_t g6 = (color16 >> 5) & 0x3F;
            uint8_t b5 = (color16) & 0x1F;
            uint32_t r8 = (r5 * 255) / 31;
            uint32_t g8 = (g6 * 255) / 63;
            uint32_t b8 = (b5 * 255) / 31;
            fb[(y + i) * fb_width + (x + j)] = (r8 << 16) | (g8 << 8) | b8;
        }
    }
}

int strncmp(const char *s1, const char *s2, size_t n) {
    while (n > 0) {
        if (*s1 != *s2 || *s1 == '\0') {
            return (unsigned char)*s1 - (unsigned char)*s2;
        }
        s1++;
        s2++;
        n--;
    }
    return 0;
}



void print_int(unsigned int n, unsigned char color) {
    char buf[11];
    int i = 10;
    buf[i] = '\0';
    if (n == 0) buf[--i] = '0';
    while (n > 0 && i > 0) {
        buf[--i] = (n % 10) + '0';
        n /= 10;
    }
    print_string(&buf[i], color);
}
int cmp(char *s1, char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }

    return *(unsigned char *)s1 - *(unsigned char *)s2;
}
