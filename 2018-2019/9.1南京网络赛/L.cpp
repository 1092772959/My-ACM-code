#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e5+5;
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

LL dist[maxn][11];
bool vis[maxn][11];
Edge edges[maxn<<2];
int head[maxn];
struct Dijstra{
    int n,m,tot;
    int k;
    void init(int n,int k){
        this->n = n;
        this->k = k;
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
        memset(vis,0,sizeof(vis));
        priority_queue<HeapNode> Q;
        memset(dist,0x3f,sizeof(dist));
        dist[s][0]=0;
        Q.push((HeapNode){0,s});
        while(!Q.empty()){
            HeapNode x =Q.top(); Q.pop();
            int lev = x.u/(n+1); 
            int u = x.u%(n+1);
            if(vis[u][lev]) continue;
            vis[u][lev] = 1;
            for(int i=head[u];~i;i= edges[i].next){
                int v =edges[i].to;
                if(dist[u][lev]+edges[i].val<dist[v][lev]){         //同一层中的松弛操作
                    dist[v][lev] = dist[u][lev] + edges[i].val;
                    Q.push((HeapNode){dist[v][lev],lev*(n+1)+v});
                }
                if(lev==k) continue;
                if(dist[v][lev+1]>dist[u][lev]){                    //往下一层推进的松弛操作
                    dist[v][lev+1] = dist[u][lev];
                    Q.push((HeapNode){dist[v][lev+1],(lev+1)*(n+1)+v});
                }
            }
        }
    }
}G;


map<int,map<int,LL> > dp;

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif  
    int T,N,M; scanf("%d",&T);
    while(T--){
        int k;
        scanf("%d %d %d",&N,&M,&k);
        G.init(N,k);
        dp.clear();
        int u,v; LL tmp;
        while(M--){
            scanf("%d %d %lld",&u,&v,&tmp);
            if(!dp[u][v] ||dp[u][v]>tmp){
                dp[u][v] = tmp;
            }
        }
        for(int i=1;i<=N;++i){
            map<int,LL> ::iterator it;
            for(it = dp[i].begin();it!=dp[i].end();++it){
                G.Addedge(i,it->first,it->second);
            }
        }
        G.dijkstra(1);
        printf("%lld\n",dist[N][k]);
    }
    return 0;
}
