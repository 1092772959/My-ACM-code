#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1005;
const int INF =0x3f3f3f3f;
vector<int> G[maxn],nG[maxn];
stack<int> S;
int pre[maxn],low[maxn],sccno[maxn],ind[maxn],cost[maxn],dfn,scc_cnt;
struct Node{
    int x,y,r,c;
}vis[maxn];

void init(int N)
{
    dfn=scc_cnt=0;
    for(int i=0;i<=N;++i){
        G[i].clear();
        nG[i].clear();
        pre[i]=low[i]=sccno[i]=ind[i]=0;
        cost[i] = INF;
    }
}

void AddEdge(int u,int v)
{
    G[u].push_back(v);
}

void Tarjan(int u)
{
    int v;
    pre[u]=low[u]=++dfn;
    S.push(u);
    for(int i=0;i<G[u].size();++i){
        v= G[u][i];
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
            cost[scc_cnt]=min(cost[scc_cnt],vis[x].c);
            if(x==u)break;
        }
    }    
}

int main()
{
    int T,N,u,v;
    scanf("%d",&T);
    for(int cas=1;cas<=T;++cas){
        scanf("%d",&N);
        init(N);
        for(int i=1;i<=N;++i){
            scanf("%d%d%d%d",&vis[i].x,&vis[i].y,&vis[i].r,&vis[i].c);    
        }
        LL dist =0;
        for(int i=1;i<=N;++i){
            for(int j=1;j<i;++j){
                dist=0;
                dist+= (LL)(vis[i].x-vis[j].x)*(vis[i].x-vis[j].x);
                dist+= (LL)(vis[i].y-vis[j].y)*(vis[i].y-vis[j].y);   
                if(dist<=(LL)vis[i].r*vis[i].r)  AddEdge(i,j);
                if(dist<=(LL)vis[j].r*vis[j].r)  AddEdge(j,i);
            }
        }
        for(int i=1;i<=N;++i){
            if(!pre[i])
                Tarjan(i);
        }
        int res=0;
        for(int i=1;i<=N;++i){
            for(int j=0;j<G[i].size();++j){
                u = G[i][j];
                if(sccno[i]!=sccno[u]){
                    nG[sccno[i]].push_back(sccno[u]);
                    ind[sccno[u]]++;
                }
            }
        }
        for(int i=1;i<=scc_cnt;++i){
            if(!ind[i]){
                res+=cost[i];
            }
        }
        printf("Case #%d: %d\n",cas,res);
    }
    return 0;
}