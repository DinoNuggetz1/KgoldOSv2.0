#include "stdio.h"
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;
char* ACPI_reader(){
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
struct XSDP_t {
 char Signature[8];
 uint8_t Checksum;
 char OEMID[6];
 uint8_t Revision;
 uint32_t RsdtAddress;      // deprecated since version 2.0
 uint32_t Length;
 uint64_t XsdtAddress;
 uint8_t ExtendedChecksum;
 uint8_t reserved[3];
} __attribute__ ((packed));



void ACPI_DUMP(){
        struct XSDP_t *rsdp = (struct XSDP_t*)ACPI_reader();
        print_string("OEMID: ", 0x0E);
        print_char('\n',0x0e);
        print_string(rsdp->Signature,0x0e);
        print_char('\n',0x0e);
        print_int(rsdp->Checksum,0x0e);
        print_char('\n',0x0e);
        print_string(rsdp->OEMID,0x0e);
        print_char('\n',0x0e);
        print_int(rsdp->Revision,0x0e);
        print_char('\n',0x0e);
        print_int(rsdp->RsdtAddress,0x0e);
        print_char('\n',0x0e);
        print_int(rsdp->Length,0x0e);
        print_char('\n',0x0e);
        print_int(rsdp->XsdtAddress,0x0e);
        print_char('\n',0x0e);
        print_int(rsdp->ExtendedChecksum,0x0e);
        print_char('\n',0x0e);
        print_int(rsdp->reserved[0], 0x0e);
        print_int(rsdp->reserved[1], 0x0e);
        print_int(rsdp->reserved[2], 0x0e);

        if (!rsdp) {
            print_string("RSDP not found, fatal boot error", 0x04);
            return;
        }
        
}