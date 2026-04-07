void clear_screen();
static inline void outb(unsigned short port, unsigned char data); 
void set_cursor(int col, int row);

void _start(){

    clear_screen();

    while(1){

    }
}

void print(){

}

void clear_screen(){
    char* video_memory = (char*) 0xb8000;

    for(int i = 0; i < 2000; i++){
        video_memory[2 * i] = ' ';
        video_memory[2 * i + 1] = 0x0F;
    }
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

void set_cursor(int col, int row){

    unsigned short position = (row * 80 + col);

    outb(0x3d4, 0x0f);
    unsigned char low = (unsigned char) (position & 0xff);
    outb(0x3d5, low);

    outb(0x3d4, 0xe);
    unsigned char high = (unsigned char) ((position >> 8) & 0xff);
    outb(0x3d5, high);

}