#include<stdio.h>
#include<stdlib.h>

void createlps(char* pattern,int lenp,int* lpst)
{
    lpst[0]=0;//initial character's suffix==prefix, length ==0
    int i=0;
    int j=1;
    while(j<lenp)
    {
        if (pattern[i]==pattern[j])
            {
				lpst[j++]=++i;//indicates how many characters you need to skip->those many characters are matched already
			}
        else
            {
                if (lpst[i]==0)
                    {lpst[j++]=0;}
                else
                    i=lpst[i-1];//it is like the find data structure in data science
            }
    }
}

int main()
{
   int n;
   scanf("%d",&n);
   char* P=malloc(sizeof(char)*(n+1));
   char* Q=malloc(sizeof(char)*(n+1));
   scanf("%s",P);
   P[n]='\0';
   scanf("%s",Q);
   Q[n]='\0';
   //for effective rotation of values.
   char* dq=malloc(sizeof(char)*(2*n+1));
   for(int i=0;i<n;++i)
   {
       dq[i]=Q[i];
       dq[i+n]=Q[i];
   }
   dq[2*n]='\0';
   //printf("%s\n",dq);
   //Now P is the pattern and Q is the text in which we will search for.
   int maxi=0;int R=0;int lR=0;
   int *prefixtable=malloc(sizeof(int)*(n));
   createlps(P,n,prefixtable);
   /*
   	for(int i=0;i<n;++i)
		printf("%d ",prefixtable[i]);
    printf("\n");
	*/
   int i=0;
   int j=0;
   int curcount=0;
   while(i<n)
   {
       //printf("%d %d\n",i,curcount);
       if (P[j]==Q[i])
       {
           curcount++;
           j++;
       }
       else
       {
           maxi=maxi>curcount?maxi:curcount;
		if (maxi==curcount)
			R=i-curcount;
           if (j!=0)
           {
               j=prefixtable[j-1];
               curcount=j;
           }
       }
       i++;
   }
   maxi=maxi>curcount?maxi:curcount;
   if (maxi==curcount)
	R=i-curcount;
   printf("%d\n",R);
   free(P);
   free(Q);
   free(dq);
   return 0;
}
