#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define PI 3.1415926535
typedef long long int uli;
//%llu

typedef struct complex
{
    double real;
    double imag;
}complex;

void multiply(complex A,complex B,complex* C)
{
    (*C).imag=A.real*B.imag+B.real*A.imag;
    (*C).real=A.real*B.real-A.imag*B.imag;
}

int fft(int n,complex* A,int negative)
{
    if (n==1)
        return 0;
    complex* aodd=malloc(sizeof(complex)*n/2);
    complex* aeven=malloc(sizeof(complex)*(n+1)/2);//for odd n->there are odd number of elements in aeven
    for(int i=0;2*i<n;++i)
    {
        aeven[i]=A[2*i];
        aodd[i]=A[2*i+1];
    }
    fft(n/2,aodd,negative);
    fft(n/2,aeven,negative);
    double theta=(2*PI)/((float)n);
    //printf("THETA: %lf\n",theta);
    if (negative)
        theta*=-1;
    complex w;
    w.real=1;w.imag=0;
    complex wn;
    wn.real=cos(theta);wn.imag=sin(theta);
    //printf("n:%d wn %lf r:%lf im:%lf\n",n,theta,wn.real,wn.imag);
    for(int i=0;2*i<n;++i)
    {
        complex k;
        multiply(aodd[i],w,&k);
        A[i].real=aeven[i].real+k.real;A[i].imag=aeven[i].imag+k.imag;
        A[i+n/2].real=aeven[i].real-k.real;A[i+n/2].imag=aeven[i].imag-k.imag;
        if (negative)
        {
            A[i].real/=2;A[i].imag/=2;
            A[i+n/2].real/=2;A[i+n/2].imag/=2;
        }
        // if (w.imag==0)
        //     w.imag=1;
        multiply(w,wn,&k);
        w.real=k.real;w.imag=k.imag;
        //printf("HERE %lf %lf %lf %lf\n",w.real,w.imag,wn.real,wn.imag);
    }
    return 1;
}

int main()
{
    int n;
    scanf("%d",&n);
    complex* A = malloc(sizeof(complex)*(2*n));
    complex* B = malloc(sizeof(complex)*(2*n));
    //printf("DONE\n");
    for(int i=0;i<n;++i)
    {
        scanf("%lf",&(A[i].real));
        A[i].imag=0;
    }
    for(int i=0;i<n;++i)
    {
        scanf("%lf",&(B[i].real));
        B[i].imag=0;
    }
    for(int i=n;i<2*n;++i)
    {
        A[i].real=0;A[i].imag=0;
        B[i].real=0;B[i].imag=0;
    }
    fft(2*n,A,0);
    //arrprint(2*n,A);
    fft(2*n,B,0);
    //arrprint(2*n,B);
    complex k;
    for(int i=0;i<2*n;++i)
    {
        multiply(A[i],B[i],&k);
        A[i]=k;
    }
    fft(2*n,A,1);
    uli co;
    //arrprint(2*n,A);
    for(int i=0;i<2*n;++i)
    {
        co=A[i].real-floor((A[i].real))>ceil(A[i].real)-A[i].real?ceil(A[i].real):floor(A[i].real);
        printf("%lld ",co);
    }
    printf("\n");    
    return 0;
}
