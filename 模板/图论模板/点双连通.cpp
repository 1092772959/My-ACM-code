#include<bits/stdc++.h>
using namespace std;
const int maxn =1e3+5;
const int maxm = 1e6+5;
struct Edge{
    int to,next;
}edges[maxm<<1];
bool instack[maxn];
int bccno[maxn],head[maxn],dfn[maxn],low[maxn],clk,top,scc;
stack<int> S;

void init()
{
    clk = top = scc = 0;
    memset(head,-1,sizeof(head));
    memset(dfn,0,sizeof(dfn));
    memset(bccno,0,sizeof(bccno));
    memset(instack,0,sizeof(instack));
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
    for(int i=head[u];~i;i=edges[i].next){
        v = edges[i].to;
        if(i==(id^1))   continue;
        if(!dfn[v]){
            Tarjan(v,i);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<=low[v]){     //找到一个双连通分量
                scc++;                  //从1开始
                while(true){
                    int x =S.top();S.pop();
                    bccno[x]=scc;               //确定分量编号
                    instack[x]=false;
                    if(x==v)    break;      //找到了自己就要停止标号
                }
            }
        }
        else if(instack[v])
            low[u]= min(low[u],dfn[v]);
    }
    
}
