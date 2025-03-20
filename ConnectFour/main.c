#include "raylib.h"
#include <stdio.h>

const int screenWidth = 1000;
const int screenHeight = 1000;

int turn = 0;
int column = 3;
int redScore = 0;
int yellowScore = 0;

Vector2 circle = {500, 80};
Color circleColor;

bool redWins = false;
bool yellowWins = false;
bool gameOver = false;

int board[6][7] = {
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
};

Vector2 circlePositions[6][7] = {
    { {87.5f, 215}, {225, 215}, {362.5f, 215}, {500, 215}, {637.5f, 215}, {775, 215}, {912.5f, 215} },
    { {87.5f, 337}, {225, 337}, {362.5f, 337}, {500, 337}, {637.5f, 337}, {775, 337}, {912.5f, 337} },
    { {87.5f, 459}, {225, 459}, {362.5f, 459}, {500, 459}, {637.5f, 459}, {775, 459}, {912.5f, 459} },
    { {87.5f, 581}, {225, 581}, {362.5f, 581}, {500, 581}, {637.5f, 581}, {775, 581}, {912.5f, 581} },
    { {87.5f, 703}, {225, 703}, {362.5f, 703}, {500, 703}, {637.5f, 703}, {775, 703}, {912.5f, 703} },
    { {87.5f, 825}, {225, 825}, {362.5f, 825}, {500, 825}, {637.5f, 825}, {775, 825}, {912.5f, 825} }
};




