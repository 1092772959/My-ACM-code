#include<iostream>
#include<stdio.h>
#include<cstring>
#include<queue>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long LL;
const int maxn =1e4+5;
const int maxm =1e5+5;
const LL INF =1ll<<60;
struct Edge{
    int from,to,next;
    LL val,cap;
    bool operator <(const Edge &e) const {return val<e.val;}
};

struct HeapNode{
    LL d;           //费用或路径
    int u;
    bool operator < (const HeapNode & rhs) const{return d > rhs.d;}  
};
struct Dijstra{
    int n,m,tot;
    Edge edges[maxm];
    bool used[maxn];
    LL d[maxn];
    int head[maxn];

    void init(int n){
        this->n = n;
        this->tot=0;
        memset(head,-1,sizeof(head));
    }

    void Addedge(int u,int v ,LL dist, LL cap){
        edges[tot].to = v;
        edges[tot].val = dist;
        edges[tot].cap = cap;
        edges[tot].next = head[u];
        head[u] = tot++;
    }

    LL dijkstra(int s,LL limit){   
        memset(used,0,sizeof(used));
        priority_queue<HeapNode> Q;
        for(int i=0;i<=n;++i)    d[i]=INF;          
        d[s]=0; 
        Q.push((HeapNode){0,s});
        while(!Q.empty()){
            HeapNode x =Q.top();Q.pop();
            int u =x.u;                 
            if(used[u]) continue;
            used[u]=true;
            for(int i =head[u];~i;i = edges[i].next){
                Edge e = edges[i];
                if(e.cap<limit) continue;            //选择超过limit的路线
                int v = e.to;
                if(!used[v] && d[v]>d[u]+e.val){
                    d[v] = d[u]+e.val;
                    Q.push((HeapNode){d[v],v});
                }
            }
        }
        return d[n];                  
    }
}G;

#define LOCAL
int main()
{
    #ifdef LOCAL
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int cas,N,M,K,u,v,k;
    LL d,c,T;
    scanf("%d",&cas);
    while(cas--){
        scanf("%d%d%lld",&N,&M,&T);
        G.init(N);
        LL L=0,R=0,mid,ans=0;
        for(int i=1;i<=M;++i){
            scanf("%d%d%lld%lld",&u,&v,&c,&d);
            G.Addedge(u,v,d,c);
            G.Addedge(v,u,d,c);
            R=max(R,c);
        }
        while(L<=R){            //二分答案
            mid = (L+R)>>1;
            if(G.dijkstra(1,mid)<=T){        //只用mid及以上容量的路能在T时间内到达
                ans = mid;
                L = mid+1;    
            }
            else R =mid-1;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
