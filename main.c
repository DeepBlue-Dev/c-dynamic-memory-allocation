#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define MAX_REGION_SIZE 10000L   //  in bytes; max 10 KB of the 32KB
#define MALLOC_AMNT 5   //  the amount of integers that gets allocated per time malloc is called;

unsigned int generate_fake_sensor_data(void);
void update_time(time_t* time);

int main() {
    clock_t start_time, end_time;
    time_t now;
    //  initialize the random number generator
    srand((unsigned int) time(NULL));

    time(&now); //  update the now variable
    printf("program started at: %s\n", ctime(&now));
    start_time = clock();   //  Get the current time
    long block_size = 0;
    int* ptr = (int*)malloc(MALLOC_AMNT * sizeof(int));

    while(block_size < MAX_REGION_SIZE){

    }


    end_time = clock();
    time(&now);
    printf("program ended at: %s", ctime(&now));
    printf("execution took: %d ms", end_time - start_time);

    return 0;
}

unsigned int generate_fake_sensor_data(void){
    //  I have a 10 bit ADC -> 1024 is max
    return (rand() % 1025);
}


