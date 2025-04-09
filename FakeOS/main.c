#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "stdlib.h"
#include "time.h"

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

//Login Screen variables
float fadeLevel1 = 1.0f;
char password[64];
bool typing = false;
int currentUser = 0;
Texture2D loginBackground;
Texture2D user[3];
Texture2D currentUserText;
bool userMenu = false;
bool fadeOut = false;

//Main Screen Variables
float fadeLevel2 = 1.0f;
Color taskBarColor = (Color){30, 30, 30, 220};
Color textColor = (Color){230, 230, 230, 255};
Texture2D wifi;
Texture2D volumeText[4];
int i = 3;
float volume = 100;

//Cursor Variables
Texture2D cursorTexture;

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
    if(fadeLevel1 > 0.05f){
        fadeLevel1 -= 0.005f;
    }

    DrawTexturePro(loginBackground, (Rectangle){0,0,4096, 2304}, (Rectangle){0,0,1280,720}, (Vector2){0,0}, 0.0f,  WHITE);
    DrawRectangle(0,0, 1280, 720, Fade(BLACK, 0.25f));

    DrawTexturePro(currentUserText, (Rectangle){0,0, 512, 512}, (Rectangle){565, 150, 150, 150}, (Vector2){0,0}, 0.0f, (WHITE));
    DrawText("Welcome to KS-OS", 450, 50, 40, BLACK);

    GuiSetStyle(TEXTBOX, BORDER_COLOR_NORMAL, ColorToInt(BLACK));

    if(GuiTextBox((Rectangle){500, 350, 280, 40}, password, 32, typing)){
        typing = !typing;

        if(IsKeyPressed(KEY_ENTER)){
            if(strcmp(password, "password") == 0){
                fadeOut = true;
            }
        }
    }

    if(currentUser == 0){
        currentUserText = user[0];
        DrawText("User 1", 600, 315, 25, WHITE);
    }
    else if(currentUser == 1){
        currentUserText = user[1];
        DrawText("User 2", 600, 315, 25, BLACK);
    }
    else if(currentUser == 2){
        currentUserText = user[2];
        DrawText("User 3", 600, 315, 25, BLUE);
    }


    //Button Cusomtamization Code
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(Fade(WHITE, 0.1f)));
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(BLACK));
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt(Fade(BLACK, 0.25f)));
    GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(WHITE));
    GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, ColorToInt(WHITE));

    if(userMenu){
        DrawRectangleLines(1000, 500, 250, 250, BLACK);
        DrawRectangle(1000, 500, 250, 250, Fade(BLACK, 0.5f));
        DrawRectangle(1001, 501, 249, 20, Fade(RAYWHITE, 0.5f));
        DrawLine(1001, 521,1250, 521, BLACK);
        if(GuiButton((Rectangle){1225, 503, 15, 15}, "X")){
            userMenu = false;
        }

        if(currentUser == 0){
            DrawTexturePro(user[1], (Rectangle){0,0, 512, 512}, (Rectangle){1025, 550, 50, 50}, (Vector2){0,0}, 0.0f, WHITE);
            DrawTexturePro(user[2], (Rectangle){0,0, 512, 512}, (Rectangle){1025, 650, 50, 50}, (Vector2){0,0}, 0.0f, WHITE);

            if(GuiButton((Rectangle){1100, 550, 100, 50}, "User 2")){
                currentUser = 1;
                userMenu = false;
            }
            if(GuiButton((Rectangle){1100, 650, 100, 50}, "User 3")){
                currentUser = 2;
                userMenu = false;
            }
        }
        else if(currentUser == 1){
            DrawTexturePro(user[0], (Rectangle){0,0, 512, 512}, (Rectangle){1025, 550, 50, 50}, (Vector2){0,0}, 0.0f, WHITE);
            DrawTexturePro(user[2], (Rectangle){0,0, 512, 512}, (Rectangle){1025, 650, 50, 50}, (Vector2){0,0}, 0.0f, WHITE);

            if(GuiButton((Rectangle){1100, 550, 100, 50}, "User 1")){
                currentUser = 0;
                userMenu = false;
            }
            if(GuiButton((Rectangle){1100, 650, 100, 50}, "User 3")){
                currentUser = 2;
                userMenu = false;
            }
        }
        else if(currentUser == 2){
            DrawTexturePro(user[0], (Rectangle){0,0, 512, 512}, (Rectangle){1025, 550, 50, 50}, (Vector2){0,0}, 0.0f, WHITE);
            DrawTexturePro(user[1], (Rectangle){0,0, 512, 512}, (Rectangle){1025, 650, 50, 50}, (Vector2){0,0}, 0.0f, WHITE);

            if(GuiButton((Rectangle){1100, 550, 100, 50}, "User 1")){
                currentUser = 0;
                userMenu = false;
            }
            if(GuiButton((Rectangle){1100, 650, 100, 50}, "User 2")){
                currentUser = 1;
                userMenu = false;
            }
        }


    }
    else{
        if(GuiButton((Rectangle){1050, 625, 125, 60}, "Change User")){
            userMenu = true;
        }
    }

    if(fadeOut){
        if(fadeLevel1 < 1.0f){
            fadeLevel1 += 0.05f;
        }
        else{
            currentScene++;
        }
        DrawRectangle(0,0, 1280, 720, Fade(BLACK, fadeLevel1));
    }
    DrawRectangle(0,0, 1280, 720, Fade(BLACK, fadeLevel1));



}

