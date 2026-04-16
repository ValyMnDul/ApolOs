// DECLARE

#define MaxCommandLen 128

static inline unsigned char inb(unsigned short port);
static inline void outb(unsigned short port, unsigned char data);
void set_cursor(int col, int row);
unsigned int strlen(char* string);
int strcmp(const char* str1, const char* str2);
void clear_screen();
void printChar(char chr);
void printf(char* format, ...);
void idtSetGate(int nr, unsigned int adr);
void initPic();
void idtInstall();
struct interrupt_frame; __attribute__((interrupt)) void keyboard_handler(struct interrupt_frame* frame);
void appendToBuffer(char c);
void clearBuffer();
void executeCommand(char* command);
int hexToInt(char* hex);

// START

void _start(){

    clear_screen();
    idtInstall();
    printf("Welcome to ApolOS\n");
    printf("Track all Nasa missions!\n");
    printf("Are you ready? (y/n): \n");
    printf("\n");

    printf("> ");


    while(1){

    }
}

// GLOBALS

unsigned short cursor_current_row = 0;
unsigned short cursor_current_col = 0;

char keyboardBuffer[MaxCommandLen];
short keyboardBufferIndex = 0;

unsigned char currentColor = 0x0F;

// STRUCTS

struct interrupt_frame;
__attribute__((interrupt)) void keyboard_handler(struct interrupt_frame* frame);

struct idt_entry{
    unsigned short offset_low;
    unsigned short selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short offset_high;
} __attribute__ ((packed));

