//割点/边

#include<iostream>
#include<cstring>
#include<stdio.h>
#include<algorithm>
using namespace std;
const int maxn =1e5+5;
struct Edge{
    int to,next;
}edges[maxn*8];
int pre[maxn],low[maxn],f[maxn],head[maxn],dfn,num,tot;
bool isbridge[maxn];

void init(int n)
{
    num=dfn=tot=0;
    memset(head,-1,sizeof(head));
    memset(pre,0,sizeof(pre));
    memset(low,0,sizeof(low));
    memset(f,0,sizeof(f));
    memset(isbridge,0,sizeof(isbridge));
}

void AddEdge(int u,int v)
{
    edges[num].to= v;
    edges[num].next = head[u];
    head[u]=num++;
}


void tarjan(int u,int fa)
{
    int flag=0;
    pre[u]=low[u]=++dfn;
    for(int i=head[u];i!=-1;i=edges[i].next)
    {
        int v=edges[i].to;
        if(v==fa&&!flag){flag=1;continue;}
        if(!pre[v])
        {
            f[v]=u;
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>pre[u]){
                isbridge[v]=1;
                tot++;
            }
        }
        else low[u]=min(low[u],pre[v]);
    }
}


void LCA(int u,int v)
{
    while(pre[u]<pre[v]){
        if(isbridge[v]){isbridge[v]=false;tot--;}
        v = f[v];
    }
    while(pre[u]>pre[v]){
        if(isbridge[u]){isbridge[u]=false;tot--;}
        u = f[u];
    }
    while(u!=v)
    {
        if(isbridge[u]){tot--;isbridge[u]=false;}
        if(isbridge[v]){tot--;isbridge[v]=false;}
        u=f[u];v=f[v];
    }
}

int main()
{
    int N,M,u,v,tmp,Q;
    int T=1;
    while(~scanf("%d%d",&N,&M),N+M){
        init(N);
        for(int i=0;i<M;++i){
            scanf("%d%d",&u,&v);
            AddEdge(u,v);
            AddEdge(v,u);
        }
        tarjan(1,0);
        printf("Case %d:\n",T++);
        scanf("%d",&Q);
        int s,t;

        for(int i=0;i<Q;++i){
            scanf("%d%d",&u,&v);        //选取low较小的点作为终点
            LCA(u,v);
            printf("%d\n",tot);
        }
    }   
    return 0;
}

//