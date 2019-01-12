#include<stack>
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#include<cstring>
using namespace std;
typedef long long LL;
const int MAXN = 5e3+10;
vector<int> G[MAXN],nG[MAXN];
int dfn[MAXN],low[MAXN],sccno[MAXN],dfs_clock,scc_cnt;
int out[MAXN],ans[MAXN];
stack<int> S;
void init(int N)
{
    dfs_clock=scc_cnt=0;
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(out,0,sizeof(out));
    memset(sccno,0,sizeof(sccno));
    for(int i=0;i<=N;++i)
        G[i].clear();
}

void Tarjan(int u)
{
    int v;
    dfn[u]=low[u]=++dfs_clock;
    S.push(u);
    for(int i=0;i<G[u].size();++i){
        v = G[u][i];
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

int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int T,N,M,u,v; 
    while(scanf("%d%d",&N,&M)==2){
        if(!N) break;
        init(N);
        for(int i=1;i<=M;++i){
            scanf("%d%d",&u,&v);
            G[u].push_back(v);
        }
        for(int i=1;i<=N;++i){
            if(!dfn[i])
                Tarjan(i);
        }
        for(int i=1;i<=N;++i){
            for(int j=0;j<G[i].size();++j){
                v = G[i][j];
                if(sccno[i]!=sccno[v]){
                    out[sccno[i]]++;
                }
            }
        }
        int cnt=0;
        for(int i=1;i<=N;++i){
            if(!out[sccno[i]])
                ans[cnt++]=i;
        }
        if(!cnt) {printf("\n");continue;}
        for(int i=0;i<cnt;++i){
            printf("%d%c",ans[i],i==cnt-1?'\n':' ');
        }
    }
    return 0;
}