#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

const int screenWidth = 1324;
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

char capturedBlackPieces[2][8] = {
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
};
Vector2 whitePiecesLocation[2][8] = {
    {{1030, 75}, {1065, 75}, {1100, 75}, {1135, 75}, {1170, 75}, {1205, 75}, {1240, 75}, {1275, 75}},
    {{1030, 150}, {1065, 150}, {1100, 150}, {1135, 150}, {1170, 150}, {1205, 150}, {1240, 150}, {1275, 150}}
};

char capturedWhitePieces[2][8] = {
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
};

Vector2 blackPiecesLocation[2][8] = {
    {{1030, 587}, {1065, 587}, {1100, 587}, {1135, 587}, {1170, 587}, {1205, 587}, {1240, 587}, {1275, 587}},
    {{1030, 662}, {1065, 662}, {1100, 662}, {1135, 662}, {1170, 662}, {1205, 662}, {1240, 662}, {1275, 662}}
};

int turn = 0;
int squareSize = 128;

int selectedRow = -1;
int selectedCol = -1;
int newRow;
int newCol;
bool selected  = false;
bool start = true;
bool capture = false;

Color boardBrown = {139, 69, 19, 255};
Color boardWhite = {245, 245, 220, 255};
Color boardHighlight = {255, 223, 0, 150};
Color circleColor = { 143, 188, 143, 255 };

Sound captureSound;
Sound gameEndSound;
Sound illegalSound;
Sound checkSound;
Sound moveSound;

bool isWhitePiece(char piece) {
    return (piece >= 'A' && piece <= 'Z');
}

bool isBlackPiece(char piece) {
    return (piece >= 'a' && piece <= 'z');
}

bool isUpDiagonalClear(){
    int testCol = 0;
    bool legal = false;
    
    //Up Right Movement
    if(abs(selectedRow - newRow) == abs(selectedCol - newCol)){
        if(newRow < selectedRow && newCol > selectedCol){
            testCol = selectedCol + 1;
            for(int i = selectedRow - 1; i >= newRow; i--){
                if(i == newRow){
                    legal = true;
                }
                else{
                    if(boards[i][testCol] != ' '){
                        legal = false;
                        break;
                    }
                }
                testCol++;
            }
        }
        //Up Left Movement
        else if(newRow < selectedRow && newCol < selectedCol){
            testCol = selectedCol - 1;
            for(int i = selectedRow - 1; i >= newRow; i--){
                if(i == newRow){
                    legal = true;
                }
                else{
                    if(boards[i][testCol] != ' '){
                        legal = false;
                        break;
                    }
                }
                testCol--;
            }
        }
    }    

return legal;
}

bool isDownDiagonalClear(){
    int testCol = 0;
    bool legal = false;
    
    if(abs(selectedRow - newRow) == abs(selectedCol - newCol)){
        //Down Left Movement
        if(newRow > selectedRow && newCol < selectedCol){
            testCol = selectedCol - 1;
            for(int i = selectedRow + 1; i <= newRow; i++){
                if(i == newRow){
                    legal = true;
                }
                else{
                    if(boards[i][testCol] != ' '){
                        legal = false;
                        break;
                    }
                }
                testCol--;
            }
        }
        //Down Right Movement
        else if(newRow > selectedRow && newCol > selectedCol){
            testCol = selectedCol + 1;
            for(int i = selectedRow + 1; i <= newRow; i++){
                if(i == newRow){
                    legal = true;
                }
                else{
                    if(boards[i][testCol] != ' '){
                        legal = false;
                        break;
                    }
                }
                testCol++;
            }
        }
    }
    return legal;
}

bool isVerticalPathClear(){

    bool legal = false;

    if(selectedRow > newRow){

        for(int i = selectedRow-1; i >= newRow; i--){
            if(i == newRow && boards[newRow][newCol] != ' '){
                legal = true;
            }
            else{
                if(boards[i][selectedCol] == ' '){
                    legal = true;
                }
                else{
                    legal = false;
                    break;
                }
            }
        }

    }
    else{
        for(int i = selectedRow+1; i <= newRow; i++){
            if(i == newRow && boards[newRow][newCol] != ' '){
                legal = true;
            }
            else{
                if(boards[i][selectedCol] == ' '){
                    legal = true;
                }
                else{
                    legal = false;
                    break;
                }
            }
        }
        
    }

    return legal;
}

