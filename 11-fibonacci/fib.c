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

    // printf("start: %s + %s\n", a, b);
    int buffer = 0;
    for(int i=major-1; i >= 0; i--){ // sums each number digit
        int aux_sum = (a[i] - '0') + (b[i] - '0') + buffer;
        // printf("a %c | b %c | aux_sum[%d]: %d\n", a[i], b[i], i, aux_sum);
        aux[i+1] = aux_sum % 10 + '0';
        if(aux_sum > 9)
            buffer = 1;
        else
            buffer = 0;
    }
    if(buffer)
        aux[0] = '1';
    else
        aux[0] = '0';
    aux[major+1] = '\0';
    // printf("aux mid result: %s\n", aux);
    
    if(aux[0] == '0'){ // removes the first empty digit
        for(int i=0; i < strlen(aux)-1; i++){
            aux[i] = aux[i+1];
        }
        aux[strlen(aux)-1] = '\0';
    }

    return aux;
}

char * subtract(char * a, char * b, char * aux){ // subtracts two numbers stored as strings
    // TODO
} 

char * greater(char * a, char * b){ // compares two numbers stored as strings
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

// int fibonacci(int number){ // Fibonacci recursive function
//     return (number < 3 ? 1 : fibonacci(number - 1) + fibonacci(number - 2));
// }

int main(){
    int result = 0;

    char a[MAX_LENGTH], b[MAX_LENGTH], aux[MAX_LENGTH];
    for(scanf("%s %s", a, b); a[0] != '0' || b[0] != '0'; scanf("%s %s", a, b)){
        printf("%s %s\n", a, b);
        printf("greater value: %s\n", greater(a, b));
        printf("%s + %s = %s\n", a, b, sum(a, b, aux));
        // char fib[100] = fibonacci(1);
        // for(int i=2; fib < b; i++){
            // if(fib >= a)
                // result++;
            // fib = fibonacci(i);
        // }
        // printf("%d\n", result);
    }
    return 0;
}