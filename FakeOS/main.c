#include <raylib.h>

const int screenWidth = 1000;
const int screenHeight = 1000;

void draw(){
    BeginDrawing();

    ClearBackground(RAYWHITE);

    EndDrawing();
}

int main(void){
    InitWindow(screenWidth, screenHeight, "Raylib Sample Project");
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        draw();
    }
}