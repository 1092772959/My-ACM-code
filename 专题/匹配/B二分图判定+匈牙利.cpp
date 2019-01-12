#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;
const int maxn =205;
const int INF =0x3f3f3f3f;

int N;
struct Edge{
    LL val;
    int to,next;
}edges[maxn*maxn];
int head[maxn],tot;
int linker[maxn];
int used[maxn];

void init()
{
    tot=0;
    memset(head,-1,sizeof(head));
    memset(used,0,sizeof(used));
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
            used[v]=1;
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

bool dfs_p(int u,int col)
{
    used[u]=col;
    for(int i=head[u];~i;i=edges[i].next){
        int v = edges[i].to;
        if(!used[v] && !dfs_p(v,-col))  return false;
        else if(used[v]==used[u]) return false;
    }
    return true;
}

//#define LOCAL
int main(){
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,M,u,v,tmp;
    while(scanf("%d%d",&N,&M)==2){
        init();
        for(int i=1;i<=M;++i){
            scanf("%d%d",&u,&v);
            AddEdge(u,v,1);
            AddEdge(v,u,1);
        }       
        bool flag = true;
        for(int i=1;i<=N;++i){
            if(!used[i] && !dfs_p(1,1)){
                flag = false;
                break;
            }
        }
        if(!flag) printf("No\n");
        else printf("%d\n",hungary()/2);
    }
    return 0;
}
