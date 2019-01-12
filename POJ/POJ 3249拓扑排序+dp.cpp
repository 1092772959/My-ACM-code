#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>
using namespace std;
const int maxn = 1e5+5;
typedef long long LL;
const LL INF = (1LL)<<60;
LL dp[maxn],W[maxn];
int ind[maxn],out[maxn];
struct Edge{
    int v,next;
}edges[maxn*11];
int head[maxn],tot,N;
bool vis[maxn];

void init()
{
    tot = 0;
    memset(out,0,sizeof(out));
    memset(vis,0,sizeof(vis));
    memset(ind,0,sizeof(ind));
    memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v)
{
    ind[v]++;
    out[u]++;
    edges[tot] =  (Edge){v,head[u]};
    head[u] = tot++;
}

void topo()
{
    queue<int> Q;
    for(int i=1;i<=N;++i){
        if(!ind[i]) {
            Q.push(i);
            dp[i] = W[i];
        }
        else dp[i] = -INF;
    }
    vector<int> res;
    while(!Q.empty()){
        int u = Q.front(); Q.pop();
        res.push_back(u);
        for(int i=head[u];~i;i=edges[i].next){
            int v = edges[i].v;
            ind[v]--;
            if(!ind[v]) Q.push(v);
        }
    }
    int len = res.size();
    for(int i=0;i<len;++i){
        int u = res[i];
        for(int j= head[u];~j;j = edges[j].next){
            int v = edges[j].v;
            dp[v] = max(dp[v],dp[u]+W[v]);
        }
    }
    LL ans = -INF;
    for(int i=1;i<=N;++i){
        if(!out[i]){
            ans = max(ans,dp[i]);
        }
    }
    printf("%lld\n",ans);
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int M,u,v;
    while(scanf("%d %d",&N,&M)==2){
        init();
        for(int i=1;i<=N;++i)
            scanf("%lld",&W[i]);
        while(M--){
            scanf("%d%d",&u,&v);
            AddEdge(u,v);
        }
        topo();        
    }
    return 0;
}