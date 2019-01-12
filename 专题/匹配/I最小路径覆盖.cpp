#include<bits/stdc++.h>
#define Lson rt<<1,l,m
#define Rson rt<<1|1,m+1,r
using namespace std;
typedef long long LL;
const int maxn = 2e3+5;
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
    int u;
    int res=0;
    memset(linker,-1,sizeof(linker));
    for(u=0;u<N;u++){
        memset(used,0,sizeof(used));
        if(dfs(u)) res++;
    }
    return res; 
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,M,u,v,tmp,k;
    while(scanf("%d",&N)==1){
        init();
        for(int i=0;i<N;++i){
            scanf("%d:(%d)",&u,&k);
            for(int j=0;j<k;++j){
                scanf("%d",&v);
                AddEdge(u,v);
                AddEdge(v,u);
            } 
        }
        printf("%d\n",hungary()/2);
    }
    return 0;
}
