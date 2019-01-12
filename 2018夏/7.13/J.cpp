#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 2e2+5;
struct Node{
    LL x,y;
}s[maxn],t[maxn];
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

bool dfs(int u,LL limit){
    int v,st,ed;
    for(int i=head[u];~i;i = edges[i].next){
        v = edges[i].to;
        if(!used[v] && edges[i].val <=limit){
            used[v]=true;
            if(linker[v]==-1||dfs(linker[v],limit)){
                linker[v]=u;
                return true;
            }
        }
    }
    return false;
}

bool hungary(LL limit){
    int u;
    int res=0;
    memset(linker,-1,sizeof(linker));
    for(u=1;u<=N;u++){
        memset(used,0,sizeof(used));
        if(dfs(u,limit)) res++;
    }
    return res==N; 
}

//#define LOCAL
int main()
{
    #ifdef LOCAL
    	freopen("in.txt","r",stdin);
    	freopen("out.txt","w",stdout);
   	#endif
    int T;
    LL X,Y;
    while(scanf("%d",&N)==1){
        init();
        for(int i=1;i<=N;++i)
            scanf("%lld%lld",&s[i].x,&s[i].y);
        for(int i=1;i<=N;++i)
            scanf("%lld%lld",&t[i].x,&t[i].y);
        LL mx=-1;
        for(int i=1;i<=N;++i){
            for(int j=1;j<=N;++j){
                LL dist = abs(s[i].x-t[j].x)+abs(s[i].y-t[j].y);
                AddEdge(i,j+N,dist);
                AddEdge(j+N,i,dist);
                mx = max(mx,dist);
            }
        }
        LL L=0,R=mx,mid;
        while(R-L>1){
            mid = L+(R-L)/2;
            if(hungary(mid)) R = mid;
            else L = mid;
        }
        printf("%lld\n",R);
    }
    return 0;
}
