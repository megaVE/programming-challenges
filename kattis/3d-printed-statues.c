// Source:
// https://open.kattis.com/problems/3dprinter

#include <stdio.h>

int main(){
    int input;
    scanf("%d", &input);

    int days=0;

    for(int aux=1; aux < input; days++)
        aux = aux * 2;

    printf("%d", days+1);
}