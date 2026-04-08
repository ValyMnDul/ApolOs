static inline void outb(unsigned short port, unsigned char data);
void clear_screen();
void set_cursor(int col, int row);
unsigned int strlen(char* string);
void print(char* string);

void _start(){

    clear_screen();
    print("Welcome to ApolOS\n");
    print("Track all Nasa missions!\n");
    print("Are you ready? (y/n): \n");
    print("\n");

    char lenght = 48 + strlen("test str");
    print(&lenght);

    while(1){

    }
}

unsigned int strlen(char* string){
    unsigned int len = 0;
    for(int i = 0; string[i] != '\0'; i++){
        len++;
    }
    return len;
}

unsigned short cursor_current_row = 0;
unsigned short cursor_current_col = 0;

void print(char* string){
    char* video_memory = (char*) 0xb8000;

    for(unsigned long long i = 0; string[i] != '\0'; i++){
        if(string[i] == '\n'){
            cursor_current_col = 0;
            cursor_current_row++;
        }
        else{
            int distance = (cursor_current_row * 80 + cursor_current_col) * 2;
            
            video_memory[distance] = string[i];
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
    }

    set_cursor(cursor_current_row, cursor_current_col);
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