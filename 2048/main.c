#include "raylib.h"
#include <string.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

const int screenWidth = 750;
const int screenHeight = 850;

Color titleColor = (Color){ 237, 194, 46, 255 };
Rectangle titleRec = {250, 10, 250, 75};

Rectangle boards = {25, 115, 700, 700};

Color Background = (Color){ 250, 248, 239, 255 };
Color tileEmpty = (Color){ 205, 193, 180, 255 };  // Empty tiles
Color boardBackground = (Color){ 168, 156, 145, 255 };  // Board base + lines

Color tile2    = { 0xEE, 0xE4, 0xDA, 0xFF }; // #EEE4DA
Color text2    = { 0x77, 0x6E, 0x65, 0xFF }; // #776E65

Color tile4    = { 0xED, 0xE0, 0xC8, 0xFF }; // #EDE0C8
Color text4    = { 0x77, 0x6E, 0x65, 0xFF }; // #776E65

Color tile8    = { 0xF2, 0xB1, 0x79, 0xFF }; // #F2B179
Color text8    = { 0xF9, 0xF6, 0xF2, 0xFF }; // #F9F6F2

Color tile16   = { 0xF5, 0x95, 0x63, 0xFF }; // #F59563
Color text16   = { 0xF9, 0xF6, 0xF2, 0xFF }; // #F9F6F2

Color tile32   = { 0xF6, 0x7C, 0x5F, 0xFF }; // #F67C5F
Color text32   = { 0xF9, 0xF6, 0xF2, 0xFF }; // #F9F6F2

Color tile64   = { 0xF6, 0x5E, 0x3B, 0xFF }; // #F65E3B
Color text64   = { 0xF9, 0xF6, 0xF2, 0xFF }; // #F9F6F2

Color tile128  = { 0xED, 0xCF, 0x72, 0xFF }; // #EDCF72
Color text128  = { 0xF9, 0xF6, 0xF2, 0xFF }; // #F9F6F2

Color tile256  = { 0xED, 0xCC, 0x61, 0xFF }; // #EDCC61
Color text256  = { 0xF9, 0xF6, 0xF2, 0xFF }; // #F9F6F2

Color tile512  = { 0xED, 0xC8, 0x50, 0xFF }; // #EDC850
Color text512  = { 0xF9, 0xF6, 0xF2, 0xFF }; // #F9F6F2

Color tile1024 = { 0xED, 0xC5, 0x3F, 0xFF }; // #EDC53F
Color text1024 = { 0xF9, 0xF6, 0xF2, 0xFF }; // #F9F6F2

Color tile2048 = { 0xED, 0xC2, 0x2E, 0xFF }; // #EDC22E
Color text2048 = { 0xF9, 0xF6, 0xF2, 0xFF }; // #F9F6F2

int board [4][4] = {
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
};

bool changed = false;

int maxMovesRight(int i, int j);
int maxMovesLeft(int i, int j);
int maxMovesUp(int i, int j);
int maxMovesDown(int i, int j);


// Row 0
Rectangle tileRects[4][4] = {
    {
        // Top-left tile: (25..195) wide => 170px
        { 25, 115, 170, 170 },
        // Top-inner tiles: (205..370) & (380..545) => 165px each
        { 205, 115, 165, 170 },
        { 380, 115, 165, 170 },
        // Top-right tile: (555..725) => 170px
        { 555, 115, 170, 170 }
    },
    // Row 1
    {
        { 25, 295, 170, 165 },
        { 205, 295, 165, 165 },
        { 380, 295, 165, 165 },
        { 555, 295, 170, 165 }
    },
    // Row 2
    {
        { 25, 470, 170, 165 },
        { 205, 470, 165, 165 },
        { 380, 470, 165, 165 },
        { 555, 470, 170, 165 }
    },
    // Row 3
    {
        { 25, 645, 170, 170 },
        { 205, 645, 165, 170 },
        { 380, 645, 165, 170 },
        { 555, 645, 170, 170 }
    }
};

int random1, random2;
int gameState = 0;
bool merged[4][4] = { false };
int prevBoard[4][4];

void generateRandomTile(){
    random1 = GetRandomValue(0,3);
    random2 = GetRandomValue(0,3);

    while(board[random1][random2] != 0){
        random1 = GetRandomValue(0,3);
        random2 = GetRandomValue(0,3);
    }
    
    board[random1][random2] = 2;
        
}


