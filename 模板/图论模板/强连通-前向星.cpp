#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e6+5;
struct Edge{
    int v,next;  
}edges[maxn];
int head[maxn],tot;
stack<int> S;
int pre[maxn],low[maxn],sccno[maxn],dfn,scc_cnt;
int sccnum[maxn];
void init()
{
    tot = dfn = scc_cnt=0;
    memset(pre,0,sizeof(pre));
    memset(sccnum,0,sizeof(sccnum));
    memset(sccno,0,sizeof(sccno));
    memset(head,-1,sizeof(head));
}
void AddEdge(int u,int v)   {
    edges[tot] = (Edge){v,head[u]};
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
            sccnum[scc_cnt]++;
            if(x==u)break;
        }
    }    
}