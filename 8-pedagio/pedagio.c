#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HOURS 24
#define LICENCE_LENGTH 20
#define STATUS_LENGTH 9
#define MAX_RECORDS 1000
#define EXIT "exit"
#define ENTER "enter"
#define BILL_TAX 200
#define TRAVEL_TAX 100

struct car_register{ // Struct for each registered car
    char licence_number[LICENCE_LENGTH+1];
    int month;
    int day;
    int hour;
    int minute;
    char status[STATUS_LENGTH+1];
    int kilometer;
};

int absolute(int a){
    if(a > 0)
        return a;
    return -1 * a;
}

void strcharcat(char * string, char append){
    int length = strlen(string);
    for(int i = length; i > 0; i--)
        string[i] = string[i-1];
    string[0] = append;
    string[length+1] = '\0';
}

int getLicenceNumberAmount(struct car_register * registers, int * position, int length){
    char current_licence_number[LICENCE_LENGTH+1];
    int counter = 0;

    strcpy(current_licence_number, registers[0].licence_number);
    for(int i=1; i < length; i++){
        if(strcmp(registers[i].licence_number, current_licence_number)){
            position[counter] = i-1;
            strcpy(current_licence_number, registers[i].licence_number);
            counter++;
        }
    }
    position[counter] = length-1;
    
    return counter+1;
}

int compareTime(const void * p, const void * q){ // Auxiliar function for the qsort method
    char * a = ((struct car_register*)p)->licence_number;
    int ad = ((struct car_register*)p)->day * 10000;
    int ah = ((struct car_register*)p)->hour * 100;
    int am = ((struct car_register*)p)->minute;
    char * b = ((struct car_register*)q)->licence_number;
    int bd = ((struct car_register*)q)->day * 10000;
    int bh = ((struct car_register*)q)->hour * 100;
    int bm = ((struct car_register*)q)->minute;
    return ((*a * 1000000 + ad + ah + am)-(*b * 1000000 + bd + bh + bm));
}

int main(void){
    int cases;
    scanf("%d", &cases); // Cases
    getchar(); // Buffer
    getchar(); // Empty Space

    for(int i=0; i < cases; i++){ // For Each Case
        int hours_cost[HOURS];
        for(int j=0; j < HOURS; j++){
            scanf("%d", &hours_cost[j]); // Hour Price Input
        }
        getchar();

        struct car_register records[MAX_RECORDS];
        int size_record = 0;
        char aux = getchar();
        while(aux != EOF && aux != '\0' && aux != '\n' && aux != ' '){
            scanf("%s %d:%d:%d:%d %s %d",
                records[size_record].licence_number,
                &records[size_record].month,
                &records[size_record].day,
                &records[size_record].hour,
                &records[size_record].minute,
                records[size_record].status,
                &records[size_record].kilometer); // Vehicle Report Input
            getchar(); // Buffer
            strcharcat(records[size_record].licence_number, aux);

            aux = getchar();
            size_record++;
        }
        qsort(records, size_record, sizeof(struct car_register), compareTime); // Sort by time and licence
        
        char previous_licence[LICENCE_LENGTH+1];
        strcpy(previous_licence, records[0].licence_number);
        
        char previous_status[STATUS_LENGTH+1];
        strcpy(previous_status, records[0].status);
        
        int initial_time = records[0].hour;
        int previous_kilometer = records[0].kilometer;
        
        int bill = BILL_TAX;
        for(int j=1; j < size_record; j++){
            if(strcmp(previous_licence, records[j].licence_number)){ // Different licence -> ends the previous bill
                if(bill != BILL_TAX)
                    printf("%s $%d.%d\n", previous_licence, bill / 100, bill % 100);
                strcpy(previous_licence, records[j].licence_number);
                strcpy(previous_status, records[j].status);
                previous_kilometer = records[j].kilometer;
                initial_time = records[j].hour;
                bill = BILL_TAX;
            } else if(!strcmp(ENTER, records[j].status)){ // Same licence, has entered -> saves the info
                strcpy(previous_licence, records[j].licence_number);
                strcpy(previous_status, records[j].status);
                previous_kilometer = records[j].kilometer;
                initial_time = records[j].hour;
            } else { // Same licence, has exited
                if(!strcmp(ENTER, previous_status))
                    bill += (TRAVEL_TAX + hours_cost[initial_time] * absolute(records[j].kilometer - previous_kilometer));
            }
        }
        if(bill != BILL_TAX)
            printf("%s $%d.%d\n", previous_licence, bill / 100, bill % 100);
        putchar('\n');
    }
    return 0;
}