#include<stdio.h>
#include<stdlib.h>

int mod = 1000000007;//according to cp-algorithms.com, 10**9+9 is better
int prime = 29;//smallest prime number>26

//to construct prime**index for all index>0 and lesser than n
void createpower(int n,long long int* powerarray)
{
    powerarray[0]=1;
    long long int x;
    for(int i=1;i<n;++i)
    {
        x = (prime*(powerarray[i-1]))%mod;
        powerarray[i] = x;
    }
}

void createarray(int len,char* text,int* parray)
{
    //saw the material from cp-algorithms.com
    //we compute parray for all prefixes of the string text and start from index 0
    //hash of 'a' is 1, 'b' is 2 and so on
    //we have assumed basetopower- initially as prime which is the closest prime number>26.
    long int basetopower=prime;//sometimes might just go above the limits->better to have long rather than just int
    parray[0]=text[0]-'a'+1;
    for(int i=1;i<len;++i)
    {
        //printf("btp %ld\n",basetopower);
        parray[i]=(parray[i-1]+(text[i]-'a'+1)*basetopower)%mod;
        basetopower = ((basetopower%mod)*prime)%mod;
    }
    //for (int i=0;i<len;++i) printf("%d ",parray[i]);printf("\n");
}

int main()
{
    //getting the inputs
    int n;
    scanf("%d",&n);
    char* text = malloc(sizeof(char)*(n+1));
    scanf("%s",text);
    text[n]='\0';

    //calculate the hashmap-table
    int* parray = malloc(sizeof(int)*n);
    createarray(n,text,parray);

    //calculate the powers for each valid index
    long long int* powerarray = malloc(sizeof(long long int)*n);
    createpower(n,powerarray);

    //get all queries and respective calculation
    int q;
    scanf("%d",&q);
    while(q)
    {
        int index;
        scanf("%d",&index);
        //important to do this step so as to compute p^index to multiply for all strings in text[0...index-1].
        //otherwise we have to compute multiplicative modulo inverse of p[index] which is cumbersome
        long long int indexpower=powerarray[index];

        //length of string B will be index and length of string C will be n(len of string)-index
        //we will need to search only in the minimum of the lengths

        int minl = index<n-index?index:n-index;
        int low=0;int high = minl-1;int mid;int maxl=0;

        while(low<=high)
        {
            mid=low+(high-low)/2;
    
            //we now need to find hash of parray[0...mid] and parray[index.....index+mid]
            //hashim is hash of index+middle waala string
            //we add mod because the subtraction might by some chance give a negative answer->no problem in adding a mod
            long int hashim=(parray[index+mid]-parray[index-1]+mod)%mod;

            //hashm is the hash of string text[0...mid]
            long int hashm = (parray[mid]%mod*indexpower)%mod;
            if (hashm==hashim)
            {
                // printf("%c %c\n",text[mid],text[index+mid]);
                maxl=maxl>mid+1?maxl:mid+1;
                low=mid+1;//there can be many more matches->we need to increment low by 1;
            }
            else
            {//match has not been found at higher index-> no reason to check after mid->prefixes wont match;
                high=mid-1;//high has to go below mid
            }  
        }
        printf("%d\n",maxl);
        q--;
    }
    
    return 0;
}
