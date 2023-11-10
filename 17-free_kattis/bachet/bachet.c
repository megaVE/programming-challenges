#include <stdio.h>

// n pedras iniciais
// Stan e Ollie são os jogadores
// Stan joga primeiro
// Movimento válido = remove o número de pedras do array
// O vencedor pega a última pedra

#define MAX_M_SIZE 10

int includes(int * array, int array_size, int number){ // Checks if the array includes a number
    for(int i = 0; i < array_size; i++)
        if(array[i] == number) return 1;
    return 0;
}

void sortArray(int * array, int array_size){ // Sorts an array
    int i, j, was_swapped;
    for(i = 0; i < array_size - 1; i++){
        was_swapped = 0;
        for(j = 0; j < array_size - i - 1; j++){
            if(array[j] > array[j + 1]){
                was_swapped = 1;
                
                int aux = array[j + 1];
                array[j + 1] = array[j];
                array[j] = aux;
            }
        }
        if(!was_swapped) break;
    }
}

int main(){
    int lines;
    scanf("%d", &lines); // Number of Cases
    
    for(int i = 0; i < lines; i++){
        int n;
        scanf("%d", &n); // Number of Stones
    
        int m;
        scanf("%d", &m); // Number of Valid Moves

        int k[MAX_M_SIZE];
        for(int j = 0; j < m; j++)
            scanf("%d", k[j]); // Valid Moves Array

        while(1){
            // Stan
            puts("Stan wins");
            break;
            
            // Ollie
            puts("Ollie wins");
            break;
        }
    }


    return 0;
}