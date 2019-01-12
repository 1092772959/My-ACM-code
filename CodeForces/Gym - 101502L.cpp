#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e6+5;
const LL INF =(1LL<<60);
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
    Edge edges[maxn<<2];
    bool used[maxn];
    LL d[maxn];
    int head[maxn];

    void init(int n){
        this->n = n;
        this->tot = 0;
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

LL dp[25005][26];
vector<int> pt[maxn];
LL sec[25005][26];

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,N,M; scanf("%d",&T);
    int u,v;
    LL w;
    while(T--){
        scanf("%d %d",&N,&M);
        LL c=0, t=0;

        for(int i=1;i<=N;++i){
            LL mn = INF;
            pt[i].clear();
            for(int j=1;j<=M;++j){
                scanf("%lld", &w);
                if(w<mn){
                    mn = w;
                    pt[i].clear();
                    pt[i].push_back(j);
                }
                else if(w==mn) pt[i].push_back(j);
            }
            c+=mn;
        }
        
        int cnt = N*M+1;
        int ed = N*M+1, st = 1;
        
        G.init(cnt);

        for(int i=1;i<=N;++i){
            for(int j=1;j<M;++j){
                scanf("%lld", &sec[i][j]);
                u = (i-1)*M +j;
                v = u + 1;
                G.Addedge(u,v,sec[i][j]);
                G.Addedge(v,u,sec[i][j]);
            }
        }
        
        for(int i=1;i<N;++i){
            for(int j=0;j<pt[i].size();++j){
                int u = (i-1)*M+pt[i][j];
                int v = u+M;
                G.Addedge(u,v,0); 
            }
        }
        
        for(int i=0;i<pt[N].size();++i){
            int v = (N-1)*M+ pt[N][i];
            G.Addedge(v,ed,0);
        }
        
        G.dijkstra(st);

        printf("%lld %lld\n",c,G.d[ed]);
    }
    return 0;
}