#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1e3+5;
int N;
struct Edge{
    LL val;
    int to,next;
}edges[maxn<<2];
int head[maxn],tot;
int linker[maxn];
bool used[maxn];

void init()
{
    tot=0;
    memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v, LL val)
{
    edges[tot].val = val;
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
    int u;
    int res=0;
    memset(linker,-1,sizeof(linker));
    for(u=1;u<=N;u++){
        memset(used,0,sizeof(used));
        if(dfs(u)) res++;
    }
    return res; 
}


