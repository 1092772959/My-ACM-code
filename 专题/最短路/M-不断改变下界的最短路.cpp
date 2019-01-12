#include<iostream>
#include<cstring>
#include<stdio.h>
#include<vector>
#include<string>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;
typedef int LL;
const int maxn =1e3+5;
const LL INF =0x3f3f3f3f;
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
    Edge edges[maxn<<8];
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
        Q.push((HeapNode){d[s],s});
        while(!Q.empty()){
            HeapNode x =Q.top();Q.pop();
            int u =x.u; 
            if(used[u])    continue;
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

struct Node{
    LL P;
    int L,X;
    vector<int> item,cost;
}vis[maxn];


//#define LOCAL
int main()
{
    #ifdef LOCAL
    	freopen("in.txt","r",stdin);
    	freopen("out.txt","w",stdout);
   	#endif
    int N,M,u,v,a;
    LL tmp,b;
    while(scanf("%d%d",&M,&N)==2){
        for(int i=1;i<=N;++i){
            scanf("%d%d%d",&vis[i].P,&vis[i].L,&vis[i].X);
            vis[i].item.clear();
            vis[i].cost.clear();
            for(int j=1;j<=vis[i].X;++j){
                scanf("%d%d",&a,&b);
                vis[i].item.push_back(a);
                vis[i].cost.push_back(b);
            }
        }
        LL res=INF;
        for(int i=1;i<=N;++i){
            G.init(N+1);
            int low = vis[i].L;
            for(int j=1;j<=N;++j)
                G.Addedge(N+1,j,vis[j].P);
            for(int j=1;j<=N;++j){
                if(low>vis[j].L || vis[j].L-low>M) continue;
                for(int k=0;k<vis[j].X;++k){
                    u = vis[j].item[k];
                    if(vis[u].L-low>M || low>vis[u].L) continue;
                    G.Addedge(u,j,vis[j].cost[k]);   
                }
            }
            G.dijkstra(N+1);
            res = min(res,G.d[1]);   
        }
        printf("%d\n",res);
    }
    return 0;
}
