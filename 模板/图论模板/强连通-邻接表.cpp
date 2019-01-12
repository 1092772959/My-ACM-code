#include<iostream>
#include<stack>
#include<cstring>
#include<vector>
#include<algorithm>
#include<stdio.h>
using namespace std;
typedef long long LL;
const int maxn =1e5+5;
const int INF =0x3f3f3f3f;
vector<int> G[maxn],nG[maxn];
stack<int> S;
int pre[maxn],low[maxn],sccno[maxn],dfn,scc_cnt;
int sccnum[maxn];
void init(int N)
{
    dfn=scc_cnt=0;
    memset(pre,0,sizeof(pre));
    memset(sccnum,0,sizeof(sccnum));
    memset(sccno,0,sizeof(sccno));
    for(int i=0;i<=N;++i){
        G[i].clear();
        nG[i].clear();
    }
}
void AddEdge(int u,int v)   {G[u].push_back(v);}
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
            sccnum[scc_cnt]++;
            if(x==u)break;
        }
    }    
}