bool isHovered(Rectangle rect){
    bool hovered = false;
    if(CheckCollisionPointRec(GetMousePosition(), rect)){
        hovered = true;
    }

    return hovered;
}

void drawMainScreen(){
    if(fadeLevel2 > 0.05f){
        fadeLevel2 -= 0.05;
    }

    //Time variables
    time_t raw = time(NULL);
    struct tm *t = localtime(&raw);
    char timeStr[6];
    strftime(timeStr, sizeof(timeStr), "%I:%M %p", t);

    DrawTexturePro(loginBackground, (Rectangle){0,0,4096, 2304}, (Rectangle){0,0,1280,720}, (Vector2){0,0}, 0.0f,  WHITE);
    DrawRectangle(0, 670, 1280, 50, taskBarColor);
    DrawLineEx((Vector2){0, 670}, (Vector2){1280, 670}, 2.0f, BLACK);

    //Task bar drawing
    DrawText(timeStr, 1200, 685, 20, textColor);

    Rectangle wifiRect = (Rectangle){1140, 675, 40, 40};
    DrawTexturePro(wifi,(Rectangle){0,0, 64, 64}, (Rectangle){1150, 685, 20, 20}, (Vector2){0,0}, 0.0f, WHITE);
    DrawRectangleRec(wifiRect, isHovered(wifiRect) ? Fade(BLUE,0.1f):Fade(WHITE,0.0f));

    DrawTexturePro(volumeText[i],(Rectangle){0,0, 50, 50}, (Rectangle){1100, 685, 20, 20}, (Vector2){0,0}, 0.0f, WHITE);
    DrawRectangle(1090, 675, 40, 40, isHovered((Rectangle){1090, 675, 40, 40}) ? Fade(BLUE,0.1f):Fade(WHITE,0.0f));







    DrawRectangle(0,0, 1280, 720, Fade(BLACK, fadeLevel2));

}

void drawCursor(){
    Vector2 mousePos = GetMousePosition();
    DrawTexturePro(cursorTexture, (Rectangle){0,0, 320, 320}, (Rectangle){mousePos.x, mousePos.y, 50, 50}, (Vector2){14,6}, 0.0f, WHITE);
}

void draw(){

    BeginDrawing();


    if(currentScene == 0){
        drawLoadingScreen();
    }
    else if(currentScene == 1){
        drawLoginScreen();
        drawCursor();
        
    }
    else if(currentScene == 2){
        drawMainScreen();
        drawCursor();
        

    }

    EndDrawing();
}

void init(){
    InitWindow(screenWidth, screenHeight, "KS-OS");
    SetTargetFPS(60);

    //Textures
    logo = LoadTexture("../assets/logo.png");
    user[0] = LoadTexture("../assets/user.png");
    user[1] = LoadTexture("../assets/user2.png");
    user[2] = LoadTexture("../assets/user3.png");
    cursorTexture = LoadTexture("../assets/cursor.png");
    loginBackground = LoadTexture("../assets/loginBackground.jpg");
    wifi = LoadTexture("../assets/wifi.png");
    volumeText[0] = LoadTexture("../assets/volumeMute.png");
    volumeText[1] = LoadTexture("../assets/volumeLow.png");
    volumeText[2] = LoadTexture("../assets/volumeMid.png");
    volumeText[3] = LoadTexture("../assets/volumeMax.png");

    //HideCursor();
}



int main(void){

    //Call init function
    init();

    while(!WindowShouldClose()){
        draw();
    }
}