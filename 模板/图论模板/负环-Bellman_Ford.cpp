#include<bits/stdc++.h>
typedef long long LL;
const int maxn =1e2+5;
const int INF =0x3f3f3f3f;
struct Edge{
    int from,to,next;
    double cost;  
}edges[maxn<<2];
int tot,head[maxn];
double d[maxn];

void init()
{
    memset(head,-1,sizeof(head));
    tot=0;
}

void Addedge(int u,int v,double val)
{
    edges[tot].from = u;
    edges[tot].to = v;
    edges[tot].cost  = val;
    edges[tot].next = head[u];
    head[u]=tot++;
}

int N;

bool bellman_ford()
{
    memset(d,0,sizeof(d));
    for(int i=1;i<=N;++i){
        for(int j=0;j<tot;++j){
            Edge e = edges[j];
            if(d[e.to] > d[e.from] + e.cost){      
                d[e.to] = d[e.from] + e.cost;
                if(i==N) return true;               //第N次还在更新说明有负环
            }       
        }
    }
    return false;       //无环
}
