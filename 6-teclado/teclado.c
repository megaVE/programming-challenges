#include <stdio.h>
#include <string.h>

#define QWERTY "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./" // qwerty keyboard layout
#define SIZE strlen(QWERTY)

char decode(char letter){ // decodes the readen input
    if(letter == '\n')
        return '\n';
    for(int i=0; i < SIZE; i++)
        if(letter == QWERTY[i])
            return QWERTY[i-1];
    return ' ';
}

int main(){
    char input[256];
    char output[256];
    
    while(fgets(input, 256, stdin)){ // In
        int i=0;
        for(; input[i] != '\0'; i++) // Decodes the message
            output[i] = decode(input[i]);
        output[i] = '\0';

        printf("%s", output); // Out
    }
    putchar('\n');
    return 0;
}