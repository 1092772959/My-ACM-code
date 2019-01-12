#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn =1e4+5;
const int INF = 0x3f3f3f3f;
struct Edge{
    int to,next;
}E[2*maxn];
int n,head[maxn],tot;
int idx,size[maxn],fa[maxn],son[maxn],dep[maxn],top[maxn],id[maxn];
int e[maxn][3];

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
    int sum,mx;
}tree[maxn<<2];

void pushup(int rt) {
    tree[rt].mx = max(tree[lson].mx,tree[rson].mx);  
}

void build(int l,int r,int rt)
{
    if(l==r){
        tree[rt].mx = 0;
        if(l==1) tree[rt].mx = -INF;
        return;
    }
    int m =(l+r)>>1;
    build(Lson);
    build(Rson);
    pushup(rt);
}

void update(int p,int w,int l=1,int r=n,int rt=1)
{
    if(l==r){
        tree[rt].mx = w;
        return ;
    }
    int m =(l+r)>>1;
    if(p<=m) update(p,w,Lson);
    else update(p,w,Rson);
    pushup(rt);
}

int MAX(int L,int R,int l=1,int r=n,int rt=1)
{
    if(L<=l && R>=r)
        return tree[rt].mx;
    int ans = -INF;
    int m =(l+r)>>1;
    if(L<=m) ans = max(ans,MAX(L,R,Lson));
    if(R>m) ans = max(ans,MAX(L,R,Rson));
    return ans;
}

int QMAX(int u,int v)
{
    int ans = -INF;
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        ans = max(ans,MAX(id[top[u]],id[u]));
        u = fa[top[u]];
    }
    if(u==v) return ans;
    if(dep[u]>dep[v]) swap(u,v);
    return max(ans,MAX(id[son[u]],id[v]));
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T;scanf("%d",&T);
    int q,u,v,k,w;
    while(T--){
        scanf("%d",&n);
        init();
        for(int i=1;i<n;++i){
            scanf("%d%d%d",&u,&v,&e[i][2]);
            AddEdge(u,v);
            AddEdge(v,u);
            e[i][0] = u,e[i][1] =v;
        }
        dfs1(1);
        dfs2(1,1);
        build(1,n,1);
        for(int i=1;i<n;++i){
            if(dep[e[i][0]]>dep[e[i][1]]) swap(e[i][0],e[i][1]);
            update(id[e[i][1]],e[i][2]);
        }
        char op[10];
        while(scanf("%s",op)==1){
            if(op[0]=='D') break;
            else if(op[0]=='Q'){
                scanf("%d%d",&u,&v);
                printf("%d\n",QMAX(u,v));
            }
            else{
                scanf("%d%d",&k,&w);
                v = e[k][1];
                update(id[v],w);
            }
        }
    }
    return 0;
}