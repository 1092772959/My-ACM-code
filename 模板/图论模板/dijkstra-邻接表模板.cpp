#include<iostream>
#include<cstring>
#include<stdio.h>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef long long LL;
const int maxn =2e3+5,INF=0x3f3f3f3f;
struct Edge{
    int from,to;
    LL val;
};
struct HeapNode{
    LL d;           //费用或路径
    int u;
    bool operator < (const HeapNode & rhs) const{return d > rhs.d;}  
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
        memset(used,0,sizeof(used));
    }

    void Addedge(int from,int to ,LL dist){
        edges.push_back((Edge){from,to,dist});
        m = edges.size();
        G[from].push_back(m-1);
    }

    void dijkstra(int s){   
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
    int N,M,u,v;
    LL tmp;
    while(~scanf("%d%d",&N,&M)){
        go.init(N);
        for(int i=0;i<M;++i){
            scanf("%d%d%d",&u,&v,&tmp);
            go.Addedge(u,v,tmp);
            go.Addedge(v,u,tmp);
        }
        go.dijkstra(1);
        printf("%d\n",go.d[N]);
    }
    return 0;
}