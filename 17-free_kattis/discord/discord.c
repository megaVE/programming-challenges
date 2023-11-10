#include <stdio.h>

// Submit is causing compile errors

#define MAX_ARRAY_SIZE 100

int maxChange(int number){
    int max_digit = 1;
    for(;; max_digit *= 10)
        if(number / max_digit == 0) break;
    // Example: number = 81. max_digit = 100. return = 91
    return number - (number / (max_digit / 10) * (max_digit / 10)) + (max_digit - max_digit / 10);
}

int minChange(int number){
    if(number < 10) return 0;
    int max_digit = 1;
    for(;; max_digit *= 10)
        if(number / max_digit == 0) break;
    // Example: number = 81. max_digit = 100. return = 11
    return number - (number / (max_digit / 10) * (max_digit / 10)) + (max_digit / 10);
}

int main(){
    int n;
    if(scanf("%d\n", &n)); // Array size
    // printf("Array Size: %d\n", n);

    int array[MAX_ARRAY_SIZE]; // Array
    for(int i = 0; i < n; i++){
        if (scanf("%d", &array[i])); // Array elements
        // printf("Array[%d]: %d\n", i, array[i]);
    }

    int has_solution = 0;

    for(int i = 0; i < n - 1; i++){
        // printf("number: %d. max_change: %d. next_number: %d\n", array[i], maxChange(array[i]), array[i + 1]);
        if(maxChange(array[i]) > array[i + 1]){
            // puts("solvable");
            array[i] = maxChange(array[i]);
            has_solution = 1;
            break;
        }
    }

    for(int i = n - 1; i >= 0 && !has_solution; i--){
        // printf("number: %d. min_change: %d. previous_number: %d\n", array[i], minChange(array[i]), array[i - 1]);
        if(minChange(array[i]) < array[i - 1]){
            // puts("solvable");
            array[i] = minChange(array[i]);
            has_solution = 1;
            break;
        }
    }

    if(has_solution){
        printf("%d", array[0]);
        for(int i = 1; i < n; i++)
            printf(" %d", array[i]);
        putchar('\n');
    } else
        puts("impossible");
    
    return 0;
}