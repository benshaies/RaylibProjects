#include <raylib.h>
#include "raygui.h"

const int screenWidth = 1280;
const int screenHeight = 720;

//Loading Screen Variables
Texture2D logo;
Rectangle loadingBar = {440, 335, 400, 50};
Rectangle loadingBarFilling = {442, 338, 5, 45};
float loadingScreenTime = 0;
float fadeLevel = 1.0f;

//Current Scene
int currentScene = 0;
Texture2D user;

//Login Screen variables
float fadeLevel1 = 0.005f;


void drawLoadingScreen(){

    ClearBackground(Fade(BLACK, fadeLevel));

    DrawTexturePro(logo, (Rectangle){0,0, 1024,1024}, (Rectangle){465, 0, 350, 350}, (Vector2){0,0}, 0.0f, Fade(WHITE, fadeLevel));

    DrawText("Loading...", 445, 290, 35, Fade(WHITE, fadeLevel));
    DrawRectangleRec(loadingBarFilling, Fade(WHITE, fadeLevel));
    DrawRectangleLinesEx(loadingBar, 1.5f, Fade(WHITE, fadeLevel));

    loadingScreenTime += GetFrameTime();

    if(loadingScreenTime > 0.1f){
        loadingBarFilling.width += 5.0f;
        loadingScreenTime = 0;
    }

    if(loadingBarFilling.width >= 398){
        loadingBarFilling.width = 398;
        fadeLevel -= 0.005f;

        if(fadeLevel <= 0.05f){
            currentScene = 1;
        }
    }
}

void drawLoginScreen(){
    if(fadeLevel1 < 1.0f){
        fadeLevel1 += 0.005f;
    }

    DrawRectangle(0,0, 1280, 720, Fade((Color){200, 220, 240, 255}, fadeLevel1));

    DrawTexturePro(user, (Rectangle){0,0, 512, 512}, (Rectangle){565, 150, 150, 150}, (Vector2){0,0}, 0.0f, Fade(WHITE, fadeLevel1));

}


void draw(){
    BeginDrawing();

    if(currentScene == 0){
        drawLoadingScreen();
    }
    else if(currentScene == 1){
        drawLoginScreen();
    }

    EndDrawing();
}

void init(){
    InitWindow(screenWidth, screenHeight, "KS-OS");
    SetTargetFPS(60);

    //Textures
    logo = LoadTexture("../assets/logo.png");
    user = LoadTexture("../assets/user.png");
}



int main(void){

    //Call init function
    init();

    while(!WindowShouldClose()){
        draw();
    }
}