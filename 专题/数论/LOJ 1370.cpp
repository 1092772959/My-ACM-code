#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1100005;
int phi[maxn];
int res[maxn];
bool isprime[maxn];

void Euler(){             //欧拉筛
    for(int i=1;i<maxn;++i) phi[i] = i;
    memset(isprime,1,sizeof(isprime));
    isprime[0] = isprime[1] = false;
    phi[1] =0;
    for(int i=2;i<maxn;++i){
        if(!isprime[i]) continue;
        for(int j=i;j<maxn;j+=i){
            isprime[j] = false;
            phi[j] -= phi[j]/i;
        }
    }
}

void pre(){
    memset(res,0,sizeof(res));
    for(int i=1;i<maxn;++i){
        for(int j=phi[i];j>=0 && res[j]==0;--j){
            res[j] = i;
        }
    }
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,N,a,cas=1;
    Euler();
    pre();
    scanf("%d",&T);
    while(T--){
        scanf("%d",&N);
        LL sum=0;
        for(int i=0;i<N;++i){
            scanf("%d",&a);
            sum +=res[a];
        }
        printf("Case %d: %lld Xukha\n",cas++,sum);
    }
    return 0;
}