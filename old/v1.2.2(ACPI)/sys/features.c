typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
char vendor[13];

void get_cpu_vendor(char *vendor) {
    uint32_t ebx, edx, ecx;
    uint32_t eax = 0;

    asm volatile (
        "cpuid"
        : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
        : "a"(eax)
    );

    ((uint32_t*)vendor)[0] = ebx;
    ((uint32_t*)vendor)[1] = edx;
    ((uint32_t*)vendor)[2] = ecx;
    vendor[12] = '\0';
}

void hardwarefind(){
    get_cpu_vendor(vendor);
    print_string("\nCPU Vendor: ", 0x0e);
}






void write(char *filename ){
    #define FLASH_START 0x90000000
}

//void draw_rect(int x, int y, int width, int height, char *color){
//        unsigned char *location = (unsigned char*)0xA0000 + (y * 320) + x;
//        *location = color;
//        for (int i = 0; i < height; i++) {
//        for (int j = 0; j < width; j++) {
//            location[(y + i) * 320 + (x + j)] = color;
//        }
//    }
//}
void panic(void){
    print_string("\nCrash Trigger Accepted approx~ 0.5 Secs to crash\nExit Code 0", 0xC0);
        for(volatile int i = 0; i < 800000000; i++);
    volatile int *p = (int *)0;
    *p = 0xDEADBEEF; 
        struct {
            unsigned short limit;
            unsigned int base;
        } __attribute__((packed)) idtr = {0, 0};
        
        __asm__ __volatile__ ("lidt %0" : : "m"(idtr));

        volatile int zero = 0;
        volatile int trigger = 10 / zero;

        __asm__ __volatile__ ("cli; hlt");
}

void Shutdown() {
    print_string("H", 0x0F);
    __asm__ __volatile__("cli");
    while(1) {
        __asm__ __volatile__("hlt");
    }
}
