#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn =5e4+5;
struct Edge{
    int to,next;
}E[2*maxn];
int n,head[maxn],tot;
int idx,size[maxn],fa[maxn],son[maxn],dep[maxn],top[maxn],l[maxn],r[maxn];
int edge[maxn][3];
int bit[maxn];

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
    l[u] = ++idx;
    if(son[u]) dfs2(son[u],top[u]);
    for(int i=head[u];~i;i=E[i].next){
        int v=E[i].to;
        if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
    }
    r[u] = idx;
}

void add(int pos,int val){
    for(int i=pos;i<=n;i+= i&(-i)) bit[i]+=val;
}

inline int sum(int pos){
    int res=0;
    for(int i=pos;i;i-= i&(-i)) res+=bit[i];
    return res;
}

int lca(int u,int v){
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        u = fa[top[u]];
    }
    return dep[u]<dep[v] ? u:v;
}

int dist(int u,int v){
    return sum(l[u])+sum(l[v]) - 2*sum(l[lca(u,v)]);
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int q,s,op,u,v,w;
    while(scanf("%d%d",&n,&q)==2){
        init();
        memset(bit,0,sizeof(bit));
        for(int i=1;i<n;++i){
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v);
            AddEdge(v,u);
            edge[i][0] = u,edge[i][1] =v,edge[i][2] =w;
        }        
        dfs1(1);
        dfs2(1,1);
        for(int i=1;i<n;++i){
            if(dep[edge[i][0]]>dep[edge[i][1]]) swap(edge[i][0],edge[i][1]);
            v = edge[i][1];
            add(l[v],edge[i][2]);
            add(r[v]+1,-edge[i][2]);
        }

        while(q--){
            scanf("%d",&op);
            if(op==1){
                scanf("%d%d",&u,&v);
                printf("%d\n",dist(u,v));
            }
            else{
                int k;
                scanf("%d%d",&k,&w);
                v = edge[k][1];
                add(l[v],w-edge[k][2]);
                add(r[v]+1,-w+edge[k][2]);
                edge[k][2] =w;
            }
        }
    }
    return 0;
}