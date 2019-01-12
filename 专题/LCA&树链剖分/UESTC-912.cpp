#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
struct Edge{
    int to,next,id;
}edge[maxn<<1];
 
int n,a[maxn],head[maxn],dep[maxn<<1],cnt,pos[maxn],dfs_seq[maxn<<1],dfn,f[maxn<<1][20];
int W[maxn],L[maxn],R[maxn],dfs_clock,C[maxn],G[maxn];

inline void add(int u,int v,int id)
{
    edge[cnt].to=v;
    edge[cnt].next=head[u];
    edge[cnt].id=id;
    head[u]=cnt++;
}
 
inline int lowbit(int x){return (x)&(-x);}
 
void init()
{
    memset(head,-1,sizeof(head));
    memset(pos,-1,sizeof(pos));
    memset(C,0,sizeof(C));
    cnt=dfn=0;
    dfs_clock=0;
}
 
void dfs(int u,int deep)
{
    dfs_seq[dfn]=u,dep[dfn]=deep,pos[u]=dfn++;
    L[u]=++dfs_clock;
    for(int i=head[u];~i;i=edge[i].next){
        int v=edge[i].to;
        if(pos[v]==-1){
            G[edge[i].id]=v;                //important
            dfs(v,deep+1);
            dfs_seq[dfn]=u,dep[dfn++]=deep;
        }
    }
    R[u]=dfs_clock;
}
 
void init_RMQ(int n)
{
    for(int i=1;i<=n;++i) f[i][0]=i;
    for(int j=1;(1<<j)<=n;++j)
        for(int i=1;i+(1<<j)-1<=n;++i){
            if(dep[f[i][j-1]]<dep[f[i+(1<<(j-1))][j-1]]) f[i][j]=f[i][j-1];
            else f[i][j]=f[i+(1<<(j-1))][j-1];
        }
}
 
inline int RMQ(int L,int R)
{
    int k=0;
    while(1<<(k+1)<=R-L+1) ++k;
    if(dep[f[L][k]]<dep[f[R-(1<<k)+1][k]]) return f[L][k];
    return f[R-(1<<k)+1][k];
}
 
inline int lca(int u,int v)
{
    if(pos[u]>pos[v]) return dfs_seq[RMQ(pos[v],pos[u])];
    return dfs_seq[RMQ(pos[u],pos[v])];
}
 
inline void update(int i,int x)
{
    for(;i<=n;i+=lowbit(i)) C[i]+=x;
}
 
inline int sum(int i)
{
    int s=0;
    for(;i>0;i-=lowbit(i)) s+=C[i];
    return s;
}
 
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int i,u,v,k,q,w,op;
    while(~scanf("%d",&n)){
        init();
        for(i=1;i<n;++i){
            scanf("%d%d%d",&u,&v,&w);
            add(u,v,i);
            add(v,u,i);
            W[i]=w;
        }
        dfs(1,0);
        init_RMQ(dfn-1);
        for(i=1;i<n;++i){
            update(L[G[i]],W[i]);
            update(R[G[i]]+1,-W[i]);
        }
        scanf("%d",&q);
        while(q--){
            scanf("%d",&k);
            if(k==2){
                scanf("%d%d",&u,&w);
                update(L[G[u]],w-W[u]);
                update(R[G[u]]+1,-w+W[u]);
                W[u]=w;
            }
            else{
                scanf("%d%d",&u,&v);
                printf("%d\n",sum(L[u])+sum(L[v])-2*sum(L[lca(u,v)]));
            }
        }
    }
    return 0;
}
