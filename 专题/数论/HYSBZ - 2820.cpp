#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=1e7+5;
bool vis[maxn];
int prime[maxn],mu[maxn];
int sum[maxn];
void init(){
    memset(vis,false,sizeof(vis));
    mu[1] = 1;
    prime[0] = 0;
    int cnt=0;
    for(int i=2;i<maxn;++i){
        if(!vis[i]){
            mu[i] = -1;
            sum[i] = 1;
            prime[++cnt] = i;
        }
        for(int j=1;j<=cnt;++j){
            if(i*prime[j] >= maxn)  break;
            vis[i*prime[j]] = true;
            if(i % prime[j]){
                mu[i*prime[j]] = -mu[i];
                sum[i*prime[j]] = mu[i] - sum[i];
            }
            else{
                mu[i*prime[j]] = 0;
                sum[i*prime[j]] = mu[i];
                break;
            }
        }
    }
    for(int i =2;i<maxn;++i) sum[i]+=sum[i-1];
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    init();
    LL N,M;
    int T; scanf("%d",&T);
    while(T--){
        scanf("%lld %lld",&N,&M);
        LL res=0;
        if(N>M) swap(N,M);
        for(LL i=1,j;i<=N;i=j+1){
            j = min(N/(N/i),M/(M/i));
            res += (sum[j]-sum[i-1])*(N/i)*(M/i);
        }
        printf("%lld\n",res);
    } 
    return 0;
}

