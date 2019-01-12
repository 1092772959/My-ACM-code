#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
const int maxn = 1e5+5;
typedef long long LL;
LL a[maxn];
LL b[maxn];
LL qpow(LL a,int N)
{
    LL res=1;
    while(N){
        if(N&1) res = res*a%mod;
        a = a*a%mod;
        N>>=1;
    }
    return res;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int N;
    while(scanf("%d",&N)==1){
        if(!N) break;
        LL tot = 1;
        for(int i=1;i<=N;++i){
            scanf("%lld",&a[i]);
            tot = tot*a[i] %mod;
            b[i] =qpow(a[i],mod-2);
        }  
        for(int i=1;i<=N;++i){
            b[i] = tot * b[i] %mod;
            printf("%lld%c",b[i],i==N?'\n':' ');
        }
    }   
    return 0;
}