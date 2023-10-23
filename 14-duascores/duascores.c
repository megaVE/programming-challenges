#include <stdio.h>

#define MAX_NODES 200

int main(){
    int node_number;
    scanf("%d", &node_number); // Nodes
    while(node_number != 0){
        int nodes[MAX_NODES];
        for(int i=0; i < MAX_NODES; i++)
            nodes[i] = 0; // Nodes Color. 0 = no color | -1 = color 1 | 1 = color 2

        int edge_number;
        scanf("%d", &edge_number); // Edges
        
        int edges[MAX_NODES][MAX_NODES];
        for(int i=0; i < MAX_NODES; i++)
            for(int j=0; j < MAX_NODES; j++)
                edges[i][j] = 0;

        for(int i=0; i < edge_number; i++){
            int aux1, aux2;
            scanf("%d %d", &aux1, &aux2); // Edges Matrix
            edges[aux1][aux2] = 1;
            edges[aux2][aux1] = 1;
        }

        int current_neighbor[MAX_NODES] = {0};
        int current_neighbor_amount = 1;

        int next_neighbor[MAX_NODES];
        int next_neighbor_amount = 0;

        int bicolorable = 1;
        for(int i=0, current_color = 1; i < current_neighbor_amount && bicolorable; i++, current_color = (current_color == -1) ? 1 : -1){
            for(int j=0; j < node_number && bicolorable; j++) // Paints the node's neighbors
                if(edges[i][j] == 1 && j != i){
                    if(nodes[j] == 0){
                        nodes[j] = current_color;
                        next_neighbor[next_neighbor_amount++] = j;
                    } else if(nodes[j] != current_color)
                        bicolorable = 0;                        
                }
                
            current_neighbor_amount = next_neighbor_amount; // Refills the neighbor queue
            for(int j=0; j < next_neighbor_amount; j++)
                current_neighbor[j] = next_neighbor[j];

            next_neighbor_amount = 0;
        }
        bicolorable ? puts("BICOLORABLE.") : puts("NOT BICOLORABLE.");

        scanf("%d", &node_number);
    }
    return 0;
}