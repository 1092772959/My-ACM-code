#include<iostream>
#include<cstring>
#include<stdio.h>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef long long LL;
#define INF (LL)1<<60
const int maxn =1e5+5,maxm = 1e6+5;

bool stop[maxm<<1];
vector<int> res;

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
        memset(p,-1,sizeof(p));
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
                if(d[u]==INF) continue;
                if(d[e.to] > d[u] + e.val){ 
                    d[e.to] = d[u] +e.val;
                    p[e.to] = u;           //记录边的编号
                    Q.push((HeapNode){d[e.to],e.to});
                }
            }
        }
    }
    
}go;

bool dfs(int u)
{
    go.used[u] = true;
    if(u==1) {
        res.push_back(u);
        return true;
    }
    for(int i=0;i<go.G[u].size();++i){
        int id =go.G[u][i];
        Edge e = go.edges[id];
        int v=e.to;
        if(go.used[v]||go.p[u]==v) continue;
        go.used[v] = true;
        if(dfs(v)){
            res.push_back(u);
            return true;
        }
    }
    return false;
}


int main()
{
    int N,M,u,v;
    LL tmp;
    while(scanf("%d%d",&N,&M)==2){
        go.init(N);
        res.clear();
        memset(stop,0,sizeof(stop));
        for(int i=0;i<M;++i){
            scanf("%d%d%lld",&u,&v,&tmp);
            go.Addedge(u,v,tmp);
            go.Addedge(v,u,tmp);
        }
        go.dijkstra(1);

        memset(go.used,0,sizeof(go.used));
        go.used[0]=true;
        if(dfs(0)){
            reverse(res.begin(),res.end());
            printf("%d",res.size());
            for(int i=0;i<res.size();++i){
                printf(" %d",res[i]);
            }
            printf("\n");
        }
        else
            printf("impossible\n");
    }
    return 0;
}