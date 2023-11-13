#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 50 + 1

int main(){
    char string[MAX_STRING_LENGTH];
    scanf("%s", string);

    int deletions = 0;
    int max_index;
    for(int i = 1; i < strlen(string); i++){
        if(string[i] <= string[i - 1])
            deletions++;
        else
            max_index = i;
    }

    printf("Deletions: %d. Insertions: %d\n", deletions, string[max_index] - 'a');
    printf("%d\n", deletions + string[max_index] - 'a');

    return 0;
}