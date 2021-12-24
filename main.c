#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_REGION_SIZE 100L   //  in bytes; max 10 KB of the 32KB
#define MALLOC_AMNT 5   //  the amount of integers that gets allocated per time malloc is called;

//  struct to hold the info to the memory region
typedef struct Region{
	int* ptr;
	int element_count;
	unsigned long size;
}region;

int generate_fake_sensor_data(void);
void resize(region* p_mem);

int main() {
	clock_t start_time, end_time;
	time_t now;
	//  initialize the random number generator
	srand((unsigned int) time(NULL)); // NOLINT(cert-msc51-cpp)
	time(&now); //  update the now variable
	printf("program started at: %s\n", ctime(&now));
	start_time = clock();   //  Get the current time

	region mem = {
			NULL,
			0,
			0,
	};

	mem.ptr = (int*) malloc(MALLOC_AMNT * sizeof(int));
	unsigned int index = 0;
	if(mem.ptr == NULL){
		printf("ptr to region is NULL");
		exit(0);
	}

	while( (mem.element_count * sizeof(int)) < MAX_REGION_SIZE && mem.ptr != NULL){
		if(mem.element_count * sizeof(int) == mem.size){
			resize(&mem);
		}

		mem.ptr[index] = generate_fake_sensor_data();
		index++;
		mem.element_count++;
	}

	for(unsigned int element = 0; element < mem.element_count; element++){
		printf("%d, ",mem.ptr[element]);
		if(!(element % 10) && element != 0){
			printf("\n");
		}
	}
	printf("\n\n");

	end_time = clock();
	printf("%Lf %Lf \n", (long double)start_time, (long double) end_time);
	printf("execution took: %Lf ms\n", (long double)(end_time - start_time));
	printf("Allocated %d bytes, held %d elements\n", mem.size, mem.element_count);
	free(mem.ptr);

	time(&now);
	printf("program ended at: %s", ctime(&now));
	return 0;
}

int generate_fake_sensor_data(void){
	//  I have a 10 bit ADC -> 1024 is max
	return (rand() % 1025); // NOLINT(cert-msc50-cpp)
}

void resize(region* p_mem){
	p_mem->ptr = realloc(p_mem->ptr,
						 p_mem->size + (MALLOC_AMNT * sizeof(int)));	//	grows the region
	p_mem->size += MALLOC_AMNT * sizeof(int);
}
