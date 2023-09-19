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

int lesser_x = -1;
int lesser_y = -1;

int min(int a, int b){ // Returns the lesser number 
    if(a < b)
        return a;
    return b;
}

int setLesser(int x, int y){ // Changes the new values
    if(lesser_x == -1 || y < lesser_y || y == lesser_y && x < lesser_x){
        lesser_x = x;
        lesser_y = y;
    }
}

void toLowerString(char * string, int size){ // Lowercases a string
    for(int i=0; i < size; i++)
        if(string[i] != tolower(string[i]))
            string[i] = tolower(string[i]);
}

int findStart(char * word, char * string){ // Returns where the word was found in the array
    int word_completion = 0;
    // printf("word %s string %s\n", word, string);
    int i=0;
    for(; i < strlen(string); i++){
        // printf("word %c compare string %c\n", word[word_completion], string[i]);
        if(word_completion == strlen(word))
            return i - word_completion;
        if(word[word_completion] == string[i])
            word_completion++;
        else{
            word_completion = 0;
            if(word[word_completion] == string[i])
                word_completion++;  
        }
    }
    // printf("word completion final: %d\n", word_completion);
    if(word_completion == strlen(word))
        return i - word_completion;
    return -1;
}

void searchHorizontal(char * input, char * word, int width, int height){ // Searches the word on every row
    char * aux = (char*)malloc(height * sizeof(char));
    for(int i=0; i < height; i++){
        strncpy(aux, input+(i * width), width);
        if(strstr(aux, word) != NULL)
            setLesser(findStart(word, aux), i);
        // printf("Encontrado %s\n", word);
        if(strstr(strrev(aux), word) != NULL)
            setLesser(width - findStart(word, aux)-1, i);
        // printf("Encontrado ao contrário %s\n", word);
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
        if(strstr(aux, word) != NULL){
            setLesser(i, findStart(word, aux));
        }
        // printf("Encontrado %s\n", word);
        if(strstr(strrev(aux), word) != NULL){
            setLesser(i, height - findStart(word, aux) - 1);
        }
        // printf("Encontrado ao contrário %s\n", word);
    }
}

char *getDescendingDiagonal(char * input, char * aux, int index, int width, int height){ // Returns a string with the matching diagonal
    int limit = (index >= width) ? min(width, height-(index / width)) : min(width-index, height);

    int i=0;
    for(; i < limit; i++)
        aux[i] = input[index + (i * width + i)];
    aux[i] = '\0';
    return aux;
}

void searchDescendingDiagonal(char * input, char * word, int width, int height){ // Searches the word on every diagonal line
    char * aux = (char*)malloc(height * sizeof(char));
    for(int i=0; i < width; i++){
        aux = getDescendingDiagonal(input, aux, i, width, height);
        // printf("aux : %s\n", aux);
        if(strstr(aux, word) != NULL){
            int position = findStart(word, aux);
            // printf("position %d i %d\n", position, i);
            setLesser(i+position, position);
            // printf("mdi %d %d\n", lesser_x, lesser_y);
        }
            // printf("Encontrado %s\n", word);
        if(strstr(strrev(aux), word) != NULL){
            int position = findStart(word, aux);
            setLesser(width - position - i - 1, height - position - 1);
            // printf("mdi %d %d\n", lesser_x, lesser_y);
        }
            // printf("Encontrado ao contrário %s\n", word);
    }
    for(int i=1; i < height; i++){
        aux = getDescendingDiagonal(input, aux, i * width, width, height);
        // printf("aux : %s\n", aux);
        if(strstr(aux, word) != NULL){
            int position = findStart(word, aux);
            // printf("position %d i %d\n", position, i);
            setLesser(position, i+position);
            // printf("mdi %d %d\n", lesser_x, lesser_y);
        }
        // printf("Encontrado %s\n", word);
        if(strstr(strrev(aux), word) != NULL){
            int position = findStart(word, aux);
            setLesser(width - position - 1, height - i - position - 1);
            // printf("mdi %d %d\n", lesser_x, lesser_y);
        }
            // printf("Encontrado ao contrário %s\n", word);
    }
}

char *getAscendingDiagonal(char * input, char * aux, int index, int width, int height){ // Returns a string with the matching diagonal
    int limit = (index >= width) ? min(width, height - (index - (width-1)) / width) : min(index+1, height);

    int i=0;
    for(; i < limit; i++)
        aux[i] = input[index + (i * width - i)];
    aux[i] = '\0';
    return aux;
}

void searchAscendingDiagonal(char * input, char * word, int width, int height){ // Searches the word on every diagonal line
    char * aux = (char*)malloc(height * sizeof(char));
    for(int i=0; i < width; i++){
        aux = getAscendingDiagonal(input, aux, i, width, height);
        // printf("aux : %s\n", aux);
        if(strstr(aux, word) != NULL){
            int position = findStart(word, aux);
            // printf("position %d i %d\n", position, i);
            setLesser(i-position, position);
            // printf("mdi %d %d\n", lesser_x, lesser_y);
        }
            // printf("Encontrado %s\n", word);
        if(strstr(strrev(aux), word) != NULL){
            int position = findStart(word, aux);
            // printf("position %d i %d\n", position, i);
            setLesser(width - (i-position) - 1, height - position - 1);
            // printf("mdi %d %d\n", lesser_x, lesser_y);
        }
            // printf("Encontrado ao contrário %s\n", word);
    }
    for(int i=1; i < height; i++){
        aux = getAscendingDiagonal(input, aux, (width-1) + i * width, width, height);
        // printf("aux : %s\n", aux);
        if(strstr(aux, word) != NULL){
            int position = findStart(word, aux);
            setLesser(width-1 - position,i + position);
            // printf("mdi %d %d\n", lesser_x, lesser_y);
        }
            // printf("Encontrado %s\n", word);
        if(strstr(strrev(aux), word) != NULL){
            int position = findStart(word, aux);
            setLesser(width-1- (width-1 - position), height-1 - (i+position));
            // printf("mdi %d %d\n", lesser_x, lesser_y);
        }
            // printf("Encontrado ao contrário %s\n", word);
    }
}

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

        // printf("FULL INPUT: %s\n", input); // debug

        scanf("%d", &k);
        for(int j=0; j < k; j++){
            lesser_x = -1;
            lesser_y = -1;

            scanf("%s", input_line);
            toLowerString(input_line, strlen(input_line));

            // printf("\n\nprocurando %s\n", input_line);

            // printf("horizontal\n");
            searchHorizontal(input, input_line, n, m);
            // printf("vertical\n");
            searchVertical(input, input_line, n, m);
            // printf("diagonal 1\n");
            searchDescendingDiagonal(input, input_line, n, m);
            // printf("diagonal 2\n");
            searchAscendingDiagonal(input, input_line, n, m);

            if(lesser_x != -1)
                printf("%d %d\n", lesser_y+1, lesser_x+1);
        }
    }

    return 0;
}