#include<bits/stdc++.h>
using namespace std;
const int MAXL = 20;
typedef long long LL;
LL dp[MAXL][1030][12][12];
int a[MAXL];
int mod;
inline int getone(int x)
{
    int res=0;
    for(;x;x-= x&-x) res++;
    return res;
}

LL dfs(int pos,int sta,int re,bool limit,bool pre0)
{
    if(pos==-1){
        int cnt = getone(sta);
        if(cnt==0) cnt=1;
        return cnt==mod && re%mod==0;
    }
    if(!limit && dp[pos][sta][re][mod]!=-1)  return dp[pos][sta][re][mod];
    int up = limit? a[pos]:9;
    LL res = 0;
    for(int i = 0;i<=up;++i){
        res+=dfs(pos-1,(pre0&&i==0)?sta:sta|(1<<i),(re*10+i)%mod,limit &&i==a[pos],pre0 &&(i==0));
    }
    if(!limit) dp[pos][sta][re][mod] = res;
    return res;
}

LL solve(LL n)
{
    int pos=0;
    while(n){
        a[pos++] = n%10;
        n/=10;
    }
    LL res=0;
    for(int i=1;i<=10;++i){
        mod = i;
        res+=dfs(pos-1,0,0,1,1);
    }
    return res;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T;scanf("%d",&T);
    LL L,R;
    memset(dp,-1,sizeof(dp));
    while(T--){
        scanf("%lld%lld",&L,&R);
        printf("%lld\n",solve(R)-solve(L-1));   
    }
    return 0;
}