void moveBoard(){
    int temp = 0;
    if(IsKeyPressed(KEY_RIGHT)){
        memset(merged, false, sizeof(merged));
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                prevBoard[i][j] = board[i][j];
            }
        }  
        for(int i  = 3; i > -1; i--){
            for (int j = 3; j > -1; j--){
                if(board[i][j] != 0){
                    if(!merged[i][j + maxMovesRight(i, j) + 1]&&board[i][j + maxMovesRight(i, j) + 1] == board[i][j]){
                        temp = board[i][j];
                        board[i][j] = 0;
                        board[i][j + maxMovesRight(i, j) + 1] *= 2;
                        merged[i][j + maxMovesRight(i, j) + 1] = true;
                    }
                    else{
                        temp = board[i][j];
                        board[i][j] = 0;
                        board[i][j + maxMovesRight(i, j)] = temp;
                    }
                }
            }
        }
        changed = false;
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                if (board[i][j] != prevBoard[i][j]){
                    changed = true; 
                    i = j = 4;
                    break; 
                }
            }
        }           
        
        if(changed){
            generateRandomTile();
        }
    }
    if(IsKeyPressed(KEY_LEFT)){
        memset(merged, false, sizeof(merged));
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                prevBoard[i][j] = board[i][j];
            }
        }  
        for(int i  = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                if(board[i][j] != 0){
                    if(!merged[i][j - maxMovesLeft(i, j) - 1] && board[i][j - maxMovesLeft(i, j) - 1] == board[i][j]){
                        temp = board[i][j];
                        board[i][j] = 0;
                        board[i][j - maxMovesLeft(i, j) - 1] *= 2;
                        merged[i][j - maxMovesLeft(i, j) - 1] = true;
                    }
                    else{
                        temp = board[i][j];
                        board[i][j] = 0;
                        board[i][j - maxMovesLeft(i, j)] = temp;
                    }
                }
            }
        }
        changed = false;
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                if (board[i][j] != prevBoard[i][j]){
                    changed = true;
                    i = j = 4; 
                    break; 
                }
            }
        }           
        
        if(changed){
            generateRandomTile();
        }
    }
    if(IsKeyPressed(KEY_UP)){
        memset(merged, false, sizeof(merged));
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                prevBoard[i][j] = board[i][j];
            }
        }  
        for(int i  = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                if(board[i][j] != 0){
                    if(!merged[i - maxMovesUp(i, j) - 1][j] && board[i - maxMovesUp(i, j) - 1][j] == board[i][j]){
                        temp = board[i][j];
                        board[i][j] = 0;
                        board[i - maxMovesUp(i, j) - 1][j] *= 2;
                        merged[i - maxMovesUp(i, j) - 1][j] = true;
                    }
                    else{
                        temp = board[i][j]; 
                        board[i][j] = 0;
                        board[i - maxMovesUp(i, j)][j] = temp;
                    }
                }
            }
        }
        changed = false;
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                if (board[i][j] != prevBoard[i][j]){
                    changed = true;
                    i = j = 4; 
                    break; 
                }
            }
        }           
        
        if(changed){
            generateRandomTile();
        }
    }
    if(IsKeyPressed(KEY_DOWN)){
        memset(merged, false, sizeof(merged));
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                prevBoard[i][j] = board[i][j];
            }
        }  
        for(int i  = 3; i > -1; i--){
            for (int j = 0; j < 4; j++){
                if(board[i][j] != 0){
                    if(!merged[i + maxMovesDown(i, j) + 1][j] && board[i + maxMovesDown(i, j) + 1][j] == board[i][j]){
                        temp = board[i][j];
                        board[i][j] = 0;
                        board[i + maxMovesDown(i, j) + 1][j] *= 2;
                        merged[i + maxMovesDown(i, j) + 1][j] = true;
                    }
                    else{
                        temp = board[i][j]; 
                        board[i][j] = 0;
                        board[i + maxMovesDown(i, j)][j] = temp;
                    }
                }
            }
        }
        changed = false;
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                if (board[i][j] != prevBoard[i][j]){
                    changed = true;
                    i = j = 4; 
                    break; 
                }
            }
        }           
        
        if(changed){
            generateRandomTile();
        }
    }


}

int maxMovesRight(int i, int j){
    int moves = 0;
    for(int temp = j+1; temp < 4; temp++){
        if(board[i][temp] == 0){
            moves++;
        }
        else{
            break;
        }
    }
    return moves;
}

int maxMovesLeft(int i, int j){
    int moves = 0;
    for(int temp = j-1; temp > -1; temp--){
        if(board[i][temp] == 0){
            moves++;
        }
        else{
            break;
        }
    }
    return moves;
}

int maxMovesUp(int i, int j){
    int moves = 0;
    for(int temp = i-1; temp > -1; temp--){
        if(board[temp][j] == 0){
            moves++;
        }
        else{
            break;
        }
    }
    return moves;
}

int maxMovesDown(int i, int j){
    int moves = 0;
    for(int temp = i+1; temp < 4; temp++){
        if(board[temp][j] == 0){
            moves++;
        }
        else{
            break;
        }
    }
    return moves;
}

void checkGameEnd(){
    bool canMove = false;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 2048) {
                gameState = 3;  // Win
                return;
            }

            if (board[i][j] == 0 || 
                maxMovesRight(i,j) > 0 || maxMovesLeft(i,j) > 0 || 
                maxMovesUp(i,j) > 0 || maxMovesDown(i,j) > 0) {
                canMove = true;
            }
        }
    }

    if (!canMove) gameState = 2;
}

