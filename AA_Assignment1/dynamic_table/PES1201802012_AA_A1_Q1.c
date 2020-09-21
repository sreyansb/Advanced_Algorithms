#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include "dyntable_impl.h"

int no_of_copies=0;

typedef struct dyntable{
    int cursize;
    int capacity;
    int* numbers;
}dyntable;

void* make_new_dynamic_table(int maxsize)
{
    void* dtable = malloc(sizeof(dyntable));
    //printf("size%d\n",maxsize);
    ((dyntable*)dtable)->capacity = maxsize;
    ((dyntable*)dtable)->cursize = 0;
    ((dyntable*)dtable)->numbers = malloc(sizeof(int)*maxsize);
    return dtable;
}

void push_back(void** dtable, int element)
{  
    if ((*(dyntable**)dtable)->cursize==(*(dyntable**)dtable)->capacity)
        {   
            no_of_copies+=(*(dyntable**)dtable)->cursize;
            if ((*(dyntable**)dtable)->capacity == 0)
                {((*(dyntable**)dtable)->capacity)+=1;(*(dyntable**)dtable)->numbers = realloc((*(dyntable**)dtable)->numbers,sizeof(int));}
	    else
	    {
             (*(dyntable**)dtable)->numbers = realloc((*(dyntable**)dtable)->numbers,sizeof(int)*ceil((((*(dyntable**)dtable)->capacity*3.0)/2)));
             (*(dyntable**)dtable)->capacity =ceil((((*(dyntable**)dtable)->capacity*3.0)/2));
	    }
	    //printf("copies %d\n",no_of_copies);
        }
    (*(dyntable**)dtable)->numbers[(*(dyntable**)dtable)->cursize] = element;
    (*(dyntable**)dtable)->cursize += 1;
    //printf("CAPU %d\n",(*(dyntable**)dtable)->capacity);
}

void pop_back(void** dtable)
{
    if ((*(dyntable**)dtable)->cursize==0)
    {
        (*(dyntable**)dtable)->capacity =ceil((((*(dyntable**)dtable)->capacity)*1.0)/4);
        if ((*(dyntable**)dtable)->capacity==0)
            ++((*(dyntable**)dtable)->capacity);
        (*(dyntable**)dtable)->numbers = realloc((*(dyntable**)dtable)->numbers,sizeof(int)*(*(dyntable**)dtable)->capacity);
    }
    else
    {
        --((*(dyntable**)dtable)->cursize);
        if ((*(dyntable**)dtable)->cursize <= 0.25 * (*(dyntable**)dtable)->capacity)
        {
            no_of_copies+=(*(dyntable**)dtable)->cursize; //only cursize number of elements are present in the array=>we need to only copy cursize number of elements

            (*(dyntable**)dtable)->capacity =ceil((((*(dyntable**)dtable)->capacity)*1.0)/4);
            if ((*(dyntable**)dtable)->capacity==0)
                ++((*(dyntable**)dtable)->capacity);
            
            (*(dyntable**)dtable)->numbers = realloc((*(dyntable**)dtable)->numbers,sizeof(int)*(*(dyntable**)dtable)->capacity);
            //printf("pop copies %d \n",no_of_copies);
            //printf("CAPA %d\n",(*(dyntable**)dtable)->capacity);
        }
    }
    //printf("CAPO %d\n",(*(dyntable**)dtable)->capacity);    
}
/*
void print_table(dyntable* table){
    printf("\n");
    printf("\n");
    printf("Array: ");
    for(int i = 0; i < table -> cursize; ++i){
        printf("%d ", table ->numbers[i]);
    }
    printf("\n");
    printf("Filled: %d\n", table -> cursize);
    printf("Capacity: %d\n", table -> capacity);
    printf("Sizeof: %d\n", sizeof(table->numbers));
    printf("\n");
    printf("\n");
}
*/
/*
int main(){
    void* table = (dyntable*)make_new_dynamic_table(0);
    print_table(((dyntable*)table));
    pop_back(&table);
    pop_back(&table);

    print_table(((dyntable*)table));
    
    push_back(&table, 4);
    push_back(&table, 3);
    push_back(&table, 2);
    print_table(((dyntable*)table));

    pop_back(&table);
    print_table(((dyntable*)table));

    pop_back(&table);
    print_table(((dyntable*)table));
    pop_back(&table);
    print_table(((dyntable*)table));

    pop_back(&table);
    pop_back(&table);
    print_table(((dyntable*)table));

    push_back(&table, 1);
    push_back(&table, 2);
    push_back(&table, 3);
    push_back(&table, 4);
    push_back(&table, 5);
    push_back(&table, 6);
    push_back(&table, 7);
    push_back(&table, 8);
    push_back(&table, 9);
    push_back(&table, 10);
    push_back(&table, 11);
    push_back(&table, 12);
    push_back(&table, 13);
    print_table(((dyntable*)table));

    pop_back(&table);
    pop_back(&table);
    pop_back(&table);
    pop_back(&table);
    pop_back(&table);
    pop_back(&table);
    pop_back(&table);
    pop_back(&table);
    pop_back(&table);
    pop_back(&table);
    pop_back(&table);
    print_table(((dyntable*)table));
    pop_back(&table);
    print_table(((dyntable*)table));
    pop_back(&table);
    print_table(((dyntable*)table));
    pop_back(&table);
    print_table(((dyntable*)table));
    pop_back(&table);
    print_table(((dyntable*)table));

    push_back(&table, 13);
    print_table(((dyntable*)table));
    push_back(&table, 13);
    print_table(((dyntable*)table));
    push_back(&table, 13);
    print_table(((dyntable*)table));
    push_back(&table, 12);
    print_table(((dyntable*)table));
    push_back(&table, 11);
    print_table(((dyntable*)table));
    push_back(&table, 11);
    print_table(((dyntable*)table));
    push_back(&table, 11);
    print_table(((dyntable*)table));
}
*/


