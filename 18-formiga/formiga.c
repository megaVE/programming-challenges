#include <stdio.h>

void setProgress(int * x, int * y, char direction){ // Progress towards the maze
    switch(direction){
        case 'w':
            ++*y;
            break;

        case 'a':
            --*x;
            break;

        case 's':
            --*y;
            break;

        case 'd':
            ++*x;
            break;
    }
}

char nextDirection(char direction){ // Sets the next direction to go
    switch(direction){
        case 'w': return 'a';
        case 'a': return 'd';
        case 'd': return 's';        
        case 's': return 'w';
    }
}

int main(){
    int n;
    scanf("%d", &n); // Time

    while(n != 0){
        int x = 1, y = 1; // Initial position: (1,1)
        int square_size = 2;
        char direction = 'd';
        int local_progress = 0;

        if(n != 1) y = 2; // First Upward Move

        for(int i = 2; i < n; i++){
            // printf("[%d]: (%d,%d)\n", i+1, x, y);
            if(i == square_size * square_size){ // Transition to a New Square
                if(x == 1){
                    y++;
                    direction = 'd';
                }else{ // if(y == 1)
                    x++;
                    direction = 'w';
                }
                local_progress = 0;
                square_size++;
            }else{
                if(local_progress == square_size - 1){ // Changing Direction
                    direction = nextDirection(direction);
                    local_progress = 0;
                }
                setProgress(&x, &y, direction); // Moving
                local_progress++;
            }
        }
        printf("%d %d\n", x, y); // Result
        
        scanf("%d", &n); // Next Case
    }
    return 0;
}