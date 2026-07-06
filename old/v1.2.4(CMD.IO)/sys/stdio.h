#ifndef STDIO_H
#define STDIO_H
#define print(x) _Generic((x), \
    char: print_char, \
    unsigned char: print_char, \
    int: print_int, \
    unsigned int: print_int, \
    long: print_int, \
    unsigned long: print_int, \
    char*: print_string \
)(x, 0x0F)
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long  uint32_t;
typedef unsigned long size_t;
#define SCANCODE_TABLE_SIZE 58
static inline unsigned char inportb (unsigned short _port) {
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}
static inline void outportb(unsigned short port, unsigned char val) {
    __asm__ __volatile__ ("outb %0, %1" : : "a"(val), "Nd"(port));
}
extern unsigned short *vga_buffer;
extern int x;
extern int y;
extern int gui_x;
extern int gui_y;
extern char *logo;
extern char vendor[13];
extern const char scancode_to_ascii[SCANCODE_TABLE_SIZE];
#define IMG_W 1024
#define IMG_H 768
extern const uint16_t Background[];
extern const uint16_t Untitled[];
extern const uint16_t Taskbar[];
extern char cmd[32]; 
extern int cmd_idx;
unsigned char get_input_key(void);
int strncmp(const char *s1, const char *s2, size_t n);
void abet(void);
void draw_let(uint32_t *fb, int fb_width, int x, int y, const uint16_t *data);
void print_char(char c, unsigned char color);
void print_string(char *str, unsigned char color);
void draw_image(uint32_t *fb, int fb_width, int x, int y, int img_w, int img_h, const uint16_t *data);
void print_int(unsigned int n, unsigned char color);
int cmp(char *s1, char *s2);
#endif