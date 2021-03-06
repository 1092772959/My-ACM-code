#include<iostream>
#include<stdio.h>
#include<stack>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
const int maxn =3e4+5;
struct Edge{
    int to,next;
}edges[maxn<<2];
bool instack[maxn];
int bccno[maxn],head[maxn],dfn[maxn],low[maxn],degree[maxn],clk,top,scc;
stack<int> S;

void init()
{
    clk = top = scc =0;
    memset(head,-1,sizeof(head));
    memset(dfn,0,sizeof(dfn));
    memset(bccno,0,sizeof(bccno));
    memset(instack,0,sizeof(instack));
    memset(degree,0,sizeof(degree));
}

void AddEdge(int u,int v)
{
    edges[top].to = v;
    edges[top].next =head[u];
    head[u] = top++;
}

void Tarjan(int u,int id)
{
    int v;
    low[u]=dfn[u]=++clk;
    S.push(u);
    instack[u]=true;
    for(int i=head[u];i!=-1;i=edges[i].next){
        v = edges[i].to;
        if(i==(id^1))   continue;
        if(!dfn[v]){
            Tarjan(v,i);
            low[u]=min(low[u],low[v]);
        }
        else if(instack[v])
            low[u]= min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u]){     //找到一个双连通分量
        scc++;                  //从1开始
        int x;
        while(true){
            x =S.top();S.pop();
            bccno[x]=scc;               //确定分量编号
            instack[x]=false;
            if(x==u)    break;      //找到了自己就要停止标号
        }
    }
}

int main()
{
    int N,M,Q,u,v,tmp;
    while(scanf("%d%d",&N,&M)==2){
        init();
        for(int i=0;i<M;++i){
            scanf("%d%d",&u,&v);
            AddEdge(u,v);
            AddEdge(v,u);
        }
        for(int i=1;i<=N;++i){
            if(!dfn[i]){
                Tarjan(i,-1);
            }
        }
        scanf("%d",&Q);
        for(int i=0;i<Q;++i){
            scanf("%d%d",&v,&u);
            if(bccno[v]==bccno[u])  printf("Yes\n");
            else printf("No\n");
        }
    }
    return 0;
}