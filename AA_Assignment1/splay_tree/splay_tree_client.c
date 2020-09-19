#include "splay_tree_imp.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define BENCHMARK_COUNT 2000


// function to start a nanosecond-resolution timer
struct timespec timer_start(){
	struct timespec start_time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
	return start_time;
}

// function to end a timer, returning nanoseconds elapsed as a long
long timer_end(struct timespec start_time){
	struct timespec end_time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
	long diffInNanos = (end_time.tv_sec - start_time.tv_sec) * (long)1e9 + (end_time.tv_nsec - start_time.tv_nsec);
	return diffInNanos;
}



/*
int main(){
    void* tree = make_new_dictionary();
    /*
    insert(dictionary, 77, 5);
    insert(dictionary, 35, 6);
    insert(dictionary,62,7);
    insert(dictionary,59,6);
    insert(dictionary,40,5);
    insert(dictionary,30,5);
    insert(dictionary,29,5);
    insert(dictionary,56,5);
    insert(dictionary,29,5);
    insert(dictionary,19,5);
    insert(dictionary,13,5);
    printf("found %d\n",find(dictionary,56));
    insert(dictionary,70,5);
    insert(dictionary,84,5);
    printf("done\n");
    
   /*
    insert(tree,67 , rand()%BENCHMARK_COUNT);
	insert(tree,45, rand()%BENCHMARK_COUNT);
	insert(tree,89, rand()%BENCHMARK_COUNT);
	insert(tree,56, rand()%BENCHMARK_COUNT);
	insert(tree,31, rand()%BENCHMARK_COUNT);
	insert(tree,35, rand()%BENCHMARK_COUNT);
	insert(tree,28, rand()%BENCHMARK_COUNT);
	insert(tree,64, rand()%BENCHMARK_COUNT);
	insert(tree,53, rand()%BENCHMARK_COUNT);
	insert(tree,91, rand()%BENCHMARK_COUNT);
	insert(tree,93, rand()%BENCHMARK_COUNT);
	insert(tree,92, rand()%BENCHMARK_COUNT);    
    
}
*/


int main() {
    long totaltime = 0;
    void* dictionary = make_new_dictionary();
    for(int i=1; i<=BENCHMARK_COUNT; ++i) {
        struct timespec vartime = timer_start();
        if(rand()%2) {
            insert(dictionary, random()%BENCHMARK_COUNT, random()%BENCHMARK_COUNT);
        }
        else {
            //printf("found %d\n", find(dictionary, random()%BENCHMARK_COUNT));
            find(dictionary, random()%BENCHMARK_COUNT);
        }
        long time_elapsed_nanos = timer_end(vartime);
        totaltime+=time_elapsed_nanos;
        //printf("%d %ld\n",i, time_elapsed_nanos);
    }
    printf("Total Time %ld\n",totaltime);
}

