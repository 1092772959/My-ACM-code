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
const int maxn =1e5+5;
struct Edge{
    int to,next;
}E[2*maxn];
int n,head[maxn],tot;
int cnt,idx,size[maxn],fa[maxn],son[maxn],dep[maxn],top[maxn],id[maxn],rnk[maxn];
int a[maxn];
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

struct Node{
    int sum,add,lc,rc;
}tree[maxn<<2];
int Lc,Rc;
void pushup(int rt){                //区间合并
    tree[rt].sum = tree[lson].sum + tree[rson].sum; 
    tree[rt].lc = tree[lson].lc;
    tree[rt].rc = tree[rson].rc;
    if(tree[lson].rc==tree[rson].lc)
        tree[rt].sum--;
}
void pushdown(int l,int r,int rt){
    if(tree[rt].add){
        tree[lson].add = tree[rson].add = 1;
        tree[lson].sum = tree[rson].sum = 1;
        tree[lson].lc = tree[lson].rc = tree[rt].lc;
        tree[rson].lc = tree[rson].rc = tree[rt].lc;
        tree[rt].add = 0;
    }
}

void build(int l,int r,int rt)
{
    tree[rt].add = 0;
    if(l==r){
        tree[rt].sum = 1;
        tree[rt].lc = tree[rt].rc = a[rnk[l]];
        return;
    }
    int m = (l+r)>>1;
    build(Lson);
    build(Rson);
    pushup(rt);
}

void update(int L,int R,int col,int l=1,int r=n,int rt=1){
    if(L<=l && R>=r){
        tree[rt].sum = tree[rt].add =1;
        tree[rt].lc = tree[rt].rc = col;
        return ;
    }
    pushdown(l,r,rt);
    int m =(l+r)>>1;
    if(L<=m) update(L,R,col,Lson);
    if(R>m) update(L,R,col,Rson);
    pushup(rt);
}

int query(int L,int R,int l=1,int r=n,int rt=1){        //单点
    if(L==l) Lc = tree[rt].lc;
    if(R==r) Rc = tree[rt].rc;
    if(L<=l && R>=r)
        return tree[rt].sum;
    pushdown(l,r,rt);
    int m = (l+r)>>1 , ans=0; bool left = false;
    if(L<=m) {
        ans+=query(L,R,Lson);
        left = true;
    }
    if(R>m){
        ans +=query(L,R,Rson);
        if(left && tree[lson].rc ==tree[rson].lc) ans--;
    } 
    pushup(rt);
    return ans;
}

void CHANGE(int u,int v,int col)
{
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        update(id[top[u]],id[u],col);
        u = fa[top[u]];    
    }
    if(dep[u]>dep[v]) swap(u,v);
    update(id[u],id[v],col);
}

int Qsum(int u,int v)
{
    int c1=-1,c2=-1, ans=0;     //记录上条链最左侧的颜色
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]){
            swap(u,v);
            swap(c1,c2);        
        }
        ans +=query(id[top[u]],id[u]);
        if(Rc == c1) ans--;
        c1 = Lc;
        u = fa[top[u]];
    }
    if(dep[u]>dep[v]){swap(u,v);swap(c1,c2);}
    ans += query(id[u],id[v]);
    if(Lc==c1) ans--;
    if(Rc==c2) ans--;
    return ans; 
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int m,q,u,v;
    char op[5];
    while(scanf("%d%d",&n,&m)==2){
        init();
        for(int i=1;i<=n;++i) scanf("%d",&a[i]);
        for(int i=1;i<n;++i){
            scanf("%d%d",&u,&v);
            AddEdge(u,v);
            AddEdge(v,u);
        }
        dfs1(1);
        dfs2(1,1);
        build(1,n,1);
        while(m--){
            scanf("%s",op);
            if(op[0]=='Q'){
                scanf("%d%d",&u,&v);
                printf("%d\n",Qsum(u,v));
            }
            else{
                int col;
                scanf("%d%d%d",&u,&v,&col);
                CHANGE(u,v,col);
            }
        }
    }
    return 0;
}