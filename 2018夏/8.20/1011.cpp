#include<bits/stdc++.h>
typedef long long LL;
#define INF 0x3f3f3f3f
const int maxn=1e5+10;
const int MAXN=1e3+10;
const LL mod=998244353;
using namespace std;

LL qpow(LL a,int n)
{
    LL res=1;
    while(n){
        if(n&1) res = res*a %mod;
        a = a*a %mod;
        n>>=1;
    }
    return res;
}

LL Comb(LL n,LL k)
{
    if(n<k) return 0;
    if(k==1) return n;
    if(k==2) {
        LL rev2 = qpow(2,mod-2);
        return (n*(n-1)%mod)*rev2 %mod;
    }
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int a,b,c,d;
    int T; scanf("%d",&T);
    while(T--){
        scanf("%d%d%d%d",&a,&b,&c,&d);
        LL res=0;
        int n = (a+b+c+d);
        //k拍 0球
        res = (res+qpow(2,b))%mod;
        //0拍 k球
        res = (res+qpow(2,c))%mod;
        
        //1拍 k球
        res = (res + d*qpow(2,c)%mod) %mod;
        res = (res + b*qpow(2,c)%mod) %mod;

        //1拍0球 被重复算了一次
        res = (res+mod-b)%mod;

        res = res * qpow(2,a) %mod;

        res = (res - qpow(2,a)+mod) %mod;

        printf("%lld\n",res); 
    }
    return 0;
}