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
int sccnum[maxn],ind[maxn],outd[maxn];

void init(int N)
{
    dfn=scc_cnt=0;
    memset(pre,0,sizeof(pre));
    memset(low,0,sizeof(low));
    memset(sccnum,0,sizeof(sccnum));
    memset(sccno,0,sizeof(sccno));
    memset(ind,0,sizeof(ind));
    memset(outd,0,sizeof(outd));
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

int main()
{
    int T,N,M,u,v,tmp;
    scanf("%d",&T);
    for(int cas=1;cas<=T;++cas){
        scanf("%d%d",&N,&M);
        init(N);
        for(int i=0;i<M;++i){
            scanf("%d%d",&u,&v);
            AddEdge(u,v);
        }
        for(int i=1;i<=N;++i){
            if(!pre[i])
                Tarjan(i);
        }

        printf("Case %d: ",cas);
        if(scc_cnt==1)  {printf("-1\n");continue;}
        
        for(int i=1;i<=N;++i){
            for(int j = 0;j<G[i].size();++j){
                v = G[i][j];
                if(sccno[i]!=sccno[v]){
                    nG[sccno[i]].push_back(v);
                    outd[sccno[i]]++;
                    ind[sccno[v]]++;
                }
            }
        }
        int mn=INF;
        for(int i=1;i<=scc_cnt;++i){
            if(!outd[i]||!ind[i]){
                if(sccnum[i]<mn)
                    mn =sccnum[i];
            }
        }
        LL ans = (LL)(N*(N-1))-M-(LL)(mn*(N-mn));
        printf("%lld\n",ans);
    }
    return 0;
}