struct idt_ptr{
    unsigned short limit;
    unsigned int base;
} __attribute__ ((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

// FUNC

static inline unsigned char inb(unsigned short port) {
    unsigned char rezultat;
    __asm__ volatile("inb %1, %0" : "=a"(rezultat) : "Nd"(port));
    return rezultat;
}

static inline void outb(unsigned short port, unsigned char data){
    __asm__ volatile(
        "outb %0, %1"
        :
        : "a"(data),
        "Nd"(port)
    );
}

void set_cursor(int row, int col){

    unsigned short position = (row * 80 + col);

    outb(0x3d4, 0x0f);
    unsigned char low = (unsigned char) (position & 0xff);
    outb(0x3d5, low);

    outb(0x3d4, 0xe);
    unsigned char high = (unsigned char) ((position >> 8) & 0xff);
    outb(0x3d5, high);

}

unsigned int strlen(char* string){
    unsigned int len = 0;
    for(int i = 0; string[i] != '\0'; i++){
        len++;
    }
    return len;
}

int strcmp(const char* str1, const char* str2){
    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0'){
        if(str1[i] != str2[i]){
            return str1[i] - str2[i];
        }

        i++;
    }
    return (str1[i] - str2[i]);
}

void clear_screen(){
    currentColor = 0x0F;

    char* video_memory = (char*) 0xb8000;

    for(int i = 0; i < 2000; i++){
        video_memory[2 * i] = ' ';
        video_memory[2 * i + 1] = currentColor;
    }
    cursor_current_col = 0;
    cursor_current_row = 0;
    set_cursor(0, 0);
}

void printChar(char chr){
    
    char* video_memory = (char*) 0xb8000;

    if(chr == '\n'){
        cursor_current_col = 0;
        cursor_current_row++;
    }
    else if(chr == '\b'){
        if(cursor_current_col > 0){
            cursor_current_col--;
        }
        else if(cursor_current_row > 0){
            cursor_current_row--;
            cursor_current_col = 79;
        }
        int distance = (cursor_current_row * 80 + cursor_current_col) * 2;
        video_memory[distance] = ' ';
        video_memory[distance + 1] = currentColor;  
    }
    else{
        int distance = (cursor_current_row * 80 + cursor_current_col) * 2;
        
        video_memory[distance] = chr;
        video_memory[distance + 1] = currentColor;

        cursor_current_col++;
    }

    if(cursor_current_col >= 80){
        cursor_current_row++;
        cursor_current_col = 0;
    }

    if(cursor_current_row >= 25){
        cursor_current_row = 24;

        for(short r = 0; r <= 23; r++){
            for(short c = 0; c <= 79; c++){
                video_memory[(r * 80 + c) * 2] = video_memory[((r + 1) * 80 + c) * 2];
                video_memory[(r * 80 + c) * 2 + 1] = video_memory[((r + 1) * 80 + c) * 2 + 1];
            }
        }
        for(short c = 0; c <= 79; c++){
            video_memory[(1920 + c) * 2] = ' ';
            video_memory[(1920 + c) * 2 + 1] = currentColor;
        }
    }
    set_cursor(cursor_current_row, cursor_current_col);
}

void printf(char* format, ...){
    
    int* argPtr = (int*)&format + 1;

    for(int i = 0; format[i] != '\0'; i++){
        if(format[i] != '%'){
            printChar(format[i]);
        }
        else {
            i++;

            if(format[i] == 'd'){
                int num = *argPtr;
                argPtr++;
                
                if(num == 0){
                    printChar('0');
                }
                else {
                    if(num < 0){
                        printChar('-');
                        num = num * (-1);
                    }

                    char buffer[16];
                    int j = 0;
                    while(num != 0){
                        short rest = num % 10;
                        buffer[j] = 48 + rest;
                        num = num / 10;
                        j++;
                    }

                    for(int k = j - 1; k >= 0; k--){
                        printChar(buffer[k]);
                    }
                }

            }
            else if(format[i] == 's'){
                char* str = (char*) *argPtr;
                argPtr++;

                for(int j = 0; str[j] != '\0'; j++){
                    printChar(str[j]);
                }
            } 
            else if(format[i] == 'c'){
                printChar((char)(*argPtr));
                argPtr++;
            }
            else if(format[i] == 'x'){
                unsigned int num = (unsigned int) *argPtr;
                argPtr++;

                if(num == 0){
                    printChar('0');
                }
                else {
                    char buffer[16];
                    int j = 0;

                    while(num != 0){
                        unsigned int rest = num % 16;
                        if(rest <= 9){
                            buffer[j] = 48 + rest;
                        }
                        else{
                            buffer[j] = (rest - 10) + 'A';
                        }

                        num = num /16;
                        j++;
                    }

                    for(int k = j - 1; k >= 0; k--){
                        printChar(buffer[k]);
                    }
                }
            }
            else if(format[i] == '%'){
                printChar('%');
            }
        }
    }
}

void idtSetGate(int nr, unsigned int adr){
    idt[nr].offset_low = adr & 0xFFFF;
    idt[nr].selector = 0x08;
    idt[nr].zero = 0;
    idt[nr].type_attr = 0x8E;
    idt[nr].offset_high = (adr >> 16) & 0xFFFF;
}

void initPic(){
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    outb(0x21, 0x20);
    outb(0xA1, 0x28);

    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    outb(0x21, 0x0);
    outb(0xA1, 0x0);
    outb(0x21, 0xFD);
    outb(0xA1, 0xFF);
}

void idtInstall(){
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base = (unsigned int) &idt;

    for (int i = 0; i < 256; i++) {
        idtSetGate(i, 0);
    }

    idtSetGate(33, (unsigned int) keyboard_handler);

    initPic();

    __asm__ volatile("lidt %0" : : "m" (idtp));
    __asm__ volatile("sti");
}

__attribute__((interrupt)) void keyboard_handler(struct interrupt_frame* frame){

    unsigned char QWERTY[128] = {
        0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
        '-', '=', '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u',
        'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's', 'd', 'f', 'g',
        'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c',
        'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0
    };

    unsigned char scancode = inb(0x60);
    
    if(scancode < 128 && QWERTY[scancode] != 0){
        unsigned char c = QWERTY[scancode];

        if(c == '\n'){
            printf("\n");
            executeCommand(keyboardBuffer);
            clearBuffer();
            printf("> ");
        }
        else if(c == '\b'){
            if(keyboardBufferIndex > 0){
                keyboardBuffer[--keyboardBufferIndex] = '\0';
                printf("\b");
            }
        } else {
            appendToBuffer(c);
            printf("%c", c);
        }
    }
    
    outb(0x20, 0x20);
}

void appendToBuffer(char c){
    if(keyboardBufferIndex < MaxCommandLen - 1){
        keyboardBuffer[keyboardBufferIndex++] = c;
        keyboardBuffer[keyboardBufferIndex] = '\0';
    }
}

void clearBuffer(){
    keyboardBufferIndex = 0;
    keyboardBuffer[0] = '\0';
}

int hexToInt(char* hex){
    int val = 0;
    int i = 0;

    if(hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X')){
        i = 2;
    }

    while(hex[i] != '\0' && hex[i] != ' '){
        char byte = hex[i];

        if(byte >= '0' && byte <= '9') byte = byte - '0';
        else if (byte >= 'a' && byte <= 'f') byte = byte - 'a' + 10;
        else if (byte >= 'A' && byte <= 'F') byte = byte - 'A' + 10;
        else return -1;

        val = (val << 4) | (byte & 0xF);
        i++;
    }
    return val;
}

void executeCommand(char* command){
    if(command[0] == '\0'){
        return;
    }

    int i = 0;
    while (command[i] != ' ' && command[i] != '\0'){
        i++;
    }

    char* args = 0x0;
    
    if(command[i] == ' '){
        command[i] = '\0';
        args = &command[i + 1];

        while (*args == ' '){
            args++;
        }
    }

    if(strcmp(command, "help") == 0){
        printf("Available commands:\n");
        printf("  clear - Clears the screen\n");    
        printf("  help  - Shows this message\n");
        printf("  info  - Shows OS information\n");
        printf("  whoami - Shows the current user\n");
        printf("  echo [text] - Prints the provided text\n");
        printf("  color [hex_code] - Changes text color (e.g., color 0x1E)\n"); 
    }
    else if(strcmp(command, "clear") == 0){
        clear_screen();
    }
    else if(strcmp(command, "info") ==0 ){
        printf("ApolOS v0.1\n");
    }
    else if(strcmp(command, "whoami") == 0){
        printf("root\n");
    }
    else if(strcmp(command, "echo") == 0){
        if(args != 0x0){
            printf("%s\n", args);
        }
        else{
            printf("\n");
        }
    }
    else if(strcmp(command, "color") == 0){
        if(args != 0 && args[0] != '\0'){
            int newColor = hexToInt(args);
            if(newColor >= 0 && newColor <= 0xFF){
                currentColor = (unsigned char) newColor;
            }
            else {
                printf("Invalid hex color code.\n");
            }
        } 
        else {
            printf("Usage: color [hex_code]\n");
            printf("Format: 0xBG (B=Background, G=Foreground)\n");
            printf("---------------------------------------\n");
            printf(" 0 - Black     8 - Dark Gray\n");
            printf(" 1 - Blue      9 - Light Blue\n");
            printf(" 2 - Green     A - Light Green\n");
            printf(" 3 - Cyan      B - Light Cyan\n");
            printf(" 4 - Red       C - Light Red\n");
            printf(" 5 - Magenta   D - Light Magenta\n");
            printf(" 6 - Brown     E - Yellow\n");
            printf(" 7 - L. Gray   F - White\n");
            printf("---------------------------------------\n");
            printf("Example: color 0x0A (Green text on Black bg)\n");
            printf("         color 0x4F (White text on Red bg)\n");
        }
    }
    else{
        printf("Unknown command: %s\n", command);

    }
}