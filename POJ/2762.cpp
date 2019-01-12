#include<stack>
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#include<cstring>
#include<queue>
using namespace std;
typedef long long LL;
const int MAXN = 1e3+10;
struct Edge{
    int to,next;
}edges[MAXN<<3],E[MAXN<<3];
int ID,H[MAXN];
int dfn[MAXN],low[MAXN],sccno[MAXN],head[MAXN],tot,dfs_clock,scc_cnt,in[MAXN],sccnum[MAXN];
stack<int> S;

void init()
{
    ID=dfs_clock=tot=scc_cnt=0;
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(in,0,sizeof(in));
    memset(sccno,0,sizeof(sccno));
    memset(head,-1,sizeof(head));
    memset(H,-1,sizeof(H));
}

void Tarjan(int u)
{
    int v;
    dfn[u]=low[u]=++dfs_clock;
    S.push(u);
    for(int i=head[u];~i;i=edges[i].next){
        v = edges[i].to;
        if(!dfn[v]){
            Tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(!sccno[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(dfn[u]==low[u]){
        ++scc_cnt;
        while(true){
            int x = S.top();S.pop();
            sccno[x] = scc_cnt;
            if(x==u) break;
        }
    }
}

void AddEdge(int u,int v)
{
    edges[tot]=(Edge){v,head[u]};
    head[u]=tot++;
}
void new_AddEdge(int u,int v){
    E[ID]= (Edge){v,H[u]};
    H[u]=ID++;
}

bool Topo()
{
    queue<int> Q;
    for(int u=1;u<=scc_cnt;++u){
        if(!in[u]) Q.push(u);
    }
    if(Q.size()>1) return false;
    while(!Q.empty()){
        int x = Q.front();Q.pop();
        for(int i=H[x];~i;i=E[i].next){
            int v =E[i].to;
            in[v]--;
            if(!in[v]) Q.push(v);
        }
        if(Q.size()>1) return false;
    }
    return true; 
}

int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int T,N,M,u,v;
    scanf("%d",&T); 
    while(T--){
        scanf("%d%d",&N,&M);
        init();
        for(int i=1;i<=M;++i){
            scanf("%d%d",&u,&v);
            AddEdge(u,v);
        }
        for(int i=1;i<=N;++i){
            if(!dfn[i])Tarjan(i);
        }
        for(int u=1;u<=N;++u){
            for(int i=head[u];~i;i=edges[i].next){
                int v=edges[i].to;
                if(sccno[u]!=sccno[v]){
                    new_AddEdge(sccno[u],sccno[v]);
                    in[sccno[v]]++;
                }
            }            
        }
        if(Topo()||scc_cnt==1) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
