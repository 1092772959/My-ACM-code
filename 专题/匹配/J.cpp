#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;
const int maxn =125;
int N;
struct Edge{
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

int main(){
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,M,u,v,tmp;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d%d",&N,&M);
        for(int i=1;i<=M;++i){
            scanf("%d%d",&u,&v);
            AddEdge(u,v);
        }
        int res = N-hungary();              
        printf("%d\n",res);
    }
    return 0;
}
