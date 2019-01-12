#include<iostream>
#include<stdio.h>
#include<cstring>
#include<queue>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long LL;
const int maxn =5e4+5;
const LL INF =(1ll<<60);
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
    Edge edges[maxn<<2];
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
            if(used[u]) continue;
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

LL w[maxn];

#define LOCAL
int main()
{
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,N,M,u,v;
    LL tmp;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&N,&M);
        G.init(N);
        for(int i=1;i<=N;++i)   scanf("%lld",&w[i]);
        for(int i=1;i<=M;++i){
            scanf("%d%d%lld",&u,&v,&tmp);
            G.Addedge(u,v,tmp);
            G.Addedge(v,u,tmp);
        }
        G.dijkstra(1);  
        LL res=0;
        bool flag = true;
        for(int i=2;i<=N;++i){
            if(G.d[i]==INF){
                flag = false;
                break;
            } 
            res+=G.d[i]*w[i];
        }
        if(!flag) printf("No Answer\n");
        else printf("%lld\n",res);
    }
    return 0;
}
