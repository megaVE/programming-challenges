#include <stdio.h>
#include <string.h>

#define NUMBER_LENGTH 10
#define NUMBER_COMPONENTS 7

char number_code[NUMBER_LENGTH][NUMBER_COMPONENTS + 1];

int getNumberLength(int number){ // Returns the size of a number
    int i = 0;
    for(; number > 0; i++, number /= 10);
    return i;
}

char * numberToString(int number){ // Converst an int number to the calculator display
    switch(number){
        case 0: return "abcefg\0";
        case 1: return "cf\0";
        case 2: return "acdeg\0";
        case 3: return "acdfg\0";
        case 4: return "bcdf\0";
        case 5: return "abdfg\0";
        case 6: return "abdefg\0";
        case 7: return "acf\0";
        case 8: return "abcdefg\0";
        case 9: return "abcdfg\0";
    }
}

void printRow(int * index, char letter, int s, int length){
    for(int i = 0; i < length; i++){
        putchar(' ');

        for(int j = 0; j < s; j++) number_code[i][index[i]] == letter ? putchar('-') : putchar(' ');
        if(number_code[i][index[i]] == letter) index[i]++;
        
        putchar(' ');

        putchar(' ');
    }
    putchar('\n');
}

void printColumn(int * index, char letter1, char letter2, int s, int length){
    int aux[NUMBER_LENGTH];
    for(int n = 0; n < s; n++){
        if(n > 0){
            for(int i = 0; i < length; i++)
                index[i] = aux[i];
        }
        for(int i = 0; i < length; i++){
            aux[i] = index[i];
            number_code[i][index[i]] == letter1 ? putchar('|') : putchar(' ');
            if(number_code[i][index[i]] == letter1) index[i]++;
            
            for(int j = 0; j < s; j++) putchar(' ');
            
            number_code[i][index[i]] == letter2 ? putchar('|') : putchar(' ');
            if(number_code[i][index[i]] == letter2) index[i]++;

            putchar(' ');
        }
        putchar('\n');
    }
}

int main(){
    int s;
    long int n;
    scanf("%d %ld", &s, &n); // Input

    while(s != 0 && n != 0){
        int number_size = getNumberLength(n);
        // printf("Number Size: %d\n", number_size);
        
        if(number_size == 0){ // Number to calc display
            strcpy(number_code[0], "abcefg\0"); // 0
            number_size = 1;
        }else{
            long int n_copy = n;
            for(int i = 1; i <= number_size; i++, n_copy /= 10)
                strcpy(number_code[number_size - i], numberToString(n_copy % 10));
        }

        // Last index array
        int number_index[NUMBER_LENGTH];
        for(int i = 0; i < NUMBER_LENGTH; i++)
            number_index[i] = 0;

        // Individual
        // for(int i = 0; i < number_size; i++)
        //     printf("[%d]: %s\n", i, number_code[i]);
        
        // Print calc
        printRow(number_index, 'a', s, number_size); // a
        printColumn(number_index, 'b', 'c', s, number_size); // b c
        printRow(number_index, 'd', s, number_size); // d
        printColumn(number_index, 'e', 'f', s, number_size); // e f
        printRow(number_index, 'g', s, number_size); // g
        putchar('\n');

        scanf("%d %ld", &s, &n); // Input
    }
    return 0;
}