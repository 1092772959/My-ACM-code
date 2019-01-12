#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5+5,maxk=503;
int dp[maxn][maxk];
vector<int> G[maxn];
int N,K;
/*
初级通路
dfs求出的dp[i][j] 为 以i为根，i的子树中长度为j的路径数目
solve求出的dp[i][j] 为 以i为根，i到所有点的长度为j的路径数目
最后枚举所有点dp[i][K],因为所有长度为k的路径被枚举两次，所以将最后结果除2
*/
void init()
{
    memset(dp,0,sizeof(dp));
    for(int i=0;i<=N;++i)   G[i].clear();
}

void dfs(int v,int p)
{
    int u;
    dp[v][0]=1;             //长度为0的路径数肯定为1
    for(int i=0;i<G[v].size();++i){
        u = G[v][i];
        if(u==p) continue;
        dfs(u,v);
        for(int j=1;j<=K;++j){
            dp[v][j]+=dp[u][j-1];
        }
    }
}

void solve(int v,int p)
{
    int u;
    for(int i=0;i<G[v].size();++i){
        u = G[v][i];
        if(u==p) continue;
        for(int j=K;j>=1;--j){
            dp[u][j]+=dp[v][j-1];
            if(j>1) dp[u][j]-=dp[u][j-2];           
        }
        solve(u,v);
    }
}

int main()
{
    int x,y;
    while(~scanf("%d%d",&N,&K)){
        init();
        for(int i=0;i<N-1;++i){
            scanf("%d%d",&x,&y);
            G[x].push_back(y);
            G[y].push_back(x);
        }
        dfs(1,-1);
        solve(1,-1);
        ll ans=0;
        for(int i=1;i<=N;++i){
            ans+=dp[i][K];
        }
        ans>>=1;
        cout<<ans<<endl;
    }
    return 0;
}
