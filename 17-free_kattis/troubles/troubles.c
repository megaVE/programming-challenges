#include <stdio.h>
#include <string.h>

// Timeout Issues

#define MAX_SUBMITIONS 100000
#define MAX_RESULT_LENGTH 15 + 1

struct answer{
    char text[MAX_RESULT_LENGTH];
    int counter;
};

int min(int a, int b){ return (a < b) ? a : b; }

int answerIndex(struct answer * list, int list_length, char * answer){
    for(int i = 0; i < list_length; i++)
        if(strcmp(list[i].text, answer) == 0) return i;

    return -1;
}

void addToList(struct answer * list, int * length, char * answer){
    int answer_index = answerIndex(list, *length, answer);
    
    if(answer_index == -1){
        // printf("Answer %s is not included\n", answer);
        strcpy(list[*length].text, answer);
        list[*length].counter = 1;
        (*length)++;
        // printf("Final Length: %d\n", *length);
    }else{
        // printf("Answer %s is already included\n", answer);
        list[answer_index].counter++;
    }
    // printf("Length: %d\n", *length);
}

int main(){
    int n;
    scanf("%d", &n); // Submissions
    // printf("Submits: %d\n", n);

    struct answer domjudge_submissions[MAX_SUBMITIONS]; // DOMjudge
    int domjudge_length = 0;

    char aux[MAX_RESULT_LENGTH];

    for(int i = 0; i < n; i++){
        scanf("%s", aux);
        addToList(domjudge_submissions, &domjudge_length, aux);
    }
    
    struct answer kattis_submissions[MAX_SUBMITIONS]; // Kattis
    int kattis_length = 0;
    
    for(int i = 0; i < n; i++){
        scanf("%s", aux);
        addToList(kattis_submissions, &kattis_length, aux);
    }

    int result = 0;

    for(int i = 0; i < domjudge_length; i++){
        int answer_index = answerIndex(kattis_submissions, kattis_length, domjudge_submissions[i].text);
        // printf("Current Checked Answer: %s\n", domjudge_submissions[i].text);
        
        if(answer_index != -1){
            // puts("Included on Both");
            // printf("DOM: %d. Kattis: %d\n", domjudge_submissions[i].counter, kattis_submissions[answer_index].counter);
            result += min(domjudge_submissions[i].counter, kattis_submissions[answer_index].counter);
        }
    }

    printf("%d\n", result);

    return 0;
}