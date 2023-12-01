#include <stdio.h>
#include <math.h>

int main(){
    float a, b, c;
    while(scanf("%f %f %f", &a, &b, &c) != EOF){
        float p = (a + b + c) / 2;
        float area = sqrt(p * (p - a) * (p - b) * (p - c));
        float r = (2 * area) / (a + b + c);
        
        printf("The radius of the round table is: %.3f\n", r);
    }
    return 0;
}