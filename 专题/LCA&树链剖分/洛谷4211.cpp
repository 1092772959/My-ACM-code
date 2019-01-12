#include<algorithm>
#include<stdio.h>
#include<cstring>
#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#define lson rt<<1
#define rson rt<<1|1
#define Lson l,m,lson
#define Rson m+1,r,rson
using namespace std;
typedef long long LL;
const LL maxn =1e5+5;
struct Edge{
    LL to,next;
}E[maxn<<1];
LL n,head[maxn],tot;
LL idx,size[maxn],fa[maxn],son[maxn],dep[maxn],top[maxn],id[maxn],rnk[maxn];
LL a[maxn];
void init()
{   
    idx=tot=0;
    memset(head,-1,sizeof(head));
    dep[1]=0,fa[1]=1,size[0]=0;
    memset(son,0,sizeof(son));
}
void AddEdge(LL u,LL v)
{
    E[tot] = (Edge){v,head[u]};
    head[u]=tot++;
}
void dfs1(LL u)
{
    size[u]=1;
    for(LL i=head[u];~i;i=E[i].next){
        LL v=E[i].to;
        if(v!=fa[u]){
            fa[v]=u;
            dep[v]=dep[u]+1;
            dfs1(v);
            size[u]+=size[v];
            if(size[son[u]]<size[v]) son[u]=v;
        }
    }
}

void dfs2(LL u,LL topu)
{
    top[u]= topu;
    id[u] = ++idx;
    rnk[idx] = u;           //建树用
    if(!son[u]) return;
    dfs2(son[u],top[u]);
    for(LL i=head[u];~i;i=E[i].next){
        LL v=E[i].to;
        if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
    }
}

struct STtree{
    LL sum,lazy;
}tree[maxn<<2];

void pushup(LL rt)
{
    tree[rt].sum  = tree[lson].sum + tree[rson].sum;
}

void pushdown(LL l,LL r,LL rt)
{
    if(tree[rt].lazy){
        LL add  =tree[rt].lazy;
        tree[lson].lazy += add;
        tree[rson].lazy += add;
        LL m = (l+r)>>1;
        tree[lson].sum += (m-l+1)*add;
        tree[rson].sum += (r-m)*add;
        tree[rt].lazy=0;
    }
}

void update(LL L,LL R,LL v,LL l=1,LL r=n,LL rt=1)
{
    if(L<=l && R>=r){
        tree[rt].lazy += v;
        tree[rt].sum  += (r-l+1)*v;
        return ;
    }
    pushdown(l,r,rt);
    LL m = (l+r)>>1;
    if(L<=m) update(L,R,v,Lson);
    if(R>m) update(L,R,v,Rson);
    pushup(rt);
}

LL query(LL L,LL R,LL l=1,LL r= n,LL rt=1)
{
    if(L<=l && R>=r) return tree[rt].sum;
    pushdown(l,r,rt);
    LL m = (l+r)>>1,ans=0;
    if(L<=m) ans+=query(L,R,Lson);
    if(R>m) ans+=query(L,R,Rson);
    //pushup(rt);
    return ans;
}

void UPDATE(LL u,LL v,LL w=1)
{
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        update(id[top[u]],id[u],w);
        u = fa[top[u]];
    }
    if(dep[u]>dep[v]) swap(u,v);
    update(id[u],id[v],w);
}

LL SUM(LL u,LL v)
{
    LL ans =0 ;
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        ans += query(id[top[u]],id[u]);
        u = fa[top[u]];
    }
    if(dep[u]>dep[v]) swap(u,v);
    ans += query(id[u],id[v]);
    return ans;
}

struct Qeury{
    LL pos,num,z;
    bool tag;
    bool operator < (const Qeury & rhs) const {return pos<rhs.pos;}
}que[maxn];
LL res[maxn];
const LL MOD = 201314;

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    LL q,u,v,tmp;
    scanf("%lld %lld",&n,&q);
    init();
    for(LL i=2;i<=n;++i){
        scanf("%lld",&u); u++;
        AddEdge(u,i);
        AddEdge(i,u);
    }
    dfs1(1);
    dfs2(1,1);
    LL l,r,z,cnt = 0;
    for(LL i=1;i<=q;++i){
        scanf("%lld %lld %lld",&l,&r,&z); l++,r++,z++;
        que[cnt++] = (Qeury){l-1,i,z,0};
        que[cnt++] = (Qeury){r,i,z,1};
    }
    sort(que,que+cnt);
    LL cur =1;
    for(LL i=0;i<cnt;++i){
        while(cur<=que[i].pos){
            UPDATE(1,cur++);
        }
        if(que[i].tag) res[que[i].num] += SUM(1,que[i].z);
        else res[que[i].num] -=SUM(1,que[i].z);
        res[que[i].num] += MOD;
        res[que[i].num] %=MOD;
    }
    for(LL i=1;i<=q;++i){
        printf("%lld\n",res[i]);
    }
    return 0;
}
