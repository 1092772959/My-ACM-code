#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long LL;
const int maxn =1e4+5;
const int INF = 0x3f3f3f3f;
struct Edge{
    int to,next;
}E[2*maxn];
int n,head[maxn],tot;
int idx,size[maxn],fa[maxn],son[maxn],dep[maxn],top[maxn],id[maxn];
int edge[maxn][3];
void init()
{   
    idx=tot=0;
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
    if(son[u]) dfs2(son[u],top[u]);
    for(int i=head[u];~i;i=E[i].next){
        int v=E[i].to;
        if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
    }
}
#define lson rt<<1
#define rson rt<<1|1
#define Lson l,m,lson
#define Rson m+1,r,rson
struct Node{
    int mx,mn,add;
}tree[maxn<<2];

inline void solve(int &a,int &b){
    int tmp = a;
    a = -b;
    b = -tmp;
}
void pushup(int rt) {
    tree[rt].mx = max(tree[lson].mx,tree[rson].mx);
    tree[rt].mn = min(tree[lson].mn,tree[rson].mn);
}
void pushdown(int l,int r,int rt)
{
    if(tree[rt].add){
        tree[lson].add ^= 1;
        tree[rson].add ^= 1;
        solve(tree[lson].mx,tree[lson].mn);
        solve(tree[rson].mx,tree[rson].mn);
        tree[rt].add=0;
    }
}

void build(int l,int r,int rt)
{
    tree[rt].add = 0;
    if(l==r){
        tree[rt].mx = tree[rt].mn = 0;
        return;
    }
    int m =(l+r)>>1;
    build(Lson);
    build(Rson);
    pushup(rt);
}

void update1(int p,int v,int l=1,int r=n,int rt=1)
{
    if(l==r){
        tree[rt].mx = tree[rt].mn = v;
        tree[rt].add = 0;
        return;
    }
    pushdown(l,r,rt);
    int m = (l+r)>>1;
    if(p<=m) update1(p,v,Lson);
    else update1(p,v,Rson);
    pushup(rt);
}

void update2(int L,int R,int l=1,int r=n,int rt=1)
{
    if(L<=l && R>=r){
        tree[rt].add ^=1;
        solve(tree[rt].mx,tree[rt].mn);
        return;
    }
    pushdown(l,r,rt);
    int m = (l+r)>>1;
    if(L<=m) update2(L,R,Lson);
    if(R>m) update2(L,R,Rson);
    pushup(rt);
}

int query(int L,int R,int l=1,int r=n,int rt=1)
{
    if(L<=l && R>=r)
        return tree[rt].mx;

    pushdown(l,r,rt);
    int m = (l+r)>>1;
    int ans = -INF;
    if(L<=m) ans = max(ans,query(L,R,Lson));
    if(R>m) ans = max(ans,query(L,R,Rson));
    pushup(rt);
    return ans;
}

//树剖
int find(int u,int v)
{
    int ans=  -INF;
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        ans = max(ans,query(id[top[u]],id[u],1,n,1));
        u = fa[top[u]];
    }
    if(u==v) return ans;
    if(dep[u]>dep[v]) swap(u,v);
    return max(ans,query(id[son[u]],id[v],1,n,1));    
}

void reverse(int u,int v)
{
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        update2(id[top[u]],id[u],1,n,1);
        u = fa[top[u]];
    }
    if(u==v) return;
    if(dep[u]>dep[v]) swap(u,v);
    update2(id[son[u]],id[v],1,n,1);
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T; scanf("%d",&T);
    while(T--){
        init();
        scanf("%d",&n);
        int u,v,w;
        for(int i=1;i<n;++i){
            scanf("%d%d%d",&u,&v,&edge[i][2]);
            AddEdge(u,v);
            AddEdge(v,u);
            edge[i][0] = u,edge[i][1] =v;
        }
        dfs1(1); 
        dfs2(1,1);
        build(1,n,1);
        for(int i=1;i<n;++i){                   
            if(dep[edge[i][1]]<dep[edge[i][0]]) swap(edge[i][0],edge[i][1]);
            v  =edge[i][1];
            update1(id[v],edge[i][2],1,n,1);
        }
        char op[10];
        while(scanf("%s",op)==1){
            if(op[0]=='D') break;
            else if(op[0]=='Q'){
                scanf("%d%d",&u,&v);
                printf("%d\n",find(u,v));
            }
            else if(op[0]=='N'){
                scanf("%d%d",&u,&v);
                reverse(u,v);
            }
            else{       //单点修改
                int k;
                scanf("%d%d",&k,&w);
                v = edge[k][1];
                update1(id[v],w);
            }
        }
    }
    return 0;
}