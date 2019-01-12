#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
const int INF =0x3f3f3f3f;
typedef long long LL;
int a[20];
LL dp[13][105][150];
int mod;

LL dfs(int pos,int sum,int remain,bool limit){
    if(pos==-1) return (sum==mod && !remain);
    if(dp[pos][sum][remain]!=-1 && !limit) return dp[pos][sum][remain];
    int up = limit? a[pos]:9;
    LL res=0;
    for(int i=0;i<=up;++i){
        if(i+sum>mod) break;
        res+=dfs(pos-1,sum+i,(remain*10+i)%mod,limit && i==a[pos]);
    }
    if(!limit) dp[pos][sum][remain] = res;
    return res;
}

LL solve(LL N)
{
    int pos=0;
    LL x=N;
    while(x){
        a[pos++]=x%10;
        x/=10;
    }
    LL res=0;
    for(int i=1;i<=9*pos;++i){
        mod=i;
        memset(dp,-1,sizeof(dp));
        res+=dfs(pos-1,0,0,true);
    }
    return res;
}

int main(){
    int T,M,num,t,x;
    LL N;
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    while(scanf("%lld",&N)==1){
        printf("%lld\n",solve(N));
    }
    return 0;
}