bool isHorizontalPathClear(){
    bool legal = false;

    if(newCol > selectedCol){
        for(int i = selectedCol+1; i <= newCol; i++){
            if(i == newCol && boards[newRow][newCol] != ' '){
                legal = true;
                if(newCol == selectedCol){
                    PlaySound(captureSound);
                }
            }
            else{
                if(boards[selectedRow][i] == ' '){
                    legal = true;
                }
                else{
                    legal = false;
                    break;
                }
            }
            
        }
    }
    else{
        for(int i = selectedCol-1; i >= newCol; i--){
            if(i == newCol && boards[newRow][newCol] != ' '){
                legal = true;
                if(newCol == selectedCol){
                    PlaySound(captureSound);
                }
            }
            else{
                if(boards[selectedRow][i] == ' '){
                    legal = true;
                }
                else{
                    legal = false;
                    break;
                }
            }
        }
    }

    return legal;
    
}

void drawUI(){

    DrawRectangle(1024, 0, 300, 512, boardBrown);
    DrawRectangle(1024, 512, 300, 512, boardWhite);

    if(turn == 0){
        DrawCircle(1174, 768, 50.0f, circleColor);
        DrawCircleLines(1174, 768, 50.0f, BLACK);
    }
    else{
        DrawCircle(1174, 256, 50.0f, circleColor);
        DrawCircleLines(1174, 256, 50.0f, BLACK);
    }

    DrawText("Pieces Captured", 1050, 10, 30, BLACK);
    DrawText("Pieces Captured", 1050, 522, 30, BLACK);

    DrawLine(0, 0, 1024, 0, BLACK);
    DrawLine(1, 1, 1024, 1, BLACK);

    DrawLine(2, 2, 2, 1024, BLACK);
    DrawLine(1, 1, 1, 1024, BLACK);

    DrawLine(0, 1022, 1022, 1022, BLACK);
    DrawLine(0, 1023, 1023, 1023, BLACK);

    DrawLine(1024, 512, 1324, 512, BLACK);
    DrawLine(1024, 513, 1324, 513, BLACK);

    DrawRectangleLines(1024, 0, 300, 1024, BLACK);
    DrawRectangleLines(1025, 1, 298, 1022, BLACK);
    DrawRectangleLines(1026, 2, 296, 1020, BLACK);
}

void draw(Texture2D wKing, Texture2D wBishop, Texture2D wKinght, Texture2D wPawn, Texture2D wQueen, Texture2D wRook, Texture2D bKing, Texture2D bBishop, Texture2D bKnight, Texture2D bPawn, Texture2D bQueen, Texture2D bRook ){
    BeginDrawing();

    ClearBackground(RAYWHITE);

    drawUI();

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

    for(int row = 0; row < 2; row++){
        for(int col = 0; col < 8; col++){
            if(capturedBlackPieces[row][col] == 'r'){
                DrawTextureEx(bRook, blackPiecesLocation[row][col], 0.0f, 0.25f, WHITE);
            }
            if(capturedBlackPieces[row][col] == 'n'){
                DrawTextureEx(bKnight, blackPiecesLocation[row][col], 0.0f, 0.25f, WHITE);
            }
            if(capturedBlackPieces[row][col] == 'b'){
                DrawTextureEx(bBishop, blackPiecesLocation[row][col], 0.0f, 0.25f, WHITE);
            }
            if(capturedBlackPieces[row][col] == 'q'){
                DrawTextureEx(bQueen, blackPiecesLocation[row][col], 0.0f, 0.25f, WHITE);
            }
            if(capturedBlackPieces[row][col] == 'k'){
                DrawTextureEx(bKing, blackPiecesLocation[row][col], 0.0f, 0.25f, WHITE);
            }
            if(capturedBlackPieces[row][col] == 'p'){
                DrawTextureEx(bPawn, blackPiecesLocation[row][col], 0.0f, 0.25f, WHITE);
            }

            if(capturedWhitePieces[row][col] == 'R'){
                DrawTextureEx(wRook, whitePiecesLocation[row][col], 0.0f, 0.25f, WHITE);
            }
            if(capturedWhitePieces[row][col] == 'N'){
                DrawTextureEx(wKinght, whitePiecesLocation[row][col], 0.0f, 0.25f, WHITE);
            }
            if(capturedWhitePieces[row][col] == 'B'){
                DrawTextureEx(wBishop, whitePiecesLocation[row][col], 0.0f, 0.25f, WHITE);
            }
            if(capturedWhitePieces[row][col] == 'Q'){
                DrawTextureEx(wQueen, whitePiecesLocation[row][col], 0.0f, 0.25f, WHITE);
            }
            if(capturedWhitePieces[row][col] == 'K'){
                DrawTextureEx(wKing, whitePiecesLocation[row][col], 0.0f, 0.25f, WHITE);
            }
            if(capturedWhitePieces[row][col] == 'P'){
                DrawTextureEx(wPawn, whitePiecesLocation[row][col], 0.0f, 0.25f, WHITE);
            }
        }
    }


    EndDrawing();
}

