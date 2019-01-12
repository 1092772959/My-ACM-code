#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e6+5;
struct Edge{
    int v,next;
    LL val;  
}edges[maxn],E[maxn];
int head[maxn],tot,H[maxn],tt;
stack<int> S;
int pre[maxn],low[maxn],sccno[maxn],dfn,scc_cnt;
LL W[maxn];
LL dp[maxn];
void init()
{
    tot = dfn = scc_cnt=tt=0;
    memset(H,-1,sizeof(H));
    memset(W,0,sizeof(W));
    memset(dp,0,sizeof(dp));
    memset(pre,0,sizeof(pre));
    memset(sccno,0,sizeof(sccno));
    memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v,LL val)   {
    edges[tot] = (Edge){v,head[u],val};
    head[u] = tot++;
}

void Tarjan(int u)
{
    int v;
    pre[u]=low[u]=++dfn;
    S.push(u);
    for(int i=head[u];~i;i=edges[i].next){
        v= edges[i].v;
        if(!pre[v]){
            Tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(!sccno[v]){
            low[u]=min(low[u],pre[v]);
        }
    }
    if(pre[u]==low[u]){
        int x;
        ++scc_cnt;
        for(;;){
            x = S.top();S.pop();
            sccno[x]=scc_cnt;
            if(x==u)break;
        }
    }    
}


void nAddEdge(int u,int v,LL w)
{
    E[tt] = (Edge){v,H[u],w};
    H[u] = tt++;
}

LL dfs(int u)
{
    if(dp[u]) return dp[u];
    for(int i=H[u];~i;i=E[i].next){
        int v = E[i].v;
        dp[u] = max(dp[u],dfs(v)+E[i].val);
    }
    dp[u]+=W[u];
    return dp[u];
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int N,M; 
    while(scanf("%d%d",&N,&M)==2){
        init();
        int st,u,v; LL w;
        while(M--){
            scanf("%d%d%lld",&u,&v,&w);
            AddEdge(u,v,w);
        }
        scanf("%d",&st);
        for(int i=1;i<=N;++i){
            if(!pre[i]){
                Tarjan(i);
            }
        }
        
        for(int u =1;u<=N;++u){
            for(int i =head[u];~i;i = edges[i].next){
                v = edges[i].v;
                LL w = edges[i].val;
                if(sccno[u]!=sccno[v]){
                    nAddEdge(sccno[u],sccno[v],w);
                }
                else{
                    int t = (int)(1+sqrt(1+8*w))/2;
                    W[sccno[u]] += (LL)t*w - (LL)(t-1)*t*(t+1)/6;
                }
            }
        }
        for(int i=1;i<=scc_cnt;++i){
            if(!dp[i]){
                dfs(i);
            }
        }
        printf("%lld\n",dp[sccno[st]]);
    }
    return 0;
}