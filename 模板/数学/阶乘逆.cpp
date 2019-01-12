#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e5+5;
int mod;
const LL INF =0x3f3f3f3f;
LL fac[maxn],inv[maxn];
LL res[maxn];
LL qpow(LL b,int n){
    LL res=1;
    while(n){
        if(n&1) res=res*b%mod;
        b = b*b%mod;
        n>>=1;
    }
    return res;
}

LL Comb(int n,int k)
{
    return fac[n]*inv[k]%mod *inv[n-k]%mod;
}

void pre()
{
    fac[0]=fac[1]=1;
    for(int i=2;i<maxn;++i) fac[i]=i*fac[i-1]%mod;
    inv[maxn-1]=qpow(fac[maxn-1],mod-2);
    for(int i=maxn-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
