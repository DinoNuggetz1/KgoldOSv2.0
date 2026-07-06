#ifndef STDIO_H
#define STDIO_H
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long  uint32_t;
#define SCANCODE_TABLE_SIZE 58
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
unsigned char inportb(unsigned short _port);
unsigned char get_input_key(void);
void abet(void);
void draw_let(uint32_t *fb, int fb_width, int x, int y, const uint16_t *data);
void print_char(char c, unsigned char color);
void print_string(char *str, unsigned char color);
void draw_image(uint32_t *fb, int fb_width, int x, int y, int img_w, int img_h, const uint16_t *data);
void print_int(unsigned int n, unsigned char color);
int cmp(char *s1, char *s2);
#endif