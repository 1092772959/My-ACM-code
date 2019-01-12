#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e7+5,maxv = 5e6+5;
const int INF =0x3f3f3f3f;
bool notprime[maxn];
int prime[maxv];              //prime[0] 表示当前范围内有多少素数,prime[i] 表示第i个素数是多少

void pre()
{
    memset(notprime,0,sizeof(notprime));
    notprime[0] = notprime[1] = true;
    memset(prime,0,sizeof(prime));
    for(int i=2;i<maxn;++i){
        if(!notprime[i]) prime[++prime[0]] = i;
        for(int j=1 ; j<=prime[0] && prime[j] <= maxn / i ;++j){
            notprime[prime[j]*i] = true;
            if(i%prime[j]==0) break;        //每个合数保证只被它最小的那个质因子筛选
        }
    }
}


int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    pre();
    int T,N,u,v,tmp,cas=1;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&N);
        int res=0;
        for(int i =1;i<=prime[0] && prime[i]<=N/2;++i){
            if(notprime[N-prime[i]]) continue;
            res++;
        }
        printf("Case %d: %d\n",cas++,res);
    }
    return 0;
}
