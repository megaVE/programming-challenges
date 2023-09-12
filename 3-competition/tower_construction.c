// Source:
// https://open.kattis.com/contests/dr4gz5/problems/tornbygge

#include <stdio.h>

int main(){
    int inLen, size;
    int towers = 0;
    scanf("%d", &inLen);
    if(inLen > 0){
        scanf("%d", &size);
        towers = 1;
    }
    for(int i = 1; i < inLen; i++){
        int new;
        scanf("%d", &new);
        if(new > size)
            towers++;
        size = new;
    }
    printf("%d\n", towers);
}