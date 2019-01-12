#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#define lson rt<<1
#define rson rt<<1|1
#define Lson l,m,lson
#define Rson m+1,r,rson
using namespace std;
const int maxn =5e4+5;
struct Edge{
    int to,next;
}E[2*maxn];
int n,head[maxn],tot;
int idx,size[maxn],fa[maxn],son[maxn],dep[maxn],top[maxn],id[maxn],rnk[maxn];
int a[maxn];
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
    rnk[idx] = u;           //建树用
    if(!son[u]) return;
    dfs2(son[u],top[u]);
    for(int i=head[u];~i;i=E[i].next){
        int v=E[i].to;
        if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
    }
}

int bit[maxn];
void add(int pos,int val){
    for(int i=pos;i<=n;i+= i&(-i)) bit[i]+=val;
}

inline int sum(int pos){
    int res=0;
    for(int i=pos;i;i-= i&(-i)) res+=bit[i];
    return res;
}

void UPDATE2(int u,int v,int w)                 //树状数组维护
{
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        add(id[top[u]],w);
        add(id[u]+1,-w);
        u = fa[top[u]];
    }
    if(dep[u]>dep[v]) swap(u,v);
    add(id[u],w);
    add(id[v]+1,-w);
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int m,q,u,v;
    char op[5];
    while(scanf("%d%d%d",&n,&m,&q)==3){
        init();
        for(int i=1;i<=n;++i)  scanf("%d",&a[i]);
        while(m--){
            scanf("%d%d",&u,&v);
            AddEdge(u,v);
            AddEdge(v,u);
        }
        dfs1(1);
        dfs2(1,1);
        //build(1,n,1);
        memset(bit,0,sizeof(bit));
        for(int i=1;i<=n;++i){
            add(id[i],a[i]);
            add(id[i]+1,-a[i]);
        }
        while(q--){
            scanf("%s",op);
            if(op[0]=='Q'){
                scanf("%d",&u);
                printf("%d\n",sum(id[u]));
                //printf("%d\n",query(id[u],1,n,1));
            }
            else{
                int w;
                scanf("%d%d%d",&u,&v,&w);
                if(op[0]=='D') w = -w;
                UPDATE2(u,v,w);
                //UPDATE(u,v,w);
            }
        }
    }
    return 0;
}