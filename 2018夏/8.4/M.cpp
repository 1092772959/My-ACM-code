#include<bits/stdc++.h>
#define lson rt<<1
#define rson rt<<1|1
#define Lson l,m,lson
#define Rson m+1,r,rson
using namespace std;
typedef long long LL;
const int maxn = 4e5+5;
const LL INF = (1LL)<<60;
struct Edge{
    int to,next;
    LL w;
}edges[maxn<<4];
int head[maxn<<4],tot;
int ID[maxn<<2],rID[maxn<<2];
int id;

void init(int N)
{
    memset(head,-1,sizeof(head));
    tot=0;
    id = N;
}

void AddEdge(int u,int v,LL w){
    edges[tot] = (Edge){v,head[u],w};
    head[u] = tot++;
}

void build(int l,int r,int rt,bool flag)
{
    if(!flag) ID[rt] = ++id;
    else rID[rt] = ++id;
    if(!flag) {for(int i=l;i<=r;++i) AddEdge(ID[rt],i,0);}
    else {for(int i=l;i<=r;++i) AddEdge(i,rID[rt],0);}
    if(l==r) return;
    int m = (l+r)>>1;
    build(Lson,flag);
    build(Rson,flag);
}


void update(int L,int R,LL w,int u,int l,int r,int rt,bool flag)
{
    if(L<=l && R>=r){
        if(!flag)AddEdge(u,ID[rt],w);
        else AddEdge(rID[rt],u,w);
        return;
    }
    int m =(l+r)>>1;
    if(L<=m) update(L,R,w,u,Lson,flag);
    if(R>m) update(L,R,w,u,Rson,flag);
}

LL d[maxn<<4];
bool used[maxn<<4];
struct HeapNode{
    LL d;
    int u;
    bool operator <(const HeapNode & rhs) const {return d > rhs.d;}
};
void dijkstra(int s){   
        memset(used,0,sizeof(used));
        priority_queue<HeapNode> Q;
        for(int i=0;i<=id;++i)    d[i]=INF;
        d[s]=0;
        Q.push((HeapNode){0,s});
        while(!Q.empty()){
            HeapNode x =Q.top();Q.pop();
            int u =x.u;
            if(used[u])  continue;
            used[u]= true;
            for(int i=head[u];~i;i=edges[i].next){
                Edge & e = edges[i];
                if(d[e.to] > d[u] + e.w){
                    d[e.to] = d[u] +e.w;
                    Q.push((HeapNode){d[e.to],e.to});
                }
            }
        }
    }
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,N,M,q,s,u,v,op,L,R;
    LL w;
    while(scanf("%d%d%d",&N,&q,&s)==3){
        init(N);
        build(1,N,1,0);
        build(1,N,1,1);
        while(q--){
            scanf("%d",&op);
            if(op==1){
                scanf("%d%d%lld",&u,&v,&w);
                AddEdge(u,v,w);
            }
            else if(op==2){
                scanf("%d%d%d%lld",&u,&L,&R,&w);
                update(L,R,w,u,1,N,1,0);
            }
            else{
                scanf("%d%d%d%lld",&u,&L,&R,&w);
                update(L,R,w,u,1,N,1,1);
            }
        }
        dijkstra(s);
        for(int i=1;i<=N;++i)
            printf("%lld%c",d[i]==INF?-1:d[i],i==N?'\n':' ');
    }
    return 0;
}