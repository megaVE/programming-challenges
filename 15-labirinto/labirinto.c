#include <stdio.h>

#define MAX_W 75
#define MAX_H 75

struct node{
    int color; // 0 = blue. 1 = violet

    int top_left; // -1 = doesn't have. 0 = blocked. 1 = available
    int bottom_left;
    int top_right;
    int bottom_right;
};

void startNode(struct node * new_node, int color){
    new_node->color = color;
    new_node->top_left = -1;
    new_node->top_right = -1;
    new_node->bottom_left = -1;
    new_node->bottom_right = -1;
}

int main(){
    int w, h;
    scanf("%d %d\n", &w, &h);
    printf("w: %d, h: %d\n", w, h);

    char maze[MAX_H][MAX_W + 1];
    for(int i = 1; w != 0 || h != 0; i++, scanf("%d %d\n", &w, &h)){
        for(int j=0; j < h; j++){
            scanf("%s", maze[j]);
            printf("%s\n", maze[j]);
        }

        struct node graph[MAX_H * 2 - 1][MAX_W];
        for(int j = 0; j < w - 1; j++) // First Blue Line
            startNode(&graph[0][j], 0);

        for(int j = 1; j < h * 2 - 1; j++){
            for(int k = 0; k < w; k++){ // Violet Line
                startNode(&graph[j][k], 1);

                if(maze[j][k] == '/'){
                    graph[j][k].top_left = 0;
                    graph[j][k].top_right = 1;
                }
                else{
                    graph[j][k].top_left = 1;
                    graph[j][k].top_right = 0;
                }
            }
            graph[j][0].top_left = -1;
            graph[j][w - 1].top_right = -1;
            j++;

            for(int k = 0; k < w - 1; k++){ // Blue Line
                startNode(&graph[j][k], 0);

                if(maze[j][k] == '/')
                    graph[j][k].top_left = 0;
                else
                    graph[j][k].top_left = 1;

                if(maze[j][k + 1] == '/')
                    graph[j][k].top_right = 1;
                else
                    graph[j][k].top_right = 0;
            }
        }

        for(int j = 0; j < h * 2 - 1; j++){
            for(int k = 0; k < w-1; k++){
                printf("%d [%d %d %d %d] ", graph[j][k].color, graph[j][k].top_left, graph[j][k].top_right, graph[j][k].bottom_left, graph[j][k].bottom_right);
            }
            if(j % 2 != 0) printf("%d ", graph[j][w-1].color);
            putchar('\n');
        }
        
        int cycles = 0;
        int longest_cycle = 0;

        printf("Maze #%d:\n", i);
        if(cycles)
            printf("%d Cycles; the longest has length %d.\n\n", cycles, longest_cycle);
        else
            puts("There are no cycles.\n");

        scanf("%d %d\n", &w, &h);
        printf("w: %d, h: %d\n", w, h);
    }
    return 0;
}