#include "dyntable_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define BENCHMARK_COUNT 100

extern int no_of_copies;
// call this function to start a nanosecond-resolution timer
struct timespec timer_start(){
	struct timespec start_time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
	return start_time;
}

// call this function to end a timer, returning nanoseconds elapsed as a long
long timer_end(struct timespec start_time){
	struct timespec end_time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
	long diffInNanos = (end_time.tv_sec - start_time.tv_sec) * (long)1e9 + (end_time.tv_nsec - start_time.tv_nsec);
	return diffInNanos;
}


int main() {
	long fulltime=0;
	void* dt = make_new_dynamic_table(1);
	for(int i=1; i<=BENCHMARK_COUNT; ++i) {
		//printf("opno %d\n",i);
        struct timespec vartime = timer_start();
		if(rand()%2) {        
			push_back(&dt, random()%BENCHMARK_COUNT);
		}
        else {
          	pop_back(&dt);
        }
        long time_elapsed_nanos = timer_end(vartime);
        printf("%ld\n", time_elapsed_nanos);
		fulltime+=time_elapsed_nanos;
    }
	printf("Fulltime %ld\n",fulltime);
	printf("Copies %d\n",no_of_copies);
}
