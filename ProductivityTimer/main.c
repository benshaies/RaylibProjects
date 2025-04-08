#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#define Min(a,b) ((a) < (b) ? (a) : (b))

int screenWidth = 1920;
int screenHeight = 1080;

float timer = 1500.0f;
int minutes;
int seconds;

int sessions;

bool fullscreen = false;

Texture2D background[48];
Texture2D campfire[7];
int currentFrame = 0;
float timerr = 0.0f;
float campTimer = 0.0f;
int campfireFrame = 0;
bool showStart = true;

bool startTimer = false;

Color deepPurple = (Color){ 45, 20, 50, 255 };
Color buttonColor = (Color){ 120, 75, 50, 255 };
Color hoverColor = (Color){ 150, 95, 65, 255 };
Color textColor   = WHITE;
Color fadeBox = (Color){ 100, 60, 40, 150 };
Color labelZero;
Color labelOne;
Color labelNeg;
Color plainBackground = (Color){ 60, 40, 50, 255 }; // deep indi

Color themeCalm = (Color){ 25, 20, 35, 255 }; // Deep indigo  
Color themeCozy = (Color){ 80, 50, 60, 255 }; // Blush-red dusk  
Color themeFresh = (Color){ 50, 70, 90, 255 }; // Muted teal  
Color themeDreamy = (Color){ 60, 40, 70, 255 }; // Plum purple  
Color themeDark = (Color){ 20, 20, 20, 255 }; // Pure dark gray  

Rectangle calm = {50, 25, 50, 50};
Rectangle cozy = {150, 25, 50, 50};
Rectangle fresh = {250, 25, 50, 50};
Rectangle dreamy = {350, 25, 50, 50};
Rectangle dark = {450, 25, 50, 50};
Rectangle white = {550, 25, 50, 50};

Sound startButtonClick;
Sound tabClick;
Sound timerDone;

bool breakTime = false;
bool displayBackground = true;

Rectangle timerBackground = {765, 230, 400, 150};
Rectangle startButton = {960 - 95, 400, 200, 75};
Rectangle labelPomodoro = {905, 175, 125, 40};
Rectangle labelShortBreak = {770, 175, 125, 40};
Rectangle labelLongBreak = {1040, 175, 125, 40};

int selectedTab = 0;

bool isClicked(Rectangle rec){
    bool hovering = CheckCollisionPointRec(GetMousePosition(), rec);
    if(hovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        return true;
    }
    else{
        return false;
    }
}

void controlUI(){
    if(isClicked(labelPomodoro)){
        PlaySound(tabClick);
        startTimer = false;
        showStart = true;
        selectedTab = 0;
        timer = 1500.0f;
    }
    else if(isClicked(labelShortBreak)){
        PlaySound(tabClick);
        startTimer = false;
        showStart = true;
        selectedTab = -1;
        timer = 300.0f;
    }
    else if(isClicked(labelLongBreak)){
        PlaySound(tabClick);
        startTimer = false;
        showStart = true;
        selectedTab = 1;
        timer = 900.0f;
    }

    if(isClicked(startButton)){
        PlaySound(startButtonClick);
        if(!startTimer){
            startTimer = true;
            showStart = false;
        }
        else{
            startTimer = false;
            showStart = true;
        }
    }

    if(timer <= 0){
        PlaySound(timerDone);
        if(selectedTab == 0 && sessions < 4){
            sessions++;
            selectedTab = -1;
            startTimer = false;
            showStart = true;
            selectedTab = -1;
            timer = 300.0f;
        }
        else if(selectedTab == 0 && sessions >= 4){
            sessions = 0;
            selectedTab = 1;
            startTimer = false;
            showStart = true;
            selectedTab = 1;
            timer = 900.0f;
        }
        else if(selectedTab == -1 || selectedTab == 1){
            selectedTab = 0;
            showStart = true;
            startTimer = false;
            timer = 1500.0f;
        }
    }

}

void drawBackground(){

    timerr += GetFrameTime();
    if(timerr >= 0.033){
        currentFrame++;
        timerr = 0;
        if(currentFrame >= 48){
            currentFrame = 1;
        }
    }

    DrawTexturePro(background[currentFrame], (Rectangle){0,0,1920, 1080}, (Rectangle){0,0, 1920, 1080}, (Vector2){0,0}, 0.0f, WHITE);
    
}

bool hovered(Rectangle button){
    bool hovered = CheckCollisionPointRec(GetMousePosition(), button);
    
    return hovered;
}

