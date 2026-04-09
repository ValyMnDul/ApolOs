// DECLARE

static inline void outb(unsigned short port, unsigned char data);
void set_cursor(int col, int row);
unsigned int strlen(char* string);
void clear_screen();
void printChar(char chr);
void printf(char* format, ...);

// START

void _start(){

    clear_screen();
    printf("Welcome to ApolOS\n");
    printf("Track all Nasa missions!\n");
    printf("Are you ready? (y/n): \n");
    printf("\n");

    printf("Decimal: %d\nCharacter: %c\nString: %s\nModulo: %%\n", 10, '*', "test");

    while(1){

    }
}

// GLOBALS

char* video_memory = (char*) 0xb8000;

unsigned short cursor_current_row = 0;
unsigned short cursor_current_col = 0;

// FUNC

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

void clear_screen(){

    char* video_memory = (char*) 0xb8000;

    for(int i = 0; i < 2000; i++){
        video_memory[2 * i] = ' ';
        video_memory[2 * i + 1] = 0x0F;
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
    else{
        int distance = (cursor_current_row * 80 + cursor_current_col) * 2;
        
        video_memory[distance] = chr;
        video_memory[distance + 1] = 0x0F;

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
            video_memory[(1920 + c) * 2 + 1] = 0x0F;
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
            else if(format[i] = '%'){
                printChar('%');
            }
        }
    }
}