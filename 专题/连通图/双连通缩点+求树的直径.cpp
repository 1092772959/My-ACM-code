#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include<stdio.h>
using namespace std;
const int maxn =2e5+5;
struct Edge{
    int to,next;
}edges[maxn*8];
bool instack[maxn],vis[maxn];
int bccno[maxn],head[maxn],dfn[maxn],low[maxn],clk,top,bcc,tot;
stack<int> S;
vector<int> nG[maxn];
int dep[maxn];
int mx;

void init(int N)
{
    for(int i=0;i<=N;++i)   nG[i].clear();
    clk = top = bcc =tot=0;
    memset(head,-1,sizeof(head));
    memset(dfn,0,sizeof(dfn));
    memset(instack,0,sizeof(instack));
    memset(dep,0,sizeof(dep));
    memset(vis,0,sizeof(vis));
}

void AddEdge(int u,int v)
{
    edges[top].to = v;
    edges[top].next =head[u];
    head[u] = top++;
}

void Tarjan(int u,int id)       //边双连通
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
            if(low[v]>dfn[u]){              //统计割边
                tot++;
            }
        }
        else if(instack[v])
            low[u]= min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u]){     //找到一个双连通分量
        bcc++;                  //从1开始
        int x;
        while(true){
            x =S.top();S.pop();
            bccno[x]=bcc;           //确定分量编号
            instack[x]=false;
            if(x==u)    break;      //找到了自己就要停止标号
        }
    }
}

void bfs(int u)
{
    queue<int> Q;
    Q.push(u);
    vis[u]=true;
    int x,v;
    while(!Q.empty()){
        x =Q.front(); Q.pop();
        for(int i=0;i<nG[x].size();++i){
            v = nG[x][i];
            if(vis[v])  
                continue;
            dep[v] = dep[x]+1;
            Q.push(v);
            vis[v]=true;
        }
    }
}

int main()
{
    int N,M,u,v,tmp;
    while(~scanf("%d%d",&N,&M)){
        if(N+M==0)  break;
        init(N);
        for(int i=0;i<M;++i){
            scanf("%d%d",&u,&v);
            AddEdge(u,v);
            AddEdge(v,u);
        }
        
        Tarjan(1,-1);
        //缩点
        for(int i=1;i<=N;++i){
            for(int j=head[i];j!=-1;j=edges[j].next){
                v = edges[j].to;
                if(bccno[i]!=bccno[v]){
                    nG[bccno[i]].push_back(bccno[v]);    
                }
            }
        }
        //求缩点后生成树的直径
        mx=1;
        bfs(1);
        for(int i=1;i<=N;++i){
            if(dep[mx]<dep[i])
                mx=i;
        }
        memset(dep,0,sizeof(dep));
        memset(vis,0,sizeof(vis));
        bfs(mx);
        for(int i=1;i<=N;++i){
            if(dep[mx]<dep[i])
                mx=i;
        }
        int res = tot-dep[mx];
        printf("%d\n",res);
    }
    return 0;
}