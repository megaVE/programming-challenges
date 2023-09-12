// Autor: Vinícius Eduardo de Souza Honório
// Matrícula: 2021.1.08.024

#include <stdio.h>

long solve(long x){
    for(long y = 1; ; y++){
        if(x == 1)
            return y;
        else{
            if(x % 2 != 0)
                x = 3 * x + 1;
            else
                x = x / 2;
        }
    }
}

int main (){
    int i, j;

    while(scanf("%d %d", &i, &j) != EOF){
        long max = 0;
        int aux = 0;

        if(i > j){
            aux = i;
            i = j;
            j = aux;
        }

        for(int count = i; count <= j; count++){
            long result = solve(count);
            if(result > max)
                max = result;
        }

        if(aux)
            printf("%d %d %ld\n", j, i, max);
        else
            printf("%d %d %ld\n", i, j, max);
    }
    return 0;
}