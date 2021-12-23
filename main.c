#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_MEMORY 10000L   //  in bytes; max 10 KB of the 32KB
unsigned int generate_fake_sensor_data(void);

int main() {
    //  initialize the random number generator
    srand((unsigned int) time(NULL));
    //  get local time
    time_t now = time(0);
    printf("program started at: %s\n", ctime(&now));

    return 0;
}

unsigned int generate_fake_sensor_data(void){
    //  i have a 10 bit ADC -> 1024 is max
    return (rand() % 1025);
}
