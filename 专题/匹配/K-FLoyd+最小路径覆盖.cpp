#include<iostream>
#include<stdio.h>
#include<cmath>
#include<cstring>
#define Lson rt<<1,l,m
#define Rson rt<<1|1,m+1,r
using namespace std;
typedef long long LL;
const int maxn = 1e3+5,maxm = 2e5+5;
int N;
struct Edge{
    int to,next;
}edges[maxm];
int head[maxn],tot;
int linker[maxn];
bool used[maxn];

void init()
{
    tot=0;
    memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v)
{
    edges[tot].to = v;
    edges[tot].next = head[u];
    head[u] = tot++;
}

bool dfs(int u){
    int v,st,ed;
    for(int i=head[u];~i;i = edges[i].next){
        v = edges[i].to;
        if(!used[v]){
            used[v]=true;
            if(linker[v]==-1||dfs(linker[v])){
                linker[v]=u;
                return true;
            }
        }
    }
    return false;
}

int hungary(){
    int res=0;
    memset(linker,-1,sizeof(linker));
    for(int u=1;u<=N;u++){
        memset(used,0,sizeof(used));
        if(dfs(u)) res++;
    }
    return res; 
}

void Floyd()
{
    for(int u=1;u<=N;++u){
        for(int i = head[u];~i;i =edges[i].next){
            int v=edges[i].to;
            for(int j=head[v];~j;j=edges[j].next){
                AddEdge(u,edges[j].to);
            }
        }
    }
}

void debug()
{
    
}

int main()
{
    int T,M,u,v,tmp,k;
    while(scanf("%d%d",&N,&M)==2){
        if(!N) break;
        init();
        for(int i=1;i<=M;++i){
            scanf("%d%d",&u,&v);
            AddEdge(u,v);
        }
        Floyd();      
        printf("%d\n",N-hungary());
    }
    return 0;
}
