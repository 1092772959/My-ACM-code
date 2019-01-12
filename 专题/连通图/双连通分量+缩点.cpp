/*POJ 3177  ---边双连通 缩点
在同一个边双连通分量中，任意两点都有至少两条独立路可达，所以同一个边双连通分量里的所有点可以看做同一个点。
缩点后，新图是一棵树，树的边就是原无向图的桥。
现在问题转化为：在树中至少添加多少条边能使图变为双连通图。
结论：添加边数=（树中度为1的节点数+1）/2
具体方法为，首先把两个最近公共祖先最远的两个叶节点之间连接一条边，
这样可以把这两个点到祖先的路径上所有点收缩到一起，因为一个形成的环一定是双连通的。
然后再找两个最近公共祖先最远的两个叶节点，这样一对一对找完，恰好是(leaf+1)/2次，把所有点收缩到了一起。
其实求边双连通分量和求强连通分量差不多，每次访问点的时候将其入栈，当low[u]==dfn[u]时就说明找到了一个连通的块，
则栈内的所有点都属于同一个边双连通分量
*/
#include<iostream>
#include<stdio.h>
#include<stack>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
const int maxn =5e4+5;
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
    int N,M,v,u,tmp;
    while(~scanf("%d%d",&N,&M)){
        init();
        for(int i=0;i<M;++i){
            scanf("%d%d",&u,&v);
            AddEdge(u,v);
            AddEdge(v,u);
        }
        Tarjan(1,-1);
        for(int i=1;i<=N;++i){
            for(int j =head[i];j!=-1;j=edges[j].next){
                v = edges[j].to;
                if(bccno[i]!=bccno[v]){     //根据分量编号缩点，计算度
                    degree[bccno[i]]++;     
                }
            }
        }
        int res=0;
        for(int i=1;i<=scc;++i){
            if(degree[i]==1)
                res++;
        }
        printf("%d\n",(res+1)/2);
    }
    return 0;
}
