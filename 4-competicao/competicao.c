#include <stdio.h>
#include <string.h>

#define PENALTY 20
#define PLAYERS 100
#define PROBLEMS 9

struct player{ // Contestants' Struct
    int id;
    int time;
    int score;
    int problems[PROBLEMS];
    int problemsPenalties[PROBLEMS];
};

struct player contestants[PLAYERS];

void bubbleSort(int start, int end, char type){ // BubbleSort ordering Struct Array
    struct player aux;
    if(type == 's'){ // Reverse Sort by Score
        for(int i=start; i < end-1; i++)
            for(int j=start; j < end-i-1; j++)
                if(contestants[j].score < contestants[j+1].score){
                    aux = contestants[j];
                    contestants[j] = contestants[j+1];
                    contestants[j+1] = aux;
                }
    } else if(type == 't'){ // Sort by Time
        for(int i=start; i < end-1; i++)
            for(int j=start; j < end-i-1; j++)
                if(contestants[j].time > contestants[j+1].time){
                    aux = contestants[j];
                    contestants[j] = contestants[j+1];
                    contestants[j+1] = aux;
                }
    }
}

int main(){
    char entry[20];
    int firstEntry = 1, countEntry = 0;
    int contestant, problem, time;
    char answerType;

    scanf("%d", &firstEntry); // In. Number of Cases
    while(getchar() != '\n');

    getchar();
    
    for(;countEntry < firstEntry;countEntry++){
        for(int i=0; i < PLAYERS; i++){ // Resets contestants array
            contestants[i].id = i;
            contestants[i].time = -1; // -1 = Unavailable participant
            contestants[i].score = 0;
            for(int j=0; j < PROBLEMS; j++){
                contestants[i].problems[j] = 0;
                contestants[i].problemsPenalties[j] = 0;
            }
        }

        while(fgets(entry, 20, stdin)){
            if(entry[0] == '\0' || entry[0] == '\n') // Checks for Final Input
                break;
            sscanf(entry, "%d %d %d %c", &contestant, &problem, &time, &answerType);
            problem--;
            if(answerType == 'C'){ // Correct Answer
                if(contestants[contestant].time == -1) // Enables the Contestant
                    contestants[contestant].time = 0;
                if(contestants[contestant].problems[problem] == 0){ // Defines Score if Not Solved
                    contestants[contestant].problems[problem] = 1;
                    contestants[contestant].time += (time + contestants[contestant].problemsPenalties[problem] * PENALTY);
                    contestants[contestant].score++;
                }
            } else if(answerType == 'I'){
                if(contestants[contestant].time == -1) // Enables the Contestant
                    contestants[contestant].time = 0;
                if(contestants[contestant].problems[problem] == 0) // Adds Penalty if Not Solved
                    contestants[contestant].problemsPenalties[problem]++;
            } else
                if(contestants[contestant].time == -1) // Enables the Contestant
                    contestants[contestant].time = 0;
        }

        bubbleSort(0, PLAYERS, 's'); // Score Sort with Bubble Sort

        int chain = 0;
        int last = 0;
        int lastScore = contestants[0].score;
        for(int i=1; i < PLAYERS; i++){
            if(contestants[i].score != lastScore){ // Ends chain and continue
                if(chain == 1){
                    bubbleSort(last, i,'t'); // Time Sort with Bubble Sort
                    chain = 0;
                }
                last = i;
                lastScore = contestants[i].score;
            }
            else{
                chain = 1;
            }
        }

        if(countEntry != 0) // Out
            printf("\n");
        for(int i=0; i < PLAYERS; i++){
            if(contestants[i].time > -1)
                printf("%d %d %d\n", contestants[i].id, contestants[i].score, contestants[i].time);
    }
    }
    return 0;
}