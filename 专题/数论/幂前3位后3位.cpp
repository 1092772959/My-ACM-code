#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e5+5;
const int INF =0x3f3f3f3f;

int fpow(LL a,LL n,int mod)
{
    int res=1;
    while(n){
        if(n&1) res = res * a %mod;
        a = a*a %mod;
        n>>=1;
    }
    return res;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,N,u,v,tmp,cas=1;
    scanf("%d",&T);
    while(T--){
        LL n,k;
        scanf("%lld %lld",&n,&k);
        double ans1;
        LL ans2;
        ans1 = pow(10,k*log10(n)-(int)(k*log10(n)));
        ans2 = fpow(n,k,1000);
        printf("Case %d: %d %03d\n",cas++,(int)(ans1*100),ans2%1000);
    }
    return 0;
}
