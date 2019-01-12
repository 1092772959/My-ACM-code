#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =3e4+5;
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
