void clear_screen();

void _start(){

    clear_screen();

    while(1){

    }
}

void clear_screen(){
    char* video_memory = (char*) 0xb8000;

    for(int i = 0; i < 2000; i++){
        video_memory[2 * i] = ' ';
        video_memory[2 * i + 1] = 0x0A;
    }
}