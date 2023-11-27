#include <stdio.h>

#define PUZZLE_SIZE 4
#define MAX_STEPS 50

int checkSolution(int puzzle[PUZZLE_SIZE][PUZZLE_SIZE]){ // Checks if the current solution is valid
    for(int i = 0; i < PUZZLE_SIZE; i++)
        for(int j = 0; j < PUZZLE_SIZE; j++)
            if(puzzle[i][j] != i * PUZZLE_SIZE + j) return 0;
    
    return 1;
}

void copyMatrix(int copy_matrix[PUZZLE_SIZE][PUZZLE_SIZE], int matrix[PUZZLE_SIZE][PUZZLE_SIZE]){
    for(int i = 0; i < PUZZLE_SIZE; i++)
        for(int j = 0; j < PUZZLE_SIZE; j++)
            copy_matrix[i][j] = matrix[i][j];
}

void puzzleSolver(int puzzle[PUZZLE_SIZE][PUZZLE_SIZE], int x, int y, char * solution, int solution_progress, int * has_solution){
    if(*has_solution || solution_progress > MAX_STEPS) return; // Solution path ending

    if(checkSolution(puzzle)){ // Valid solution
        puts("Solution");
        // *has_solution = 1;
        // solution[solution_progress] = '\0';
        return;
    }

    int copy_puzzle[PUZZLE_SIZE][PUZZLE_SIZE];
    
    puts("parede");
    
    if(x > 0){ // Move Left
        copyMatrix(copy_puzzle, puzzle);
        copy_puzzle[y][x] = copy_puzzle[y][x - 1];
        copy_puzzle[y][x - 1] = 0;
        puzzleSolver(copy_puzzle, x - 1, y, solution, solution_progress + 1, has_solution);
    }

    if(y > 0){ // Move Up
        copyMatrix(copy_puzzle, puzzle);
        copy_puzzle[y][x] = copy_puzzle[y - 1][x];
        copy_puzzle[y - 1][x] = 0;
        puzzleSolver(copy_puzzle, x, y - 1, solution, solution_progress + 1, has_solution);
    }
    
    if(x < PUZZLE_SIZE - 1){ // Move Right
        copyMatrix(copy_puzzle, puzzle);
        copy_puzzle[y][x] = copy_puzzle[y][x + 1];
        copy_puzzle[y][x + 1] = 0;
        puzzleSolver(copy_puzzle, x + 1, y, solution, solution_progress + 1, has_solution);
    }
    
    if(y < PUZZLE_SIZE - 1){ // Move Down
        copyMatrix(copy_puzzle, puzzle);
        copy_puzzle[y][x] = copy_puzzle[y - 1][x];
        copy_puzzle[y - 1][x] = 0;
        puzzleSolver(puzzle, x, y + 1, solution, solution_progress + 1, has_solution);
    }
}

int main(){
    int n;
    scanf("%d", &n); // Cases
    printf("Cases: %d\n", n);

    for(int i = 0; i < n; i++){
        int puzzle[PUZZLE_SIZE][PUZZLE_SIZE];
        
        int zero_x, zero_y;

        for(int j = 0; j < PUZZLE_SIZE; j++){
            for(int k = 0; k < PUZZLE_SIZE; k++){
                scanf("%d", &puzzle[j][k]);
                if(puzzle[j][k] == 0){
                    zero_x = j;
                    zero_y = k;
                }
                printf("%d, ", puzzle[j][k]);
            }
            putchar('\n');
        }
        printf("Zero Position: [%d, %d]\n", zero_x, zero_y);

        int has_solution = 0;
        char solution[MAX_STEPS+1];

        puzzleSolver(puzzle, zero_x, zero_y, solution, 0, &has_solution);

        if(has_solution)
            printf("%s\n", solution);
        else
            puts("This puzzle is not solvable");
    }
    return 0;
}