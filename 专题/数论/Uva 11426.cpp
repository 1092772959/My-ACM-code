#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 4e6+5;
int phi[maxn];              //欧拉函数
LL ans[maxn];
void Euler()
{             //欧拉函数表
    for(int i=1;i<maxn;++i) phi[i] = i;
    for(int i=2;i<maxn;++i){
        if(phi[i]==i){
            for(int j=i;j<maxn;j+=i)
                phi[j] = phi[j] - phi[j]/ i;
        }
        for(int j=1;j*i<maxn;++j) ans[j*i] += j*phi[i];
    }
    for(int i=2;i<maxn;++i) ans[i]+=ans[i-1];
}

int main() 
{
    #ifndef ONLINE_JUDGE
            freopen("in.txt","r",stdin);
            freopen("out.txt","w",stdout);
    #endif
    Euler();
    int N;
    while(scanf("%d",&N)==1){
        if(!N) break;
        printf("%lld\n",ans[N]);
    }
    return 0;
}
