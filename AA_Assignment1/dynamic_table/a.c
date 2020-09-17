#include<stdlib.h>
#include<stdio.h>

typedef struct hello
{
    int *a;
}hello;

void fn(void** g,int n)
{
    for (int i=0;i<n;++i)
        printf("%d here1 %d\n",i,(*(hello**)g)->a[i]);
}

int main()
{
    void* q = (void* )malloc(sizeof(hello));
    ((hello*)q)->a=calloc(6,sizeof(int));
    fn(&q,6);
    ((hello*)q)->a=realloc(((hello*)q)->a,(sizeof(int)*6*3)/2);
    fn(&q,9);
    // for(int i=0;i<5;++i)
    //     ((hello*)q)->p[i]=50;
    // fn(&q,5);
    // printf("\n");
    // //it is a deep-copy
    // q=realloc(q,sizeof(hello)+10*sizeof(int));
    // for(int i=5;i<10;++i)
    //     ((hello*)q)->p[i]=20;
    // fn(&q,10);
    /*
    ((hello*)q)->p =realloc(((hello*)q)->p,10*sizeof(int));
    for(int i=0;i<10;++i)
    ((hello*)q)->p[i]=20;
    fn(&q,10);
    */
    //int a=12;
    // // a*=1.5;
    // // printf("%d",a);
}
