#include<iostream>
#include<cstring>
#include<stdio.h>
#include<vector>
#include<string>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;
typedef long long LL;
const int maxn = 3e5+5;
const LL INF = 1ll<<60;
struct Edge{
    int to,next;
    LL val;
};
struct HeapNode{
    LL d;           //费用或路径
    int u;
    bool operator < (const HeapNode & rhs) const{return d > rhs.d;}  
};
struct Dijstra{
    int n,m,tot;
    Edge edges[maxn<<4];
    bool used[maxn];
    LL d[maxn];
    int head[maxn];

    void init(int n){
        this->n = n;
        this->tot=0;
        memset(head,-1,sizeof(head));
    }

    void Addedge(int u,int v ,LL dist){
        edges[tot].to = v;
        edges[tot].val = dist;
        edges[tot].next = head[u];
        head[u] = tot++;
    }

    void dijkstra(int s){   
        memset(used,0,sizeof(used));
        priority_queue<HeapNode> Q;
        for(int i=0;i<=n;++i)    d[i]=INF;
        d[s]=0;
        Q.push((HeapNode){0,s});
        while(!Q.empty()){
            HeapNode x =Q.top();Q.pop();
            int u =x.u;
            if(used[u]) 
                continue;
            used[u]= true;
            for(int i=head[u];~i;i=edges[i].next){
                Edge & e = edges[i];
                if(d[e.to] > d[u] + e.val){
                    d[e.to] = d[u] +e.val;
                    Q.push((HeapNode){d[e.to],e.to});
                }
            }
        }
    }
}G;

int lay[maxn];

//#define LOCAL
int main()
{
    #ifdef LOCAL
    	freopen("in.txt","r",stdin);
    	freopen("out.txt","w",stdout);
   	#endif
    int N,M,T,u,v,cas=1;
    LL tmp,C;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%lld",&N,&M,&C);
        G.init(3*N);
        for(int i=1;i<=N;++i){
            scanf("%d",&tmp);
            G.Addedge(i,tmp+N,0);           //1~N为层,N~2*N为出点，2*N~3*N为入点
            G.Addedge(tmp+2*N,i,0);
        }
        for(int i=1;i<=N-1;++i){
            G.Addedge(N+i,2*N+i+1,C);
            G.Addedge(N+i+1,2*N+i,C);
        }
        for(int i=1;i<=M;++i){
            scanf("%d%d%lld",&u,&v,&tmp);
            G.Addedge(u,v,tmp);
            G.Addedge(v,u,tmp);
        }
        G.dijkstra(1);
        if(G.d[N]==INF) G.d[N]=-1;
        printf("Case #%d: %lld\n",cas++,G.d[N]);
    }  
    return 0;
}
