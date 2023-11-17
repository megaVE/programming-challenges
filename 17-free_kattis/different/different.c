#include <stdio.h>
#include <string.h>

#define MAX_NUMBER_SIZE 16 + 1

int isLargerThan(char * number1, char * number2){ // Compares two string numbers
    if(strlen(number1) < strlen(number2)) return 0; // 1 is shorter than 2
    if(strlen(number1) > strlen(number2)) return 1; // 1 is longer than 2

    for(int i = 0; i < strlen(number1); i++){
        if(number1[i] < number2[i]) return 0; // 1 is lower than 1
        if(number1[i] > number2[i]) return 1; // 1 is higher than 2
    }
    return 0; // both numbers are equal
}

void setLeftZeros(char * number, int length){ // Equals a number cases to the larger one
    char left_zeros[MAX_NUMBER_SIZE];
    
    for(int i = 0; i < length - strlen(number); i++) left_zeros[i] = '0';
    left_zeros[length - strlen(number)] = '\0';
    
    strcat(left_zeros, number); // inserts the zeros before the number
    strcpy(number, left_zeros);
}

void calculateDifference(char * number1, char * number2, char * result){ // Calculates the difference between two string numbers
    int carry = 0;
    for(int i = strlen(number1) - 1, carry; i >= 0; i--){
        if(carry){ // Consumes the carry
            number2[i]++;
            carry--;
        }

        result[i] = number1[i] - number2[i] + '0';

        if(result[i] < '0'){ // Stores the carry
            carry++;
            result[i] += 10;
        }
    }
    result[strlen(number1)] = '\0';
}

int main(){
    char number1[MAX_NUMBER_SIZE], number2[MAX_NUMBER_SIZE]; // Input
    
    while(scanf("%s %s", number1, number2) != EOF){
        int is_number1_larger = isLargerThan(number1, number2);

        char result[MAX_NUMBER_SIZE];
        if(is_number1_larger){
            setLeftZeros(number2, strlen(number1));
            calculateDifference(number1, number2, result);
        }else{
            setLeftZeros(number1, strlen(number2));
            calculateDifference(number2, number1, result);
        }

        int i = 0;
        while(result[i] == '0') i++; // Skip difference's left zeros

        if(i == strlen(result)) putchar('0'); // If the difference is 0

        for(; i < strlen(result); i++) putchar(result[i]); // Prints the difference
        putchar('\n');
    }
    return 0;
}