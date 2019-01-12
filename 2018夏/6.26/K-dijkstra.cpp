#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =2e5+5,INF=0x3f3f3f3f;
struct Edge{
    int from,to;
    LL val;
};
struct HeapNode{
    LL d;           //费用或路径
    int u;
    bool operator < (const HeapNode & rhs) const{
        return d > rhs.d;
    }  
};
struct Dijstra{
    int n,m;
    vector<Edge> edges;
    vector<int> G[maxn];
    bool used[maxn];
    LL d[maxn];
    int p[maxn];
    
    void init(int n){
        this->n = n;
        for(int i=0;i<=n;++i)    G[i].clear();
        edges.clear();
    }

    void Addedge(int from,int to ,LL dist){
        edges.push_back((Edge){from,to,dist});
        m = edges.size();
        G[from].push_back(m-1);
    }

    void dijkstra(int s){    //s 源点
        priority_queue<HeapNode> Q;
        //for(int i=0;i<=n;++i)    d[i]=INF;
        d[s]=0;
        memset(used,0,sizeof(used));
        Q.push((HeapNode){0,s});
        while(!Q.empty()){
            HeapNode x =Q.top();Q.pop();
            int u =x.u;
            if(used[u]) continue;
            used[u]= true;
            for(int i=0;i<G[u].size();++i){
                Edge & e = edges[G[u][i]];
                if(d[e.to] > d[u] + e.val){
                    d[e.to] = d[u] +e.val;
                    p[e.to] = G[u][i];
                    Q.push((HeapNode){d[e.to],e.to});
                }
            }
        }
    }
}go;

int main()
{
    int N,M,from,to;
    LL cost;
    while(scanf("%d%d",&N,&M)==2){
        go.init(N+1);
        for(int i=0;i<M;++i){
            scanf("%d%d%lld",&from,&to,&cost);
            go.Addedge(from,to,2*cost);
            go.Addedge(to,from,2*cost);
        }
        for(int i=1;i<=N;++i){
            scanf("%lld",&cost);
            go.Addedge(N+1,i,0);
            go.d[i]=cost;
        }
        go.dijkstra(N+1);
        for(int i=1;i<N;++i)    printf("%lld ",go.d[i]);
        printf("%lld\n",go.d[N]);
    }
    return 0;
}