void drawUI(){
    if(selectedTab == 0){
        labelZero = WHITE;
    }
    else{
        labelZero = (Color){ 200, 180, 160, 255 };
    }

    if(selectedTab == -1){
        labelNeg = WHITE;
    }
    else{
        labelNeg = (Color){ 200, 180, 160, 255 };
    }

    if(selectedTab == 1){
        labelOne = WHITE;
    }
    else{
        labelOne = (Color){ 200, 180, 160, 255 };
    }


    startButton.x = screenWidth/2 - 95;
    labelPomodoro.x = screenWidth/2 - 55;
    labelShortBreak.x =  screenWidth/2 - 190;
    labelLongBreak.x = screenWidth/2 + 80;

    DrawRectangleRec(startButton, hovered(startButton) ? hoverColor : buttonColor);
    DrawRectangleLinesEx(startButton, 2.5f, WHITE);

    if(showStart){
        DrawText("START", startButton.x + 22.5, startButton.y + 17.5, 45, WHITE);
    }else{
        DrawText("PAUSE", startButton.x + 22.5, startButton.y + 17.5, 45, WHITE);
    }
    

    DrawRectangleRec(labelPomodoro, hovered(labelPomodoro) ? hoverColor : buttonColor);
    DrawText("Pomodoro", labelPomodoro.x+5, labelPomodoro.y+7.5, 25, labelZero);
    DrawRectangleLinesEx(labelPomodoro, 1.5f, WHITE);

    DrawRectangleRec(labelShortBreak, hovered(labelShortBreak) ? hoverColor : buttonColor);
    DrawText("Short Break", labelShortBreak.x+10, labelShortBreak.y+12.5, 18, labelNeg);
    DrawRectangleLinesEx(labelShortBreak, 1.5f, WHITE);

    DrawRectangleRec(labelLongBreak, hovered(labelLongBreak) ? hoverColor : buttonColor);
    DrawText("Long Break", labelLongBreak.x+5, labelLongBreak.y+10, 20, labelOne);
    DrawRectangleLinesEx(labelLongBreak, 1.5f, WHITE);

}

void drawCampfire(){
    campTimer += GetFrameTime();
    if(campTimer >= 0.1){
        campfireFrame++;
        campTimer = 0;
        if(campfireFrame >= 6){
            campfireFrame = 0;
        }
    }

    DrawTexturePro(campfire[campfireFrame], (Rectangle){0,0, 1080, 852}, (Rectangle){screenWidth/2 - 200, 550, 400, 400}, (Vector2){0,0}, 0.0f, WHITE);
}

void draw(){
    BeginDrawing();

    ClearBackground(plainBackground);

    if(displayBackground){
        drawBackground();
    }
    else{
        drawCampfire();

        DrawRectangleRec(calm, themeCalm);
        DrawRectangleRec(cozy, themeCozy);
        DrawRectangleRec(fresh, themeFresh);
        DrawRectangleRec(dreamy, themeDreamy);
        DrawRectangleRec(dark, themeDark);
        DrawRectangleRec(white, WHITE);

    }
    

    timerBackground.x = screenWidth/2 - 195;
    DrawRectangleRec(timerBackground, Fade(fadeBox, 0.75f));
    DrawText(TextFormat("%02d:%02d", minutes, seconds), screenWidth/2 - 150, 250, 125, WHITE);

    drawUI();

    if(breakTime){
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.10f));
    }

    EndDrawing();
}

int main(void){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Pomodoro Timer");
    SetTargetFPS(60);

    for(int i = 0; i < 48; i++){
        char filename[64];
        sprintf(filename, "../assets/frame_%02d.png", i + 1);
        background[i] = LoadTexture(filename);
    }

    for(int i = 0; i < 7; i++){
        char filename[64];
        sprintf(filename, "../campfire/frame_%d.png", i);
        campfire[i] = LoadTexture(filename);
    }

    InitAudioDevice();
    startButtonClick = LoadSound("../assets/click.mp3");
    tabClick = LoadSound("../assets/tabClick.wav");
    timerDone = LoadSound("../assets/timerDone.mp3");

    while(!WindowShouldClose()){
        minutes = timer/60;
        seconds = timer - (minutes*60);

        
        controlUI();

        if(!displayBackground){
            if(isClicked(calm)){
                plainBackground = themeCalm;
            }
            else if(isClicked(cozy)){
                plainBackground = themeCozy;
            }
            else if(isClicked(fresh)){
                plainBackground = themeFresh;
            }
            else if(isClicked(dreamy)){
                plainBackground = themeDreamy;
            }
            else if(isClicked(dark)){
                plainBackground = themeDark;
            }
            else if(isClicked(white)){
                plainBackground = WHITE;
            }
        }

        if(startTimer){
            timer -= GetFrameTime();
            if(selectedTab == -1 || selectedTab == 1){
                breakTime = true;
            }
            else{
                breakTime = false;
            }
        }

        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();

        if (GetScreenWidth() > 1920 || GetScreenHeight() > 1080) {
            SetWindowSize(Min(GetScreenWidth(), 1920), Min(GetScreenHeight(), 1080));
        }

        if(IsKeyPressed(KEY_TAB)){
            if(displayBackground){
                displayBackground = false;
            }
            else{
                displayBackground = true;
            }
        }


        if(IsKeyPressed(KEY_ENTER)){
            if(!fullscreen){
                SetWindowState(FLAG_WINDOW_UNDECORATED);
                fullscreen = true;
            }
            else{
                ClearWindowState(FLAG_WINDOW_UNDECORATED);
                fullscreen = false;
            }
        }

        draw();
    }
    UnloadSound(startButtonClick);
    UnloadSound(tabClick);
    UnloadSound(timerDone);
    CloseAudioDevice();
}
