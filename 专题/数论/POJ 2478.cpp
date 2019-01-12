#include<stdio.h>
#include<cstring>
using namespace std;
const int maxn = 1000010;
typedef long long LL;
int phi[maxn];              //欧拉函数
int res[maxn];              //res[i]:求最小的满足phi[x]>=i的X
bool isprime[maxn];
LL ans[maxn];

void Euler()
{             //欧拉函数表
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
    ans[1] = 0;
    for(int i=2;i<maxn;++i){
        ans[i] = ans[i-1] +phi[i];
    }
}



int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    Euler();   
    int N;
    while(scanf("%d",&N),N){
        printf("%lld\n",ans[N]);
    }        
    return 0;
}
