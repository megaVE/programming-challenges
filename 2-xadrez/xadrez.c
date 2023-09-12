// Autor: Vinícius Eduardo de Souza Honório
// Matrícula: 2021.1.08.024

#include <stdio.h>

#define SIZE 8

char board[SIZE][SIZE+1];
int kingX, kingY;

int checkPosition(int x, int y){ // Checks if the Current Position is Valid
    return (x > -1 && y > -1 && x < 8 && y < 8) ? 1 : 0;
}

int seekKing(char piece){ // Returns the Position of a King on the Board
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            if(board[i][j] == piece){
                kingX = j;
                kingY = i;
                return 0;
            }
    return -1;
}

int checkPawn(char p){ // Checks if a Pawn is meaning the King
    if(p == 'p'){ // Black Pawn above
        if((checkPosition(kingY-1, kingX-1) && board[kingY-1][kingX-1] == p) || (checkPosition(kingY-1, kingX+1) && board[kingY-1][kingX+1] == p))
            return -1;
    }
    else if(p == 'P'){ // White Pawn bellow
        if((checkPosition(kingY+1, kingX-1) && board[kingY+1][kingX-1] == p) || (checkPosition(kingY+1, kingX+1) && board[kingY+1][kingX+1] == p))
            return -1;
    }
    return 0;   
}

int checkKnight(char n){ // Checks if a Knight is menacing the King
    for(int i = -1+kingX; i < 2+kingX; i += 2)
        for(int j = -2+kingY; j < 3+kingY; j += 4)
            if((checkPosition(i, j) && board[i][j] == n) || (checkPosition(j, i) && board[j][i] == n))
                return -1;
    for(int i = -2+kingX; i < 3+kingX; i += 4)
        for(int j = -1+kingY; j < 2+kingY; j += 2)
            if((checkPosition(i, j) && board[i][j] == n) || (checkPosition(j, i) && board[j][i] == n))
                return -1;
    return 0;
}

int checkLine(char r, char q){ // Checks if Rook or Queen is menacing the King
    for(int i = kingX+1; i < SIZE; i++){
        if(board[kingY][i] == r || board[kingY][i] == q)            
            return -1;
        else if(board[kingY][i] != '.') // Blocking piece
            break;
    }
    for(int i = kingX-1; i > -1; i--){
        if(board[kingY][i] == r || board[kingY][i] == q)
            return -1;
        else if(board[kingY][i] != '.') // Blocking piece
            break;
    }
    for(int i = kingY+1; i < SIZE; i++){
        if(board[i][kingX] == r || board[i][kingX] == q)
            return -1;
        else if(board[i][kingX] != '.') // Blocking piece
            break;
    }
    for(int i =kingY-1; i > -1; i--){
        if(board[i][kingX] == r || board[i][kingX] == q)
            return -1;
        else if(board[i][kingX] != '.') // Blocking piece
            break;
    }
    return 0;
}

int checkDiagonal(char b, char q){ // Checks if a Bishop or Queen is menacing the King
    for(int i = kingX+1, j = kingY+1; i < SIZE, j < SIZE; i++, j++){
        if(board[j][i] == b || board[j][i] == q)
            return -1;
        else if(board[j][i] != '.') // Blocking piece
            break;
    }
    for(int i = kingX+1, j = kingY-1; i < SIZE, j > -1; i++, j--){
        if(board[j][i] == b || board[j][i] == q)
            return -1;
        else if(board[j][i] != '.') // Blocking piece
            break;
    }
    for(int i = kingX-1, j = kingY+1; i > -1, j < SIZE; i--, j++){
        if(board[j][i] == b || board[j][i] == q)
            return -1;
        else if(board[j][i] != '.') // Blocking piece
            break;
    }
    for(int i = kingX-1, j = kingY-1; i > -1, j > -1; i--, j--){
        if(board[j][i] == b || board[j][i] == q)
            return -1;
        else if(board[j][i] != '.') // Blocking piece
            break;
    }
    return 0;
}

int checkCheck(char k, char* pieces){ // Checks if the King is being menaced
    int check = 0;
    if(seekKing(k)) // No King found (Final Input)
        return 1;
    check += checkPawn(pieces[0]);
    check += checkKnight(pieces[4]);    
    check += checkLine(pieces[1], pieces[3]);
    check += checkDiagonal(pieces[2], pieces[3]);
    return check;
}

int main(){
    int gameCount = 1;
    char line[SIZE+1]; // Individual Row
    int whiteSide, blackSide;
    char blackPieces[] = "prbqn";
    char whitePieces[] = "PRBQN";

    while(1){
        for(int i = 0; i < SIZE; i++){ // Input Reading
            do scanf("%s", line); while(line[0] == '\n');
            for(int j = 0; j < SIZE; j++)
                board[i][j] = line[j];
            board[i][SIZE] = '\0';
        }

        whiteSide = checkCheck('K', blackPieces); // Solution White Side
        blackSide = checkCheck('k', whitePieces); // Solution Black Side

        if(whiteSide == 1 || blackSide == 1) // Final Input
            break;
        else if(whiteSide < 0)
            printf("Game #%d: white king is in check.\n", gameCount);
        else if(blackSide < 0)
            printf("Game #%d: black king is in check.\n", gameCount);
        else
            printf("Game #%d: no king is in check.\n", gameCount);

        gameCount++;
    }
    return 0;
}