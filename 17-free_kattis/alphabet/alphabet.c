#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 50 + 1

int main(){
    char string[MAX_STRING_LENGTH];
    scanf("%s", string);

    int deletions = 0;
    int max_index;
    char lesser_letter = string[0];
    for(int i = 1; i < strlen(string); i++){
        if(string[i] <= string[i - 1])
            deletions++;
        else
            max_index = i;
        if(string[i] < lesser_letter){
            deletions = i;
            lesser_letter = string[i];
        }
    }

    printf("Deletions: %d. Insertions: %d\n", deletions, string[max_index] - 'a');
    printf("%d\n", deletions + string[max_index] - 'a');

    return 0;
}