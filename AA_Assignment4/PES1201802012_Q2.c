#include<stdio.h>
#include<stdlib.h>

int mod=1000000007;

int gcd(long long int a,int b,int* x,int* y)
{
    if (!a)
    {
        *x=0;*y=1;return b;
    }
    int x1;int y1;
    int calcgcd=gcd(b%a,a,&x1,&y1);
    *x=y1-(b/a)*x1;
    *y=x1;
    return calcgcd;
}

int inverse(long long int a,int m)
{
    int x,y;
    int g=gcd(a,m,&x,&y);
    return (x%m+m)%m;
}

int main()
{
    int n;
    scanf("%d",&n);
    int* divisors=malloc(sizeof(int)*n);
    int* remainders=malloc(sizeof(int)*n);
    int* pi=malloc(sizeof(int)*n);
    long long int totprod=1;
    for(int i=0;i<n;++i)
    {
        scanf("%d%d",&divisors[i],&remainders[i]);
        totprod*=divisors[i];
    }
    for(int i=0;i<n;++i)
        pi[i]=totprod/divisors[i];
    int* y=malloc(sizeof(int)*n);
    for(int i=0;i<n;++i)
        y[i]=inverse(pi[i],divisors[i]);
    long long int sol=0;
    for(int i=0;i<n;++i)
    {
        sol=(sol+(remainders[i]*pi[i]*y[i])%totprod)%totprod;
    }
    printf("%lld\n",(sol%totprod)%mod);
}
