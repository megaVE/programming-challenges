// Source:
// https://open.kattis.com/contests/dr4gz5/problems/skruop

#include <stdio.h>

int main(){
    int inInit;
    int volume = 7;
    char request[10];
    scanf("%d", &inInit);
    for(int i = 0; i < inInit; i++){
        fgets(request, sizeof(request), stdin);
        if(request[5] == 'o' && volume < 10)
            volume++;
        else if(request[5] == 'n' && volume > 0)
            volume--;
    }
    printf("%d\n", volume);
}