#include <stdio.h>
#include <string.h>

#define ASCII_ALPHABET 97
#define KEYQUOTE "the quick brown fox jumps over the lazy dog"
// #define KEYQUOTE_WORDS {3,5,5,3,5,4,3,4,3}
#define ALPHABET_LENGTH 26
#define MAX_QUOTE_LENGTH 80
#define MAX_QUOTE_AMOUNT 100

char encodedQuotes[MAX_QUOTE_AMOUNT][MAX_QUOTE_LENGTH+1];

int checkCodeQuote(char * baseQuote, int * keyquoteWords){ // Checks if the readen quote matches the keyquote
    char splitedQuote[9][6]; // 9 words, 5 letters max length
    
    sscanf(baseQuote, "%s %s %s %s %s %s %s %s %s"
    , splitedQuote[0] // the
    , splitedQuote[1] // quick
    , splitedQuote[2] // brown
    , splitedQuote[3] // fox
    , splitedQuote[4] // jumps
    , splitedQuote[5] // over
    , splitedQuote[6] // the
    , splitedQuote[7] // lazy
    , splitedQuote[8] // dog
    );

    for(int i = 0; i < sizeof(keyquoteWords)+1; i++)
        if(strlen(splitedQuote[i]) != keyquoteWords[i])
            return 0;
    return 1;
}

void decodesAlphabet(char * alphabetSource, char * decodedAlphabet){ // Decodes the alphabet
    for(int i=0; i < strlen(alphabetSource); i++)
        if(alphabetSource[i] != ' ' && alphabetSource[i] != '\n' && alphabetSource[i] != '\0')
            decodedAlphabet[KEYQUOTE[i]-ASCII_ALPHABET] = alphabetSource[i];
}

void resetAlphabet(char * decodedAlphabet){ // Resets the decodedAlphabet
        for(int i = 0; i < ALPHABET_LENGTH; i++)
            decodedAlphabet[i] = '\0';
        decodedAlphabet[ALPHABET_LENGTH] = '\0';
}

int findLetter(char letter, char * decodesAlphabet){ // Decodes a letter
    for(int i=0; i < ALPHABET_LENGTH; i++)
        if(decodesAlphabet[i] == letter)
            return i;
    return -1;
}

int checkSolution(char * decodedAlphabet){ // Checks if the decoded quote fufilled the decodedAlphabet
    int letterList[ALPHABET_LENGTH];
    for(int i=0; i < ALPHABET_LENGTH; i++)
        letterList[i] = 0;
    for(int i=0; i < ALPHABET_LENGTH; i++){
        letterList[decodedAlphabet[i]-ASCII_ALPHABET] = 1;
        if(decodedAlphabet[i] == '\0' || decodedAlphabet[i] == '\n')
            return -1;
    }
    for(int i=0; i < ALPHABET_LENGTH; i++)
        if(!letterList[i])
            return -1;
    return 1;
}

void decodeQuote(char * decodedAlphabet, char * encodedQuote){ // Decodes a quote
    for(int i=0; i < strlen(encodedQuote); i++)
        if(encodedQuote[i] != ' ')
            encodedQuote[i] = findLetter(encodedQuote[i], decodedAlphabet)+ASCII_ALPHABET;
}

int main(){
    int cases;
    int keyquoteWords[] = {3,5,5,3,5,4,3,4,3};
    char input[MAX_QUOTE_LENGTH+1];
    char decodedAlphabet[ALPHABET_LENGTH+1];

    scanf("%d", &cases); // In. Cases
    while(getchar() != '\n');

    getchar(); // Empty line

    for(int i = 0; i < cases; i++){
        resetAlphabet(decodedAlphabet);

        int hasSolution = 0;
        int quotes = 0;
        while(fgets(input, MAX_QUOTE_LENGTH+1, stdin)){
            if(input[0] == '\0' || input[0] == '\n') // Checks for Final Input
                break;

            strcpy(encodedQuotes[quotes], input); // Adds quote to quote list
            quotes++;
            
            if(!hasSolution && checkCodeQuote(input, keyquoteWords)){ // Checks if the quote is the Keyquote
                decodesAlphabet(input, decodedAlphabet);
                if(hasSolution != -1)
                    hasSolution = checkSolution(decodedAlphabet); // Checks if the whole alphabet could be decoded
                if(!hasSolution)
                    resetAlphabet(decodedAlphabet);
            }
        }
        if(quotes == 0 && (input[0] == '\0' || input[0] == '\n'))
            getchar();

        if(hasSolution == 1){ // Prints the decoded quotes
            for(int j=0; j < quotes; j++){
                decodeQuote(decodedAlphabet, encodedQuotes[j]);
                encodedQuotes[j][strlen(encodedQuotes[j])-1] = '\0';
                printf("%s\n", encodedQuotes[j]);
            }
        } else {
            printf("No solution.\n");
        }
        if(i < cases-1)
            printf("\n");

    }
    return 0;
}