void drawBoard(){
    DrawRectangleRec(boards, tileEmpty);
    DrawRectangleRoundedLinesEx(boards, 0.01f, 0, 10.0f, boardBackground);

    DrawLineEx((Vector2){200, 115}, (Vector2){200, 815}, 10.0f, boardBackground);
    DrawLineEx((Vector2){375, 115}, (Vector2){375, 815}, 10.0f, boardBackground);
    DrawLineEx((Vector2){550, 115}, (Vector2){550, 815}, 10.0f, boardBackground);

    DrawLineEx((Vector2){25, 290}, (Vector2){725, 290}, 10.0f, boardBackground);
    DrawLineEx((Vector2){25, 465}, (Vector2){725, 465}, 10.0f, boardBackground);
    DrawLineEx((Vector2){25, 640}, (Vector2){725, 640}, 10.0f, boardBackground);

    for(int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if(board[i][j] != 0){
                if(board[i][j] == 2){
                    DrawRectangleRec(tileRects[i][j], tile2);
                    DrawText("2", tileRects[i][j].x+65, tileRects[i][j].y+55, 75, text2);
                }
                else if(board[i][j] == 4){
                    DrawRectangleRec(tileRects[i][j], tile4);
                    DrawText("4", tileRects[i][j].x+65, tileRects[i][j].y+55, 75, text4);
                }
                else if(board[i][j] == 8){
                    DrawRectangleRec(tileRects[i][j], tile8);
                    DrawText("8", tileRects[i][j].x+65, tileRects[i][j].y+55, 75, text8);
                }
                else if(board[i][j] == 16){
                    DrawRectangleRec(tileRects[i][j], tile16);
                    DrawText("16", tileRects[i][j].x+55, tileRects[i][j].y+55, 75, text16);
                }
                else if(board[i][j] == 32){
                    DrawRectangleRec(tileRects[i][j], tile32);
                    DrawText("32", tileRects[i][j].x+50, tileRects[i][j].y+55, 75, text32);
                }
                else if(board[i][j] == 64){
                    DrawRectangleRec(tileRects[i][j], tile64);
                    DrawText("64", tileRects[i][j].x+45, tileRects[i][j].y+55, 75, text64);
                }
                else if(board[i][j] == 128){
                    DrawRectangleRec(tileRects[i][j], tile128);
                    DrawText("128", tileRects[i][j].x+45, tileRects[i][j].y+55, 65, text128);
                }
                else if(board[i][j] == 256){
                    DrawRectangleRec(tileRects[i][j], tile256);
                    DrawText("256", tileRects[i][j].x+37.5, tileRects[i][j].y+55, 65, text256);
                }
                else if(board[i][j] == 512){
                    DrawRectangleRec(tileRects[i][j], tile512);
                    DrawText("512", tileRects[i][j].x+45, tileRects[i][j].y+55, 65, text512);
                }
                else if(board[i][j] == 1024){
                    DrawRectangleRec(tileRects[i][j], tile1024);
                    DrawText("1024", tileRects[i][j].x+35, tileRects[i][j].y+60, 50, text1024);
                }
                else if(board[i][j] == 2048){
                    DrawRectangleRec(tileRects[i][j], tile2048);
                    DrawText("2048", tileRects[i][j].x+30, tileRects[i][j].y+60, 50, text2048);
                }
            
            }
        }
    }
}

void reset(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            board[i][j] = 0;
        }
    }

    random1, random2 = -1;
    gameState = 0;
}

void draw(){
    BeginDrawing();

    ClearBackground(Background);
    
    //Draw Title
    DrawRectangleRounded(titleRec, 0.2f, 0, titleColor);
    DrawRectangleRoundedLines(titleRec, 0.25f, 0, BLACK);
    DrawText("2048", titleRec.x+50, titleRec.y+10, 65, WHITE);

    //Draw board function
    drawBoard();

    if(gameState == 0){
        DrawText("Press ENTER to start", 25, screenHeight/2, 60, BLACK);
    }
    else if(gameState == 2){
        DrawText("GAME OVER!!, ENTER TO RESTART", 25, screenHeight/2, 40, BLACK);
    }
    else if(gameState == 3){
        DrawText("YOU WIN!, ENTER TO RESTART", 25, screenHeight/2, 40, BLACK);
    }

    if (GuiButton((Rectangle){ 25, 25, 200, 75 }, "Restart")) {
        reset();
    }


    EndDrawing();
}




int main(void){

    InitWindow(screenWidth, screenHeight, "2048");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    
    while(!WindowShouldClose()){

        if(IsKeyPressed(KEY_ENTER) && gameState == 0){
            gameState = 1;
            generateRandomTile();
            generateRandomTile();
        }
        else if(gameState == 1){
            moveBoard();
            checkGameEnd();
        }
        else if(gameState == 2 && IsKeyPressed(KEY_ENTER)){
            reset();
            gameState = 0;
        }
        else if(gameState == 3 && IsKeyPressed(KEY_ENTER)){
            reset();
            gameState=  0;
        }
        
        draw();

        
    }    
}
