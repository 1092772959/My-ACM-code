#include<bits/stdc++.h>
using namespace std;


int main()
{
    int T,n;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        int tmp = n^(n-1);
        int res=0;
        for(;tmp;tmp-=tmp&-tmp) res++;
        printf("%d\n",res); 
    }
    return 0;
}