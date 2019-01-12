#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e5+5;
const int INF =0x3f3f3f3f;

int main(){
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,N,u,v,tmp,cas=1;
    scanf("%d",&T);
    while(T--){
        LL n,m;
        scanf("%lld",&n);
        m  = sqrt(1.0*n);
        LL res=0;
        for(int i=1;i<=m;++i) res+=n/i;
        res<<=1; res-=m*m;
        printf("Case %d: %lld\n",cas++,res);
    }
    return 0;
}
