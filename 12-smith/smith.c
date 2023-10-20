#include <stdio.h>
#include <math.h>

// #define PRIME_BETWEEN 79000
#define PRIME_BETWEEN 790000

long int prime_list[PRIME_BETWEEN];
int prime_list_length = 1;

int isPrime(long int number){ // Checks if a number is prime
    if(number % 2 == 0) return 0;
    
    // printf("number: %ld\n", number);
    number = (long int)sqrt((double)number);
    // printf("square root: %ld\n", number);
    for(long int i = 3; i < number-1; i += 2)
        if(number % i == 0) return 0;
    return 1;
}

long int nextPrime(long int number){ // Finds the next prime number greater than the input
    for(long int i = number+1; 1; i++)
        if(isPrime(i)) return i;
}

int inPrimeList(long int number){ // Checks if a number is in the prime array
    for(int i=0; prime_list[i] <= number; i++)
        if(prime_list[i] == number) return 1;
    return 0;
}

int sumDigits(long int number){ // Sums all the digits of a number
    int sum = 0;
    long int aux = number;
    for(; number > 0; number /= 10)
        sum += number % 10;
    // printf("sum %ld = %d\n", aux, sum);
    return sum;
}

int decomposePrime(long int number){
    int result = 0;
    for(int i = 0; prime_list[i] <= number; i++)
        if(number % prime_list[i] == 0){
            // printf("%ld decomposed\n", prime_list[i]);
            number /= prime_list[i];
            result += sumDigits(prime_list[i]);
            i = -1;
        }
    return result;
}

// int decomposePrime(long int number){
//     int result = 0;
//     for(int i = 2; i <= number; nextPrime(i))
//         if(number % i == 0){
//             // printf("%ld decomposed\n", i);
//             number /= i;
//             result += sumDigits(i);
//             i = -1;
//         }
//     return result;
// }

int isSmith(long int number){
    if(inPrimeList(number)) return 0;
    // printf("%d vs %d\n", decomposePrime(number), sumDigits(number));
    if(decomposePrime(number) == sumDigits(number)) return 1;
    return 0;
}

// int isSmith(long int number){
//     if(isPrime(number)) return 0;
//     // printf("%d vs %d\n", decomposePrime(number), sumDigits(number));
//     if(decomposePrime(number) == sumDigits(number)) return 1;
//     return 0;
// }


int main(){
    prime_list[0] = 2;

    int cases;
    scanf("%d", &cases);
    for(int i=0; i < cases; i++){
        long int number;
        scanf("%ld", &number);
        number++;
        
        while(number > prime_list[prime_list_length-1]){ // Fills the prime number list
            prime_list[prime_list_length++] = nextPrime(prime_list[prime_list_length-1]);
            // printf("added %ld\n", prime_list[prime_list_length-1]);
        }

        for(; 1; number++){ // Finds the closest Smith Number
            printf("testing %ld\n", number);
            if(isPrime(number))
                prime_list[prime_list_length++] = number;

            // printf("number %ld\n", number);
            if(isSmith(number)){
                printf("%ld\n", number); // Output
                break;
            }
        }


        puts("- PRIME LIST -\n");
        for(int i=0; i < prime_list_length; i++)
            printf("[%d], %ld\n", i, prime_list[i]);

        puts("- NUMBER -");
        printf("-> %ld\n", number);

        puts("- SUM DIGITS -\n");
        printf("-> %d\n", sumDigits(number));

        puts("- IS SMITH -\n");
        printf("-> %d\n", isSmith(number));

    }

    return 0;
}