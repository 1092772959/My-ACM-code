#include<iostream>
#include<stdio.h>
#include<cstring>
#include<queue>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
typedef int LL;
const int maxn =1e3+5;
const int maxm =5e4+5;
const LL INF =0x3f3f3f3f;
struct Edge{
    int from,to,next;
    LL val;
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

    void Addedge(int u,int v ,LL dist){
        edges[tot].to = v;
        edges[tot].val = dist;
        edges[tot].next = head[u];
        head[u] = tot++;
    }

    int dijkstra(int s,int limit){   
        memset(used,0,sizeof(used));
        priority_queue<HeapNode> Q;
        for(int i=0;i<=n;++i)    d[i]=INF;          //d[i]记录的是到i点走过的权值超过limit的边数
        d[s]=0;
        Q.push((HeapNode){0,s});
        while(!Q.empty()){
            HeapNode x =Q.top();Q.pop();
            int u =x.u;
            if(d[u]<x.d) continue;                      //没有更新的必要,不加判断也对，但是慢一点点
            for(int i=head[u];~i;i=edges[i].next){
                int nd = d[u]+(edges[i].val>=limit?1:0);
                int v = edges[i].to;
                if (d[v] > nd){
			        d[v] = nd;
				    Q.push({d[v], v});
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
    int N,M,K,u,v,k;
    LL tmp;
    while(scanf("%d%d%d",&N,&M,&K)==3){
        G.init(N);
        int maxL = -1;
        for(int i=0;i<M;++i){
            scanf("%d%d%d",&u,&v,&tmp);
            G.Addedge(u,v,tmp);
            G.Addedge(v,u,tmp);
            if(maxL<tmp) maxL = tmp;
        }
        int res = G.dijkstra(1,0);
        if(res==INF){
            printf("-1\n");
            continue;
        }
        else if(res<=K){                //
            printf("0\n");
            continue;
        }
        int L =0,R=maxL,mid,ans;
        while(L<R){
            mid  =(L+R)>>1;
            if(G.dijkstra(1,mid)>K){    
                ans = mid;              //此时能确定的是：肯定要花费mid的代价
                L = mid+1;
            }
            else R =mid-1;
        }
        printf("%d\n",ans);
    }
    return 0;
}