int main(void){
    InitWindow(screenWidth, screenHeight, "Connect Four");
    SetTargetFPS(60);
    Texture2D logo = LoadTexture("build/logo.png");

    InitAudioDevice(); 
    Music backgroundMusic = LoadMusicStream("background.ogg");
    Music end = LoadMusicStream("end.ogg");
    PlayMusicStream(end);
    SetMusicVolume(backgroundMusic, 0.15f);
    SetMusicVolume(end, 0.5f);

    Sound click = LoadSound("capture.mp3");
    SetSoundVolume(click, 2.0f);

    while(!WindowShouldClose()){
        
        if(!gameOver){
            UpdateMusicStream(backgroundMusic);
            if(IsKeyPressed(KEY_RIGHT)&& circle.x !=  912.5){
                circle.x += 137.5;
                column++;
            }
            if(IsKeyPressed(KEY_LEFT) && circle.x != 87.5){
                circle.x -= 137.5;
                column--;
            }

            if(IsKeyPressed(KEY_ENTER)){
                PlaySound(click);
                for(int i = 5; i >= 0; i--){
                    if(board[i][column] == 0){
                        if(turn == 0){
                            board[i][column] = 1;
                            turn = 1;
                            column = 3;
                            circle.x = 500;
                            break;
                        }
                        else if(turn == 1){
                            board[i][column] = 2;
                            turn = 0;
                            column = 3;
                            circle.x = 500;
                            break;
                        }
                    }
                }
            }

            for(int i = 5; i >= 0; i--){
                for(int j = 0; j < 7; j++){
                    if(board[i][j] == 1){
                        //Horizontal Check
                        if(board[i][j+1] == 1 && board[i][j+2] == 1 && board[i][j+3] == 1){
                            redWins = true;
                        }
                        //Vertical Check
                        if(board[i-1][j] == 1 && board[i-2][j] == 1 && board[i-3][j] == 1){
                            redWins = true;
                        }
                        //Up Right
                        if(board[i-1][j+1] == 1 && board[i-2][j+2] == 1 && board[i-3][j+3] == 1 && i-3 >= 0 && j+3 <= 6){
                            redWins = true;
                        }
                        //Up Left
                        if(board[i-1][j-1] == 1 && board[i-2][j-2] == 1 && board[i-3][j-3] == 1 && i-3 >= 0 && j-3 >= 0){
                            redWins = true;
                        }
                        //Down Left
                        if(board[i+1][j-1] == 1 && board[i+2][j-2] == 1 && board[i+3][j-3] == 1 && i+3 <= 5 && j-3 >= 0 ){
                            redWins = true;
                        }
                        //Down Right
                        if(board[i+1][j+1] == 1 && board[i+2][j+2] == 1 && board[i+3][j+3] == 1 && j+3 <= 6 && i+3 <= 5){
                            redWins = true;
                        }
                        

                    }
                    if(board[i][j] == 2){
                        if(board[i][j+1] == 2 && board[i][j+2] == 2 && board[i][j+3] == 2){
                            yellowWins = true;
                        }
                        if(board[i-1][j] == 2 && board[i-2][j] == 2 && board[i-3][j] == 2){
                            yellowWins = true;
                        }

                        //Up Right
                        if(board[i-1][j+1] == 2 && board[i-2][j+2] == 2 && board[i-3][j+3] == 2 && i-3 >= 0 && j+3 <= 6){
                            yellowWins = true;
                        }
                        //Up Left
                        if(board[i-1][j-1] == 2 && board[i-2][j-2] == 2 && board[i-3][j-3] == 2 && i-3 >= 0 && j-3 >= 0){
                            yellowWins = true;
                        }
                        //Down Left
                        if(board[i+1][j-1] == 2 && board[i+2][j-2] == 2 && board[i+3][j-3] == 2 && i+3 <= 5 && j-3 >= 0 ){
                            yellowWins = true;
                        }
                        //Down Right
                        if(board[i+1][j+1] == 2 && board[i+2][j+2] == 2 && board[i+3][j+3] == 2 && j+3 <= 6 && i+3 <= 5){
                            yellowWins = true;
                        }
                    }

                }
            }
            if(redWins||yellowWins){
                gameOver = true;
            }

            BeginDrawing();

            ClearBackground(BLUE);
            DrawRectangle(0,0, 1000, 150, BEIGE);
            DrawLine(0, 150, 1000, 150, BLACK);
            DrawLine(0, 149, 1000, 149, BLACK);
            DrawLine(0, 151, 1000, 151, BLACK);
            DrawLine(0, 148, 1000, 148, BLACK);
            DrawRectangle(0, 900, 1000, 100, BEIGE);
            DrawLine(0, 900, 1000, 900, BLACK);
            DrawLine(0, 901, 1000, 901, BLACK);
            DrawLine(0, 902, 1000, 902, BLACK);
            DrawLine(0, 903, 1000, 903, BLACK);
            DrawLine(0, 904, 1000, 904, BLACK);

            DrawCircleV(circle, 50, circleColor);
            DrawCircleLinesV(circle, 51, BLACK);
            DrawCircleLinesV(circle, 50, BLACK);
            DrawCircleLinesV(circle, 52, BLACK);

            if(turn == 0){
                circleColor = RED;
            }
            else{
                circleColor = YELLOW;
            }

            DrawRectangle(30, 920, 250, 60, RED);
            DrawRectangleLines(30, 920, 250, 60, BLACK);
            DrawText(TextFormat("Red Wins:%d", redScore), 50, 930, 40, BLACK);
            DrawRectangle(680, 920, 300, 60, YELLOW);
            DrawRectangleLines(680, 920, 300, 60, BLACK);
            DrawText(TextFormat("Yellow Wins:%d", yellowScore), 700, 930, 40, BLACK);

            DrawTextureEx(logo, (Vector2){360,915}, 0.0f, 0.4f, WHITE);

            for (int row = 0; row < 6; row++) {
                for (int col = 0; col < 7; col++) {
                    if(board[row][col] == 0){
                        DrawCircleV(circlePositions[row][col], 50, WHITE);
                    }
                    else if(board[row][col] == 1){
                        DrawCircleV(circlePositions[row][col], 50, RED);
                    }
                    else if(board[row][col] == 2){
                        DrawCircleV(circlePositions[row][col], 50, YELLOW);
                    }
                    DrawCircleLines(circlePositions[row][col].x, circlePositions[row][col].y, 51, BLACK);
                    DrawCircleLines(circlePositions[row][col].x, circlePositions[row][col].y, 50, BLACK);
                    DrawCircleLines(circlePositions[row][col].x, circlePositions[row][col].y, 52, BLACK);
                }
            }

            EndDrawing();
        }
        else{
        	if(IsKeyPressed(KEY_R)){
                for(int i = 0; i < 6; i++){
                    for(int j = 0; j < 7; j++){
                        board[i][j] = 0;
                    }
                }
                if(redWins){
                    redScore++;
                }
                else{
                    yellowScore++;
                }
                circle.x = 500;
                redWins = false;
                yellowWins = false;
                turn = 0;
                column = 3;
                gameOver = false;
            }
            BeginDrawing();

            UpdateMusicStream(end);

            ClearBackground(WHITE);
            if(redWins){
                DrawText("Red Wins!", 450, 500, 50, RED);
            }
            else if(yellowWins){
                DrawText("Yellow Wins!", 350, 500, 50, YELLOW);
            }

            DrawText("PRESS R TO RESTART", 350, 550, 45, BLACK);

            EndDrawing();

            

        }
        
    }
    UnloadMusicStream(backgroundMusic);
    CloseAudioDevice();
}
