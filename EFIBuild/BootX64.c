#include <uefi.h>
void* Buffer;
#define KERNEL_BSS_SIZE 0x898
efi_status_t status;
efi_guid_t gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
efi_gop_t *gop = NULL;
static void fERR(const char* FileP,size_t* extra);
const char* BinFload(const char* FileP, size_t Fsize);
static void ExecBin();
static int StartK();
typedef void (__attribute__((sysv_abi)) *KernelEntry)(
    uint64_t framebuffer_base,
    uint64_t framebuffer_pitch,
    uint64_t framebuffer_width,
    uint64_t framebuffer_height,
    uint64_t framebuffer_format);

void main(){
    printf("Hello, World?\n\r");
    FILE* kernel_file = fopen("EFI\\BOOT\\kernel.bin", "r");
    if (kernel_file == NULL) {
        fERR("EFI\\BOOT\\kernel.bin", NULL);
    }
    fseek(kernel_file, 0, SEEK_END);
    long kernel_size = ftell(kernel_file);
    fseek(kernel_file, 0, SEEK_SET);
    fclose(kernel_file);
    const char* success = BinFload("EFI\\BOOT\\kernel.bin", (size_t)kernel_size);
    printf(success);
    printf("\n\r");
    status = BS->LocateProtocol(&gop_guid, NULL, (void **)&gop);
    printf("%p",(uintptr_t)gop->Mode->FrameBufferBase);
    printf("\n\r");
    if (success != NULL && strcmp(success, "\n\rFile Loaded\n\r") == 0){
        printf("jumping");
        StartK();
        printf("kernel started");
        printf("Failed");
    }
    while(1);
}
const char* BinFload(const char* FileP, size_t Fsize){
    const char* T = NULL;
    //Open file
    FILE* File = fopen(FileP, "r");
    if (File == NULL) {
        fERR(FileP, NULL);
        return "\n\rFile Not Loaded\n\r";
    }
    //Allocate memory outside POSIX malloc tracking
    status = BS->AllocatePool(EfiLoaderData, Fsize + KERNEL_BSS_SIZE, &Buffer);
    if (EFI_ERROR(status) || Buffer == NULL) {
        fclose(File);
        fERR(FileP, NULL);
        return "\n\rFile Not Loaded\n\r";
    }
    //Read
    size_t BytesRead = fread(Buffer, 1, Fsize, File);
    //error handle
    if (File == NULL)fERR(FileP,(size_t*)File);else printf("\n\rRead Success\n\r");
    if (Buffer == NULL)fERR(FileP,(size_t*)Buffer);else printf("\n\rMalloc Success\n\r");
    if (BytesRead != Fsize)fERR(FileP,&BytesRead);else printf("\n\rLoad Success\n\r");
    if (BytesRead == Fsize && Buffer != NULL && File != NULL){
        T = "\n\rFile Loaded\n\r";
    }
    else
        T="\n\rFile Not Loaded\n\r";
    if (File != NULL) fclose(File);
    memset((unsigned char *)Buffer + Fsize, 0, KERNEL_BSS_SIZE);
    return T;
    }
static void fERR(const char* FileP, size_t* extra){
        printf("Error: Could not open file %s", FileP);
        printf("   %s", extra);
        printf("   %d", errno);
        

}

static int StartK(){
    if (gop == NULL)printf("GOP String Is Null");
    uint64_t pitch = gop->Mode->Information->PixelsPerScanLine;
    uint64_t width = gop->Mode->Information->HorizontalResolution;
    uint64_t height = gop->Mode->Information->VerticalResolution;
    uint64_t format = (uint64_t)gop->Mode->Information->PixelFormat;
    if (exit_bs() != 0) return 0;
    ((KernelEntry)Buffer)(
        (uintptr_t)gop->Mode->FrameBufferBase,
        pitch,
        width,
        height,
        format);
    return 1;
}
static void ExecBin(){

    asm volatile(
        "jmp *%0"
        : 
        : "r" (Buffer)
    );



}