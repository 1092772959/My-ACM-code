#include<bits/stdc++.h>
using namespace std;
#define lson rt<<1
#define rson rt<<1|1
#define Lson l,m,lson
#define Rson m+1,r,rson
using namespace std;
typedef long long LL;
const int maxn=1e5+5;

int L[maxn],R[maxn],dfs_clock;
struct Edge{
    int v,next;
}edges[maxn<<1];
int head[maxn], tot;
LL W[maxn];
LL val[maxn];
struct TreeNode{
    LL num;
    LL tag;
}tree[maxn<<2];

void pushup(int rt){ tree[rt].num = tree[lson].num + tree[rson].num;}

void pushdown(int l,int r,int rt){
    if(tree[rt].tag!=0){
        tree[lson].tag +=tree[rt].tag;
        tree[rson].tag +=tree[rt].tag;
        int m = (l+r)>>1;
        tree[lson].num += (LL)(m-l+1)*tree[rt].tag;
        tree[rson].num += (LL)(r-m)*tree[rt].tag;
        tree[rt].tag =0;
    }
}

void build(int l,int r,int rt)
{
    tree[rt].tag =0;
    if(l==r){
        tree[rt].num = val[l];
        return;
    }
    int m = (l+r)>>1;
    build(Lson);
    build(Rson);
    pushup(rt);
}

void update(int L,int R,LL z,int l,int r,int rt)      //区间LR
{
    if(L<=l && R>=r){       //完全覆盖
        tree[rt].tag += z;
        tree[rt].num += z*(r-l+1);
        return;
    }
    pushdown(l,r,rt);
    int m = (l+r)>>1;
    if(L<=m) update(L,R,z,Lson);
    if(R>m) update(L,R,z,Rson);
    pushup(rt);
}

LL query(int L,int R,int l,int r,int rt)           //查询
{
    if(L<=l && R>=r) return tree[rt].num;
    pushdown(l,r,rt);
    int m= (l+r)>>1;
    LL ans = 0;
    if(L<=m) ans += query(L,R,Lson);
    if(R>m) ans += query(L,R,Rson);
    pushup(rt);
    return ans;
}

bool vis[maxn];
void init()
{
    dfs_clock = tot=0;
    memset(vis,0,sizeof(vis));
    memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v)
{
    edges[tot] = (Edge){v,head[u]};
    head[u] =tot++;
}

void dfs(int u)
{
    vis[u] = true; 
    L[u] = ++dfs_clock;
    val[dfs_clock] = W[u];
    for(int i=head[u];~i;i=edges[i].next){
        int v= edges[i].v;
        if(vis[v]) continue;
        dfs(v);
    }    
    R[u] =dfs_clock;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int N,Q,s,u,v,tmp;
    while(scanf("%d %d %lld",&N,&Q,&W[1])==3){
        if(N==0 &&Q==0 && W[1]==0) break;
        init();
        for(int i=2;i<=N;++i){
            scanf("%d %lld",&u,&W[i]);
            u++;
            AddEdge(u,i);
            AddEdge(i,u);
        }
        dfs(1);
        build(1,N,1);
        char op[20];
        int x; LL y,z;
        while(Q--){
            scanf("%s %d",op,&x);
            x++;
            scanf("%lld %lld ",&y,&z);
            if(op[0]=='e'){
                LL sum = query(L[x],L[x],1,N,1);
                if(sum<y) update(L[x],L[x],z,1,N,1);
            }
            else{
                LL sum = query(L[x],R[x],1,N,1);
                if(sum<(LL)y*(R[x]-L[x]+1)) update(L[x],R[x],z,1,N,1);
            }
        }
        for(int i=1;i<=N;++i){
            printf("%lld\n",query(L[i],L[i],1,N,1));   
        }
        printf("\n");
    }
    return 0;
}