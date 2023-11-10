#include <stdio.h>
#include <string.h>

#define X_LENGTH 10000 + 1
#define Z_LENGTH 100 + 1

int checkSubsequence(char * string, char * subsequence, int * current_subsequence, int length){ // Checks if the substring is a subsequence
    char current_subsequence_string[Z_LENGTH];

    for(int i = 0; i < length; i++)
        current_subsequence_string[i] = string[current_subsequence[i]];
    current_subsequence_string[length] = '\0';
    
    // printf("[%d] Expected: %s. Get: %s\n", length, subsequence, current_subsequence_string);

    return (strcmp(current_subsequence_string, subsequence) == 0) ? 1 : 0;
}

void nextSubsequence(char * string, int string_length, int * current_subsequence, int subsequence_length){
    for(int i = 1; i <= subsequence_length; i++){
        if(current_subsequence[subsequence_length - i] < string_length - i){
            current_subsequence[subsequence_length - i]++;
            break;
        } else
            current_subsequence[subsequence_length - i] = -1;
    }

    if(current_subsequence[0] < 0) return;
    
    for(int i = 0; i < subsequence_length; i++)
        current_subsequence[i] = (current_subsequence[i] < 0) ? current_subsequence[i - 1] + 1 : current_subsequence[i];
}

int getSubsequences(char * string, int string_length, char * subsequence, int subsequence_length, int * current_subsequence){
    int subsequences = 0;

    while(current_subsequence[0] >= 0){
        // puts("Number Sequence: ");
        // for(int i = 0; i < subsequence_length; i++)
        //     printf("%d, ", current_subsequence[i]);
        // putchar('\n');

        int is_subsequence = checkSubsequence(string, subsequence, current_subsequence, subsequence_length);

        if(is_subsequence){
            // puts("+ One more subsequence");
            subsequences++;
        }

        nextSubsequence(string, string_length, current_subsequence, subsequence_length);
    }
    // printf("subsequences: %d\n", subsequences);
    return subsequences;
}

int main(){
    int cases;
    scanf("%d", &cases); // Cases
    // printf("Cases: %d\n", cases);

    for(int i = 0; i < cases; i++){
        char x[X_LENGTH];
        scanf("%s", x); // Large String
        // printf("String[%ld]: %s\n", strlen(x), x);

        char z[Z_LENGTH];
        scanf("%s", z); // Sequence
        // printf("Subsequence[%ld]: %s\n", strlen(z), z);

        int current_subsequence[Z_LENGTH - 1];
        for(int j = 0; j < strlen(z); j++)
            current_subsequence[j] = j; // Current Sequence Array

        int subsequences = getSubsequences(x, strlen(x), z, strlen(z), current_subsequence);
        printf("%d\n", subsequences);
    }
    return 0;
}