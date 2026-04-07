void _start(){
    char* video_memory = (char*) 0xb8000;
    *video_memory = 'N';
    *(video_memory + 1) = 0xAC;

    while(1){

    }

}