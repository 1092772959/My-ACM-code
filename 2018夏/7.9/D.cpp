#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e5+5;

int main()
{
    int T,N,M;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&N,&M);
        if(M>N) swap(N,M);
        LL res=0;
        int onrow1 = (N>>1)+1;
        int onrow2 = (N+1)>>1;
        for(int i=1;i<=M;++i){
            if(i&1) res+=onrow2;
            else res+=onrow1;
        }
        printf("%lld\n",res);
    }
    return 0;
}