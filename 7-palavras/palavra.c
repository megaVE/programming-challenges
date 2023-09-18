#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *strrev(char *str){ // strrev: library function fix
    char aux;
    int len = strlen(str);
    for(int i=0; i <= len/2; i++){
        aux = str[len-i-1];
        str[len-i-1] = str[i];
        str[i] = aux;
    }
    return str;
}

#define MAX_N 50
#define MAX_K 20

void toLowerString(char * string, int size){ // Lowercases a string
    for(int i=0; i < size; i++)
        if(string[i] != tolower(string[i]))
            string[i] = tolower(string[i]);
}

void searchHorizontal(char * input, char * word, int width, int height){ // Searches the word on every row
    char * aux = (char*)malloc(height * sizeof(char));
    for(int i=0; i < height; i++){
        strncpy(aux, input+(i * width), width);
        if(strstr(aux, word) != NULL)
            printf("Encontrado %s\n", word);
        if(strstr(strrev(aux), word) != NULL)
            printf("Encontrado ao contrário %s\n", word);
    }
}

char *getColumn(char * input, char * aux, int index, int width, int height){ // Returns a string with the matching column
    int i=0;
    for(; i < height; i++)
        aux[i] = input[i * width + index];
    aux[i] = '\0';
    return aux;
}

void searchVertical(char * input, char * word, int width, int height){ // Searches the word on every column
    char * aux = (char*)malloc(width * sizeof(char));
    for(int i=0; i < width; i++){
        aux = getColumn(input, aux, i, width, height);
        if(strstr(aux, word) != NULL)
            printf("Encontrado %s\n", word);
        if(strstr(strrev(aux), word) != NULL)
            printf("Encontrado ao contrário %s\n", word);
    }
}

char *getDescendingDiagonal(char * input, char * aux, int index, int width, int height){ // Returns a string with the matching diagonal
    int i=0;
    for(; index + i * width + i < width * height; i++)
        aux[i] = input[index + i * width + i];
    aux[i] = '\0';
    return aux;
}

void searchDescendingDiagonal(char * input, char * word, int height, int width){ // Searches the word on every diagonal line
    char * aux = (char*)malloc(height * sizeof(char));
    for(int i=0; i < width; i++){
        aux = getDescendingDiagonal(input, aux, i, width, height);
        printf("aux: %s\n", aux);
        if(strstr(aux, word) != NULL)
            printf("Encontrado %s\n", word);
        if(strstr(strrev(aux), word) != NULL)
            printf("Encontrado ao contrário %s\n", word);
    }
    printf(".\n");
    for(int i=1; i < height; i++){
        aux = getDescendingDiagonal(input, aux, i * width, width, height);
        printf("aux: %s\n", aux);
        if(strstr(aux, word) != NULL)
            printf("Encontrado %s\n", word);
        if(strstr(strrev(aux), word) != NULL)
            printf("Encontrado ao contrário %s\n", word);
    }
}

// char *getAscendingDiagonal(char * input, char * aux, int index, int width, int height){ // Returns a string with the matching diagonal
//     return aux;    
// }

// void searchAscendingDiagonal(char * input, char * word, int height, int width){ // Searches the word on every diagonal line
//     char * aux = (char*)malloc(height * sizeof(char));
//     for(int i=0; i < width+height-1; i++){
//         if(strstr(aux, word) != NULL)
//             printf("Encontrado %s\n", word);
//         if(strstr(strrev(aux), word) != NULL)
//             printf("Encontrado ao contrário %s\n", word);
//     }
// }

int main(){
    int cases, m, n, k;
    char * input;
    char input_line[MAX_N+1];

    scanf("%d", &cases);
    getchar();
    getchar(); // Empty line

    for(int i=0; i < cases; i++){
        scanf("%d %d", &m, &n);
        input = (char*)malloc(m * n * sizeof(char));

        for(int j=0; j < m; j++){
            scanf("%s", input_line);
            toLowerString(input_line, strlen(input_line));
            strcat(input, input_line);
        }

        printf("FULL INPUT: %s\n", input); // debug

        scanf("%d", &k);
        for(int j=0; j < k; j++){
            scanf("%s", input_line);
            toLowerString(input_line, strlen(input_line));

            printf("\n\nprocurando %s\n", input_line);

            // searchHorizontal(input, input_line, n, m);
            // searchVertical(input, input_line, n, m);
            searchDescendingDiagonal(input, input_line, n, m);
            // searchAscendingDiagonal(input, input_line, n, m);
            // int lesser_x, lesser_y;
            // code
            // printf("%d %d\n", lesser_x+1, lesser_y+1);
        }
    }

    return 0;
}