#include <stdio.h>

long int reverse(long int number){ // Reverses an integer number
    for(long int result=0; ; number = number / 10){
        if(number == 0)
            return result;
        result = result * 10 + number % 10;
    }
}

int main(){
    int cases;
    scanf("%d", &cases);

    for(int i=0; i < cases; i++){
        long int input;
        scanf("%ld", &input);

        input += reverse(input); // 1st iteration
        for(int iterations=1; ; iterations++){
            if(input == reverse(input)){ // Checks whether the number is a palindrome
                printf("%d %ld\n", iterations, input);
                break;
            }
            input += reverse(input);
        }
    }
    return 0;
}