#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int mod=1000000007;

void convert(char* s,int lenofs)
{
    //int lenofs=strlen(s);
    for(int i=0;i<lenofs;++i)
    {
        if(s[i]>64 && s[i]<91)
            s[i]+=32;
    }
}

int minfind(int a,int b,int c)
{
    return a<b?(a<c?a:c):(b<c?b:c);
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        char* sm=(char*)malloc(1005);
        char* sn=(char*)malloc(1005);
        scanf("%s %s",sm,sn);

        int m=strlen(sm);
        int n=strlen(sn);
        convert(sm,m);
        convert(sn,n);
        
        //has m+1 rows and n+1 columns, therefore to access lpstable[x][y] = lpstable[(x)*(n+1)+y]
        int* lpstable=(int*)malloc((m+1)*(n+1)*sizeof(int));
        for(int i=0;i<=m;++i)
        {
            for(int j=0;j<=n;++j)
            {
                if (i==0 || j==0)
                    lpstable[i*(n+1)+j]=j==0?i:j;
                else
                    {
                        if (sm[i-1]==sn[j-1])
                            lpstable[i*(n+1)+j]=(lpstable[(i-1)*(n+1)+j-1]);
                        else
                            lpstable[i*(n+1)+j]=(1+minfind(lpstable[(i-1)*(n+1)+j-1],lpstable[(i-1)*(n+1)+j],lpstable[(i)*(n+1)+j-1]))%mod;
                    }             
            }
        }
        printf("%d\n",(lpstable[m*(n+1)+n])%mod);
	    free(lpstable);
        free(sm);
        free(sn);
    }
}
/*
test case:
3
ABC bD
space ship
ship dock
*/
