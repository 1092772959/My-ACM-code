#include<iostream>
#include<vector>
#include<stdio.h>
#include<algorithm>
#include<stack>
//#include<bits/stdc++.h>
using namespace std;
const int maxn =105;
vector<int> G[maxn],nG[maxn];
stack<int> S;
int pre[maxn],low[maxn],sccno[maxn],ind[maxn],outd[maxn],dfn,scc_cnt;

void init(int N)
{
    dfn=scc_cnt=0;
    for(int i=0;i<=N;++i){
        G[i].clear();
        nG[i].clear();
        ind[i]=outd[i]=pre[i]=low[i]=sccno[i]=0;
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
            if(x==u)break;
        }
    }    
}

int main()
{
    int N,tmp,u,v;
    while(~scanf("%d",&N)){
        init(N);
        int totin=0,totout=0;
        for(int i=1;i<=N;++i){
            while(scanf("%d",&u),u){
                AddEdge(i,u);
            }
        }
        for(int i=1;i<=N;++i){          //强连通分量
            if(!pre[i])
                Tarjan(i);
        }
        
        for(int i=1;i<=N;++i){       //缩点建新图
            for(int j=0;j<G[i].size();++j){
                int u = G[i][j];
                if(sccno[u]!=sccno[i]){
                    nG[sccno[i]].push_back(sccno[u]);
                    ind[sccno[u]]++;
                    outd[sccno[i]]++;
                }
            }
        }
        
        for(int i=1;i<=scc_cnt;++i){
            if(!ind[i]) totin++;
            if(!outd[i])    totout++;
        }

        printf("%d\n",totin);
        if(scc_cnt==1)  printf("0\n");
        else printf("%d\n",max(totin,totout));
    }
    return 0;
}
