#include "stdio.h"
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;
uint32_t *ACPIADDR;

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



void RSDT_DUMP(){
        struct XSDP_t *rsdp = (struct XSDP_t*)ACPI_reader();
        if (!rsdp) {
            print_string("RSDP not found, fatal boot error", 0x04);
            return;
        }
        ACPIADDR = (void*)rsdp->RsdtAddress;

        if (rsdp->Revision == 0){
            print_char('\n',0x0e);
            print_string("Sig: ",0x0e);
            print_string(rsdp->Signature,0x0e);
            print_char('\n',0x0e);
            print_string("Check: ",0x0e);
            print_int(rsdp->Checksum,0x0e);
            print_char('\n',0x0e);
            print_string("OEM: ",0x0e);
            print_string(rsdp->OEMID,0x0e);
            print_char('\n',0x0e);
            print_string("Rev: ",0x0e);
            print_int(rsdp->Revision,0x0e);
            print_char('\n',0x0e);
            print_string("RSDT ADDR: ",0x0e);
            print_int(rsdp->RsdtAddress,0x0e);
            print_char('\n',0x0e);
            print_string("RSDP 1.0",0x0e);
            print_char('\n',0x0e);
            print_char('\n',0x0e);
            print_string("Warning, possible garbage data!",0x0e);
            print_char('\n',0x0e);
            print_char('\n',0x0e);
            ACPI_DUMP();
        }
        else{        
                print_char('\n',0x0e);
            print_string("Sig: ",0x0e);
            print_string(rsdp->Signature,0x0e);
            print_char('\n',0x0e);
            print_string("Check: ",0x0e);
            print_int(rsdp->Checksum,0x0e);
            print_char('\n',0x0e);
            print_string("OEM: ",0x0e);
            print_string(rsdp->OEMID,0x0e);
            print_char('\n',0x0e);
            print_string("Rev: ",0x0e);
            print_int(rsdp->Revision,0x0e);
            print_char('\n',0x0e);    
            print_int(rsdp->Length,0x0e);
            print_char('\n',0x0e);
            print_string("XSDT ADDR: ",0x0e);
            print_int(rsdp->XsdtAddress,0x0e);
            print_char('\n',0x0e);
            print_string("EXTD CHECK: ",0x0e);
            print_int(rsdp->ExtendedChecksum,0x0e);
            print_char('\n',0x0e);
            print_string("Resv: ",0x0e);
            print_int(rsdp->reserved[0], 0x0e);
            print_int(rsdp->reserved[1], 0x0e);
            print_int(rsdp->reserved[2], 0x0e);
            }

        
}
struct RSDT_t {
    char Sig[4];
    uint32_t Len;
    uint8_t Revision;
    uint8_t Checksum;
    char OEMID[6];
    char OEMTID[8];
    uint32_t OEMRevision;
    uint32_t CreatorID;
    uint32_t CreatorRevision;
    uint32_t Entries[];
} __attribute__((packed));

void ACPI_DUMP(){
    struct XSDP_t *rsdp = (struct XSDP_t*)ACPI_reader();
    ACPIADDR = (void*)rsdp->RsdtAddress;

    char *p = (char*)ACPIADDR;
print_char('\n',0x0e);
print_char(p[0],0x0e);
print_char(p[1],0x0e);
print_char(p[2],0x0e);
print_char(p[3],0x0e);
    struct RSDT_t *rsdt = (struct RSDT_t*)ACPIADDR;
    print_int(rsdt->Len,0x0e);
    int tables = (rsdt->Len - 36) / 4;
    int Entries = rsdt->Entries[tables];
    print_string("\nTable count: ", 0x0);
    print_int(tables,0x0);
    print_string("\nCheck: ", 0x0);
    print_int(rsdt->Checksum,0xe);
    print_string("\nOEMTID: ", 0x0);
    print_string(rsdt->OEMTID,0x0e);
    print_string("\nRevision: ",0x0e);
    print_int(rsdt->OEMRevision,0);
    print_string("\nSig: ", 0x0e);
    uint8_t *s = (uint8_t*)rsdt->Sig;
    for (size_t i = 0; i < 4; i++) {
       print_char(s[i],0x0e);
    }
    print_string("\nEntries: ", 0x0);
    uint8_t *c = (uint8_t*)rsdt->Entries;
    for (size_t i = 0; i < 32; i++) {
       print_int(c[i],0x0e);

}
        
}
