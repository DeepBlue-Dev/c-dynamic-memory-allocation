#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_REGION_SIZE 100L   //  in bytes; max 10 KB of the 32KB
#define MALLOC_AMNT 5   //  the amount of integers that gets allocated per time malloc is called;

//  struct to hold the info to the memory region
typedef struct Region{
	unsigned short* ptr;
	unsigned int element_count;
	unsigned long size;
	unsigned char is_compressed:1;
}region;

unsigned short generate_fake_sensor_data(void);
unsigned short compress_data(unsigned short p_data1, unsigned short p_data2);
void resize(region* p_mem);
void compress_region(region* p_mem);

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
			0
	};

	mem.ptr = (unsigned short*) malloc(MALLOC_AMNT * sizeof(short));
	unsigned short index = 0;
	if(mem.ptr == NULL){
		printf("ptr to region is NULL");
		exit(0);
	}

	while( (mem.element_count * sizeof(short)) < MAX_REGION_SIZE && mem.ptr != NULL){
		if(mem.element_count * sizeof(short) == mem.size){
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
	printf("Allocated %d bytes, held %d elements\n", mem.size, mem.element_count);
	compress_region(&mem);
	printf("compressed allocated bytes %d, held %d elements", mem.size,mem.element_count);

	printf("\n\n");	//	fixes format
	end_time = clock();
	printf("execution took: %Lf ms\n", (long double)(end_time - start_time));

	free(mem.ptr);	//	release memory back to the os

	time(&now);
	printf("program ended at: %s", ctime(&now));
	return 0;
}

//	generates reasonably accurate data that comes from the adc.
unsigned short generate_fake_sensor_data(void){
	//  I have a 10 bit ADC -> 1024 is max
	return (short)(rand() % 1025); // NOLINT(cert-msc50-cpp)
}

//	increases the size of the memory region
void resize(region* p_mem){
	p_mem->ptr = realloc(p_mem->ptr,
						 p_mem->size + (MALLOC_AMNT * sizeof(unsigned short)));	//	grows the region
	p_mem->size += MALLOC_AMNT * sizeof(unsigned short);
}

//
unsigned short compress_data(unsigned short p_data1, unsigned short p_data2){
	return USHRT_MAX;
}

void compress_region(region* p_mem){

	unsigned short roof;	//	the index of the last item, we do not want to read out of bounds

	roof = p_mem->element_count - ((p_mem->element_count & 0x01)?(3):(2));	//	if the number of elements is uneven, make it even

	for(unsigned short index = 0; index < roof; index += 2){
		p_mem->ptr[index] = (unsigned short)(p_mem->ptr[index] << 2) | (p_mem->ptr[index + 1] & 0x0300);
		p_mem->ptr[index + 1] = (unsigned short)(p_mem->ptr[index + 1] & 0x00FF);	//	discard the bits we moved to the left
	}
	//	calculate new region size
	p_mem->size = (unsigned short) (((p_mem->size * 8) - (2 * p_mem->element_count)) / 8);
}