bool isLegalPawnMove(){
    bool legal = false;
    capture = false;

    if(turn == 0){
        if(selectedRow == 6 ){
            if( (newRow == selectedRow-1 || newRow == selectedRow-2) && selectedCol == newCol){
                legal = true;
            }
            else if(boards[newRow][newCol] != ' ' && (newRow == selectedRow-1 && (newCol == selectedCol-1 || newCol == selectedCol+1)) && isBlackPiece(boards[newRow][newCol]) && (newCol != selectedCol)){
                capture = true;
                legal = true;
            }
        }
        else{
            if(newRow == selectedRow-1 && selectedCol == newCol && boards[newRow][newCol] == ' '){
                legal = true;
            }
            else if(boards[newRow][newCol] != ' ' && (newRow == selectedRow-1 && (newCol == selectedCol-1 || newCol == selectedCol+1)) && isBlackPiece(boards[newRow][newCol]) && (newCol != selectedCol)){
                capture = true;
                legal = true;
            }
        }
    }
    else{
        if(selectedRow == 1 ){
            if( (newRow == selectedRow+1 || newRow == selectedRow+2) && selectedCol == newCol){
                legal = true;
            }
            else if((newRow == selectedRow+1 && (newCol == selectedCol-1 || newCol == selectedCol+1)) && isWhitePiece(boards[newRow][newCol]) && (newCol != selectedCol)){
                capture = true;
                legal = true;
            }
        }
        else{
            if(newRow == selectedRow+1 && selectedCol == newCol && boards[newRow][newCol] == ' '){
                legal = true;
            }
            else if((newRow == selectedRow+1 && (newCol == selectedCol-1 || newCol == selectedCol+1)) && isWhitePiece(boards[newRow][newCol]) && (newCol != selectedCol)){
                capture = true;
                legal = true;
            }
        }
    }

    return legal;    
}

bool isLegalRookMove(){
    bool legal = false;
    bool capture = false;

    if(isVerticalPathClear() && newCol == selectedCol){
        legal = true;
    }
    else if(isHorizontalPathClear() && newRow == selectedRow){
        legal = true;
    }
    else{
        legal = false;
    }

    return legal;
}

bool isLegalBishopMove(){
    bool legal = false;

    if(isUpDiagonalClear()||isDownDiagonalClear() ){
        legal = true;
    }
    else{
        legal = false;
    }

    return legal;
}

