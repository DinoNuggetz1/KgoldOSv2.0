#include "sys/stdio.h"
#include "sys/features.h"
char files[13] = "read.me";
int none = 0;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
int memsrch(char *start, char *end, char obj) {
    for (char *p = start; p < end; p++) {
        if (*p == obj)
            return (int)p;
    }
    return 0;
}

int ACPI_reader(){
    for (char *p = (char*)0xE0000;
        p < (char*)0x100000;
        p += 16)

        if (p[0]=='R' &&
            p[1]=='S' &&
            p[2]=='D' &&
            p[3]==' ' &&
            p[4]=='P' &&
            p[5]=='T' &&
            p[6]=='R' &&
            p[7]==' ')
        
        return p;
    
}



void shell(unsigned char scancode) {
    if (scancode >= sizeof(scancode_to_ascii)) return;
    
    char c = scancode_to_ascii[scancode];
    if (c == 0) return;

    if (c == '\n') {

        cmd[cmd_idx] = '\0';

        int handled = 0;

        if (cmp(cmd, "help") == 0) {
            print_string("\nCommands: help, cred, int0, clr, gui, logo", 0x0E);
            handled = 1;
        }

        else if (cmp(cmd, "cred") == 0) {
            print_string("\nKernel Build 0.2 (x86)\nNo warranty.", 0x04);
            hardwarefind();
            print_string("\nCPU: ", 0x0F);
            print_string(vendor, 0x0E);
            handled = 1;
        }

        else if (cmp(cmd, "int0") == 0) {
            print_string("\nTriggering panic...", 0x0E);
            panic();
            handled = 1;
        }
        else if(cmp(cmd, "acpi dump") == 0){
            long general = ACPI_reader();
            print_char('\n',0x0e);
            print_string(general,0x0e);
            handled = 1;

        }

        else if (cmp(cmd, "clr") == 0) {
            for (int i = 0; i < 80 * 25; i++)
                vga_buffer[i] = (0x0F << 8) | ' ';

            x = 0;
            y = 0;

            print_string(logo, 0x0F);
            handled = 1;
        }

        else if (cmp(cmd, "gui") == 0) {
            uint32_t *fb = (uint32_t *)0xFD000000;

            gui_x = 50;
            gui_y = 50;

            draw_image(fb, 1024, 0, 0, IMG_W, IMG_H, Background);
            draw_image(fb, 1024, 400, 250, 196, 225, Untitled);
            draw_image(fb, 1024, 0, 718, 1024, 50, Taskbar);

            handled = 1;
        }

        else if (cmp(cmd, "logo") == 0) {
            print_string("\n", 0x0F);
            print_string(logo, 0x0F);
            handled = 1;
        }

        if (!handled && cmd_idx > 0) {
            print_string("\nUnknown Command", 0x50);
        }

        print_string("\nShell> ", 0x0F);

        cmd_idx = 0;
        for (int i = 0; i < 32; i++) cmd[i] = 0;

    }
    else if (c == '\b') {

        if (cmd_idx > 0) {
            cmd_idx--;
            cmd[cmd_idx] = 0;

            if (x > 0) x--;

            vga_buffer[y * 80 + x] = (0x0F << 8) | ' ';

            if (gui_x > 0) gui_x -= 15;

            draw_image((uint32_t*)0xFD000000, 1024,
                       gui_x, gui_y, 15, 25, Background);
        }

    }
    else {
        if (cmd_idx < 31) {
            cmd[cmd_idx++] = c;
            cmd[cmd_idx] = 0;

            print_char(c, 0x0F);
        }
    }
}
void kernel_main() {
    // Clear screen
    for (int i = 0; i < 80 * 25; i++) {
        vga_buffer[i] = (0x0F << 8) | ' '; 
    }
    abet();
    y = 0; x = 0;
    print_string(logo, 0x9F);
    print_string("\nWelcome To the Shell type ""help"" for a list of commands\nVersion 1.2 GNU 3 (x86)", 0x05);
    print_string("Cpu type: ", 0x0);
    hardwarefind();
    print_string(vendor,0x0);
    print_string("\nShell> ", 0x0F);
    cmd[0] = '\0';
    cmd[1] = '\0';
    cmd[2] = '\0';
    cmd[3] = '\0';
    while(1) {
        unsigned char scancode = get_input_key();
        
        if (!(scancode & 0x80)) {
            shell(scancode);
        }
    }
}
