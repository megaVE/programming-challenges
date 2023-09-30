#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100
#define MAX_FIBONACCI 500

char * resizeNumber(char * a, int new_size, char * aux){ // resizes a number stored as string
    int old_size = strlen(a);
    int difference = new_size - old_size;

    for(int i=0; i < old_size; i++){ // moves the digits aside according to the new_size difference to the original one
        aux[i + difference] = a[i];
    }
    aux[old_size + difference] = '\0';
    
    for(int i=0; i < difference; i++) // fills the first zero empty digits
        aux[i] = '0';
    
    return aux;
}

char * sum(char * a, char * b, char * aux){ // sums two numbers stored as strings
    int major = (strlen(a) > strlen(b)) ? strlen(a) : strlen(b);

    if(strlen(a) < major){ // a has less digits
        resizeNumber(a, major, aux);
        strcpy(a, aux);
    }

    if(strlen(b) < major){ // b has less digits
        resizeNumber(b, major, aux);
        strcpy(b, aux);
    }

    int buffer = 0;
    for(int i=major-1; i >= 0; i--){ // sums each number digit
        int aux_sum = (a[i] - '0') + (b[i] - '0') + buffer;
        aux[i+1] = aux_sum % 10 + '0';
        if(aux_sum > 9)
            buffer = 1;
        else
            buffer = 0;
    }
    if(buffer) // last buffer checking
        aux[0] = '1';
    else
        aux[0] = '0';
    aux[major+1] = '\0';
    
    if(aux[0] == '0'){ // removes the first empty digit
        for(int i=0; i < strlen(aux)-1; i++){
            aux[i] = aux[i+1];
        }
        aux[strlen(aux)-1] = '\0';
    }

    return aux;
}

char * greater(char * a, char * b){ // compares two numbers stored as strings and returns the greater one
    if(strlen(a) > strlen(b)) // a has more digits
        return a;

    if(strlen(b) > strlen(a)) // b has more digits
        return b;

    for(int i=0; i < strlen(a); i++){ // a and b have the same amount of digits
        if(a[i] > b[i])
            return a;

        if(b[i] > a[i])
            return b;
    }

    return a; // a equals b
}

char * fibonacci(int number, char * aux){ // Fibonacci recursive function
    char aux1[100] = "1";
    char aux2[100] = "1";
    
    for(int i=2; i <= number; i++){
        sum(aux1, aux2, aux); // aux = aux1 + aux2;
        strcpy(aux1, aux2); // aux1 = aux2;
        strcpy(aux2, aux); // aux2 = aux;
    }

    strcpy(aux, aux2);
    return aux;
}

int main(){
    char table[MAX_FIBONACCI][MAX_LENGTH+1];
    strcpy(table[0], "1"); // table[0] = 1;
    int table_length = 1;

    char aux[MAX_LENGTH+1];
    char a[MAX_LENGTH+1], b[MAX_LENGTH+1];
    for(scanf("%s %s", a, b); a[0] != '0' || b[0] != '0'; scanf("%s %s", a, b)){ // Input
        int result = 0;
                
        for(; !strcmp(greater(table[table_length-1], b), b); table_length++) // if(b >= table[table_length-1]) | Fills the Fibonacci's Table when needed
            strcpy(table[table_length], fibonacci(table_length+1, aux)); // table[table_length] = fibonacci(table_length+1, aux);

        for(int i=0; ; i++){ // Calculates the number of Fibonaccis between a and b
            if(!strcmp(greater(table[i], a), table[i])){ // if(table[i] >= a)
                if(!strcmp(greater(table[i], b), table[i])) // if(table[i] >= b)
                    if(strcmp(table[i], b)) // if(table[i] != b)
                        break;
                result++;
            }
        }

        printf("%d\n", result);
    }
    return 0;
}