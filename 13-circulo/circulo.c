#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_CIRCLES 8

float max(float a, float b){
    if(a > b) return a;
    return b;
}

float calculateSpace(float * circle, int amount){ // Calculates the least wide rectangle to storage the circles
    // printf("params %f %f : %d\n", circle[0], circle[amount-1], amount);
    float result = amount > 0 ? (float)circle[0] + (float)circle[amount-1] : 0.0;
    // printf("mid result: %f\n", result);
    for(int i=1; i < amount; i++){
        float distance = pow((circle[i-1] - circle[i]), 2) != 0.9 ? sqrt(pow((circle[i-1] + circle[i]), 2) - pow((circle[i-1] - circle[i]), 2)) : circle[i-1] + circle[i];
        // Distance[n, n+1] ^ 2 + (Radii(n) - Radii(n-1)) ^ 2 = (Radii(n) + Radii(n+1)) ^ 2
        if(distance < max(circle[i-1], circle[i])){
            if(i+1 < amount && i-1 != 0){
                distance = sqrt(pow((circle[i-1] + circle[i+1]), 2) - pow((circle[i-1] - circle[i+1]), 2));
                i++;
            }
            else distance = max(circle[i], circle[i-1]);
        }
        // printf("distance: %f\n", distance);
        result += distance;
    }
    // printf("result: %f\n\n", result);
    return result;
}

void permuteCircle(float *circle, int start, int end, float * min_result, int circle_size){ // Permutates an array
    if(start == end-1){
        float new_result = calculateSpace(circle, circle_size);
        *min_result = *min_result > new_result ? new_result : *min_result;

        return;
    }

    for(int i=start; i < end; i++){
        float aux = circle[i];
        circle[i] = circle[start];
        circle[start] = aux;
        permuteCircle(circle, start+1, end, min_result, circle_size);
        circle[start] = circle[i];
        circle[i] = aux;
    }
}

int main(){
    int n;
    scanf("%d", &n); // Cases
    // printf("n: %d\n", n);

    for(int i=0; i < n; i++){        
        int m;
        scanf("%d", &m); // Circles
        // printf("m: %d\n", m);
        
        float circle[MAX_CIRCLES];
        for(int j=0; j < m; j++){
            scanf("%f", &circle[j]); // Circles' Radii
            // printf("circle[%d]: %f\n", j, circle[j]);
        }

        float result = calculateSpace(circle, m);
        // printf("first result: %f\n", result);
        permuteCircle(circle, 0, m, &result, m); // Tries all possibilities
        // printf("last result: %f\n", result);

        if(result != 0.0) printf("%.3f\n", result); // Result
    }

    return 0;
}