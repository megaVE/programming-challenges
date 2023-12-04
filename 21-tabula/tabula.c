#include <stdio.h>
#include <math.h>

int main(){
    float a, b, c;
    while(scanf("%f %f %f", &a, &b, &c) != EOF){
        float p = (a + b + c) / 2;
        float area = (p > 0.0) ? sqrt(p * (p - a) * (p - b) * (p - c)) : 0.0;
        float r = (p > 0.0) ? (2 * area) / (a + b + c) : 0.0;
        
        printf("The radius of the round table is: %.3f\n", r);
    }
    return 0;
}