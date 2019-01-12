#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstring>
using namespace std;
const int maxn =1e5+5;
struct Edge{
    int to,next;
}edges[maxn*4];
int pre[maxn],low[maxn],f[maxn],head[maxn],dfn,tot,top;
bool judge[maxn];
void init()
{
    dfn=tot=top=0;
    memset(pre,0,sizeof(pre));
    memset(low,0,sizeof(low));
    memset(head,-1,sizeof(head));
    memset(judge,0,sizeof(judge));
}

int Find(int x)
{
    return f[x]==x? x:f[x] =Find(f[x]);
}

void Union(int u,int v)
{
    int fu= Find(u);
    int fv = Find(v);
    if(fu!=fv){             //后向前并
        f[fv] =fu;
    }
}

void AddEdge(int u,int v)
{
    edges[top].to =v;
    edges[top].next = head[u];
    head[u] = top++;
}

void Tarjan(int u,int fa,int id)            //id表示边的序号
{
    f[u]=fa;
    pre[u] = low[u]= ++dfn;
    int v;
    for(int i=head[u];i!=-1;i=edges[i].next){
        v = edges[i].to;
        if(i==(id^1))   continue;   //实际上是一条边 没有访问的必要 但需要考虑平行边
        if(!pre[v]){
            Tarjan(v,u,i);
            low[u] = min(low[u],low[v]);
        }
        else
            low[u]=min(low[u],pre[v]);
        
        if(low[v]>pre[u]){
            tot++;
            judge[v]=true;
        }
        else
            Union(u,v);             //缩点
    }   
}


void LCA(int u,int v)
{
    if(pre[v]<pre[u])
        swap(u,v);
    while(pre[v]>pre[u]){
        if(judge[v]){tot--;judge[v]=false;}
        v = f[v];
    }
    while(u!=v){
        if(judge[u]){tot--;judge[u]=false;}
        if(judge[v]){tot--;judge[v]=false;}
        u = f[u];
        v = f[v];
    }
}

int main()
{
    int N,M,u,v,tmp,Q;
    int T=1;
    while(~scanf("%d%d",&N,&M),N+M){
        init();
        for(int i=0;i<M;++i){
            scanf("%d%d",&u,&v);
            AddEdge(u,v);
            AddEdge(v,u);
        }
        Tarjan(1,1,-1);
        printf("Case %d:\n",T++);
        scanf("%d",&Q);
        for(int i=0;i<Q;++i){
            //for(int i=1;i<=N;++i)   cout<<Find(i)<<" "; cout<<endl;
            //for(int i=1;i<=N;++i)   cout<<judge[i]<<" "; cout<<endl;
            scanf("%d%d",&u,&v);       
            LCA(u,v);
            printf("%d\n",tot);
        }
        printf("\n");
    }   
    return 0;
}

/*
4 4
1 2
2 1
2 3
3 4
3
1 2
2 3
3 4
*/