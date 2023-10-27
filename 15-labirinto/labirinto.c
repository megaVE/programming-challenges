#include <stdio.h>

#define MAX_W 75
#define MAX_H 75

int main(){
    int w, h;
    scanf("%d %d\n", &w, &h);
    
    for(int i = 1; w != 0 || h != 0; i++, scanf("%d %d\n", &w, &h)){
        for(int j=0; j < h; j++)
            ; // scanf("%s", );
        
        int cycles = 0;
        int longest_cycle = 0;

        printf("Maze #%d:\n", i);
        if(cycles)
            printf("%d Cycles; the longest has length %d.\n\n", cycles, longest_cycle);
        else
            puts("There are no cycles.\n");
    }
    return 0;
}