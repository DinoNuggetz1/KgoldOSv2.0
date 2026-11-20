#include "sys/stdio.h"
#include "sys/features.h"
#include "sys/acpi.h"
#include "sys/stdlib.h"
char files[13] = "read.me";
int none = 0;
#include <stdint.h>
int memsrch(long *start, long *end, long obj) {
    for (long *p = start; p < end; p++) {
        if (*p == obj)
            return (int)p;
    }
    return 0;
}



void shell(unsigned char scancode) {
    if (scancode >= sizeof(scancode_to_ascii)) return;
    
    char c = scancode_to_ascii[scancode];
    if (c == 0) return;

    if (c == '\n') {

        cmd[cmd_idx] = '\0';

        int handled = 0;

        if (cmp(cmd, "help") == 0) {
            print_string("\nCommands: help, cred, int0, clr, gui, logo, acpi dump, progma ##", 0x0E);
            handled = 1;
        }
        else if (strncmp(cmd, "progma", 6) == 0) {
            short proc = (cmd[7] - '0') * 10 + (cmd[8] - '0');
            K_atlantic(proc);
            handled = 1;
        }
        else if (cmp(cmd, "cred") == 0) {
            print_string("\nKernel Build 1.2.5 (UEFI) (x86)\nNo warranty, GPLv3 licensing", 0x04);
            hardwarefind();
            print_string("\nCPU: ", 0x0F);
            print_string(vendor, 0x0E);
            handled = 1;
        }
        //Hardware
        else if (cmp(cmd, "int0") == 0) {
            print_string("\nTriggering panic...", 0x0E);
            panic();
            handled = 1;
        }
        else if(cmp(cmd, "acpi dump") == 0){
            ACPI_DUMP();  
            handled = 1;
        }
        else if(strncmp(cmd, "inb ", 4)==0){
            //uint16_t port = (cmd[4] - '0') * 10 + (cmd[5] - '0') * 10 + (cmd[6] - '0') * 10 + (cmd[7] - '0') * 10 + (cmd[8] - '0' ) * 10 +(cmd[9] - '0' ) * 10 +(cmd[10] - '0' );
            char *port_str = cmd + 4;
            int num = atoi(port_str);
            print_char('\n',0x0e);
            print(num);
            print_char('\n',0x0e);
            uint16_t port = (uint16_t)num;
            long result = inportb(port);
            print_int(result, 0x0e);
            handled = 1;
        }
        else if(strncmp(cmd, "outb ", 5)==0){
            //uint16_t port = (cmd[4] - '0') * 10 + (cmd[5] - '0') * 10 + (cmd[6] - '0') * 10 + (cmd[7] - '0') * 10 + (cmd[8] - '0' ) * 10 +(cmd[9] - '0' ) * 10 +(cmd[10] - '0' );
            char *port_str = cmd + 5;   // right after "outb "
            int port = atoi(port_str);
            while (*port_str && *port_str != ' ') port_str++;
            if (*port_str == 0) return;
            port_str++; // skip space
            int val = atoi(port_str);
            outportb((uint16_t)port, (uint8_t)val);
            print_string("\nOp Completed", 0x0e);
            handled = 1;
        }
        //GUI
        else if (cmp(cmd, "clr") == 0) {
            for (int i = 0; i < 80 * 25; i++)
                vga_buffer[i] = (0x0F << 8) | ' ';
            x = 0;
            y = 0;
            draw_image(framebuffer, framebuffer_pitch, 0, 0, IMG_W, IMG_H, Background);
            gui_x = 50;
            gui_y = 50;
            handled = 1;
        }

        else if (cmp(cmd, "gui") == 0) {
            gui_x = 50;
            gui_y = 50;

            draw_image(framebuffer, framebuffer_pitch, 0, 0, IMG_W, IMG_H, Background);
            draw_image(framebuffer, framebuffer_pitch, 400, 250, 196, 225, Untitled);
            draw_image(framebuffer, framebuffer_pitch, 0, framebuffer_height - 50, framebuffer_width, 50, Taskbar);

            handled = 1;
        }

        else if (cmp(cmd, "logo") == 0) {
            print_string("\n", 0x0F);
            print_string(logo, 0x0F);
            handler();
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

            draw_image(framebuffer, framebuffer_pitch,
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

typedef struct GOP{
    uint64_t FrameBufferBase;
    uint64_t FrameBufferSize;
    uint64_t HorizontalResolution;
    uint64_t VerticalResolution;
    };
__attribute__((section(".text.entry"), used))
void kernel_main(uint64_t framebuffer_base, uint64_t framebuffer_pitch,uint64_t framebuffer_width, uint64_t framebuffer_height, uint64_t framebuffer_format) {
    passfb((uint64_t)framebuffer_base, (uint32_t)framebuffer_pitch,
           (uint32_t)framebuffer_width, (uint32_t)framebuffer_height,
           (uint32_t)framebuffer_format);
    // Clear screen
    for (int i = 0; i < 80 * 25; i++) {
        vga_buffer[i] = (0x0F << 8) | ' '; 
    }
    //Starting mainh proccesses
    abet();
    y = 0; x = 0;
    print_string(logo, 0x9F);
    print_string("\nWelcome To the Shell(KGoldOS) type ""help"" for a list of command\nVersion 1.2.5 (UEFI) GNU 3 (x86)", 0x05);
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
void K_atlantic(short process){
switch (process){
    case 1: RSDT_DUMP(); break;
    case 2: panic();break;
    case 3: FrameinfoDump();

}
}
