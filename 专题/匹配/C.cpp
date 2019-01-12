#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;
const int maxn =305;
const int INF =0x3f3f3f3f;

int N,P;
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
    for(u=1;u<=P;u++){
        memset(used,0,sizeof(used));
        if(dfs(u)) res++;
    }
    return res; 
}


#define LOCAL
int main(){
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,M,u,v,tmp;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&P,&N);
        init();
        for(int i=1;i<=P;++i){
            scanf("%d",&tmp);
            for(int j=1;j<=tmp;++j){
                scanf("%d",&v);
                AddEdge(i,P+v,1);
            }
        }
        if(hungary()==P) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
