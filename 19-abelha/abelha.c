#include <stdio.h>

void moveBee(int * x, int * y, int direction){ // Makes a move
    switch(direction){
        case 0: // Top
            (*y)--;
            break;
        
        case 1: // Top-right
            (*x)++;
            (*y)--;
            break;
        
        case 2: // Bottom-right
            (*x)++;
            break;
        
        case 3: // Bottom
            (*y)++;
            break;
        
        case 4: // Bottom-left
            (*x)--;
            (*y)++;
            break;
        
        case 5: // Top-left
            (*x)--;
            break;
    }
}

int changeDirection(int direction){ // Changes the current direction
    return (direction < 5) ? direction + 1 : 0;
}

int main(){
    int coordinate;
    while(scanf("%d", &coordinate) != EOF){
        int x = 0, y = 0; // Starting Coordinates
        
        if(coordinate > 1) y = 1;

        int size = 1; // Size of the major outside hexagon
        int direction = 5; // Current direction
        int progress = 0; // Current direction's progress

        // puts("[1]: (0, 0)\n");
        for(int i = 1; i < coordinate - 1; i++, progress++){
            if(progress == size && direction != 3 || progress > size && direction == 3){
                progress = 0;
                direction = changeDirection(direction);
                if(direction == 5) size++;
            }
            // printf("[%d]: (%d, %d)\ndirection: %d\n", i+1, x, y, direction);
            moveBee(&x, &y, direction);
            // printf("[%d]: (%d, %d)\n\n", i+2, x, y);
        }
        printf("%d %d\n", x, y);
    }
    return 0;
}