bool isLegalKnightMove(){
    bool legal = false;

    if(newRow == selectedRow-2 && newCol == selectedCol + 1){
        legal = true;
    }
    else if(newRow == selectedRow - 1 && newCol == selectedCol + 2){
        legal = true;
    }
    else if(newRow == selectedRow + 1 && newCol == selectedCol + 2){
        legal = true;
    }
    else if(newRow == selectedRow + 2 && newCol == selectedCol + 1){
        legal = true;
    }
    else if(newRow == selectedRow + 2 && newCol == selectedCol - 1){
        legal = true;
    }
    else if(newRow == selectedRow + 1 && newCol == selectedCol - 2){
        legal = true;
    }
    else if(newRow == selectedRow - 1 && newCol == selectedCol - 2){
        legal = true;
    }
    else if(newRow == selectedRow - 2 && newCol == selectedCol - 1){
        legal = true;
    }

    return legal;
}

bool isLegalQueenMove(){
    bool legal = false;

    if((isVerticalPathClear() && newCol == selectedCol)||(isHorizontalPathClear() && newRow == selectedRow)||isUpDiagonalClear()||isDownDiagonalClear()){
        legal = true;
    }

    return legal;
}

bool isLegalMove(char piece, int newRow, int newCol){
    if(piece == 'P' || piece == 'p'){
        if(isLegalPawnMove()){
            return true;
        }
        else{
            PlaySound(illegalSound);
            return false;
        }
    }
    else if(piece == 'R'|| piece == 'r'){
        if(isLegalRookMove()){
            return true;
        }
        else{
            PlaySound(illegalSound);
            return false;
        }
    }
    else if(piece == 'B'||piece == 'b'){
        if(isLegalBishopMove()){
            return true;
        }
        else{
            PlaySound(illegalSound);
            return false;
        }
    }
    else if(piece == 'N'||piece == 'n'){
        if(isLegalKnightMove()){
            return true;
        }
        else{
            PlaySound(illegalSound);
            return false;
        }
    }
    else if(piece == 'Q'||piece == 'q'){
        if(isLegalQueenMove()){
            return true;
        }
        else{
            PlaySound(illegalSound);
            return false;
        }
    }
    else{
        return false;
    }
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
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&&CheckCollisionPointRec(mousePos, board[row][col])){
                newRow = row;
                newCol = col;
                if(selected && isLegalMove(boards[selectedRow][selectedCol], newRow, newCol)){
                    
                    if(boards[newRow][newCol] != ' '){
                        PlaySound(captureSound);
                        for(int i = 0; i < 2; i++){
                            for(int j = 0; j < 8; j++){
                                if(turn == 0){
                                    if(capturedBlackPieces[i][j] == ' '){
                                        capturedBlackPieces[i][j] = boards[newRow][newCol];
                                        i = 2;
                                        j = 8;
                                    }
                                }
                                else{
                                    if(capturedWhitePieces[i][j] == ' '){
                                        capturedWhitePieces[i][j] = boards[newRow][newCol];
                                        i = 2;
                                        j = 8;
                                    }
                                }
                            }
                        }
                    }
                    else{
                        PlaySound(moveSound);
                    }
                    
                    boards[newRow][newCol] = boards[selectedRow][selectedCol];
                    boards[selectedRow][selectedCol] = ' ';

                    selected = false;
                    selectedRow = -1;
                    selectedCol = -1;
                    newRow = -1;
                    newCol = -1;

                    if(turn == 0){
                        turn = 1;
                    }
                    else{
                        turn = 0;
                    }


                    break;
                }
            }
        }
        }
    }
    
int main(void){

    InitWindow(screenWidth, screenHeight, "Chess!");
    SetTargetFPS(60);

    InitAudioDevice();
    captureSound = LoadSound("/home/killswitch/RaylibProjects/Chess/Sound/capture.wav");
    gameEndSound = LoadSound("/home/killswitch/RaylibProjects/Chess/Sound/game-end.wav");
    illegalSound = LoadSound("/home/killswitch/RaylibProjects/Chess/Sound/illegal.wav");
    checkSound = LoadSound("/home/killswitch/RaylibProjects/Chess/Sound/move-check.wav");
    moveSound = LoadSound("/home/killswitch/RaylibProjects/Chess/Sound/move-self.wav");

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