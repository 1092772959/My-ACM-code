
//LightOJ - 1336
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1000015;

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,N,a,cas=1;
    LL n;
    scanf("%d",&T);
    while(T--){
        scanf("%lld",&n);
        LL ans = n - (LL)sqrt(n/2) - (LL)sqrt(n);
        printf("Case %d: %lld\n",cas++,ans);
    }
    return 0;
}