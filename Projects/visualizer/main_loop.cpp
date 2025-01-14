#include <raylib.h>
#include "main_loop.h"


void main_loop(){
        while(!WindowShouldClose()){
                BeginDrawing();
                ClearBackground(RED);
                EndDrawing();
        }
}
