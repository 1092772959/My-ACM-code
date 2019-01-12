#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL INF =(1ll<<60);
const int maxn =1e6+5;

struct Edge{
    int to,next;
    LL val;
};

struct SPFA{
    int head[maxn];
    Edge edges[maxn];
    LL d[maxn];
    bool inq[maxn];
    int n,tot;
    
    void init(int n){
        this->tot=0;
        this->n = n;
        memset(head,-1,sizeof(head));
    }
    void AddEdge(int u,int v,LL val){
        edges[tot].to = v;
        edges[tot].val = val;
        edges[tot].next = head[u];
        head[u] = tot++;
    }

    void spfa(int s){
        for(int i=0;i<=n;++i){
            inq[i]=false; 
            d[i] = INF;
        }
        queue<int> Q;
        Q.push(s);
        d[s]=0; inq[s] = true;
        while(!Q.empty()){
            int u = Q.front();Q.pop();
            inq[u] =false;
            for(int i = head[u];~i;i=edges[i].next){
                int v = edges[i].to;
                if(d[v]>d[u]+edges[i].val){
                    d[v] = d[u]+edges[i].val;
                    if(!inq[v]){
                        Q.push(v);
                        inq[v] = true;
                    }
                }
            }
        }
    }
}G;

