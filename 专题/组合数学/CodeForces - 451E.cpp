#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1e5+5;
const int mod = 1e9+7;
LL Pow(LL x, LL n, LL p)
{
    LL res=1;
    while(n)
    {
        if(n&1) res=x*res%p;
        x=x*x%p;
        n>>=1;
    }
    return res;
}

LL Lucas(LL n, LL k, LL p)
{
    if(k>n-k) k=n-k;
    LL res=1;
    while(n&&k){
        LL n0=n%p, k0=k%p;
        LL a=1,b=1;
        for(LL i=n0; i>n0-k0; i--) a=a*i%p;
        for(LL i=1; i<=k0; i++) b=b*i%p;
        res = res*a*Pow(b, p-2, p)%p;
        n/=p; k/=p;
    }
    return res;
}

LL f[30];
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    LL n,s;
    while(scanf("%lld %lld",&n,&s)==2){
        for(int i=0;i<n;++i){
            scanf("%lld", &f[i]);
        }
        LL up = 1LL << n;
        LL ans = Lucas(n+s-1,n-1,mod);
        for(int i=1;i<up;++i){
            int bit = 0;
            LL t= s;
            for(int j=0;j<n;++j){
                if(i &(1<<j)){
                    bit++;
                    t -= f[j] + 1;
                }    
            }
            if(t<0) continue;
            if(bit & 1) ans = (ans+mod -Lucas(n+t-1,n-1,mod))%mod;
            else ans = (ans+Lucas(n+t-1,n-1,mod))%mod;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
