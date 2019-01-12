#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
typedef long long ll;

ll fpow(ll base,ll n)
{
    ll res=1;
    while(n){
        if(n&1) res=res*base%mod;
        base=base*base%mod;
        n>>=1;
    }
    return res;
}



int main()
{
    int T,n,k;
    scanf("%d",&T);
    while(T--){
        ll res=0;
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;++i)   res=(res+fpow(i,k))%mod;
        printf("%lld\n",res);
    }
    return 0;
}