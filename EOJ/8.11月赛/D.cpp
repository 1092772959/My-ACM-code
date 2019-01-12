#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#define lson rt<<1
#define rson rt<<1|1
#define Lson l,m,lson
#define Rson m+1,r,rson
typedef long long LL;
using namespace std;
const int maxn =2e5+5;
struct Edge{
    int to,next;
}E[2*maxn];
int n,head[maxn],tot;
int cnt,idx,size[maxn],fa[maxn],son[maxn],dep[maxn],top[maxn],id[maxn],rnk[maxn];
int e[maxn][2];
int W[maxn];
struct Node{
    int sum,add;
}tree[maxn<<2];
void init()
{   
    cnt=idx=tot=0;
    memset(head,-1,sizeof(head));
    dep[1]=0,fa[1]=1,size[0]=0;
    memset(son,0,sizeof(son));
}
void AddEdge(int u,int v)
{
    E[tot] = (Edge){v,head[u]};
    head[u]=tot++;
}
void dfs1(int u)
{
    size[u]=1;
    for(int i=head[u];~i;i=E[i].next){
        int v=E[i].to;
        if(v!=fa[u]){
            fa[v]=u;
            dep[v]=dep[u]+1;
            dfs1(v);
            size[u]+=size[v];
            if(size[son[u]]<size[v]) son[u]=v;
        }
    }
}

void dfs2(int u,int topu)
{
    top[u]= topu;
    id[u] = ++idx;
    rnk[idx] = u;
    if(!son[u]) return;
    dfs2(son[u],top[u]);
    for(int i=head[u];~i;i=E[i].next){
        int v=E[i].to;
        if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
    }
}

void pushup(int rt){  tree[rt].sum = tree[lson].sum + tree[rson].sum; }
void pushdown(int l,int r,int rt){
    if(tree[rt].add){
        tree[lson].add += tree[rt].add;
        tree[rson].add += tree[rt].add;
        int m = (l+r)>>1;
        tree[lson].sum += (m-l+1)*tree[rt].add;
        tree[rson].sum += (r-m)*tree[rt].add; 
        tree[rt].add =0;
    }
}

void build(int l,int r,int rt)
{
    tree[rt].add = 0;
    if(l==r){
        tree[rt].sum = 0;
        return;
    }
    int m = (l+r)>>1;
    build(Lson);
    build(Rson);
    pushup(rt);
}

void update(int L,int R,int v,int l=1,int r=n,int rt=1){
    if(L<=l && R>=r){
        tree[rt].sum +=(r-l+1)*v;
        tree[rt].add +=v;
        return ;
    }
    pushdown(l,r,rt);
    int m =(l+r)>>1;
    if(L<=m) update(L,R,v,Lson);
    if(R>m) update(L,R,v,Rson);
    pushup(rt);
}

int query(int p,int l=1,int r=n,int rt=1){        //单点
    if(l==r) return tree[rt].sum;
    pushdown(l,r,rt);
    int m = (l+r)>>1,ans=0;
    if(p<=m) ans= query(p,Lson);
    else ans =query(p,Rson);
    pushup(rt);
    return ans;
}

void UPDATE(int u,int v,int w=1)
{
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        update(id[top[u]],id[u],w);   
        u = fa[top[u]]; 
    }
    if(dep[u]>dep[v])swap(u,v);
    update(id[son[u]],id[v],w);
}

int vis[maxn];

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int m,q,u,v;
    char op[5];
    while(scanf("%d",&n)==1){
        init();
        for(int i=1;i<n;++i){
            scanf("%d%d%d",&u,&v,&W[i]);
            AddEdge(u,v);
            AddEdge(v,u);
            e[i][0] =u, e[i][1] = v;
        }
        dfs1(1);
        dfs2(1,1);
        build(1,n,1);
        for(int i=1;i<n;++i){
            if(dep[e[i][0]]>dep[e[i][1]]) swap(e[i][0],e[i][1]);
        }
        scanf("%d",&q);
        while(q--){
            scanf("%d%d",&u,&v);
            UPDATE(u,v);
        }
        sort(W+1,W+n);
        LL res=0;
        for(int i=1;i<n;++i){
            v = e[i][1];
            vis[i] = query(id[v]);
        }
        sort(vis+1,vis+n);
        for(int i=1;i<n;++i){
            res+= (LL)W[i]*vis[n-i];
        }
        printf("%lld\n",res);
    }
    return 0;
}