#include <stdio.h>

int main(){
    unsigned int input1, input2;
    for(scanf("%d %d", &input1, &input2); input1 != 0 || input2 != 0; scanf("%d %d", &input1, &input2)){
        int carry = 0;

        for(int buffer=0;input1 > 0 || input2 > 0; input1 /= 10, input2 /= 10){
            if(input1 % 10 + input2 % 10 + buffer > 9){
                carry++;
                buffer = 1;
            } else 
                buffer = 0;
        }

        if(!carry)
            printf("No carry operation.\n");
        else if(carry == 1)
            printf("1 carry operation.\n");
        else
            printf("%d carry operations.\n", carry);
    }

    return 0;
}