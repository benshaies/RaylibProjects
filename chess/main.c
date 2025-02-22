#include "raylib.h"
#include <stdio.h>

const int screenWidth = 1024;
const int screenHeight = 1024;

Rectangle board[8][8];
char boards[8][8] = {
    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
};

int turn = 0;
int squareSize = 128;

int selectedRow = -1;
int selectedCol = -1;
int newRow;
int newCol;
bool selected  = false;
bool start = true;

Color boardBrown = {139, 69, 19, 255};
Color boardWhite = {245, 245, 220, 255};
Color boardHighlight = {255, 223, 0, 150};


void draw(Texture2D wKing, Texture2D wBishop, Texture2D wKinght, Texture2D wPawn, Texture2D wQueen, Texture2D wRook, Texture2D bKing, Texture2D bBishop, Texture2D bKnight, Texture2D bPawn, Texture2D bQueen, Texture2D bRook ){
    BeginDrawing();

    ClearBackground(RAYWHITE);

    //Draw Board and update board
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Color color = ((row + col) % 2 == 0) ? boardWhite : boardBrown;
            if(selectedRow == row && col == selectedCol){
                DrawRectangleRec(board[row][col], boardHighlight);
            }
            else{
                DrawRectangleRec(board[row][col], color);
            }

            if(boards[row][col] == 'r'){
                DrawTexture(bRook, board[row][col].x, board[row][col].y, WHITE);
            }
            if(boards[row][col] == 'n'){
                DrawTexture(bKnight, board[row][col].x, board[row][col].y, WHITE);
            }
            if(boards[row][col] == 'b'){
                DrawTexture(bBishop, board[row][col].x, board[row][col].y, WHITE);
            }
            if(boards[row][col] == 'q'){
                DrawTexture(bQueen, board[row][col].x, board[row][col].y, WHITE);
            }
            if(boards[row][col] == 'k'){
                DrawTexture(bKing, board[row][col].x, board[row][col].y, WHITE);
            }
            if(boards[row][col] == 'p'){
                DrawTexture(bPawn, board[row][col].x, board[row][col].y, WHITE);
            }

            if(boards[row][col] == 'R'){
                DrawTexture(wRook, board[row][col].x, board[row][col].y, WHITE);
            }
            if(boards[row][col] == 'N'){
                DrawTexture(wKinght, board[row][col].x, board[row][col].y, WHITE);
            }
            if(boards[row][col] == 'B'){
                DrawTexture(wBishop, board[row][col].x, board[row][col].y, WHITE);
            }
            if(boards[row][col] == 'Q'){
                DrawTexture(wQueen, board[row][col].x, board[row][col].y, WHITE);
            }
            if(boards[row][col] == 'K'){
                DrawTexture(wKing, board[row][col].x, board[row][col].y, WHITE);
            }
            if(boards[row][col] == 'P'){
                DrawTexture(wPawn, board[row][col].x, board[row][col].y, WHITE);
            }
        }
    }

    EndDrawing();
}

void selectPiece(){
    for(int row = 0; row < 8; row++){
        for(int col = 0; col < 8; col++){
            Vector2 mousePos = GetMousePosition();

            //Select Piece
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&&CheckCollisionPointRec(mousePos, board[row][col]) && boards[row][col] != ' '){
                if(turn == 0 && (boards[row][col] == 'R'||boards[row][col] == 'N'||boards[row][col] == 'B'||boards[row][col] == 'Q'||boards[row][col] == 'K'||boards[row][col] == 'P')){
                    selectedRow = row;
                    selectedCol = col;
                    selected = true;
                    printf("Selected Row: %d, Selected Col: %d\n", selectedRow, selectedCol);
                    break;
                }
                if(turn == 1 && (boards[row][col] == 'r'||boards[row][col] == 'n'||boards[row][col] == 'b'||boards[row][col] == 'q'||boards[row][col] == 'k'||boards[row][col] == 'p')){
                    selectedRow = row;
                    selectedCol = col;
                    selected = true;
                    printf("Selected Rows: %d, Selected Cols: %d\n", selectedRow, selectedCol);
                    break;
                }
            }

            if(selected && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&&CheckCollisionPointRec(mousePos, board[row][col]) && boards[row][col] == ' '){
                boards[row][col] = boards[selectedRow][selectedCol];
                boards[selectedRow][selectedCol] = ' ';

                selectedRow = -1;
                selectedCol = -1;
                selected = false;
                if(turn == 0){
                    turn = 1;
                }
                else{
                    turn = 0;
                }
            }
        }

            //Pick New Spot
        }
    }
    



int main(void){

    InitWindow(screenWidth, screenHeight, "Chess");
    SetTargetFPS(60);

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            board[row][col].x = col * squareSize;
            board[row][col].y = row * squareSize;
            board[row][col].width = squareSize;
            board[row][col].height = squareSize;
        }
    }

    Texture2D wKing = LoadTexture("/home/killswitch/RaylibProjects/Chess/w_King.png");
    Texture2D wBishop = LoadTexture("/home/killswitch/RaylibProjects/Chess/w_Bishop.png");
    Texture2D wKnight = LoadTexture("/home/killswitch/RaylibProjects/Chess/w_Knight.png");
    Texture2D wPawn = LoadTexture("/home/killswitch/RaylibProjects/Chess/w_Pawn.png");
    Texture2D wQueen = LoadTexture("/home/killswitch/RaylibProjects/Chess/w_Queen.png");
    Texture2D wRook = LoadTexture("/home/killswitch/RaylibProjects/Chess/w_Rook.png");

    Texture2D bKing = LoadTexture("/home/killswitch/RaylibProjects/Chess/b_King.png");
    Texture2D bBishop = LoadTexture("/home/killswitch/RaylibProjects/Chess/b_Bishop.png");
    Texture2D bKnight = LoadTexture("/home/killswitch/RaylibProjects/Chess/b_Knight.png");
    Texture2D bPawn = LoadTexture("/home/killswitch/RaylibProjects/Chess/b_Pawn.png");
    Texture2D bQueen = LoadTexture("/home/killswitch/RaylibProjects/Chess/b_Queen.png");
    Texture2D bRook = LoadTexture("/home/killswitch/RaylibProjects/Chess/b_Rook.png");    
    
    while(!WindowShouldClose()){

        draw(wKing,wBishop,wKnight, wPawn, wQueen, wRook, bKing, bBishop, bKnight, bPawn, bQueen, bRook);
        selectPiece();
    }    
}