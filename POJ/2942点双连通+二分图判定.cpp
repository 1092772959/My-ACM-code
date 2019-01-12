#include<iostream>
#include<stdio.h>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
#include<cmath>
#include<stack>
using namespace std;
const int maxn =1e3+5;
const int maxm = 1e6+5;
struct Edge{
    int to,next;
}edges[maxm<<1];
bool instack[maxn];
int bccno[maxn],head[maxn],dfn[maxn],low[maxn],clk,top,scc;
stack<int> S;
int col[maxn];
int ans;
bool check[maxn];
int tag[maxn];
bool can[maxn];

bool dfs(int u,int c)
{
    col[u]=c;
    for(int i=head[u]; i!=-1; i=edges[i].next){
        int v=edges[i].to;
        if(!check[v])
            continue;
        if(col[v]!=-1){
            if(col[v]==c)
                return false;
            continue;
        }
        if(!dfs(v,!c))
            return false;
    }
    return true;
}
void init()
{
    clk = top = scc = 0;
    memset(head,-1,sizeof(head));
    memset(dfn,0,sizeof(dfn));
    memset(bccno,0,sizeof(bccno));
    memset(instack,0,sizeof(instack));
    memset(can,0,sizeof(can));
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
                int cnt=0;
                memset(check,0,sizeof(check));         //判断是否在同一个双连通分量内
                while(true){
                    int x =S.top();S.pop();
                    tag[cnt++] = x;
                    bccno[x]=scc;               //确定分量编号
                    instack[x]=false;
                    check[x] =true;
                    if(x==v)    break;      //找到了自己就要停止标号
                }
                check[u] = true;
                memset(col,-1,sizeof(col));          //判断双连通分量内是否有奇圈
                if(!dfs(u,0)){ 
                    can[u] = true;
                    while(cnt--)  can[tag[cnt]] = true;
                }
            }
        }
        else if(instack[v])
            low[u]= min(low[u],dfn[v]);
    }
    
}

int G[maxn][maxn];

int main()
{
    #ifndef ONLINE_JUDGE
         freopen("in.txt","r",stdin);
         freopen("out.txt","w",stdout);
    #endif
    int T,N,M,u,v,tmp;
    while(scanf("%d%d",&N,&M)==2){
        if(!N) break;  
        init();
        memset(G,0,sizeof(G));
        for(int i=1;i<=M;++i){
            scanf("%d%d",&u,&v);
            G[u][v] = G[v][u] = 1;
        }
        for(int i=1;i<=N;++i){
            for(int j=i+1;j<=N;++j){
                if(!G[i][j]){
                    AddEdge(i,j);
                    AddEdge(j,i);
                }
            }
        }
        for(int i=1;i<=N;++i){
            if(!dfn[i])
                Tarjan(i,-1);
        }
        ans= N;
        for(int i=1;i<=N;++i){
            if(can[i]) ans--;
        }
        printf("%d\n",ans);    
    }
    return 0;
}
