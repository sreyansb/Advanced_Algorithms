#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "dyntable_impl.h"

int no_of_copies=0;

typedef struct dyntable{
    int cursize;
    int capacity;
    int numbers[0];
}dyntable;

void* make_new_dynamic_table(int maxie)
{
    void* dtable = malloc(sizeof(dyntable)+maxie*sizeof(int));
    ((dyntable*)dtable)->cursize = 0;
    ((dyntable*)dtable)->capacity = maxie;
    return dtable;
}

void push_back(void** dtable, int element)
{
    if ((*(dyntable**)dtable)->cursize ==(*(dyntable**)dtable)->capacity)
    {
        no_of_copies+=(*(dyntable**)dtable)->cursize;

        if ((*(dyntable**)dtable)->capacity ==0)//means it is odd so we can get an even
            ((*(dyntable**)dtable)->capacity)++;

        int k = ceil((*(dyntable**)dtable)->capacity * 1.5); 
        (*(dyntable**)dtable) = realloc((*(dyntable**)dtable),sizeof(dyntable)+sizeof(int)*k);
        ((*(dyntable**)dtable)->capacity) = k;

        printf("copies %d\n",no_of_copies);
    }
    (*(dyntable**)dtable)->numbers[(*(dyntable**)dtable)->cursize]=element;
    ++((*(dyntable**)dtable)->cursize);
    //printf("size %d\n",(*(dyntable**)dtable)->capacity);
}

void pop_back(void** dtable)
{
    if ((*(dyntable**)dtable)->cursize==0)
    {
        (*(dyntable**)dtable)->capacity =ceil(((*(dyntable**)dtable)->capacity)*0.25);
        if ((*(dyntable**)dtable)->capacity == 0)
            ++((*(dyntable**)dtable)->capacity);
        (*(dyntable**)dtable) = realloc((*(dyntable**)dtable),sizeof(dyntable)+sizeof(int)*(*(dyntable**)dtable)->capacity);
    }
    else
    {
        (*(dyntable**)dtable)->cursize--;
        if ((*(dyntable**)dtable)->cursize <= 0.25*(*(dyntable**)dtable)->capacity)
        {
            no_of_copies+=(*(dyntable**)dtable)->cursize;
            (*(dyntable**)dtable)->capacity =ceil(((*(dyntable**)dtable)->capacity)*0.25);
            if ((*(dyntable**)dtable)->capacity==0)
                (*(dyntable**)dtable)->capacity++;
            (*(dyntable**)dtable) = realloc((*(dyntable**)dtable),sizeof(dyntable)+sizeof(int)*(*(dyntable**)dtable)->capacity);
            printf("pop copies %d \n",no_of_copies);
        }
    }
    //printf("size %d\n",(*(dyntable**)dtable)->capacity);    
}

