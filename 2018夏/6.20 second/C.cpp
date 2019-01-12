#include<bits/stdc++.h>
using namespace std;
typedef long long  LL;
const int maxn =2e5+5;
const int MOD = 1e8+7;
LL fac[maxn],inv_fac[maxn];

LL qpow(LL x, LL n)
{
    LL res = 1;
    while(n){
        if(n & 1)   res = (res * x) % MOD;
        x = (x * x) % MOD;
        n >>= 1;
    }
    return res;
}

void init()
{
    fac[0]=1;
    for(int i =1;i<=200000;++i){
        fac[i]=(i*fac[i-1])%MOD;
    }
    inv_fac[200000] = qpow(fac[200000], MOD - 2);
    for(int i = 199999; i >= 0; i--)
       inv_fac[i] = (inv_fac[i + 1] * (i + 1)) % MOD;
}

LL Comb(LL n,LL k)
{
    return ((fac[n]*inv_fac[k]%MOD)*inv_fac[n-k])%MOD;
}

int main()
{
    LL n,m,p,q;
    init();
    while(~scanf("%lld%lld%lld%lld",&m,&n,&p,&q)){
        LL res=((Comb(m+n,m)*Comb(m-p+q,q)%MOD)+MOD-Comb(m+q,m)*Comb(m-p+n,n)%MOD)%MOD;
        printf("%lld\n",res);
    }
    return 0;
}

