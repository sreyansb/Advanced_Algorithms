#include<stdio.h>

int mod=1000000007;

/*
dp[n][k][0]=(dpt[n-1][k-1][2]+(dpt[n-1][k][0]+dpt[n-1][k][1]+dpt[n-1][k][3]));
dpt[n][k][1]=dpt[n-1][k][0];
dpt[n][k][2]=dpt[n-1][k][1];
dpt[n][k][3]=(dpt[n-1][k][3]+dpt[n-1][k][2]+dpt[n-1][k][1]+dpt[n-1][k][0])*25-dpt[n][k][1]-dpt[n][k][2];//has minus better to use next formula
            =(((dpt[n-1][k][3]+dpt[n-1][k][2])*25)+((dpt[n-1][k][0]+dpt[n-1][k][1])*24));
*/

int main()
{
    long long int dpt[201][67][4];

    //base cases
    for(int row=0;row<201;++row)
        for(int k=0;k<67;++k)
            for(int clue=0;clue<4;++clue)
                dpt[row][k][clue]=0;
    dpt[1][0][0]=1;dpt[1][0][3]=25;

    //filling the dp table
    for(int n=2;n<201;++n)
        {
            dpt[n][0][0]=(dpt[n-1][0][0]+dpt[n-1][0][1]+dpt[n-1][0][3])%mod;
            dpt[n][0][1]=dpt[n-1][0][0];
            dpt[n][0][2]=dpt[n-1][0][1];
            dpt[n][0][3]=((((dpt[n-1][0][3]+dpt[n-1][0][2])%mod)*25)%mod+(((dpt[n-1][0][0]+dpt[n-1][0][1])%mod)*24)%mod)%mod;
            for(int k=1;3*k+1<=n;++k)
            {
                dpt[n][k][0]=(dpt[n-1][k-1][2]+(dpt[n-1][k][0]+dpt[n-1][k][1]+dpt[n-1][k][3])%mod)%mod;
                dpt[n][k][1]=dpt[n-1][k][0];
                dpt[n][k][2]=dpt[n-1][k][1];
                dpt[n][k][3]=((((dpt[n-1][k][3]+dpt[n-1][k][2])%mod)*25)%mod+(((dpt[n-1][k][0]+dpt[n-1][k][1])%mod)*24)%mod)%mod;
            }
        }
    //printf("%lld %lld %lld %lld %lld %lld %lld \n",dpt[4][0][0],dpt[4][0][1],dpt[4][0][2],dpt[4][0][3],dpt[4][1][0],dpt[4][1][1],dpt[3][0][2]);
        
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;int k;
        scanf("%d %d",&n,&k);
        if (3*k+1>n)
            printf("0\n");
        else
            printf("%lld\n",(dpt[n][k][0]+dpt[n][k][1]+dpt[n][k][2]+dpt[n][k][3])%mod);
    }
}
