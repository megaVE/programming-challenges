// Source:
// https://open.kattis.com/problems/99problems

#include <stdio.h>

int main(){
    int input;
    scanf("%d", &input);

    if(input % 100 < 49)
        input -= 1 + input % 100;
    else
        input += 99 - (input % 100);

    if(input < 0)
        input+=100;

    printf("%d\n", input);

    return 0;
}