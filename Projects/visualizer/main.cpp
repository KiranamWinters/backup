#include <stdio.h>
#include <raylib.h>
#include "main_loop.h"

#define SCREEN_WIDTH 1900
#define SCREEN_HEIGHT 1200
#define SCREEN_TITLE "VISUALIZER"

int main(){
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
        
        main_loop();

        CloseWindow();
        return 0;
}
