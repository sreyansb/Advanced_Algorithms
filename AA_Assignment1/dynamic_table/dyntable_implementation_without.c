#include <stdio.h>
#include <stdlib.h>
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
            if ((*(dyntable**)dtable)->capacity & 1)
                ((*(dyntable**)dtable)->capacity)+=1;
            (*(dyntable**)dtable)->numbers = realloc((*(dyntable**)dtable)->numbers,sizeof(int)*(((*(dyntable**)dtable)->capacity*3)/2));
            (*(dyntable**)dtable)->capacity =((*(dyntable**)dtable)->capacity/2)*3;
        }
    (*(dyntable**)dtable)->numbers[(*(dyntable**)dtable)->cursize] = element;
    (*(dyntable**)dtable)->cursize += 1;
    printf("CAPU %d\n",(*(dyntable**)dtable)->capacity);
}

void pop_back(void** dtable)
{
    if ((*(dyntable**)dtable)->cursize==0)
    {
        (*(dyntable**)dtable)->capacity =(((*(dyntable**)dtable)->capacity)*3)/8;
        if ((*(dyntable**)dtable)->capacity==0)
            ++((*(dyntable**)dtable)->capacity);
        (*(dyntable**)dtable)->numbers = realloc((*(dyntable**)dtable)->numbers,sizeof(int)*(*(dyntable**)dtable)->capacity);
    }
    else
    {
        --((*(dyntable**)dtable)->cursize);
        if ((*(dyntable**)dtable)->cursize <= 0.5 * (*(dyntable**)dtable)->capacity)
        {
            no_of_copies+=(*(dyntable**)dtable)->cursize; //only cursize number of elements are present in the array=>we need to only copy cursize number of elements

            (*(dyntable**)dtable)->capacity =(((*(dyntable**)dtable)->capacity)*3)/8;
            if ((*(dyntable**)dtable)->capacity==0)
                ++((*(dyntable**)dtable)->capacity);
            
            (*(dyntable**)dtable)->numbers = realloc((*(dyntable**)dtable)->numbers,sizeof(int)*(*(dyntable**)dtable)->capacity);
            printf("pop copies %d \n",no_of_copies);
            //printf("CAPA %d\n",(*(dyntable**)dtable)->capacity);
        }
    }
    printf("CAPO %d\n",(*(dyntable**)dtable)->capacity);    
}




