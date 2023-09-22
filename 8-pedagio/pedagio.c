#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HOURS 24
#define LICENCE_LENGTH 20
#define STATUS_LENGTH 9
#define MAX_RECORDS 1000
#define EXIT "exit"
#define ENTER "enter"

struct car_register{ // Struct for each registered car
    char licence_number[LICENCE_LENGTH+1];
    int month;
    int day;
    int hour;
    int minute;
    char status[STATUS_LENGTH+1];
    int kilometer;
};

struct register_output{ // Struct for each registered car output
    char licence_number[LICENCE_LENGTH+1];
    int bill;
};

int absolute(int a){
    if(a > 0)
        return a;
    return -1 * a;
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

// qsort functions

int compareTime(const void * p, const void * q){ // Auxiliar function for the qsort method
    char * a = ((struct car_register*)p)->licence_number;
    char * b = ((struct car_register*)q)->licence_number;
    int ad = ((struct car_register*)p)->day;
    int ah = ((struct car_register*)p)->hour;
    int am = ((struct car_register*)p)->minute;
    int bd = ((struct car_register*)q)->day;
    int bh = ((struct car_register*)q)->hour;
    int bm = ((struct car_register*)q)->minute;
    return ((*a * 1000000 + ad * 10000 + ah * 100 + am)-(*b * 1000000 + bd * 10000 + bh * 100 + bm));
}

int main(void){
    int cases;
    scanf("%d", &cases); // Cases
    getchar();
    printf("%d Cases\n", cases);
    getchar(); // Empty Space
    printf("Empty Space\n");
    printf("-------------------\n");

    for(int i=0; i < cases; i++){ // For Each Case
        int hours_cost[HOURS];
        for(int j=0; j < HOURS; j++){
            scanf("%d", &hours_cost[j]); // Hour Price Input
            printf("%d ", hours_cost[j]);
        }
        putchar('\n');
        printf("-------------------\n");

        struct car_register records[MAX_RECORDS];
        int size_record = 0;
        scanf("%s", records[size_record].licence_number);
        while(records[size_record].licence_number[0] != '\0'){
            scanf("%d:%d:%d:%d %s %d\n",
                &records[size_record].month,
                &records[size_record].day,
                &records[size_record].hour,
                &records[size_record].minute,
                records[size_record].status,
                &records[size_record].kilometer); // Vehicle Report Input

            printf("%s %d:%d:%d:%d %s %d\n",
                records[size_record].licence_number,
                records[size_record].month,
                records[size_record].day,
                records[size_record].hour,
                records[size_record].minute,
                records[size_record].status,
                records[size_record].kilometer);

            size_record++;
            scanf("%s", records[size_record].licence_number);
        }
        printf("-------------------\n");
        printf("number of records: %d\n", size_record);
        printf("-------------------\n");

        qsort(records, size_record, sizeof(struct car_register), compareTime);
        
        struct register_output output[MAX_RECORDS];
        int count_licence_number = 0;
        int licence_number_position[500];
        count_licence_number = getLicenceNumberAmount(records, licence_number_position, size_record);
        printf("different licence numbers: %d\n", count_licence_number);
        for(int j=0; j < count_licence_number; j++)
            printf("licence #%d: %d\n", j, licence_number_position[j]);

        printf("-------------------\n");

        char current_licence[LICENCE_LENGTH+1];
        char previous_status[STATUS_LENGTH+1];
        int bill = 2;
        int previous_time = records[0].hour;
        int previous_kilometer = records[0].kilometer;
        strcpy(current_licence, records[0].licence_number);
        strcpy(previous_status, records[0].status);
        for(int j=1; j < size_record; j++){
            if(strcmp(current_licence, records[i].licence_number) != 0){
                // strcpy(current_licence);
            }
            if(strcmp(previous_status, records[i].status) != 0 && strcmp(current_licence, records[i].licence_number) == 0){
                bill += 1 + (absolute(records[i].kilometer - previous_kilometer) * hours_cost[previous_time]);
                previous_time = records[i].hour;
                previous_kilometer = records[i].kilometer;
            }

        }

        printf("-------------------\n");

        for(int k=0; k < size_record; k++)
            printf("%s %d:%d:%d:%d %s %d\n",
                records[k].licence_number,
                records[k].month,
                records[k].day,
                records[k].hour,
                records[k].minute,
                records[k].status,
                records[k].kilometer);

        printf("-------------------\n");


        // for(int k=0; k < size_record; k++)
        //     printf("%s %d:%d:%d:%d %s %d\n",
        //         records[k].licence_number,
        //         records[k].month,
        //         records[k].day,
        //         records[k].hour,
        //         records[k].minute,
        //         records[k].status,
        //         records[k].kilometer);

        // for(int j=0; j < count_licence_number; j++)
            // printf("%s $%d:%d\n", output[j].licence_number, (output[j].bill / 100) * 100, output[j].bill % 100);
    }
    return 0;
}