#include<iostream>
#include<cstring>
#include<stdio.h>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
#define INF 0x3f3f3f3f
typedef long long LL;
const int maxn =2e3+5;
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
}go,back;

int main()
{
    int T,cas=1,S,N,M,u,v,tmp;
    while(scanf("%d%d%d",&N,&M,&S)==3){
        go.init(N);back.init(N);
        for(int i=0;i<M;++i){
            scanf("%d%d%d",&u,&v,&tmp);
            go.Addedge(u,v,tmp);
            back.Addedge(v,u,tmp);
        }
        go.dijkstra(S);
        back.dijkstra(S);
        LL res=-1;
        for(int i=1;i<=N;++i){
            if(res<go.d[i]+back.d[i]){
                res = go.d[i]+back.d[i];
            }
        }
        printf("%lld\n",res);
    }
    return 0;
}


